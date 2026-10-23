#ifndef NN_OE_H
#define NN_OE_H

namespace nn { namespace oe {

// the SDK's application focus: 1 in focus, 2 out of focus, 3 in the background
enum FocusState {};
// the SDK's performance mode: -1 invalid, 0 normal (handheld), 1 boost (docked)
enum PerformanceMode {};

FocusState GetCurrentFocusState();
void SetPerformanceConfiguration(PerformanceMode mode, int config);
// the user-inactivity (auto-sleep) time extension: 1 extended, 2 extended unsafely
int GetUserInactivityDetectionTimeExtensionMode();
void SetUserInactivityDetectionTimeExtended(bool isExtended);
void SetUserInactivityDetectionTimeExtendedUnsafe(bool isExtended);
bool IsUserInactivityDetectionTimeExtended();

}}  // namespace nn::oe

#endif
