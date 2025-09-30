#include "common/params.h"

#include <dirent.h>
#include <sys/file.h>

#include <algorithm>
#include <cassert>
#include <csignal>
#include <unordered_map>

#include "common/queue.h"
#include "common/swaglog.h"
#include "common/util.h"
#include "system/hardware/hw.h"

namespace {

volatile sig_atomic_t params_do_exit = 0;
void params_sig_handler(int signal) {
  params_do_exit = 1;
}

int fsync_dir(const std::string &path) {
  int result = -1;
  int fd = HANDLE_EINTR(open(path.c_str(), O_RDONLY, 0755));
  if (fd >= 0) {
    result = fsync(fd);
    close(fd);
  }
  return result;
}

bool create_params_path(const std::string &param_path, const std::string &key_path) {
  // Make sure params path exists
  if (!util::file_exists(param_path) && !util::create_directories(param_path, 0775)) {
    return false;
  }

  // See if the symlink exists, otherwise create it
  if (!util::file_exists(key_path)) {
    // 1) Create temp folder
    // 2) Symlink it to temp link
    // 3) Move symlink to <params>/d

    std::string tmp_path = param_path + "/.tmp_XXXXXX";
    // this should be OK since mkdtemp just replaces characters in place
    char *tmp_dir = mkdtemp((char *)tmp_path.c_str());
    if (tmp_dir == NULL) {
      return false;
    }

    std::string link_path = std::string(tmp_dir) + ".link";
    if (symlink(tmp_dir, link_path.c_str()) != 0) {
      return false;
    }

    // don't return false if it has been created by other
    if (rename(link_path.c_str(), key_path.c_str()) != 0 && errno != EEXIST) {
      return false;
    }
  }

  return true;
}

std::string ensure_params_path(const std::string &prefix, const std::string &path = {}) {
  std::string params_path = path.empty() ? Path::params() : path;
  if (!create_params_path(params_path, params_path + prefix)) {
    throw std::runtime_error(util::string_format(
        "Failed to ensure params path, errno=%d, path=%s, param_prefix=%s",
        errno, params_path.c_str(), prefix.c_str()));
  }
  return params_path;
}

class FileLock {
public:
  FileLock(const std::string &fn) {
    fd_ = HANDLE_EINTR(open(fn.c_str(), O_CREAT, 0775));
    if (fd_ < 0 || HANDLE_EINTR(flock(fd_, LOCK_EX)) < 0) {
      LOGE("Failed to lock file %s, errno=%d", fn.c_str(), errno);
    }
  }
  ~FileLock() { close(fd_); }

private:
  int fd_ = -1;
};

std::unordered_map<std::string, uint32_t> keys = {
    {"AccessToken", CLEAR_ON_MANAGER_START | DONT_LOG},
    {"AlwaysOnDM", PERSISTENT},
    {"ApiCache_Device", PERSISTENT},
    {"ApiCache_NavDestinations", PERSISTENT},
    {"AssistNowToken", PERSISTENT},
    {"AthenadPid", PERSISTENT},
    {"AthenadUploadQueue", PERSISTENT},
    {"AthenadRecentlyViewedRoutes", PERSISTENT},
    {"BootCount", PERSISTENT},
    {"CalibrationParams", PERSISTENT},
    {"CameraDebugExpGain", CLEAR_ON_MANAGER_START},
    {"CameraDebugExpTime", CLEAR_ON_MANAGER_START},
    {"CarBatteryCapacity", PERSISTENT},
    {"CarParams", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"CarParamsCache", CLEAR_ON_MANAGER_START},
    {"CarParamsPersistent", PERSISTENT},
    {"CarParamsPrevRoute", PERSISTENT},
    {"CarVin", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"CompletedTrainingVersion", PERSISTENT},
    {"ControlsReady", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"CurrentBootlog", PERSISTENT},
    {"CurrentRoute", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"DisableLogging", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"DisablePowerDown", PERSISTENT | BACKUP},
    {"DisableUpdates", PERSISTENT | BACKUP},
    {"DisengageOnAccelerator", PERSISTENT | BACKUP},
    {"DmModelInitialized", CLEAR_ON_ONROAD_TRANSITION},
    {"DongleId", PERSISTENT},
    {"DoReboot", CLEAR_ON_MANAGER_START},
    {"DoShutdown", CLEAR_ON_MANAGER_START},
    {"DoUninstall", CLEAR_ON_MANAGER_START},
    {"ExperimentalLongitudinalEnabled", PERSISTENT | DEVELOPMENT_ONLY | BACKUP},
    {"ExperimentalMode", PERSISTENT | BACKUP},
    {"ExperimentalModeConfirmed", PERSISTENT | BACKUP},
    {"FirmwareQueryDone", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"ForcePowerDown", PERSISTENT},
    {"GitBranch", PERSISTENT},
    {"GitCommit", PERSISTENT},
    {"GitCommitDate", PERSISTENT},
    {"GitDiff", PERSISTENT},
    {"GithubSshKeys", PERSISTENT | BACKUP},
    {"GithubUsername", PERSISTENT | BACKUP},
    {"GitRemote", PERSISTENT},
    {"GsmApn", PERSISTENT | BACKUP},
    {"GsmMetered", PERSISTENT | BACKUP},
    {"GsmRoaming", PERSISTENT | BACKUP},
    {"HardwareSerial", PERSISTENT},
    {"HasAcceptedTerms", PERSISTENT},
    {"IMEI", PERSISTENT},
    {"InstallDate", PERSISTENT},
    {"IsDriverViewEnabled", CLEAR_ON_MANAGER_START},
    {"IsEngaged", PERSISTENT},
    {"IsLdwEnabled", PERSISTENT | BACKUP},
    {"IsMetric", PERSISTENT | BACKUP},
    {"IsOffroad", CLEAR_ON_MANAGER_START},
    {"IsOnroad", PERSISTENT},
    {"IsRhdDetected", PERSISTENT},
    {"IsReleaseBranch", CLEAR_ON_MANAGER_START},
    {"IsReleaseSPBranch", CLEAR_ON_MANAGER_START},
    {"IsTakingSnapshot", CLEAR_ON_MANAGER_START},
    {"IsTestedBranch", CLEAR_ON_MANAGER_START},
    {"JoystickDebugMode", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"LanguageSetting", PERSISTENT | BACKUP},
    {"LastAthenaPingTime", CLEAR_ON_MANAGER_START},
    {"LastGPSPosition", PERSISTENT},
    {"LastManagerExitReason", CLEAR_ON_MANAGER_START},
    {"LastOffroadStatusPacket", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"LastPowerDropDetected", CLEAR_ON_MANAGER_START},
    {"LastUpdateException", CLEAR_ON_MANAGER_START},
    {"LastUpdateTime", PERSISTENT},
    {"LiveParameters", PERSISTENT},
    {"LiveTorqueParameters", PERSISTENT | DONT_LOG},
    {"LongitudinalPersonality", PERSISTENT | BACKUP},
    {"NavDestination", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"NavDestinationWaypoints", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"NavPastDestinations", PERSISTENT},
    {"NavSettingLeftSide", PERSISTENT | BACKUP},
    {"NavSettingTime24h", PERSISTENT | BACKUP},
    {"NetworkMetered", PERSISTENT},
    {"ObdMultiplexingChanged", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"ObdMultiplexingEnabled", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"Offroad_BadNvme", CLEAR_ON_MANAGER_START},
    {"Offroad_CarUnrecognized", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"Offroad_ConnectivityNeeded", CLEAR_ON_MANAGER_START},
    {"Offroad_ConnectivityNeededPrompt", CLEAR_ON_MANAGER_START},
    {"Offroad_IsTakingSnapshot", CLEAR_ON_MANAGER_START},
    {"Offroad_NeosUpdate", CLEAR_ON_MANAGER_START},
    {"Offroad_NoFirmware", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"Offroad_Recalibration", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"Offroad_StorageMissing", CLEAR_ON_MANAGER_START},
    {"Offroad_TemperatureTooHigh", CLEAR_ON_MANAGER_START},
    {"Offroad_UnofficialHardware", CLEAR_ON_MANAGER_START},
    {"Offroad_UpdateFailed", CLEAR_ON_MANAGER_START},
    {"Offroad_OSMUpdateRequired", CLEAR_ON_MANAGER_START},
    {"OpenpilotEnabledToggle", PERSISTENT | BACKUP},
    {"PandaHeartbeatLost", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"PandaSomResetTriggered", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"PandaSignatures", CLEAR_ON_MANAGER_START},
    {"PrimeType", PERSISTENT},
    {"RecordFront", PERSISTENT | BACKUP},
    {"RecordFrontLock", PERSISTENT},  // for the internal fleet
    {"ReplayControlsState", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"RouteCount", PERSISTENT},
    {"SnoozeUpdate", CLEAR_ON_MANAGER_START | CLEAR_ON_OFFROAD_TRANSITION},
    {"SshEnabled", PERSISTENT | BACKUP},
    {"TermsVersion", PERSISTENT},
    {"Timezone", PERSISTENT},
    {"TrainingVersion", PERSISTENT},
    {"UbloxAvailable", PERSISTENT},
    {"UpdateAvailable", CLEAR_ON_MANAGER_START | CLEAR_ON_ONROAD_TRANSITION},
    {"UpdateFailedCount", CLEAR_ON_MANAGER_START},
    {"UpdaterAvailableBranches", PERSISTENT},
    {"UpdaterCurrentDescription", CLEAR_ON_MANAGER_START},
    {"UpdaterCurrentReleaseNotes", CLEAR_ON_MANAGER_START},
    {"UpdaterFetchAvailable", CLEAR_ON_MANAGER_START},
    {"UpdaterNewDescription", CLEAR_ON_MANAGER_START},
    {"UpdaterNewReleaseNotes", CLEAR_ON_MANAGER_START},
    {"UpdaterState", CLEAR_ON_MANAGER_START},
    {"UpdaterTargetBranch", CLEAR_ON_MANAGER_START},
    {"UpdaterLastFetchTime", PERSISTENT},
    {"Version", PERSISTENT},

    {"AccelPersonality", PERSISTENT | BACKUP},
    {"AccMadsCombo", PERSISTENT | BACKUP},
    {"AmapKey1", PERSISTENT | BACKUP},
    {"AmapKey2", PERSISTENT | BACKUP},
    {"ApiCache_DriveStats", PERSISTENT | BACKUP},
    {"AutoLaneChangeTimer", PERSISTENT | BACKUP},
    {"AutoLaneChangeBsmDelay", PERSISTENT | BACKUP},
    {"BelowSpeedPause", PERSISTENT | BACKUP},
    {"BrakeLights", PERSISTENT | BACKUP},
    {"BrightnessControl", PERSISTENT | BACKUP},
    {"ButtonAutoHide", PERSISTENT | BACKUP},
    {"CameraControl", PERSISTENT | BACKUP},
    {"CameraControlToggle", PERSISTENT | BACKUP},
    {"CameraOffset", PERSISTENT | BACKUP},
    {"CarModel", PERSISTENT | BACKUP},
    {"CarModelText", PERSISTENT | BACKUP},
    {"ChevronInfo", PERSISTENT | BACKUP},
    {"CustomBootScreen", PERSISTENT | BACKUP},
    {"CustomDrivingModel", PERSISTENT},
    {"CustomMapboxTokenPk", PERSISTENT | BACKUP},
    {"CustomMapboxTokenSk", PERSISTENT | BACKUP},
    {"CustomOffsets", PERSISTENT | BACKUP},
    {"CustomStockLong", PERSISTENT | BACKUP},
    {"CustomStockLongPlanner", PERSISTENT | BACKUP},
    {"CustomTorqueLateral", PERSISTENT | BACKUP},
    {"DevUIInfo", PERSISTENT | BACKUP},
    {"DisableOnroadUploads", PERSISTENT | BACKUP},
    {"DisengageLateralOnBrake", PERSISTENT | BACKUP},
    {"DrivingModelGeneration", PERSISTENT},
    {"DrivingModelMetadataText", PERSISTENT},
    {"DrivingModelName", PERSISTENT},
    {"DrivingModelText", PERSISTENT},
    {"DrivingModelUrl", PERSISTENT},
    {"DynamicExperimentalControl", PERSISTENT | BACKUP},
    {"DynamicLaneProfile", PERSISTENT | BACKUP},
    {"EnableAmap", PERSISTENT | BACKUP},
    {"EnableGmap", PERSISTENT | BACKUP},
    {"EnableMads", PERSISTENT | BACKUP},
    {"EnableSlc", PERSISTENT | BACKUP},
    {"EndToEndLongAlertLead", PERSISTENT | BACKUP},
    {"EndToEndLongAlertLight", PERSISTENT | BACKUP},
    {"EndToEndLongAlertUI", PERSISTENT | BACKUP},
    {"EndToEndLongToggle", PERSISTENT | BACKUP},
    {"EnforceTorqueLateral", PERSISTENT | BACKUP},
    {"EnhancedScc", PERSISTENT | BACKUP},
    {"FeatureStatus", PERSISTENT | BACKUP},
    {"FleetManagerPin", PERSISTENT},
    {"ForceOffroad", CLEAR_ON_MANAGER_START},
    {"GmapKey", PERSISTENT | BACKUP},
    {"HandsOnWheelMonitoring", PERSISTENT | BACKUP},
    {"HasAcceptedTermsSP", PERSISTENT},
    {"HideVEgoUi", PERSISTENT | BACKUP},
    {"HkgSmoothStop", PERSISTENT | BACKUP},
    {"HotspotOnBoot", PERSISTENT},
    {"HotspotOnBootConfirmed", PERSISTENT},
    {"LastCarModel", PERSISTENT | BACKUP},
    {"LastSpeedLimitSignTap", PERSISTENT},
    {"LastSunnylinkPingTime", CLEAR_ON_MANAGER_START},
    {"LiveTorque", PERSISTENT | BACKUP},
    {"LiveTorqueRelaxed", PERSISTENT | BACKUP},
    {"LkasToggle", PERSISTENT | BACKUP},
    {"MadsCruiseMain", PERSISTENT | BACKUP},
    {"MadsIconToggle", PERSISTENT | BACKUP},
    {"MapboxFullScreen", PERSISTENT | BACKUP},
    {"MapTargetVelocities", PERSISTENT},
    {"Map3DBuildings", PERSISTENT | BACKUP},
    {"MaxTimeOffroad", PERSISTENT | BACKUP},
    {"NavModelText", PERSISTENT | BACKUP},
    {"NavModelUrl", PERSISTENT | BACKUP},
    {"NNFF", PERSISTENT | BACKUP},
    {"NNFFCarModel", PERSISTENT | BACKUP},
    {"NNFFNoLateralJerk", PERSISTENT | BACKUP},
    {"OnroadScreenOff", PERSISTENT | BACKUP},
    {"OnroadScreenOffBrightness", PERSISTENT | BACKUP},
    {"OnroadScreenOffEvent", PERSISTENT | BACKUP},
    {"OnroadSettings", PERSISTENT | BACKUP},
    {"OsmLocal", PERSISTENT},
    {"OsmLocationName", PERSISTENT},
    {"OsmLocationTitle", PERSISTENT},
    {"OsmLocationUrl", PERSISTENT},
    {"OsmWayTest", PERSISTENT},
    {"OsmDownloadedDate", PERSISTENT},
    {"PathOffset", PERSISTENT | BACKUP},
    {"PauseLateralSpeed", PERSISTENT | BACKUP},
    {"QuietDrive", PERSISTENT | BACKUP},
    {"RoadEdge", PERSISTENT | BACKUP},
    {"ReverseAccChange", PERSISTENT | BACKUP},
    {"ReverseDmCam", PERSISTENT | BACKUP},
    {"ScreenRecorder", PERSISTENT | BACKUP},
    {"ShowDebugUI", PERSISTENT | BACKUP},
    {"SidebarTemperatureOptions", PERSISTENT | BACKUP},
    {"SpeedLimitControlPolicy", PERSISTENT | BACKUP},
    {"SpeedLimitEngageType", PERSISTENT | BACKUP},
    {"SpeedLimitValueOffset", PERSISTENT | BACKUP},
    {"SpeedLimitOffsetType", PERSISTENT | BACKUP},
    {"SpeedLimitWarningFlash", PERSISTENT | BACKUP},
    {"SpeedLimitWarningType", PERSISTENT | BACKUP},
    {"SpeedLimitWarningValueOffset", PERSISTENT | BACKUP},
    {"SpeedLimitWarningOffsetType", PERSISTENT | BACKUP},
    {"StandStillTimer", PERSISTENT | BACKUP},
    {"StockLongToyota", PERSISTENT | BACKUP},
    {"SubaruManualParkingBrakeSng", PERSISTENT | BACKUP},
    {"SunnylinkDongleId", PERSISTENT},
    {"SunnylinkEnabled", PERSISTENT},
    {"SunnylinkdPid", PERSISTENT},
    {"TermsVersionSunnypilot", PERSISTENT},
    {"TorqueDeadzoneDeg", PERSISTENT | BACKUP},
    {"TorqueFriction", PERSISTENT | BACKUP},
    {"TorqueLateralJerk", PERSISTENT | BACKUP},
    {"TorqueMaxLatAccel", PERSISTENT | BACKUP},
    {"TorquedOverride", PERSISTENT | BACKUP},
    {"ToyotaSnG", PERSISTENT | BACKUP},
    {"ToyotaTSS2Long", PERSISTENT | BACKUP},
    {"TrueVEgoUi", PERSISTENT | BACKUP},
    {"TurnSpeedControl", PERSISTENT | BACKUP},
    {"TurnVisionControl", PERSISTENT | BACKUP},
    {"DriverCameraHardwareMissing", PERSISTENT},
    {"VisionCurveLaneless", PERSISTENT | BACKUP},
    {"VwAccType", PERSISTENT | BACKUP},
    {"VwCCOnly", PERSISTENT | BACKUP},
    {"Offroad_ForceStatus", CLEAR_ON_MANAGER_START},
    {"Offroad_SupersededUpdate", PERSISTENT},
    {"TurnVisionCruise", PERSISTENT | BACKUP},
    {"SteerCruiseTune", PERSISTENT | BACKUP},
    {"StopDistance", PERSISTENT | BACKUP},
    {"ComfortBrake", PERSISTENT | BACKUP},
    {"MaxStopAccel", PERSISTENT | BACKUP},
    {"StartAccel", PERSISTENT | BACKUP},
    {"StopAccel", PERSISTENT | BACKUP},
    {"vEgoStopping", PERSISTENT | BACKUP},
    {"EnhanceTrafficLight", PERSISTENT | BACKUP},
    {"CruiseSmooth", PERSISTENT | BACKUP},
    {"UserAccelTable", PERSISTENT | BACKUP},
    {"AutoCruise", PERSISTENT | BACKUP},
    {"CruiseOnDist", PERSISTENT | BACKUP},
    {"DisEnhTrafficLightTurn", PERSISTENT | BACKUP},
    {"DisEnhanceTrafficRedLight", PERSISTENT | BACKUP},
    {"AccelSmooth", PERSISTENT | BACKUP},
    {"ConditionExperimentalMode", PERSISTENT | BACKUP},
    {"ExperimentalModeSpeed", PERSISTENT | BACKUP},
    {"ExperimentalModeAngle", PERSISTENT | BACKUP},
    {"ExperimentalModeAndSpeed", PERSISTENT | BACKUP},
    {"StartTurnLatA", PERSISTENT | BACKUP},
    {"TargetTurnLatA", PERSISTENT | BACKUP},
    {"TurnSteepNess", PERSISTENT | BACKUP},
    {"TurnLatAccel", PERSISTENT | BACKUP},
    {"EndTurnLatAccel", PERSISTENT | BACKUP},
    {"TurnMaxFactor", PERSISTENT | BACKUP},
    {"SteerTurnThr", PERSISTENT | BACKUP},
    {"SteerMaxFactor", PERSISTENT | BACKUP},
    {"DynamicPersonality", PERSISTENT | BACKUP},
    {"DisableDM", PERSISTENT | BACKUP},
    {"AChangeCost", PERSISTENT | BACKUP},
    {"AChangeCostStart", PERSISTENT | BACKUP},
    {"JEgoCost", PERSISTENT | BACKUP},
    {"NewLaneColor", PERSISTENT | BACKUP},
    {"MapdProcessEn", PERSISTENT | BACKUP},
    {"CruiseVoice", PERSISTENT | BACKUP},
    {"LongAdvCfg", PERSISTENT | BACKUP},
    {"CustomAccInc", PERSISTENT | BACKUP},
    {"ShortPressInc", PERSISTENT | BACKUP},
    {"LongPressInc", PERSISTENT | BACKUP},

    {"SunnylinkCache_Users", PERSISTENT},
    {"SunnylinkCache_Roles", PERSISTENT},

    // PFEIFER - MAPD {{
    {"MapdVersion", PERSISTENT},
    {"RoadName", CLEAR_ON_ONROAD_TRANSITION},
    {"MapSpeedLimit", CLEAR_ON_ONROAD_TRANSITION},
    {"MapAdvisorySpeedLimit", CLEAR_ON_ONROAD_TRANSITION},
    {"NextMapSpeedLimit", CLEAR_ON_ONROAD_TRANSITION},
    {"OSMDownloadBounds", PERSISTENT},
    {"OSMDownloadLocations", PERSISTENT},
    {"OsmDownloadedDate", PERSISTENT},
    {"OsmStateTitle", PERSISTENT},
    {"OsmStateName", PERSISTENT},
    {"OSMDownloadProgress", CLEAR_ON_MANAGER_START},
    {"OsmDbUpdatesCheck", CLEAR_ON_MANAGER_START},  // mapd database update happens with device ON, reset on boot

    //new
    {"ShowDebugLog",  PERSISTENT | BACKUP},
    {"CpSpdAndRoadLimit",  PERSISTENT | BACKUP},
    {"TurnToLaneChange",  PERSISTENT | BACKUP},
    {"SameSpiCamFilter",  PERSISTENT | BACKUP},
    {"ExtBlinkerCtrlTest",  PERSISTENT | BACKUP},
    {"LaneStabTime",  PERSISTENT | BACKUP},
    {"BsdDelayTime",  PERSISTENT | BACKUP},
    {"SideBsdDelayTime",  PERSISTENT | BACKUP},
    {"SideRelDistTime", PERSISTENT | BACKUP},
    {"SidevRelDistTime", PERSISTENT | BACKUP},
    {"SideRadarMinDist",  PERSISTENT | BACKUP},
    {"AutoTurnDistOffset",  PERSISTENT | BACKUP},
    {"AutoTurnInNotRoadEdge",  PERSISTENT | BACKUP},
    {"ContinuousLaneChange",  PERSISTENT | BACKUP},
    {"ContinuousLaneChangeCnt",  PERSISTENT | BACKUP},
    {"ContinuousLaneChangeInterval",  PERSISTENT | BACKUP},
    {"AutoTurnLeft",  PERSISTENT | BACKUP},
    {"AutoUpRoadLimit",  PERSISTENT | BACKUP},
    {"AutoUpHighwayRoadLimit",  PERSISTENT | BACKUP},
    {"AutoForkDistOffsetH",  PERSISTENT | BACKUP},
    {"AutoEnTurnNewLaneTimeH",  PERSISTENT | BACKUP},
    {"AutoDoForkDecalDistH",  PERSISTENT | BACKUP},
    {"AutoDoForkDecalDist",  PERSISTENT | BACKUP},
    //{"AutoDoForkCheckDistH",  PERSISTENT | BACKUP},
    {"AutoDoForkBlinkerDistH",  PERSISTENT | BACKUP},
    {"AutoDoForkNavDistH",  PERSISTENT | BACKUP},
    {"AutoForkDecalRateH",  PERSISTENT | BACKUP},
    {"AutoForkSpeedMinH",  PERSISTENT | BACKUP},
    {"AutoKeepForkSpeedH",  PERSISTENT | BACKUP},
    {"AutoForkDecalRate",  PERSISTENT | BACKUP},
    {"AutoForkSpeedMin",  PERSISTENT | BACKUP},
    {"AutoKeepForkSpeed",  PERSISTENT | BACKUP},
    {"AutoForkDistOffset",  PERSISTENT | BACKUP},
    {"AutoEnTurnNewLaneTime",  PERSISTENT | BACKUP},
    //{"AutoDoForkCheckDist",  PERSISTENT | BACKUP},
    {"AutoDoForkBlinkerDist",  PERSISTENT | BACKUP},
    {"AutoDoForkNavDist",  PERSISTENT | BACKUP},
    {"AutoUpRoadLimit40KMH",  PERSISTENT | BACKUP},
    {"AutoUpHighwayRoadLimit40KMH",  PERSISTENT | BACKUP},
    {"RoadType",  PERSISTENT | BACKUP},
    {"AutoCurveSpeedFactorH",  PERSISTENT | BACKUP},
    {"AutoCurveSpeedAggressivenessH",  PERSISTENT | BACKUP},
    {"NewLaneWidthDiff",  PERSISTENT | BACKUP},
    //new

    {"NetworkAddress", CLEAR_ON_MANAGER_START},
    {"AutoCurveSpeedFactor", PERSISTENT | BACKUP},
    {"AutoCurveSpeedAggressiveness", PERSISTENT | BACKUP},

    {"AutoNaviSpeedBumpSpeed", PERSISTENT | BACKUP},
    {"AutoNaviSpeedBumpTime", PERSISTENT | BACKUP},
    {"AutoNaviSpeedCtrlEnd", PERSISTENT | BACKUP},
    {"AutoNaviSpeedCtrlMode", PERSISTENT | BACKUP},
    {"AutoNaviSpeedSafetyFactor", PERSISTENT | BACKUP},
    {"AutoNaviSpeedDecelRate", PERSISTENT | BACKUP},
    {"AutoNaviCountDownMode", PERSISTENT | BACKUP},
    {"TurnSpeedControlMode", PERSISTENT | BACKUP},
    {"MapTurnSpeedFactor", PERSISTENT | BACKUP},
    {"AutoTurnControlSpeedTurn", PERSISTENT | BACKUP},
    {"AutoTurnMapChange", PERSISTENT | BACKUP},
    {"AutoTurnControl", PERSISTENT | BACKUP},
    {"AutoTurnControlTurnEnd", PERSISTENT | BACKUP},
    {"AutoCurveSpeedLowerLimit", PERSISTENT | BACKUP},
    {"AutoRoadSpeedLimitOffset", PERSISTENT | BACKUP},

    {"LaneChangeNeedTorque", PERSISTENT | BACKUP},
    {"LaneChangeDelay", PERSISTENT | BACKUP},
    {"LaneChangeBsd", PERSISTENT | BACKUP},
    {"DisableMinSteerSpeed", PERSISTENT | BACKUP},
    {"DisableRegister", PERSISTENT | BACKUP},

    {"UseLaneLineSpeed", PERSISTENT | BACKUP},
    {"UseLaneLineCurveSpeed", PERSISTENT | BACKUP},
    {"AdjustLaneOffset", PERSISTENT | BACKUP},
    {"PathOffset", PERSISTENT | BACKUP},
    {"LatMpcPathCost", PERSISTENT | BACKUP},
    {"LatMpcMotionCost", PERSISTENT | BACKUP},
    {"LatMpcAccelCost", PERSISTENT | BACKUP},
    {"LatMpcJerkCost", PERSISTENT | BACKUP},
    {"LatMpcSteeringRateCost", PERSISTENT | BACKUP},
    {"LatMpcInputOffset", PERSISTENT | BACKUP},
    // }} PFEIFER - MAPD
};

} // namespace


Params::Params(const std::string &path) {
  params_prefix = "/" + util::getenv("OPENPILOT_PREFIX", "d");
  params_path = ensure_params_path(params_prefix, path);
}

Params::~Params() {
  if (future.valid()) {
    future.wait();
  }
  assert(queue.empty());
}

std::vector<std::string> Params::allKeys() const {
  std::vector<std::string> ret;
  for (auto &p : keys) {
    ret.push_back(p.first);
  }
  return ret;
}

bool Params::checkKey(const std::string &key) {
  return keys.find(key) != keys.end();
}

ParamKeyType Params::getKeyType(const std::string &key) {
  return static_cast<ParamKeyType>(keys[key]);
}

int Params::put(const char* key, const char* value, size_t value_size) {
  // Information about safely and atomically writing a file: https://lwn.net/Articles/457667/
  // 1) Create temp file
  // 2) Write data to temp file
  // 3) fsync() the temp file
  // 4) rename the temp file to the real name
  // 5) fsync() the containing directory
  std::string tmp_path = params_path + "/.tmp_value_XXXXXX";
  int tmp_fd = mkstemp((char*)tmp_path.c_str());
  if (tmp_fd < 0) return -1;

  int result = -1;
  do {
    // Write value to temp.
    ssize_t bytes_written = HANDLE_EINTR(write(tmp_fd, value, value_size));
    if (bytes_written < 0 || (size_t)bytes_written != value_size) {
      result = -20;
      break;
    }

    // fsync to force persist the changes.
    if ((result = fsync(tmp_fd)) < 0) break;

    FileLock file_lock(params_path + "/.lock");

    // Move temp into place.
    if ((result = rename(tmp_path.c_str(), getParamPath(key).c_str())) < 0) break;

    // fsync parent directory
    result = fsync_dir(getParamPath());
  } while (false);

  close(tmp_fd);
  if (result != 0) {
    ::unlink(tmp_path.c_str());
  }
  return result;
}

int Params::remove(const std::string &key) {
  FileLock file_lock(params_path + "/.lock");
  int result = unlink(getParamPath(key).c_str());
  if (result != 0) {
    return result;
  }
  return fsync_dir(getParamPath());
}

std::string Params::get(const std::string &key, bool block) {
  if (!block) {
    return util::read_file(getParamPath(key));
  } else {
    // blocking read until successful
    params_do_exit = 0;
    void (*prev_handler_sigint)(int) = std::signal(SIGINT, params_sig_handler);
    void (*prev_handler_sigterm)(int) = std::signal(SIGTERM, params_sig_handler);

    std::string value;
    while (!params_do_exit) {
      if (value = util::read_file(getParamPath(key)); !value.empty()) {
        break;
      }
      util::sleep_for(100);  // 0.1 s
    }

    std::signal(SIGINT, prev_handler_sigint);
    std::signal(SIGTERM, prev_handler_sigterm);
    return value;
  }
}

std::map<std::string, std::string> Params::readAll() {
  FileLock file_lock(params_path + "/.lock");
  return util::read_files_in_dir(getParamPath());
}

void Params::clearAll(ParamKeyType key_type) {
  FileLock file_lock(params_path + "/.lock");

  // 1) delete params of key_type
  // 2) delete files that are not defined in the keys.
  if (DIR *d = opendir(getParamPath().c_str())) {
    struct dirent *de = NULL;
    while ((de = readdir(d))) {
      if (de->d_type != DT_DIR) {
        auto it = keys.find(de->d_name);
        if (it == keys.end() || (it->second & key_type)) {
          unlink(getParamPath(de->d_name).c_str());
        }
      }
    }
    closedir(d);
  }

  fsync_dir(getParamPath());
}

void Params::putNonBlocking(const std::string &key, const std::string &val) {
   queue.push(std::make_pair(key, val));
  // start thread on demand
  if (!future.valid() || future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
    future = std::async(std::launch::async, &Params::asyncWriteThread, this);
  }
}

void Params::asyncWriteThread() {
  // TODO: write the latest one if a key has multiple values in the queue.
  std::pair<std::string, std::string> p;
  while (queue.try_pop(p, 0)) {
    // Params::put is Thread-Safe
    put(p.first, p.second);
  }
}
