#pragma once

#include "selfdrive/ui/ui.h"
#include "selfdrive/ui/qt/widgets/controls.h"
#include "selfdrive/ui/qt/widgets/scrollview.h"

class AutoLaneChangeTimer : public SPOptionControl {
  Q_OBJECT

public:
  AutoLaneChangeTimer();

  void refresh();

signals:
  void toggleUpdated();

private:
  Params params;
};

class PauseLateralSpeed : public SPOptionControl {
  Q_OBJECT

public:
  PauseLateralSpeed();

  void refresh();

  signals:
    void ToggleUpdated();

private:
  Params params;
};


class LaneChangeSettings : public QWidget {
  Q_OBJECT

public:
  explicit LaneChangeSettings(QWidget* parent = nullptr);
  void showEvent(QShowEvent *event) override;

signals:
  void backPress();

public slots:
  void updateToggles();

private:
  Params params;
  std::map<std::string, ParamControl*> toggles;

  AutoLaneChangeTimer *auto_lane_change_timer;
  PauseLateralSpeed *pause_lateral_speed;
};
