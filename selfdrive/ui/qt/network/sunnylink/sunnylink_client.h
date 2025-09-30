#ifndef SUNNYLINK_CLIENT_H
#define SUNNYLINK_CLIENT_H

#include <QObject>

#include "selfdrive/ui/qt/network/sunnylink/services/role_service.h"
#include "selfdrive/ui/qt/network/sunnylink/services/user_service.h"

class SunnylinkClient : public QObject {
  Q_OBJECT

public:
  explicit SunnylinkClient(QObject* parent);
  RoleService* role_service;
  UserService* user_service;
};

#endif
