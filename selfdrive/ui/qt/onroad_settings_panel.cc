#include "selfdrive/ui/qt/onroad_settings_panel.h"

#include <QHBoxLayout>
#include <QWidget>

#include "selfdrive/ui/qt/onroad_settings.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/ui.h"

OnroadSettingsPanel::OnroadSettingsPanel(QWidget *parent) : QFrame(parent) {
  content_stack = new QStackedLayout(this);
  content_stack->setContentsMargins(0, 0, 0, 0);

  auto onroad_settings = new OnroadSettings(true, parent);
  QObject::connect(onroad_settings, &OnroadSettings::closeSettings, this, &OnroadSettings::hide);
  content_stack->addWidget(onroad_settings);
}

void OnroadSettingsPanel::toggleOnroadSettings() {
  if (isVisible()) {
    hide();
  } else {
    emit onroadSettingsPanelRequested();
    show();
  }
}
