#include "classes/ml/DevFileTh.h"
#include "classes/ml/DevGraphNx.h"
#include "classes/ml/DevPad.h"
#include "classes/ml/DevPerfNx.h"
#include "classes/ml/DevSettingNx.h"
#include "classes/ml/DevTouch.h"
#include "classes/ml/DevTouchNx.h"
#include "classes/ml/DeviceNx.h"

namespace ml {

void DevPad::wkUpdate() {}

void DevTouch::updateDevice() {}

void DevGraphNx::resetSizeSys(short, short) {}

void DevGraphNx::wkUpdate() {}

void DevGraphNx::wkRender() {}

void DevPerfNx::resumeApplication() {}

void DevTouchNx::releaseDevice() {}

DevSettingNx::~DevSettingNx() {}

void DevSettingNx::finalize() {}

void DeviceNx::createDevicePort(const char*) {}

void DevFileTh::wkUpdate() {}

void DevFileTh::icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE) {}

}  // namespace ml
