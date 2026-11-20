#ifndef NN_OE_H
#define NN_OE_H

#include "nn/settings.h"

namespace nn { namespace oe {

// the SDK's application focus: 1 in focus, 2 out of focus, 3 in the background
enum FocusState {};
// the SDK's performance mode: -1 invalid, 0 normal (handheld), 1 boost (docked)
enum PerformanceMode {};
// the SDK's operation mode: 0 handheld, 1 console
enum OperationMode {};
OperationMode GetOperationMode();
PerformanceMode GetPerformanceMode();
// the notifications ml::DevPerfNx's constructor turns on
void SetOperationModeChangedNotificationEnabled(bool enabled);
void SetPerformanceModeChangedNotificationEnabled(bool enabled);
void SetResumeNotificationEnabled(bool enabled);
void EnterExitRequestHandlingSection();

// the SDK's application environment setup (ml::DeviceNx::initializeSDK calls it first)
void Initialize();
FocusState GetCurrentFocusState();
void SetPerformanceConfiguration(PerformanceMode mode, int config);
// the user-inactivity (auto-sleep) time extension: 1 extended, 2 extended unsafely
int GetUserInactivityDetectionTimeExtensionMode();
void SetUserInactivityDetectionTimeExtended(bool isExtended);
void SetUserInactivityDetectionTimeExtendedUnsafe(bool isExtended);
bool IsUserInactivityDetectionTimeExtended();
// the language the application should use (ml::DevSettingNx::getLang maps it to a LangType)
settings::LanguageCode GetDesiredLanguage();
// whether the system's capture button may take screenshots
void EnableScreenShot();
void DisableScreenShot();

// the application's display version string (the SDK's)
struct DisplayVersion {
    char value[16];
};
void GetDisplayVersion(DisplayVersion* outValue);

}}  // namespace nn::oe

#endif
