#pragma once

#include "selfdrive/ui/qt/widgets/controls.h"

class OnroadScreenOff : public SPOptionControl {
  Q_OBJECT

public:
  OnroadScreenOff();

  void refresh();

private:
  Params params;
};

class OnroadScreenOffBrightness : public SPOptionControl {
  Q_OBJECT

public:
  OnroadScreenOffBrightness();

  void refresh();

private:
  Params params;
};

class MaxTimeOffroad : public SPOptionControl {
  Q_OBJECT

public:
  MaxTimeOffroad();

  void refresh();

private:
  Params params;
};

class BrightnessControl : public SPOptionControl {
  Q_OBJECT

public:
  BrightnessControl();

  void refresh();

private:
  Params params;
};

class DisplayPanel : public ListWidget {
  Q_OBJECT

public:
  explicit DisplayPanel(QWidget *parent = nullptr);
  void showEvent(QShowEvent *event) override;

public slots:
  void updateToggles();

private:
  Params params;
  std::map<std::string, ParamControl*> toggles;

  OnroadScreenOff *onroad_screen_off;
  OnroadScreenOffBrightness *onroad_screen_off_brightness;
};
