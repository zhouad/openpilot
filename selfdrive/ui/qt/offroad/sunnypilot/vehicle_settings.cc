#include "selfdrive/ui/qt/offroad/sunnypilot/vehicle_settings.h"

VehiclePanel::VehiclePanel(QWidget *parent) : QWidget(parent) {
  main_layout = new QStackedLayout(this);
  home = new QWidget(this);
  QVBoxLayout* fcr_layout = new QVBoxLayout(home);
  fcr_layout->setContentsMargins(0, 20, 0, 20);

  set = QString::fromStdString(params.get("CarModelText"));
  setCarBtn = new QPushButton(((set == "=== Not Selected ===") || (set.length() == 0)) ? prompt_select : set);
  setCarBtn->setObjectName("setCarBtn");
  setCarBtn->setStyleSheet("margin-right: 30px;");
  connect(setCarBtn, &QPushButton::clicked, [=]() {
    QMap<QString, QString> cars = getCarNames();
    QString currentCar = QString::fromStdString(params.get("CarModel"));
    QString selection = MultiOptionDialog::getSelection(prompt_select, cars.keys(), cars.key(currentCar), this);
    if (!selection.isEmpty()) {
      params.put("CarModel", cars[selection].toStdString());
      params.put("CarModelText", selection.toStdString());
      ConfirmationDialog::alert(tr("Updating this setting takes effect when the car is powered off."), this);
    }
    updateToggles();
  });
  fcr_layout->addSpacing(10);
  fcr_layout->addWidget(setCarBtn, 0, Qt::AlignRight);
  fcr_layout->addSpacing(10);

  home_widget = new QWidget(this);
  QVBoxLayout* toggle_layout = new QVBoxLayout(home_widget);
  home_widget->setObjectName("homeWidget");

  ScrollView *scroller = new ScrollView(home_widget, this);
  scroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  fcr_layout->addWidget(scroller, 1);

  main_layout->addWidget(home);

  setStyleSheet(R"(
    #setCarBtn {
      border-radius: 50px;
      font-size: 50px;
      font-weight: 500;
      height:100px;
      padding: 0 35 0 35;
      color: #E4E4E4;
      background-color: #393939;
    }
    #setCarBtn:pressed {
      background-color: #4a4a4a;
    }
  )");

  auto toggle_panel = new SPVehiclesTogglesPanel(this);
  toggle_layout->addWidget(toggle_panel);
}

void VehiclePanel::showEvent(QShowEvent *event) {
  updateToggles();
}

void VehiclePanel::updateToggles() {
  if (!isVisible()) {
    return;
  }

  set = QString::fromStdString(params.get("CarModelText"));
  setCarBtn->setText(((set == "=== Not Selected ===") || (set.length() == 0)) ? prompt_select : set);
}

SPVehiclesTogglesPanel::SPVehiclesTogglesPanel(VehiclePanel *parent) : ListWidget(parent, false) {
  setSpacing(50);

  // Hyundai/Kia/Genesis
  addItem(new LabelControl(tr("Hyundai/Kia/Genesis")));
  auto hkgSmoothStop = new ParamControl(
    "HkgSmoothStop",
    tr("HKG CAN: Smoother Stopping Performance (Beta)"),
    tr("Smoother stopping behind a stopped car or desired stopping event. This is only applicable to HKG CAN platforms using openpilot longitudinal control."),
    "../assets/offroad/icon_blank.png"
  );
  hkgSmoothStop->setConfirmation(true, false);
  addItem(hkgSmoothStop);

  // Subaru
  addItem(new LabelControl(tr("Subaru")));
  auto subaruManualParkingBrakeSng = new ParamControl(
    "SubaruManualParkingBrakeSng",
    tr("Manual Parking Brake: Stop and Go (Beta)"),
    tr("Experimental feature to enable stop and go for Subaru Global models with manual handbrake. Models with electric parking brake should keep this disabled. Thanks to martinl for this implementation!"),
    "../assets/offroad/icon_blank.png"
  );
  subaruManualParkingBrakeSng->setConfirmation(true, false);
  addItem(subaruManualParkingBrakeSng);

  // Toyota/Lexus
  addItem(new LabelControl(tr("Toyota/Lexus")));
  stockLongToyota = new ParamControl(
    "StockLongToyota",
    tr("Enable Stock Toyota Longitudinal Control"),
    tr("sunnypilot will <b>not</b> take over control of gas and brakes. Stock Toyota longitudinal control will be used."),
    "../assets/offroad/icon_blank.png"
  );
  stockLongToyota->setConfirmation(true, false);
  addItem(stockLongToyota);

  auto lkasToggle = new ParamControl(
    "LkasToggle",
    tr("Allow M.A.D.S. toggling w/ LKAS Button (Beta)"),
    QString("%1<br>"
            "<h4>%2</h4><br>")
            .arg(tr("Allows M.A.D.S. engagement/disengagement with \"LKAS\" button from the steering wheel."))
            .arg(tr("Note: Enabling this toggle may have unexpected behavior with steering control. It is the driver's responsibility to observe their environment and make decisions accordingly.")),
    "../assets/offroad/icon_blank.png"
  );
  lkasToggle->setConfirmation(true, false);
  addItem(lkasToggle);

  auto toyotaTss2LongTune = new ParamControl(
    "ToyotaTSS2Long",
    tr("Toyota TSS2 Longitudinal: Custom Tuning"),
    tr("Smoother longitudinal performance for Toyota/Lexus TSS2/LSS2 cars. Big thanks to dragonpilot-community for this implementation."),
    "../assets/offroad/icon_blank.png"
  );
  toyotaTss2LongTune->setConfirmation(true, false);
  addItem(toyotaTss2LongTune);

  auto toyotaSngHack = new ParamControl(
    "ToyotaSnG",
    tr("Enable Toyota Stop and Go Hack"),
    tr("sunnypilot will allow some Toyota/Lexus cars to auto resume during stop and go traffic. This feature is only applicable to certain models. Use at your own risk."),
    "../assets/offroad/icon_blank.png"
  );
  toyotaSngHack->setConfirmation(true, false);
  addItem(toyotaSngHack);

  // Volkswagen
  addItem(new LabelControl(tr("Volkswagen")));
  auto volkswagenCCOnly = new ParamControl(
    "VwCCOnly",
    tr("Enable CC Only support"),
    tr("sunnypilot supports Volkswagen MQB CC only platforms with this toggle enabled. Only enable this toggle if your car does not have ACC from the factory."),
    "../assets/offroad/icon_blank.png"
  );
  volkswagenCCOnly->setConfirmation(true, false);
  addItem(volkswagenCCOnly);

  // trigger offroadTransition when going onroad/offroad
  connect(uiState(), &UIState::offroadTransition, [=](bool offroad) {
    hkgSmoothStop->setEnabled(offroad);
    toyotaTss2LongTune->setEnabled(offroad);
    toyotaSngHack->setEnabled(offroad);
    volkswagenCCOnly->setEnabled(offroad);
  });
}
