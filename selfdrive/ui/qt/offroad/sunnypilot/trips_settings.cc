#include "selfdrive/ui/qt/offroad/sunnypilot/trips_settings.h"

TripsPanel::TripsPanel(QWidget* parent) : QFrame(parent) {
  QVBoxLayout* main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);

  // main content
  main_layout->addSpacing(25);
  center_layout = new QStackedLayout();

  driveStatsWidget = new DriveStats;
  driveStatsWidget->setStyleSheet(R"(
    QLabel[type="title"] { font-size: 51px; font-weight: 500; }
    QLabel[type="number"] { font-size: 78px; font-weight: 500; }
    QLabel[type="unit"] { font-size: 51px; font-weight: 300; color: #A0A0A0; }
  )");
  center_layout->addWidget(driveStatsWidget);

  main_layout->addLayout(center_layout, 1);

  setStyleSheet(R"(
    * {
      color: white;
    }
    TripsPanel > QLabel {
      font-size: 55px;
    }
  )");
}
