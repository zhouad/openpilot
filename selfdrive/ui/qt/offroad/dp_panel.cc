#include "selfdrive/ui/qt/offroad/dp_panel.h"

void DPPanel::add_toyota_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("Toyota / Lexus"),
      "",
    },
    {
      "dp_toyota_door_auto_lock_unlock",
      tr("Enable Door Auto Lock/Unlock"),
      "",
    },
  };

  QWidget *label = nullptr;
  bool has_toggle = false;

  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

void DPPanel::add_vag_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("VW / Audi / Skoda"),
      "",
    },
  };

  QWidget *label = nullptr;
  bool has_toggle = false;

  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

void DPPanel::add_mazda_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("Mazda"),
      "",
    },
  };

  QWidget *label = nullptr;
  bool has_toggle = false;

  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

void DPPanel::add_lateral_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("Lateral Ctrl"),
      "",
    },
    {
      "dp_lat_alka",
      tr("Enable Always-on Lane Keeping Assist"),
      "",
    },
    {
      "dp_lat_road_edge_detection",
      tr("Road Edge Detection"),
      tr("Block lane change assist when the system detects the road edge.")
    },
  };
  auto lca_speed_toggle = new ParamSpinBoxControl("dp_lat_lca_speed", tr("LCA Speed:"), tr("Off = Disable LCA\n1 mph ≈ 1.2 km/h"), "", 0, 100, 5, tr(" mph"), tr("Off"));
  lca_sec_toggle = new ParamDoubleSpinBoxControl("dp_lat_lca_auto_sec", QString::fromUtf8("　") + tr("Auto Lane Change after:"), tr("Off = Disable Auto Lane Change."), "", 0, 5.0, 0.5, tr(" sec"), tr("Off"));

  QWidget *label = nullptr;
  bool has_toggle = false;

  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      addItem(lca_speed_toggle);
      addItem(lca_sec_toggle);
      has_toggle = true;
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

void DPPanel::add_longitudinal_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("Longitudinal Ctrl"),
      "",
    },
    {
      "dp_lon_ext_radar",
      tr("Use External Radar"),
      tr("See https://github.com/eFiniLan/openpilot-ext-radar-addon for more information."),
    },
    {
      "dp_lon_acm",
      QString::fromUtf8("🚧 ") + tr("Enable Adaptive Coasting Mode (ACM)"),
      tr("Adaptive Coasting Mode (ACM) reduces braking to allow smoother coasting when appropriate."),
    },
    {
      "dp_lon_acm_downhill",
      QString::fromUtf8("　") + tr("Downhill Only"),
      tr("Limited to downhill driving."),
    },
  };

  QWidget *label = nullptr;
  bool has_toggle = false;

  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      continue;
    }
    if (param == "dp_lon_ext_radar") {
      if (!vehicle_has_radar_unavailable || !vehicle_has_long_ctrl) {
        continue;
      }
    }
    if ((param == "dp_lon_acm" || param == "dp_lon_acm_downhill") && !vehicle_has_long_ctrl) {
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

void DPPanel::add_ui_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("UI"),
      "",
    },
    {
      "dp_ui_rainbow",
      tr("Rainbow Driving Path"),
      tr("Why not?"),
    },
  };
  std::vector<QString> display_off_mode_texts{tr("Std."), tr("MAIN+"), tr("OP+"), tr("MAIN-"), tr("OP-")};
  ButtonParamControl* display_off_mode_setting = new ButtonParamControl("dp_ui_display_mode", tr("Display Mode"),
                                          tr("Std. - Stock behavior.\nMAIN+ - ACC MAIN on = Display ON.\nOP+ - OP enabled = Display ON.\nMAIN- - ACC MAIN on = Display OFF\nOP- - OP enabled = Display OFF."),
                                          "",
                                          display_off_mode_texts, 200);
  auto hide_hud = new ParamSpinBoxControl("dp_ui_hide_hud_speed_kph", tr("Hide HUD When Moves above:"), tr("To prevent screen burn-in, hide Speed, MAX Speed, and Steering/DM Icons when the car moves.\nOff = Stock Behavior\n1 km/h ≈ 0.6 mph"), "", 0, 120, 5, tr(" km/h"), tr("Off"));

  QWidget *label = nullptr;
  bool has_toggle = false;

  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      addItem(display_off_mode_setting);
      addItem(hide_hud);
      has_toggle = true;
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

void DPPanel::add_device_toggles() {
  std::vector<std::tuple<QString, QString, QString>> toggle_defs{
    {
      "",
      QString::fromUtf8("🐉 ") + tr("Device"),
      "",
    },
    {
      "dp_device_is_rhd",
      tr("Enable Right-Hand Drive Mode"),
      tr("Allow openpilot to obey right-hand traffic conventions on right driver seat."),
    },
    {
      "dp_device_monitoring_disabled",
      tr("Disable Driver Monitoring"),
      "",
    },
  };
  std::vector<QString> audible_alert_mode_texts{tr("Std."), tr("Warning"), tr("Off")};
  ButtonParamControl* audible_alert_mode_setting = new ButtonParamControl("dp_device_audible_alert_mode", tr("Audible Alert Mode"),
                                          tr("Warning - Only emits sound when there is a warning.\nOff - Does not emit any sound at all."),
                                          "",
                                          audible_alert_mode_texts);

  QWidget *label = nullptr;
  bool has_toggle = false;

  const bool disable_driver = getenv("DISABLE_DRIVER");
  for (auto &[param, title, desc] : toggle_defs) {
    if (param.isEmpty()) {
      label = new LabelControl(title, "");
      addItem(label);
      continue;
    }
    if ((param == "dp_device_is_rhd" || param == "dp_device_monitoring_disabled") && !disable_driver) {
      continue;
    }

    has_toggle = true;
    auto toggle = new ParamControl(param, title, desc, "", this);
    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);
    addItem(toggle);
    toggles[param.toStdString()] = toggle;
  }
  addItem(audible_alert_mode_setting);

  // If no toggles were added, hide the label
  if (!has_toggle && label) {
    label->hide();
  }
}

DPPanel::DPPanel(SettingsWindow *parent) : ListWidget(parent) {
  auto cp_bytes = params.get("CarParamsPersistent");
  if (!cp_bytes.empty()) {
    AlignedBuffer aligned_buf;
    capnp::FlatArrayMessageReader cmsg(aligned_buf.align(cp_bytes.data(), cp_bytes.size()));
    cereal::CarParams::Reader CP = cmsg.getRoot<cereal::CarParams>();
    brand = QString::fromStdString(CP.getBrand());
    vehicle_has_long_ctrl = hasLongitudinalControl(CP);
    vehicle_has_radar_unavailable = CP.getRadarUnavailable();
  }

  if (brand == "toyota") {
    add_toyota_toggles();
  } else if (brand == "volkswagen") {
    add_vag_toggles();
  } else if (brand == "mazda") {
    add_mazda_toggles();
  }
  add_lateral_toggles();
  add_longitudinal_toggles();
  add_ui_toggles();
  add_device_toggles();

  auto resetBtn = new ButtonControl(tr("Reset dragonpilot settings"), tr("RESET"));
  connect(resetBtn, &ButtonControl::clicked, [&]() {
    if (ConfirmationDialog::confirm(tr("Are you sure you want to reset all settings?"), tr("Reset"), this)) {
      params.putBool("dp_device_reset_conf", true);
    }
  });
  addItem(resetBtn);

  fs_watch = new ParamWatcher(this);
  QObject::connect(fs_watch, &ParamWatcher::paramChanged, [=](const QString &param_name, const QString &param_value) {
    updateStates();
  });

  connect(uiState(), &UIState::offroadTransition, [=](bool offroad) {
    is_onroad = !offroad;
    updateStates();
  });

  updateStates();
}

void DPPanel::showEvent(QShowEvent *event) {
  updateStates();
}

void DPPanel::updateStates() {
  // do fs_watch here
  fs_watch->addParam("dp_lat_lca_speed");
  if (vehicle_has_long_ctrl) fs_watch->addParam("dp_lon_acm");

  if (!isVisible()) {
    return;
  }

  // do state change logic here
  if (vehicle_has_long_ctrl) {
    bool dp_lon_acm = params.getBool("dp_lon_acm");
    if ( dp_lon_acm) {
      toggles["dp_lon_acm_downhill"]->show();
    } else {
      toggles["dp_lon_acm_downhill"]->hide();
    }
  }

  bool should_show = std::atoi(params.get("dp_lat_lca_speed").c_str()) > 0;
  lca_sec_toggle->setVisible(should_show);
}

void DPPanel::expandToggleDescription(const QString &param) {
  toggles[param.toStdString()]->showDescription();
}
