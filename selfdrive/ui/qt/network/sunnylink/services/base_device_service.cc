#include "base_device_service.h"

#include "common/swaglog.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/qt/offroad/sunnypilot/sunnylink_settings.h"

BaseDeviceService::BaseDeviceService(QObject* parent) : QObject(parent), initial_request(nullptr), repeater(nullptr) {
  param_watcher = new ParamWatcher(this);
  connect(param_watcher, &ParamWatcher::paramChanged, [=](const QString &param_name, const QString &param_value) {
    paramsRefresh();
  });
  param_watcher->addParam("SunnylinkEnabled");
}

void BaseDeviceService::paramsRefresh() {
}

void BaseDeviceService::loadDeviceData(const QString &url, bool poll) {
  if (!is_sunnylink_enabled()) {
    LOGW("Sunnylink is not enabled, refusing to load data.");
    return;
  }

  auto sl_dongle_id = getSunnylinkDongleId();
  if (!sl_dongle_id.has_value())
    return;

  QString fullUrl = SUNNYLINK_BASE_URL + "/device/" + *sl_dongle_id + url;
  if (poll && !isCurrentyPolling()) {
    LOGD("Polling %s", qPrintable(fullUrl));
    LOGD("Cache key: SunnylinkCache_%s", qPrintable(QString(getCacheKey())));
    repeater = new RequestRepeater(this, fullUrl, "SunnylinkCache_" + getCacheKey(), 60, false, true);
    connect(repeater, &RequestRepeater::requestDone, this, &BaseDeviceService::handleResponse);
  } else if(isCurrentyPolling()){
    repeater->ForceUpdate();
  } else {
    LOGD("Sending one-time %s", qPrintable(fullUrl));
    initial_request = new HttpRequest(this, true, 10000, true);
    connect(initial_request, &HttpRequest::requestDone, this, &BaseDeviceService::handleResponse);
  }
}

void BaseDeviceService::stopPolling() {
  if (repeater != nullptr) {
    repeater->deleteLater();
    repeater = nullptr;
  }
}
