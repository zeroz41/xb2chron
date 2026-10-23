// monolib_mm's own build: mm_lib's headers cite their paths from monolib_mm's build folder
#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/DevBase.h"
#include "classes/ml/DevClock.h"
#include "classes/ml/DevClockNx.h"
#include "classes/ml/DevFileTh.h"
#include "classes/ml/DevGraphNx.h"
#include "classes/ml/DevPad.h"
#include "classes/ml/DevPerf.h"
#include "classes/ml/DevPerfNx.h"
#include "classes/ml/DevSetting.h"
#include "classes/ml/DevSettingNx.h"
#include "classes/ml/DevTouch.h"
#include "classes/ml/DevTouchNx.h"
#include "classes/ml/DeviceNx.h"
#include "classes/ml/WorkCpu.h"
#include "nn/oe.h"
#include "nn/os.h"

namespace ml {

bool DevClock::getClockNow(long& clock) {
    DevClock* dev = get();
    if (dev != nullptr && dev->isLoggedIn()) {
        dev->getClockNowSys(clock);
        return true;
    }
    return false;
}

bool DevClock::getTimeNow(float& time, const long& clock) {
    DevClock* dev = get();
    if (dev != nullptr && dev->isLoggedIn()) {
        time = dev->getSecNowSys(clock);
        return true;
    }
    return false;
}

float DevClock::getClock2Sec(const long& clock) {
    DevClock* dev = get();
    if (dev != nullptr) {
        return dev->getClock2SecSys(clock);
    }
    return 0.0f;
}

bool DevClock::wkStandbyLogin() {
    return WorkObj::wkStandbyLogin();
}

bool DevClock::wkStandbyLogout() {
    if (m_childNum == 0 && mm::mtl::PtrSingleton<DevFileTh>::get() == nullptr) {
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

float DevClockNx::getPowerOnTimeSys() const {
    return getClock2SecSys(nn::os::GetSystemTick().GetInt64Value() - m_powerOnClock);
}

void DevClockNx::getClockNowSys(long& clock) const {
    clock = nn::os::GetSystemTick().GetInt64Value();
}

// the original converts and drops the result: clock is left as it was
void DevClockNx::getSec2ClockSys(long& clock, float sec) const {
    nn::os::ConvertToTick(nn::TimeSpan::FromSeconds(static_cast<long>(sec)));
}

float DevClockNx::getSecNowSys(const long& clock) const {
    return getClock2SecSys(nn::os::GetSystemTick().GetInt64Value() - clock);
}

float DevClockNx::getClock2SecSys(const long& clock) const {
    return static_cast<float>(nn::os::ConvertToTimeSpan(nn::os::Tick(clock)).GetNanoSeconds()) / 1000000000.0f;
}

DevPerf::~DevPerf() {
    if (m_impl != nullptr) {
        delete m_impl;
        m_impl = nullptr;
    }
}

bool DevPerf::wkStandbyLogin() {
    return WorkObj::wkStandbyLogin();
}

bool DevPerf::wkStandbyLogout() {
    return WorkObj::wkStandbyLogout();
}

void DevPerf::wkUpdate() {
    DevPerf* dev = get();
    if (dev != nullptr) {
        dev->m_impl->update();
    }
}

DevPerfOperationMode DevPerf::getOperationMode() {
    DevPerf* dev = get();
    if (dev != nullptr) {
        return dev->m_impl->getOperationMode();
    }
    return DevPerfOperationMode(1);
}

void DevPerf::setPerfConfig(DevPerfMode mode, DevPerfConfig config) {
    DevPerf* dev = get();
    if (dev != nullptr) {
        dev->m_impl->setPerfConfig(mode, config);
    }
}

DevPerfNx::~DevPerfNx() {
    WorkCpu::removeSystemInfoListener(this);
}

void DevPerfNx::update() {
    int state = nn::oe::GetCurrentFocusState();
    if (state >= 1 && state <= 3) {
        m_focusState = state;
    } else {
        m_focusState = 0;
    }
}

void DevPerfNx::changeOperationMode(DevPerfOperationMode mode) {
    m_operationMode = mode;
}

void DevPerfNx::changePerformanceMode(DevPerfMode mode) {
    m_performanceMode = mode;
}

DevPerfOperationMode DevPerfNx::getOperationMode() const {
    return m_operationMode;
}

DevPerfMode DevPerfNx::getPerformanceMode() const {
    return m_performanceMode;
}

int DevPerfNx::getFocusState() const {
    return m_focusState;
}

void DevPerfNx::setPerfConfig(DevPerfMode mode, DevPerfConfig config) {
    int nnConfig;
    if (config == 2) {
        nnConfig = 0x10001;
    } else if (config == 1) {
        nnConfig = 0x20004;
    } else {
        nnConfig = 0x20003;
    }
    int nnMode;
    if (mode == 1) {
        nnMode = 0;
    } else if (mode == 2) {
        nnMode = 1;
    } else {
        nnMode = -1;
    }
    nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode(nnMode), nnConfig);
    m_perfConfig[mode] = config;
}

DevPerfConfig DevPerfNx::getPerfConfig(DevPerfMode mode) const {
    return m_perfConfig[mode];
}

DevSetting::~DevSetting() {
    if (m_impl != nullptr) {
        delete m_impl;
        m_impl = nullptr;
    }
}

LangType DevSetting::getLang() {
    DevSetting* dev = get();
    if (dev != nullptr) {
        return dev->m_impl->getLang();
    }
    return m_defaultLang;
}

void DevSetting::setAutoSleepExtended(SleepExtendType type) {
    DevSetting* dev = get();
    if (dev != nullptr) {
        dev->m_impl->setAutoSleepExtended(type);
    }
}

void DevPad::wkUpdate() {}

void DevTouch::updateDevice() {}

void DevGraphNx::resetSizeSys(short, short) {}

void DevGraphNx::wkUpdate() {}

void DevGraphNx::wkRender() {}

void DevPerfNx::resumeApplication() {}

void DevTouchNx::releaseDevice() {}

DevSettingNx::~DevSettingNx() {}

void DevSettingNx::finalize() {}

void DevSettingNx::setAutoSleepExtended(SleepExtendType type) {
    if (type == 1) {
        nn::oe::SetUserInactivityDetectionTimeExtended(true);
    } else if (type == 2) {
        nn::oe::SetUserInactivityDetectionTimeExtendedUnsafe(true);
    } else if (type == 0) {
        int mode = nn::oe::GetUserInactivityDetectionTimeExtensionMode();
        if (mode == 1) {
            nn::oe::SetUserInactivityDetectionTimeExtended(false);
        } else if (mode == 2) {
            nn::oe::SetUserInactivityDetectionTimeExtendedUnsafe(false);
        }
    }
}

bool DevSettingNx::isAutoSleepExtended() const {
    return nn::oe::IsUserInactivityDetectionTimeExtended();
}

void DeviceNx::createDevicePort(const char*) {}

void DevFileTh::wkUpdate() {}

void DevFileTh::icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE) {}

}  // namespace ml
