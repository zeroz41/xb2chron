// monolib_mm's own build: mm_lib's headers cite their paths from monolib_mm's build folder
#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/DevBase.h"
#include "classes/ml/DevClock.h"
#include "classes/ml/DevClockNx.h"
#include "classes/ml/DevFileTh.h"
#include "classes/ml/DevGraphNx.h"
#include "classes/ml/DevGraphQue.h"
#include "classes/ml/DevPad.h"
#include "classes/ml/DevPadNx.h"
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
    if (m_child.size() == 0 && mm::mtl::PtrSingleton<DevFileTh>::get() == nullptr) {
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

int DevPad::getPadMax() {
    return 11;
}

bool DevPad::isConnectPad(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->isLocalConnect(pad);
    }
    return false;
}

int DevPad::getStylePad(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->getLocalStyle(pad);
    }
    return 0;
}

int DevPad::getUserSelectPadID() {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->getLocalUserSelectPadID();
    }
    return 0;
}

unsigned int DevPad::getBtn(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->m_btn[pad];
    }
    return 0;
}

unsigned int DevPad::getDown(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->m_down[pad];
    }
    return 0;
}

unsigned int DevPad::getUp(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->m_up[pad];
    }
    return 0;
}

unsigned int DevPad::getDbl(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        return dev->m_dbl[pad];
    }
    return 0;
}

float DevPad::getALX(int pad, bool deadZone) {
    DevPad* dev = get();
    if (dev == nullptr) {
        return 0.0f;
    }
    float value = dev->getLocalALX(pad);
    float zone = get() != nullptr ? get()->m_deadZone : 0.0f;
    if (deadZone && value < zone && value > -zone) {
        return 0.0f;
    }
    return value;
}

float DevPad::getALY(int pad, bool deadZone) {
    DevPad* dev = get();
    if (dev == nullptr) {
        return 0.0f;
    }
    float value = dev->getLocalALY(pad);
    float zone = get() != nullptr ? get()->m_deadZone : 0.0f;
    if (deadZone && value < zone && value > -zone) {
        return 0.0f;
    }
    return value;
}

float DevPad::getARX(int pad, bool deadZone) {
    DevPad* dev = get();
    if (dev == nullptr) {
        return 0.0f;
    }
    float value = dev->getLocalARX(pad);
    float zone = get() != nullptr ? get()->m_deadZone : 0.0f;
    if (deadZone && value < zone && value > -zone) {
        return 0.0f;
    }
    return value;
}

float DevPad::getARY(int pad, bool deadZone) {
    DevPad* dev = get();
    if (dev == nullptr) {
        return 0.0f;
    }
    float value = dev->getLocalARY(pad);
    float zone = get() != nullptr ? get()->m_deadZone : 0.0f;
    if (deadZone && value < zone && value > -zone) {
        return 0.0f;
    }
    return value;
}

void DevPad::playVibration(int pad, const PadVibrationInfo& info) {
    DevPad* dev = get();
    if (dev != nullptr) {
        dev->playLocalVibration(pad, info);
    }
}

void DevPad::stopVibration(int pad) {
    DevPad* dev = get();
    if (dev != nullptr) {
        dev->stopLocalVibration(pad);
    }
}

void DevPad::loadVibration(unsigned int id, void* data, unsigned long size) {
    DevPad* dev = get();
    if (dev != nullptr) {
        dev->loadLocalVibration(id, data, size);
    }
}

namespace dg {
int s_nVSync = -1;
int s_nVSyncOld = -1;
bool s_bIgnore;
}  // namespace dg

int DevGraph::fontGetWidth(const char* text, FONT_STYLE style, float scale) {
    DevGraph* dev = get();
    if (dev != nullptr) {
        return dev->fontGetWidthSys(text, style, scale);
    }
    return 0;
}

bool DevGraph::isIgnore() {
    return dg::s_bIgnore;
}

void DevGraph::grSetClearCol(const mm::Col4& col) {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->m_clearCol = col;
        dev->m_clearDepth = 1.0f;
    }
}

int DevGraph::getRootWidth() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        return dev->getRootWidthSys();
    }
    return 0;
}

int DevGraph::getRootHeight() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        return dev->getRootHeightSys();
    }
    return 0;
}

void* DevGraph::cmdOpenDisplayList(unsigned int size) {
    return get()->cmdOpenDisplayListSys(size, false, false);
}

bool DevGraph::cmdCloseDisplayList() {
    return get()->cmdCloseDisplayListSys(false);
}

void DevGraph::cmdExecDisplayList() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->cmdExecDisplayListSys();
    }
}

void DevGraph::pushRect(const mm::Rect<int>& a, const mm::Rect<int>& b, const mm::Rect<int>& c, bool flag) {
    get()->m_que->pushRect(a, b, c, flag);
}

void DevGraph::popRect() {
    get()->m_que->popRect();
}

void DevGraph::getPers(mm::Mat44& mtx, float fovy, float nearZ, float farZ) {
    get()->getPersSys(mtx, fovy, nearZ, farZ);
}

mm::Rect<int>& DevGraph::getViewport() {
    return get()->m_viewport;
}

float DevGraph::getScreenScaleW() {
    return get()->getScreenScaleWSys();
}

float DevGraph::getCost() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        return dev->getCostSys();
    }
    return 0.0f;
}

void DevGraph::setVSync(int vsync) {
    dg::s_nVSyncOld = dg::s_nVSync;
    dg::s_nVSync = vsync;
}

void DevGraph::setFrameSpd(float spd) {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->m_frameSpd = spd;
    }
}

}  // namespace ml

namespace ml {
DevGraph::~DevGraph() {}
}  // namespace ml
