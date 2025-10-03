"""
Copyright (c) 2025, Rick Lan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, and/or sublicense, 
for non-commercial purposes only, subject to the following conditions:

- The above copyright notice and this permission notice shall be included in 
  all copies or substantial portions of the Software.
- Commercial use (e.g. use in a product, service, or activity intended to 
  generate revenue) is prohibited without explicit written permission from 
  the copyright holder.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

#!/usr/bin/env python3

import argparse
# import asyncio
# import json
import os
import logging
from datetime import datetime
from urllib.parse import quote
# import socket
# import sys

from aiohttp import web

from openpilot.common.params import Params
from openpilot.system.hardware import PC


# --- File Browser Settings ---
DEFAULT_DIR = os.path.realpath(os.path.join(os.path.dirname(__file__), '..') if PC else '/data/media/0/realdata')
WEB_DIST_PATH = os.path.join(os.path.dirname(__file__), "..", "web", "dist")

def get_safe_path(requested_path):
    """Ensures the requested path is within DEFAULT_DIR, preventing arbitrary file access"""
    combined_path = os.path.join(DEFAULT_DIR, requested_path.lstrip('/'))
    safe_path = os.path.realpath(combined_path)
    if os.path.commonpath((safe_path, DEFAULT_DIR)) == DEFAULT_DIR:
        return safe_path
    return None

async def list_files_api(request):
    """API endpoint to list files and folders"""
    try:
        path_param = request.query.get('path', '/')
        safe_path = get_safe_path(path_param)
        if not safe_path or not os.path.isdir(safe_path):
            return web.json_response({'error': 'Invalid or Not Found Path'}, status=404)
        items = []
        for entry in os.listdir(safe_path):
            full_path = os.path.join(safe_path, entry)
            try:
                stat = os.stat(full_path)
                is_dir = os.path.isdir(full_path)
                items.append({
                    'name': entry,
                    'is_dir': is_dir,
                    'mtime': datetime.fromtimestamp(stat.st_mtime).strftime('%Y-%m-%d %H:%M'),
                    'size': stat.st_size if not is_dir else 0
                })
            except FileNotFoundError:
                continue
        directories = sorted([item for item in items if item['is_dir']], key=lambda x: x['mtime'], reverse=True)
        files = sorted([item for item in items if not item['is_dir']], key=lambda x: x['mtime'], reverse=True)
        items = directories + files
        relative_path = os.path.relpath(safe_path, DEFAULT_DIR)
        if relative_path == '.':
            relative_path = ''
        return web.json_response({'path': relative_path, 'files': items})
    except Exception as e:
        return web.json_response({'error': str(e)}, status=500)

async def serve_player_api(request):
    """API endpoint to serve the HLS player page"""
    file_path = request.query.get('file')
    if not file_path:
        return web.Response(text="File parameter is required.", status=400)

    player_html_path = os.path.join(WEB_DIST_PATH, 'pages', 'player.html')
    try:
        with open(player_html_path, 'r') as f:
            html_template = f.read()
    except FileNotFoundError:
        return web.Response(text="Player HTML not found.", status=500)

    encoded_path = quote(file_path)
    html = html_template.replace('{{FILE_PATH}}', encoded_path)
    return web.Response(text=html, content_type='text/html')

async def serve_manifest_api(request):
    """API endpoint to dynamically generate m3u8 playlist"""
    file_path = request.query.get('file').lstrip('/')
    if not file_path:
        return web.Response(text="File parameter is required.", status=400)
    encoded_path = quote(file_path)
    manifest = f"""#EXTM3U\n#EXT-X-VERSION:3\n#EXT-X-TARGETDURATION:60\n#EXT-X-PLAYLIST-TYPE:VOD\n#EXTINF:60.0,\n/media/{encoded_path}\n#EXT-X-ENDLIST\n"""
    return web.Response(text=manifest, content_type='application/vnd.apple.mpegurl')

async def save_settings_api(request):
    """API endpoint to receive and save settings"""
    try:
        data = await request.json()
        logging.getLogger("web_ui").info(f"Received settings to save: {data}")
        return web.json_response({'status': 'success', 'message': 'Settings saved successfully!'})
    except Exception as e:
        logging.getLogger("web_ui").error(f"Error saving settings: {e}")
        return web.json_response({'status': 'error', 'message': str(e)}, status=500)

async def init_api(request):
    """API endpoint to provide initial data to the client."""
    try:
        params = Params()
        return web.json_response({
            'is_metric': params.get_bool("IsMetric"), 
            'dp_dev_dashy': int(params.get("dp_dev_dashy") or 0)
        })
    except Exception as e:
        logging.getLogger("web_ui").error(f"Error fetching initial data: {e}")
        return web.json_response({'error': f"Error fetching initial data: {e}"}, status=500)

async def on_startup(app):
    logging.getLogger("web_ui").info("Web UI application starting up...")

async def on_cleanup(app):
    logging.getLogger("web_ui").info("Web UI application shutting down...")

# --- CORS Middleware ---
@web.middleware
async def cors_middleware(request, handler):
    response = await handler(request)
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, DELETE, OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
    return response

async def handle_cors_preflight(request):
    if request.method == 'OPTIONS':
        headers = {
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'GET, POST, PUT, DELETE, OPTIONS',
            'Access-Control-Allow-Headers': 'Content-Type, Authorization',
            'Access-Control-Max-Age': '86400',
        }
        return web.Response(status=200, headers=headers)
    return await request.app['handler'](request)

def setup_aiohttp_app(host: str, port: int, debug: bool):
    logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    logging.getLogger("web_ui").setLevel(logging.DEBUG if debug else logging.INFO)

    app = web.Application(middlewares=[cors_middleware])
    app['port'] = port

    # Register API endpoints
    app.router.add_get("/api/init", init_api)
    app.router.add_get("/api/files", list_files_api)
    app.router.add_get("/api/play", serve_player_api)
    app.router.add_get("/api/manifest.m3u8", serve_manifest_api)
    # app.router.add_post("/api/settings", save_settings_api)

    # Static files
    app.router.add_static('/media', path=DEFAULT_DIR, name='media', show_index=False, follow_symlinks=False)
    app.router.add_static('/download', path=DEFAULT_DIR, name='download', show_index=False, follow_symlinks=False)
    app.router.add_get("/", lambda r: web.FileResponse(os.path.join(WEB_DIST_PATH, "index.html")))
    app.router.add_static("/", path=WEB_DIST_PATH)

    app.on_startup.append(on_startup)
    app.on_cleanup.append(on_cleanup)

    # Add CORS preflight handler
    app.router.add_route('OPTIONS', '/{tail:.*}', handle_cors_preflight)

    return app

def main():
    # rick - may need "sudo ufw allow 5088" to allow port access
    parser = argparse.ArgumentParser(description="Dashy Server")
    parser.add_argument("--host", type=str, default="0.0.0.0", help="Host to listen on")
    parser.add_argument("--port", type=int, default=5088, help="Port to listen on")
    parser.add_argument("--debug", action="store_true", help="Enable debug mode")
    args = parser.parse_args()

    app = setup_aiohttp_app(args.host, args.port, args.debug)
    web.run_app(app, host=args.host, port=args.port)

if __name__ == "__main__":
    main()
