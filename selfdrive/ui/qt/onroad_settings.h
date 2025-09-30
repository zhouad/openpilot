#pragma once

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/params.h"
#include "selfdrive/ui/ui.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/qt/widgets/controls.h"

class OptionWidget;

class OnroadSettings : public QFrame {
  Q_OBJECT

public:
  explicit OnroadSettings(bool closeable = false, QWidget *parent = nullptr);
  void changeDynamicLaneProfile();
  void changeGapAdjustCruise();
  void changeAccelerationPersonality();
  void changeDynamicExperimentalControl();
  void changeSpeedLimitControl();

private:
  void showEvent(QShowEvent *event) override;
  void refresh();

  Params params;

  QVBoxLayout *options_layout;
  OptionWidget *dlp_widget;
  OptionWidget *gac_widget;
  OptionWidget *ap_widget;
  OptionWidget *dec_widget;
  OptionWidget *slc_widget;
  ParamWatcher *param_watcher;

signals:
  void closeSettings();
};

class OptionWidget : public QPushButton {
  Q_OBJECT

public:
  explicit OptionWidget(QWidget *parent = nullptr);
  void updateDynamicLaneProfile(QString param);
  void updateGapAdjustCruise(QString param);
  void updateAccelerationPersonality(QString param);
  void updateDynamicExperimentalControl(QString param);
  void updateSpeedLimitControl(QString param);

signals:
  void updateParam();

private:
  QLabel *icon, *title, *subtitle;

  Params params;
};
