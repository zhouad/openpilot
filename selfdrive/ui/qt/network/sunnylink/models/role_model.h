#ifndef ROLE_MODEL_H
#define ROLE_MODEL_H

#include <QJsonObject>

enum class RoleType {
  ReadOnly,
  Sponsor,
  Admin
};

// haha, a role model xD
class RoleModel {
protected:
  QJsonObject m_raw_json_object;
  
public:
  RoleType roleType;
  
  explicit RoleModel(const RoleType &roleType) : roleType(roleType) {
    m_raw_json_object = toJson();
  }
  explicit RoleModel(const QJsonObject &json) : RoleModel(stringToRoleType(json["role_type"].toString())) {
    m_raw_json_object = json;
  }

  [[nodiscard]] QJsonObject toJson() const {
    QJsonObject json;
    json["role_type"] = roleTypeToString(roleType);
    return json;
  }

  static RoleType stringToRoleType(const QString &roleTypeString) {
    if (roleTypeString == "ReadOnly") {
      return RoleType::ReadOnly;
    } else if (roleTypeString == "Sponsor") {
      return RoleType::Sponsor;
    } else {  // Default to Admin
      return RoleType::Admin;
    }
  }

  static QString roleTypeToString(const RoleType &roleType) {
    switch (roleType) {
      case RoleType::ReadOnly:
        return "ReadOnly";
      case RoleType::Sponsor:
        return "Sponsor";
      default:  // RoleType::Admin
        return "Admin";
    }
  }
  
  template <typename T, typename = typename std::enable_if<std::is_base_of<RoleModel, T>::value>::type>
  T as() const {
    return T(m_raw_json_object);
  }
};

#endif
