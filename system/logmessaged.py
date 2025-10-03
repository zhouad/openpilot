#!/usr/bin/env python3
import zmq
from typing import NoReturn

import cereal.messaging as messaging
from openpilot.common.logging_extra import SwagLogFileFormatter
from openpilot.system.hardware.hw import Paths
from openpilot.common.swaglog import get_file_handler
from openpilot.common.params import Params


def main() -> NoReturn:
  log_handler = get_file_handler()
  log_handler.setFormatter(SwagLogFileFormatter(None))
  log_level = 20  # logging.INFO

  ctx = zmq.Context.instance()
  sock = ctx.socket(zmq.PULL)
  sock.bind(Paths.swaglog_ipc())

  # and we publish them
  log_message_sock = messaging.pub_sock('logMessage')
  error_log_message_sock = messaging.pub_sock('errorLogMessage')

  try:
    while True:
      dat = b''.join(sock.recv_multipart())
      level = dat[0]
      raw_bytes = dat[1:]

      try:
        record = dat[1:].decode("utf-8", errors="replace")
      except Exception as e:
        print(f"decode error: {e}, skipping log")
        print(f"Raw bytes (hex): {raw_bytes.hex()[:200]}...")  # 앞부분만 출력
        Params().put_bool("CarrotException", True)
        continue

      if level >= log_level:
        log_handler.emit(record)

      if len(record) > 2*1024*1024:
        print("WARNING: log too big to publish", len(record))
        print(record[:100])
        continue

      # then we publish them
      msg = messaging.new_message(None, valid=True, logMessage=record)
      log_message_sock.send(msg.to_bytes())

      if level >= 40:  # logging.ERROR
        msg = messaging.new_message(None, valid=True, errorLogMessage=record)
        error_log_message_sock.send(msg.to_bytes())
  finally:
    sock.close()
    ctx.term()

    # can hit this if interrupted during a rollover
    try:
      log_handler.close()
    except ValueError:
      pass

if __name__ == "__main__":
  main()
