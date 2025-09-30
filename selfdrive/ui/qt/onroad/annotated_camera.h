#pragma once

#include <QVBoxLayout>
#include <memory>
#include <QTimer>

#include "selfdrive/ui/qt/onroad/buttons.h"
#include "selfdrive/ui/qt/widgets/cameraview.h"

#ifdef ENABLE_DASHCAM
#include "selfdrive/ui/qt/screenrecorder/screenrecorder.h"
#endif
#include "selfdrive/ui/qt/widgets/turn_info_drawer.h"

const int subsign_img_size = 35;
const int blinker_size = 120;

class AnnotatedCameraWidget : public CameraWidget {
  Q_OBJECT

public:
  explicit AnnotatedCameraWidget(VisionStreamType type, QWidget* parent = 0);
  void updateState(const UIState &s);

  MapSettingsButton *map_settings_btn;
  OnroadSettingsButton *onroad_settings_btn;

private:
  TurnInfoDrawer turn_info;   // 新增成员

  void drawText(QPainter &p, int x, int y, const QString &text, int alpha = 255);
  void drawCenteredText(QPainter &p, int x, int y, const QString &text, QColor color);
  void drawVisionTurnControllerUI(QPainter &p, int x, int y, int size, const QColor &color, const QString &speed,
                                  const QString &vtc_source, int alpha);
  void drawCircle(QPainter &p, int x, int y, int r, QBrush bg);
  void drawSpeedSign(QPainter &p, QRect rc, const QString &speed, const QString &sub_text, int subtext_size,
                     bool is_map_sourced, bool is_active);
  void drawTrunSpeedSign(QPainter &p, QRect rc, const QString &speed, const QString &sub_text, int curv_sign,
                         bool is_active);

  void drawColoredText(QPainter &p, int x, int y, const QString &text, QColor color);
  void drawStandstillTimer(QPainter &p, int x, int y);

  // ############################## DEV UI START ##############################
  void drawRightDevUi(QPainter &p, int x, int y);
  int drawDevUiElementRight(QPainter &p, int x, int y, const QString &value, const QString &label, const QString &units, QColor &color);
  int drawNewDevUiElement(QPainter &p, int x, int y, const QString &value, const QString &label, const QString &units, QColor &color);
  void drawNewDevUi2(QPainter &p, int x, int y);
  void drawCenteredLeftText(QPainter &p, int x, int y, const QString &text1, QColor color1, const QString &text2, const QString &text3, QColor color2);
  struct UiElement {
    QString value;
    QString label;
    QString units;
    QColor color;

    UiElement(const QString &value, const QString &label, const QString &units, const QColor &color = QColor(255, 255, 255, 255))
      : value(value), label(label), units(units), color(color) {}
  };

  UiElement getDRel();
  UiElement getVRel();
  UiElement getSteeringAngleDeg();
  UiElement getActualLateralAccel();
  UiElement getSteeringAngleDesiredDeg();
  UiElement getMemoryUsagePercent();

  UiElement getAEgo();
  UiElement getVEgoLead();
  UiElement getFrictionCoefficientFiltered();
  UiElement getLatAccelFactorFiltered();
  UiElement getSteeringTorqueEps();
  UiElement getBearingDeg();
  UiElement getAltitude();

  // ############################## DEV UI END ##############################

  void drawE2eStatus(QPainter &p, int x, int y, int w, int h, int e2e_long_status);

  void drawLeftTurnSignal(QPainter &painter, int x, int y, int circle_size, int state);
  void drawRightTurnSignal(QPainter &painter, int x, int y, int circle_size, int state);
  int blinkerPulse(int frame);
  void updateButtonsLayout();

  void drawFeatureStatusText(QPainter &p, int x, int y);
  void speedLimitSignPulse(int frame);
  void speedLimitWarning(QPainter &p, QRect sign_rect, const int sign_margin);
  void mousePressEvent(QMouseEvent* e) override;
  void drawRoadNameText(QPainter &p, int x, int y, const QString &text, QColor color);

  QVBoxLayout *main_layout;
  ExperimentalButton *experimental_btn;
  QPixmap dm_img;
  float speed;
  QString speedUnit;
  float setSpeed;
  float speedLimit;
  bool is_cruise_set = false;
  bool is_metric = false;
  bool dmActive = false;
  bool hideBottomIcons = false;
  bool rightHandDM = false;
  float dm_fade_state = 1.0;
  bool has_us_speed_limit = false;
  bool has_eu_speed_limit = false;
  bool v_ego_cluster_seen = false;
  int status = STATUS_DISENGAGED;
  std::unique_ptr<PubMaster> pm;

  int skip_frame_count = 0;
  bool wide_cam_requested = false;

  Params params;
  QHBoxLayout *buttons_layout;
  QPixmap map_img;
  QPixmap left_img;
  QPixmap right_img;
  bool left_blindspot = false;
  bool right_blindspot = false;
  bool left_front_blind = false;
  bool right_front_blind = false;
  std::unique_ptr<PubMaster> e2e_state;

  bool steerOverride = false;
  bool gasOverride = false;
  bool latActive = false;
  bool madsEnabled = false;

  bool brakeLights;

  bool standStillTimer;
  bool standStill;
  float standstillElapsedTime;

  bool showVTC = false;
  QString vtcSpeed;
  QColor vtcColor;
  QString vtcSource;

  bool showDebugUI = false;

  QString roadName = "";

  bool showSpeedLimit = false;
  float speedLimitSLC;
  float speedLimitSLCOffset;
  float speedLimitWarningOffset;
  QString slcSubText;
  float slcSubTextSize = 0.0;
  bool overSpeedLimit;
  bool mapSourcedSpeedLimit = false;
  bool slcActive = false;

  bool showTurnSpeedLimit = false;
  QString turnSpeedLimit;
  QString tscSubText;
  bool tscActive = false;
  int curveSign = 0;

  bool hideVEgoUi;

  bool splitPanelVisible;

  // ############################## DEV UI START ##############################
  bool lead_status;
  float lead_d_rel = 0;
  float lead_v_rel = 0;
  QString lateralState;
  float angleSteers = 0;
  float steerAngleDesired = 0;
  float curvature;
  float roll;
  int memoryUsagePercent;
  int devUiInfo;
  float gpsAccuracy;
  float altitude;
  float vEgo;
  float aEgo;
  float steeringTorqueEps;
  float bearingAccuracyDeg;
  float bearingDeg;
  bool torquedUseParams;
  float latAccelFactorFiltered;
  float frictionCoefficientFiltered;
  bool liveValid;
  // ############################## DEV UI END ##############################

  float btnPerc;

  bool reversing;

  int e2eState;
  int e2eStatus;

  bool left_blinker, right_blinker, lane_change_edge_block;
  int blinker_frame;
  int blinker_state = 0;
  int ext_blinker = 0;
  int ext_state = 0;

  cereal::LongitudinalPlanSP::SpeedLimitControlState slcState;
  int longitudinalPersonality;
  int dynamicLaneProfile;
  QString mpcMode;

  int speed_limit_frame;
  bool slcShowSign = true;
  QPixmap plus_arrow_up_img;
  QPixmap minus_arrow_down_img;
  QRect sl_sign_rect;
  int rn_offset = 0;
  bool e2eLongAlertUi, dynamicExperimentalControlToggle, speedLimitControlToggle, speedLimitWarningFlash;
  cereal::CarParams::Reader car_params;
  bool cruiseStateEnabled;
  bool experimentalMode;

  bool featureStatusToggle;

  int drivingModelGen;

protected:
  void paintGL() override;
  void initializeGL() override;
  void showEvent(QShowEvent *event) override;
  void updateFrameMat() override;
  void drawLaneLines(QPainter &painter, const UIState *s);
  void drawLead(QPainter &painter, const cereal::RadarState::LeadData::Reader &lead_data, const QPointF &vd, int num, float radar_d_rel, float v_ego, float radar_v_rel, int chevron_data, bool isMetric);
  void drawHud(QPainter &p);
  void drawDriverState(QPainter &painter, const UIState *s);
  inline QColor redColor(int alpha = 255) { return QColor(201, 34, 49, alpha); }
  inline QColor whiteColor(int alpha = 255) { return QColor(255, 255, 255, alpha); }
  inline QColor blackColor(int alpha = 255) { return QColor(0, 0, 0, alpha); }

  void paintEvent(QPaintEvent *event) override;
  void rocketFuel(QPainter &p);

  double prev_draw_t = 0;
  FirstOrderFilter fps_filter;

// neokii
#ifdef ENABLE_DASHCAM
private:
  ScreenRecoder* recorder;
  std::shared_ptr<QTimer> record_timer;

  private slots:
    void offroadTransition(bool offroad);
#endif
};
