#pragma once

#include "selfdrive/ui/ui.h"
#include "selfdrive/ui/qt/widgets/controls.h"
#include "selfdrive/ui/qt/widgets/scrollview.h"
#include "selfdrive/ui/qt/util.h"

class SpeedLimitWarningValueOffset : public SPOptionControl {
  Q_OBJECT

public:
  SpeedLimitWarningValueOffset();

  void refresh();

private:
  Params params;
};

class SpeedLimitWarningSettings : public QWidget {
  Q_OBJECT

public:
  explicit SpeedLimitWarningSettings(QWidget* parent = nullptr);
  void showEvent(QShowEvent *event) override;
  static const std::vector<QString> speed_limit_warning_descriptions;

signals:
  void backPress();

public slots:
  void updateToggles();

private:
  Params params;
  std::map<std::string, ParamControl*> toggles;

  SpeedLimitWarningValueOffset *slwvo;
  ButtonParamControl *speed_limit_warning_offset_settings;
  ParamControl *speed_limit_warning_flash;
  ButtonParamControl *speed_limit_warning_settings;
  ParamWatcher *param_watcher;

  QString speedLimitWarningDescriptionBuilder(QString param, std::vector<QString> descriptions) {
    std::string key = param.toStdString();
    int value = atoi(params.get(key).c_str());
    QString description = "";

    for (int i = 0; i < descriptions.size(); i++) {
      if (i == value) {
        description += "<b>" + descriptions[i] + "</b>";
      } else {
        description += descriptions[i];
      }

      if ((i >= 0) && (i < descriptions.size() - 1)) {
        description += "<br>";
      }
    }

    return description;
  }
};

inline const std::vector<QString> SpeedLimitWarningSettings::speed_limit_warning_descriptions{
  tr("Off: When the cruising speed is faster than the speed limit plus the offset, there will be no warning."),
  tr("Display: The speed on the speed limit sign turns red to alert the driver when the cruising speed is faster than the speed limit plus the offset."),
  tr("Chime: The speed on the speed limit sign turns red and chimes to alert the driver when the cruising speed is faster than the speed limit plus the offset."),
};
