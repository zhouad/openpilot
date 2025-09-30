#ifndef ROLESERVICE_H
#define ROLESERVICE_H

#include "selfdrive/ui/qt/network/sunnylink/services/base_device_service.h"
#include "selfdrive/ui/qt/network/sunnylink/models/role_model.h"

class RoleService : public BaseDeviceService {
  Q_OBJECT

public:
  explicit RoleService(QObject* parent = nullptr);
  void load();
  void startPolling();
  [[nodiscard]] QString getCacheKey() const final { return "Roles"; };

signals:
  void rolesReady(const std::vector<RoleModel> &roles);

protected:
  void handleResponse(const QString&response, bool success) override;

private:
  QString url = "/roles";
};

#endif
