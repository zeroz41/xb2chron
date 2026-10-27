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

#include "classes/ml/CacheDraw/DRLINE.h"
#include "classes/ml/CacheDraw/DRLINE_PNT.h"
#include "classes/ml/CacheDraw/DLINE_WIDTH.h"
#include "classes/ml/CacheDraw/DALPHA_BLEND.h"
#include "classes/ml/CacheDraw/DBEGIN.h"
#include "classes/ml/CacheDraw/DEND.h"
#include "classes/ml/CacheDraw/DADDV3_3.h"
#include "classes/ml/CacheDraw/DADDV3_2.h"
#include "classes/ml/CacheDraw/DADDV3_1.h"
#include "classes/ml/CacheDraw.h"
#include "mm/Col4.h"
#include "classes/ml/CacheDraw/DFONT32.h"
#include "classes/ml/CacheDraw/DFONT64.h"
#include "classes/ml/CacheDraw/DFONT128.h"
#include "classes/ml/CacheDraw/DFONT256.h"
#include "classes/ml/WinView.h"
#include "classes/ml/DevFont.h"
#include "classes/ml/FileResTh.h"
#include "classes/ml/DevFontNx.h"
#include "grlib/CGLibCtl.h"
#include "ml/WorkRoot.h"
#include "classes/grlib/CGLibManager.h"
#include "mtl/MemManager.h"

namespace ml {

// ---- debug draw commands (ml::CacheDraw::D*) and the DebDraw setters their flushes inline ----

void DebDraw::setLineWidth(unsigned int width) {
    if (m_cache->setLineWidth(width)) {
        return;
    }
    if (m_lineWidth != width) {
        m_lineWidth = width;
        m_flags &= ~4;
    }
}

void DebDraw::setAlphaBlend(bool blend) {
    if (m_cache->setAlphaBlend(blend)) {
        return;
    }
    if (blend) {
        m_flags |= 0x10;
    } else {
        m_flags &= ~0x10;
    }
}

// 1.0.0 has these out of line (DebDraw::renderLine at 0x710070D12C and 0x710070D23C); 3.0.1 inlines every use
inline void DebDraw::renderLine(const mm::Vec3& start, const mm::Vec3& end) {
    if (m_cache->renderLine(start, end)) {
        return;
    }
    begin(2, 1);
    add(start, end);
    this->end();
}

inline void DebDraw::renderLine(const mm::Pnt<int>& start, const mm::Pnt<int>& end) {
    if (m_cache->renderLine(start, end)) {
        return;
    }
    begin(2, 1);
    add(start, end);
    this->end();
}

void CacheDraw::DRLINE::flush(DebDraw* draw) {
    draw->renderLine(vec(m_start), vec(m_end));
}

void CacheDraw::DRLINE_PNT::flush(DebDraw* draw) {
    draw->renderLine(m_start, m_end);
}

void CacheDraw::DLINE_WIDTH::flush(DebDraw* draw) {
    draw->setLineWidth(m_width);
}

void CacheDraw::DALPHA_BLEND::flush(DebDraw* draw) {
    draw->setAlphaBlend(m_blend);
}

void CacheDraw::DBEGIN::flush(DebDraw* draw) {
    draw->begin(m_prim, m_param);
}

void CacheDraw::DEND::flush(DebDraw* draw) {
    draw->end();
}

void CacheDraw::DADDV3_3::flush(DebDraw* draw) {
    draw->add(vec(m_v0), vec(m_v1), vec(m_v2));
}

void CacheDraw::DADDV3_2::flush(DebDraw* draw) {
    draw->add(vec(m_v0), vec(m_v1));
}

void CacheDraw::DADDV3_1::flush(DebDraw* draw) {
    draw->add(vec(m_v0));
}

void CacheDraw::DFONT32::flush(DebDraw*) {
    WinView::getView(false)->font(m_pos.x, m_pos.y, m_text);
}

void CacheDraw::DFONT64::flush(DebDraw*) {
    WinView::getView(false)->font(m_pos.x, m_pos.y, m_text);
}

void CacheDraw::DFONT128::flush(DebDraw*) {
    WinView::getView(false)->font(m_pos.x, m_pos.y, m_text);
}

void CacheDraw::DFONT256::flush(DebDraw*) {
    WinView::getView(false)->font(m_pos.x, m_pos.y, m_text);
}

void DebDraw::fontColor(const mm::Col4& col) {
    m_cache->fontColor(col);
}

void DebDraw::font(int x, int y, const char* text) {
    m_cache->font(x, y, text);
}

void DebDraw::clrTex() {
    if (m_flags & 2) {
        m_flags &= ~6;
    }
}

void DebDraw::setOrtho() {
    if (m_cache->setOrtho()) {
        return;
    }
    if (m_flags & 8) {
        m_flags &= ~4;
    }
    m_flags &= ~8;
}

void FontLayer::fontStyle(FONT_STYLE style) {
    DevFont::fontLayerStyle(this, style);
}


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

bool DevFontNx::createFont() {
    return true;
}

int DevGraphNx::getRootWidthSys() {
    return WorkRoot::getWidth();
}

int DevGraphNx::getRootHeightSys() {
    return WorkRoot::getHeight();
}

void DevGraphNx::renderEndSys() {
    if (get() != nullptr) {
        setRenderState(static_cast<RSTAT>(1));
    }
}

void DevGraphNx::resetSizeSys(short, short) {}

void DevGraphNx::wkUpdate() {}

void DevGraphNx::wkRender() {}

int DevGraphNx::thInitialize(void*, void*) {
    return initGL();
}

int DevGraphNx::thDestroy(void*, void*) {
    mm::mtl::PtrSingleton<grlib::CGLibManager>::get()->deviceRelease();
    return true;
}

bool DevPadNx::createDevice() {
    return true;
}

void device_detail::deallocateFile(void* ptr, unsigned long) {
    mtl::MemManager::deallocate(ptr, 0, false);
}

void DevFileUtilNx::zlibFree(void*, void* ptr) {
    mtl::MemManager::deallocate(ptr, 0, false);
}

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

bool DevFileTh::icbError(ml::CERR_STRUCT*) {
    return true;
}

bool DevFileTh::checkValidFileBlock(const char* path) {
    return getFileSize(path, nullptr) >= 0;
}

void DevFileTh::addMediaPath(MEDIA media, const char* path, int prio) {
    if (path != nullptr && path[0] != '\0') {
        dvfl_detail::addMediaPath(media, path, prio);
    }
}

bool DevFileTh::isNowSaving() {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_nowSaving;
    }
    return false;
}

bool FileResTh::isExist() const {
    return m_data != nullptr;
}

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

void DevGraph::setMemPoolMemHandle(mtl::ALLOC_HANDLE handle) {
    grlib::CGLibGPUCache::setMemPoolMemHandle(handle);
}

void DevGraph::setMemPoolBuffer(void* buffer, unsigned int size) {
    grlib::CGLibGPUCache::setMemPoolBuffer(buffer, size);
}

void DevGraph::releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle) {
    grlib::CGLibGPUCache::releaseMemPoolMemHandle(handle);
}

void DevGraph::releaseMemPoolBuffer(void* buffer) {
    grlib::CGLibGPUCache::releaseMemPoolBuffer(buffer);
}

void DevGraph::renderSync() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->renderSyncSys();
        DebDraw::swap();
    }
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
