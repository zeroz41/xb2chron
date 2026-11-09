// monolib_mm's own build: mm_lib's headers cite their paths from monolib_mm's build folder
#define MM_LIB_FROM_MONOLIB_MM
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>
#include <chrono>
#include "classes/ml/DevBase.h"
#include "classes/ml/DevClock.h"
#include "classes/ml/DevClockNx.h"
#include "classes/ml/DevFileArchiveNx.h"
#include "classes/ml/DevFileNxTh.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DevFileParamTh.h"
#include "classes/ml/FileReadResult.h"
#include "classes/ml/DevFileArchiver.h"
#include "classes/ml/DevFileJob.h"
#include "classes/ml/DevFileJobValidArcNxTh.h"
#include "classes/ml/DevFileJobValidNxTh.h"
#include "classes/ml/DevFileWriterNx.h"
#include "classes/ml/DevGraphNx.h"
#include "grlib/CGLibState.h"
#include "ml/font/WriteStr.h"
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
#include "classes/ml/TUnk_B777B8.h"
#include "classes/ml/LanguageInfo.h"
#include "classes/ml/MemoryAutoReleaser.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/ErrViewer.h"
#include "classes/ml/LibMain.h"
#include "classes/ml/WorkSystem.h"
#include "classes/ml/Thread.h"
#include "nn/hid.h"
#include "nn/oe.h"
#include "nn/settings.h"
#include "nn/os.h"
#include "nn/time.h"
#include "nn/account.h"
#include "nn/diag.h"

#include "classes/ml/CacheDraw/DRLINE.h"
#include "classes/ml/CacheDraw/DRLINE_PNT.h"
#include "classes/ml/CacheDraw/DLINE_WIDTH.h"
#include "classes/ml/CacheDraw/DALPHA_BLEND.h"
#include "classes/ml/CacheDraw/DBEGIN.h"
#include "classes/ml/CacheDraw/DEND.h"
#include "classes/ml/CacheDraw/DADDV3_3.h"
#include "classes/ml/CacheDraw/DADDV3_2.h"
#include "classes/ml/CacheDraw/DADDV3_1.h"
#include "classes/ml/CacheDraw/DCLEAR.h"
#include "classes/ml/CacheDraw/DMAT.h"
#include "classes/ml/CacheDraw/DPERS.h"
#include "classes/ml/CacheDraw/DORTHO.h"
#include "classes/ml/CacheDraw/DCOL.h"
#include "classes/ml/CacheDraw/DTEX.h"
#include "classes/ml/CacheDraw/DDOUBLESIDE.h"
#include "classes/ml/CacheDraw/DZCOMP.h"
#include "classes/ml/CacheDraw/DZWRITE.h"
#include "classes/ml/CacheDraw/DRRECT.h"
#include "classes/ml/CacheDraw/DRRECT_FILL.h"
#include "classes/ml/CacheDraw/DRCUBE.h"
#include "classes/ml/CacheDraw/DRCIRCLE_MAT.h"
#include "classes/ml/CacheDraw/DRAXIS.h"
#include "classes/ml/CacheDraw/DRARROW.h"
#include "classes/ml/CacheDraw/DRARROW_CUBE.h"
#include "classes/ml/CacheDraw/DRSPHERE_REAL.h"
#include "classes/ml/CacheDraw/DRCONE_FILL.h"
#include "classes/ml/CacheDraw/DRCONE.h"
#include "classes/ml/CacheDraw/DRCYLINDER.h"
#include "classes/ml/CacheDraw/DRCAPSULE.h"
#include "classes/ml/CacheDraw/DRSQUARE.h"
#include "classes/ml/CacheDraw.h"
#include "classes/ml/DebDrawCmd.h"
#include "grlib/CGLibVtxVertex.h"
#include "mm/Col4.h"
#include "classes/ml/CacheDraw/DFONT32.h"
#include "classes/ml/CacheDraw/DFONT64.h"
#include "classes/ml/CacheDraw/DFONT128.h"
#include "classes/ml/CacheDraw/DFONT256.h"
#include "classes/ml/CacheDraw/DFONT_COL.h"
#include "classes/ml/CacheDraw/DFONT_SHADOW.h"
#include "classes/ml/CacheDraw/DFONT_FLUSH.h"
#include "classes/ml/CacheDraw/DFONT_SCALE.h"
#include "classes/ml/WinView.h"
#include "classes/ml/WinProcRoot.h"
#include "classes/ml/WinViewRoot.h"
#include "classes/ml/DevFont.h"
#include "classes/ml/DevFontLayer.h"
#include "classes/mm/Sphere.h"
#include "classes/ml/FileResTh.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ml/DevFontNx.h"
#include "classes/ml/DevFileBlackListNxTh.h"
#include "classes/ml/DevFileReaderTh.h"
#include "classes/ml/DevKeyboard.h"
#include "classes/ml/FileHandleTh.h"
#include "classes/ml/detail/FileLoader.h"
#include "nn/fs.h"
#include "ml/EventFileTh.h"
#include "ml/PathUtil.h"
#include "ml/MlMem.h"
#include "grlib/CGLibCtl.h"
#include "ml/WorkRoot.h"
#include "ml/WorkUtil.h"
#include "classes/grlib/CGLibManager.h"
#include "mtl/MemManager.h"
#include "classes/mm/threading/EventWait.h"
#include "mm/threading/SpinLock.h"
#include "classes/ml/ControllerApplet.h"
#include "nn/ec.h"
#include "classes/ml/_reslist_base.h"
#include "classes/ml/reslist.h"

namespace mm { namespace threading {

// ---- mm::threading::EventWait, SpinLock (mm_thread_nx's, built into this file) ----

EventWait::EventWait(bool manualClear, bool signaled) {
    CS lock(m_section);
    nn::os::InitializeEvent(&m_event, signaled,
                            manualClear ? nn::os::EventClearMode_ManualClear : nn::os::EventClearMode_AutoClear);
    m_initialized = true;
}

EventWait::~EventWait() {
    finalize();
}

void EventWait::finalize() {
    if (m_initialized) {
        nn::os::FinalizeEvent(&m_event);
        m_initialized = false;
    }
}

void EventWait::setSignal(bool signal) {
    if (signal) {
        nn::os::SignalEvent(&m_event);
    } else {
        CS lock(m_section);
        nn::os::ClearEvent(&m_event);
    }
}

bool EventWait::waitSignal(unsigned int milliseconds) {
    if (milliseconds != 0) {
        nn::TimeSpan timeout = nn::TimeSpan::FromMilliSeconds(milliseconds);
        return nn::os::TimedWaitEvent(&m_event, timeout);
    }
    nn::os::WaitEvent(&m_event);
    return true;
}

bool EventWait::isSignal() const {
    return nn::os::TimedWaitEvent(const_cast<nn::os::EventType*>(&m_event), nn::TimeSpan::FromMilliSeconds(0));
}

SpinLock::SpinLock() : m_lock(0) {}

void SpinLock::lock(float wait) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (__atomic_exchange_n(&m_lock, 1, __ATOMIC_ACQUIRE) == 1) {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        float sec = (now - start).count() / 1000.0f / 1000000.0f;
        if (wait > 0.0f) {
            if (sec > wait) {
                return;
            }
        } else if (sec > 0.1f) {
            start = now;
            nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(1));
        }
    }
}

}}  // namespace mm::threading

namespace ml {

bool ControllerApplet::showApplet() {
    nn::hid::ControllerSupportResultInfo info;
    nn::hid::ControllerSupportArg arg;
    arg.SetDefault();
    arg.enableSingleMode = true;
    nn::Result result = nn::hid::ShowControllerSupport(&info, arg);
    if (result.IsSuccess()) {
        DevPadNx::setUserSelectControllerID(info.selectedId);
    }
    return result.IsSuccess();
}

bool ShopAddOnContentApplet::showApplet(int flag) {
    nn::ApplicationId id;
    if (flag != 0) {
        id.value = 0x0100E95004038000ul;
    } else {
        id.value = 0x0100F3400332C000ul;
    }
    nn::ec::ShowShopAddOnContentList(id);
    return true;
}

bool ShopApplicationApplet::showApplet(int flag) {
    nn::ApplicationId id;
    if (flag != 0) {
        id.value = 0x0100E95004038000ul;
    } else {
        id.value = 0x0100F3400332C000ul;
    }
    nn::ec::ShowShopApplicationInformation(id);
    return true;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EC7360). The debug draw the statics
// work on; every user (ml/CacheDraw's code too) reaches it without the GOT, so it is file-static
static DebDraw* s_debDraw;
// Proposed name, not the original's (lbl_7100EC7368): the vertex buffer ~DebDrawCmd hands to thDestroy on the render thread
static grlib::CGLibVtxVertex* s_destroyVtx;

// commands go to the cache when a debug draw exists and the caller is not the render thread, or the cache is used
// there too (1.0.0 has it out of line; 3.0.1 inlines every use)
inline bool DebDraw::isNotRender() {
    if (s_debDraw == nullptr) {
        return false;
    }
    if (WorkCpu::getCurrentThreadId() != WorkCpu::getThreadId(WorkCpu::getRenderCPUID())) {
        return true;
    }
    return s_debDraw->m_cacheOnRender;
}

// the point v through mtx, translation included (inlined into the DebDraw shapes; the name is not the original's)
static inline mm::Vec3 mulPos(const mm::Mat44& mtx, const mm::Vec3& v) {
    return mm::Vec3(v.x * mtx.m[0][0] + v.y * mtx.m[1][0] + v.z * mtx.m[2][0] + mtx.m[3][0],
                    v.x * mtx.m[0][1] + v.y * mtx.m[1][1] + v.z * mtx.m[2][1] + mtx.m[3][1],
                    v.x * mtx.m[0][2] + v.y * mtx.m[1][2] + v.z * mtx.m[2][2] + mtx.m[3][2]);
}

// the direction v through mtx's rotation (inlined into the DebDraw shapes; the name is not the original's)
static inline mm::Vec3 mulDir(const mm::Mat44& mtx, const mm::Vec3& v) {
    return mm::Vec3(v.x * mtx.m[0][0] + v.y * mtx.m[1][0] + v.z * mtx.m[2][0],
                    v.x * mtx.m[0][1] + v.y * mtx.m[1][1] + v.z * mtx.m[2][1],
                    v.x * mtx.m[0][2] + v.y * mtx.m[1][2] + v.z * mtx.m[2][2]);
}

// ---- ml::CacheDraw: queueing a command (one per DebDraw call) ----

CacheDraw::~CacheDraw() {
    for (int i = 0; i < 2; i++) {
        mtl::MemManager::deallocate(m_buf[i].m_top, 0, false);
    }
    if (m_section != nullptr) {
        delete m_section;
        m_section = nullptr;
    }
}

DebDraw* DebDraw::get(unsigned int wid) {
    if (isNotRender()) {
        CacheDraw* cache = s_debDraw->m_cache;
        if (wid != 0xFFFFFFFF) {
            cache->m_wid = wid;
        }
        if (cache->m_prim >= 0) {
            // closes the current bank's group when it holds commands and opens the next one
            CacheDraw::BUF* buf = cache->getBuf(false);
            if (buf->m_group[buf->m_groupNum].m_begin != buf->m_group[buf->m_groupNum].m_end) {
                buf->m_groupNum++;
            }
            buf->m_group[buf->m_groupNum].m_end = buf->m_cur;
            buf->m_group[buf->m_groupNum].m_begin = buf->m_cur;
            buf->m_group[buf->m_groupNum].m_prim = cache->m_prim;
        }
    } else if (s_debDraw != nullptr) {
        s_debDraw->clear();
    }
    return s_debDraw;
}

bool CacheDraw::clear() {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DCLEAR();
    return calcCurrentBuf(sizeof(DCLEAR));
}

bool CacheDraw::setMatrix(const mm::Mat44& mtx) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DMAT(mtx);
    return calcCurrentBuf(sizeof(DMAT));
}

bool CacheDraw::setPers(const mm::Mat44& mtx, float fovy, float aspect, float near, const mm::Vec3* eye) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DPERS(mtx, fovy, aspect, near, eye);
    return calcCurrentBuf(sizeof(DPERS));
}

bool CacheDraw::setOrtho() {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DORTHO();
    return calcCurrentBuf(sizeof(DORTHO));
}

bool CacheDraw::setCol(const mm::Col4& col) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DCOL(col);
    return calcCurrentBuf(sizeof(DCOL));
}

bool CacheDraw::setTex(grlib::CGLibTextureBuffer* tex) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DTEX(tex);
    return calcCurrentBuf(sizeof(DTEX));
}

bool CacheDraw::setDoubleSide(bool doubleSide) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DDOUBLESIDE(doubleSide);
    return calcCurrentBuf(sizeof(DDOUBLESIDE));
}

bool CacheDraw::setZComp(bool on) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DZCOMP(on);
    return calcCurrentBuf(sizeof(DZCOMP));
}

bool CacheDraw::setZWrite(bool on) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    m_zWrite = on;
    new (getBuf(false)->m_cur) DZWRITE(on);
    return calcCurrentBuf(sizeof(DZWRITE));
}

bool CacheDraw::renderRect(const mm::Rect<int>& rect) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRRECT(rect);
    return calcCurrentBuf(sizeof(DRRECT));
}

bool CacheDraw::renderRectFill(const mm::Rect<int>& rect) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRRECT_FILL(rect);
    return calcCurrentBuf(sizeof(DRRECT_FILL));
}

bool CacheDraw::renderCube(const mm::Vec3& min, const mm::Vec3& max) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRCUBE(min, max);
    return calcCurrentBuf(sizeof(DRCUBE));
}

bool CacheDraw::renderCircle(const mm::Mat44& mtx, float radius, unsigned int div) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRCIRCLE_MAT(mtx, radius, div);
    return calcCurrentBuf(sizeof(DRCIRCLE_MAT));
}

bool CacheDraw::renderAxis(float length) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRAXIS(length);
    return calcCurrentBuf(sizeof(DRAXIS));
}

bool CacheDraw::renderArrow(const mm::Vec3& start, const mm::Vec3& end) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRARROW(start, end);
    return calcCurrentBuf(sizeof(DRARROW));
}

bool CacheDraw::renderCubeArrow(const mm::Vec3& start, const mm::Vec3& end) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRARROW_CUBE(start, end);
    return calcCurrentBuf(sizeof(DRARROW_CUBE));
}

bool CacheDraw::renderRealSphere(float radius, unsigned int div) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRSPHERE_REAL(radius, div);
    return calcCurrentBuf(sizeof(DRSPHERE_REAL));
}

bool CacheDraw::renderConeFill(float radius, float height, unsigned int div) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRCONE_FILL(radius, height, div);
    return calcCurrentBuf(sizeof(DRCONE_FILL));
}

bool CacheDraw::renderCone(float radius, float height, unsigned int div) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRCONE(radius, height, div);
    return calcCurrentBuf(sizeof(DRCONE));
}

bool CacheDraw::renderCylinder(float radius, float height, unsigned int div) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRCYLINDER(radius, height, div);
    return calcCurrentBuf(sizeof(DRCYLINDER));
}

bool CacheDraw::renderCapsule(float radius, float height, unsigned int div) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRCAPSULE(radius, height, div);
    return calcCurrentBuf(sizeof(DRCAPSULE));
}

bool CacheDraw::renderSquare(float width, float height) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRSQUARE(width, height);
    return calcCurrentBuf(sizeof(DRSQUARE));
}

bool CacheDraw::renderLine(const mm::Vec3& a, const mm::Vec3& b) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRLINE(a, b);
    return calcCurrentBuf(sizeof(DRLINE));
}

bool CacheDraw::renderLine(const mm::Pnt<int>& a, const mm::Pnt<int>& b) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DRLINE_PNT(a, b);
    return calcCurrentBuf(sizeof(DRLINE_PNT));
}

bool CacheDraw::setLineWidth(unsigned int width) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DLINE_WIDTH(width);
    return calcCurrentBuf(sizeof(DLINE_WIDTH));
}

bool CacheDraw::setAlphaBlend(bool blend) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DALPHA_BLEND(blend);
    return calcCurrentBuf(sizeof(DALPHA_BLEND));
}

bool CacheDraw::begin(unsigned int prim, unsigned int param) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DBEGIN(prim, param);
    return calcCurrentBuf(sizeof(DBEGIN));
}

bool CacheDraw::end() {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DEND();
    return calcCurrentBuf(sizeof(DEND));
}

bool CacheDraw::add(const mm::Vec3& v0, const mm::Vec3& v1, const mm::Vec3& v2) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DADDV3_3(v0, v1, v2);
    return calcCurrentBuf(sizeof(DADDV3_3));
}

bool CacheDraw::add(const mm::Vec3& v0, const mm::Vec3& v1) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DADDV3_2(v0, v1);
    return calcCurrentBuf(sizeof(DADDV3_2));
}

bool CacheDraw::add(const mm::Vec3& v0) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DADDV3_1(v0);
    return calcCurrentBuf(sizeof(DADDV3_1));
}

bool CacheDraw::fontColor(const mm::Col4& col) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DFONT_COL(col);
    return calcCurrentBuf(sizeof(DFONT_COL));
}

bool CacheDraw::fontShadow(bool on) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DFONT_SHADOW(on);
    return calcCurrentBuf(sizeof(DFONT_SHADOW));
}

bool CacheDraw::fontFlush(bool on) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DFONT_FLUSH(on);
    return calcCurrentBuf(sizeof(DFONT_FLUSH));
}

bool CacheDraw::fontScale(float x, float y) {
    CSNC lock(*m_section);
    if (!DebDraw::isNotRender()) {
        return false;
    }
    new (getBuf(false)->m_cur) DFONT_SCALE(x, y);
    m_fontScaleX = x;
    m_fontScaleY = y;
    return calcCurrentBuf(sizeof(DFONT_SCALE));
}

void CacheDraw::DCLEAR::flush(DebDraw* draw) {
    draw->clear();
}

void CacheDraw::DMAT::flush(DebDraw* draw) {
    draw->setMatrix(m_mtx);
}

void CacheDraw::DPERS::flush(DebDraw* draw) {
    draw->setPerspective(m_fovy, m_aspect, m_near, mat(), &vec(m_eye));
}

void CacheDraw::DORTHO::flush(DebDraw* draw) {
    draw->setOrtho();
}

void CacheDraw::DTEX::flush(DebDraw* draw) {
    draw->setTex(m_tex);
}

void DebDraw::setTex(grlib::CGLibTextureBuffer* tex) {
    if (m_cache->setTex(tex)) {
        return;
    }
    m_flags |= 2;
    m_tex = tex;
}

void CacheDraw::DCOL::flush(DebDraw* draw) {
    draw->setCol(m_col);
}

void DebDraw::setCol(const mm::Col4& col) {
    if (m_cache->setCol(col)) {
        return;
    }
    m_col = col;
    if (m_col.r < 0.0f) {
        m_col.r = 0.0f;
    }
    if (m_col.g < 0.0f) {
        m_col.g = 0.0f;
    }
    if (m_col.b < 0.0f) {
        m_col.b = 0.0f;
    }
    if (m_col.a < 0.0f) {
        m_col.a = 0.0f;
    }
    if (m_col.r > 1.0f) {
        m_col.r = 1.0f;
    }
    if (m_col.g > 1.0f) {
        m_col.g = 1.0f;
    }
    if (m_col.b > 1.0f) {
        m_col.b = 1.0f;
    }
    if (m_col.a > 1.0f) {
        m_col.a = 1.0f;
    }
    m_flags &= ~4;
}

void CacheDraw::DDOUBLESIDE::flush(DebDraw* draw) {
    draw->setDoubleSide(m_doubleSide);
}

void DebDraw::setDoubleSide(bool doubleSide) {
    if (m_cache->setDoubleSide(doubleSide)) {
        return;
    }
    if (DevGraph::get() == nullptr) {
        return;
    }
    if (doubleSide) {
        grlib::CGLibPolygon::setCullingOff();
    } else {
        grlib::CGLibPolygon::setCullingBack();
    }
}

void CacheDraw::DZCOMP::flush(DebDraw* draw) {
    draw->setZComp(m_on);
}

void DebDraw::setZComp(bool on) {
    if (m_cache->setZComp(on)) {
        return;
    }
    m_zComp = on;
    if (DevGraph::get() == nullptr) {
        return;
    }
    if (on) {
        grlib::CGLibDepthCtl::setDepthControl(1, m_zWrite, GrlCompare(3));
    } else {
        grlib::CGLibDepthCtl::setDepthControl(0, 0, GrlCompare(7));
    }
}

void CacheDraw::DZWRITE::flush(DebDraw* draw) {
    draw->setZWrite(m_on);
}

void DebDraw::setZWrite(bool on) {
    if (m_cache->setZWrite(on)) {
        return;
    }
    m_zWrite = on;
    if (DevGraph::get() == nullptr) {
        return;
    }
    if (m_zComp) {
        grlib::CGLibDepthCtl::setDepthControl(1, on, GrlCompare(3));
    } else {
        grlib::CGLibDepthCtl::setDepthControl(0, 0, GrlCompare(7));
    }
}

void CacheDraw::DRRECT::flush(DebDraw* draw) {
    draw->renderRect(m_rect);
}

void DebDraw::renderRect(const mm::Rect<int>& rect) {
    if (m_cache->renderRect(rect)) {
        return;
    }
    m_flags &= ~0xAu;
    begin(3, 5);
    add(rect.x, rect.y, 0);
    add(rect.x + rect.w, rect.y, 0);
    add(rect.x + rect.w, rect.y + rect.h, 0);
    add(rect.x - 1, rect.y + rect.h, 0);
    add(rect.x, rect.y, 0);
    end();
}

void CacheDraw::DRRECT_FILL::flush(DebDraw* draw) {
    draw->renderRectFill(m_rect);
}

void DebDraw::renderRectFill(const mm::Rect<int>& rect) {
    if (m_cache->renderRectFill(rect)) {
        return;
    }
    m_flags &= ~0xAu;
    begin(6, 4);
    add(rect.x, rect.y, 0);
    add(rect.x + rect.w, rect.y, 0);
    add(rect.x, rect.y + rect.h, 0);
    add(rect.x + rect.w, rect.y + rect.h, 0);
    end();
}

void CacheDraw::DRCUBE::flush(DebDraw* draw) {
    draw->renderCube(vec(m_min), vec(m_max));
}

void DebDraw::renderCube(const mm::Vec3& min, const mm::Vec3& max) {
    if (m_cache->renderCube(min, max)) {
        return;
    }
    m_flags &= ~4;
    begin(3, 10);
    add(min);
    add(mm::Vec3(max.x, min.y, min.z));
    add(mm::Vec3(max.x, max.y, min.z));
    add(mm::Vec3(min.x, max.y, min.z));
    add(min);
    add(mm::Vec3(min.x, min.y, max.z));
    add(mm::Vec3(max.x, min.y, max.z));
    add(mm::Vec3(max.x, max.y, max.z));
    add(mm::Vec3(min.x, max.y, max.z));
    add(mm::Vec3(min.x, min.y, max.z));
    end();
    begin(2, 3);
    add(mm::Vec3(max.x, min.y, min.z), mm::Vec3(max.x, min.y, max.z));
    add(mm::Vec3(max.x, max.y, min.z), mm::Vec3(max.x, max.y, max.z));
    add(mm::Vec3(min.x, max.y, min.z), mm::Vec3(min.x, max.y, max.z));
    end();
}

void CacheDraw::DRCIRCLE_MAT::flush(DebDraw* draw) {
    draw->renderCircle(mat(), m_radius, m_div);
}

void DebDraw::renderCircle(const mm::Mat44& mtx, float radius, int div) {
    if (m_cache->renderCircle(mtx, radius, div)) {
        return;
    }
    if (!(m_flags & 8)) {
        return;
    }
    begin(3, div + 1);
    float step = 6.2831855f / div;
    for (int i = 0; i <= div; i++) {
        float angle = step * i;
        add(mulPos(mtx, mm::Vec3(sinf(angle) * radius, 0.0f, cosf(angle) * radius)));
    }
    end();
}

void CacheDraw::DRAXIS::flush(DebDraw* draw) {
    draw->renderAxis(m_length);
}

void DebDraw::renderAxis(float length) {
    if (m_cache->renderAxis(length)) {
        return;
    }
    mm::Col4 col = m_col;
    setCol(mm::Col3::red, 1.0f);
    renderLine(mm::Vec3::zero, mm::Vec3(length, 0.0f, 0.0f));
    setCol(mm::Col3::green, 1.0f);
    renderLine(mm::Vec3::zero, mm::Vec3(0.0f, length, 0.0f));
    setCol(mm::Col3::blue, 1.0f);
    renderLine(mm::Vec3::zero, mm::Vec3(0.0f, 0.0f, length));
    setCol(col);
}

void CacheDraw::DRARROW::flush(DebDraw* draw) {
    draw->renderArrow(vec(m_start), vec(m_end));
}

void CacheDraw::DRARROW_CUBE::flush(DebDraw* draw) {
    draw->renderCubeArrow(vec(m_start), vec(m_end));
}

void CacheDraw::DRSPHERE_REAL::flush(DebDraw* draw) {
    draw->renderRealSphere(m_radius, m_div);
}

void DebDraw::renderRealSphere(float radius, int div) {
    if (m_cache->renderRealSphere(radius, div)) {
        return;
    }
    for (int i = 0; i < div; i++) {
        mm::Mat44 rot;
        rot.setRotY(i * 3.1415927f / div);
        begin(3, div + 1);
        for (int j = 0; j <= div; j++) {
            float angle = j * 6.2831855f / div;
            add(mulDir(rot, mm::Vec3(sinf(angle) * radius, cosf(angle) * radius, 0.0f)));
        }
        end();
    }
}

void CacheDraw::DRCONE_FILL::flush(DebDraw* draw) {
    draw->renderConeFill(m_radius, m_height, m_div);
}

void DebDraw::renderConeFill(float radius, float height, unsigned int div) {
    if (m_cache->renderConeFill(radius, height, div)) {
        return;
    }
    mm::Vec3 top(0.0f, radius, 0.0f);
    if (div < 8) {
        div = 8;
    }
    begin(5, div);
    float step = 6.2831855f / div;
    for (unsigned int i = 0; i < div; i++) {
        float angle0 = step * i;
        float angle1 = step * (i == div - 1 ? 0 : i + 1);
        float s0 = sinf(angle0);
        float c0 = cosf(angle0);
        float s1 = sinf(angle1);
        float c1 = cosf(angle1);
        mm::Vec3 p0(s0 * height, 0.0f, c0 * height);
        mm::Vec3 p1(s1 * height, 0.0f, c1 * height);
        add(top, p0, p1);
    }
    end();
}

void CacheDraw::DRCONE::flush(DebDraw* draw) {
    draw->renderCone(m_radius, m_height, m_div);
}

void DebDraw::renderCone(float radius, float height, unsigned int div) {
    // the original asks the cache for a filled cone here
    if (m_cache->renderConeFill(radius, height, div)) {
        return;
    }
    mm::Vec3 top(0.0f, radius, 0.0f);
    mm::Vec3 p;
    if (div < 8) {
        div = 8;
    }
    begin(3, div + 1);
    float step = 6.2831855f / div;
    for (unsigned int i = 0; i <= div; i++) {
        float angle = step * ((i + 1) % div);
        float sn = sinf(angle);
        float cs = cosf(angle);
        p = mm::Vec3(sn * height, 0.0f, cs * height);
        add(p);
    }
    end();
    begin(2, div);
    for (unsigned int i = 0; i < div; i++) {
        float angle = step * i;
        float sn = sinf(angle);
        float cs = cosf(angle);
        p = mm::Vec3(sn * height, 0.0f, cs * height);
        add(top, p);
    }
    end();
}

void CacheDraw::DRCYLINDER::flush(DebDraw* draw) {
    draw->renderCylinder(m_radius, m_height, m_div);
}

void DebDraw::renderCylinder(float radius, float height, unsigned int div) {
    if (m_cache->renderCylinder(radius, height, div)) {
        return;
    }
    mm::Vec3 p0;
    mm::Vec3 p1;
    if (div < 8) {
        div = 8;
    }
    begin(3, div + 1);
    float step = 6.2831855f / div;
    float top = radius * 0.5f;
    for (unsigned int i = 0; i <= div; i++) {
        float angle = step * ((i + 1) % div);
        float sn = sinf(angle);
        float cs = cosf(angle);
        p0 = mm::Vec3(sn * height, top, cs * height);
        add(p0);
    }
    end();
    begin(3, div + 1);
    float bottom = radius * -0.5f;
    for (unsigned int i = 0; i <= div; i++) {
        float angle = step * ((i + 1) % div);
        float sn = sinf(angle);
        float cs = cosf(angle);
        p0 = mm::Vec3(sn * height, bottom, cs * height);
        add(p0);
    }
    end();
    begin(2, div);
    for (unsigned int i = 0; i < div; i++) {
        float angle = step * i;
        float sn = sinf(angle);
        float cs = cosf(angle);
        p0 = mm::Vec3(sn * height, top, cs * height);
        p1 = mm::Vec3(sn * height, bottom, cs * height);
        add(p0, p1);
    }
    end();
}

void CacheDraw::DRCAPSULE::flush(DebDraw* draw) {
    draw->renderCapsule(m_radius, m_height, m_div);
}

void CacheDraw::DRSQUARE::flush(DebDraw* draw) {
    draw->renderSquare(m_width, m_height);
}

void DebDraw::renderSquare(float width, float height) {
    if (m_cache->renderSquare(width, height)) {
        return;
    }
    mm::Vec3 p0(width * -0.5f, height * 0.5f, 0.0f);
    mm::Vec3 p1(width * 0.5f, height * 0.5f, 0.0f);
    mm::Vec3 p2(width * -0.5f, height * -0.5f, 0.0f);
    mm::Vec3 p3(width * 0.5f, height * -0.5f, 0.0f);
    begin(3, 5);
    add(p0);
    add(p1);
    add(p3);
    add(p2);
    add(p0);
    end();
}

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

}  // namespace ml

namespace mm {
PrimBase::~PrimBase() {}
}  // namespace mm

namespace ml {

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

void FontLayer::font(int x, int y, const char* format, ...) {
    char text[0x200];
    va_list args;
    va_start(args, format);
    vsnprintf(text, sizeof(text), format, args);
    va_end(args);
    if (DebDraw::isNotRender()) {
        s_debDraw->m_cache->font(x, y, text);
    } else {
        DevFont::fontLayer(this, x, y, text);
    }
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

void CacheDraw::DFONT_COL::flush(DebDraw*) {
    WinView::getView(false)->fontColor(m_col);
}

void FontLayer::fontColor(const mm::Col4& col) {
    if (DebDraw::isNotRender()) {
        s_debDraw->m_cache->fontColor(col);
    } else {
        DevFont::fontLayerColor(this, col);
    }
}

void CacheDraw::DFONT_SHADOW::flush(DebDraw*) {
    WinView::getView(false)->fontShadow(m_on);
}

void FontLayer::fontShadow(bool on) {
    if (DebDraw::isNotRender()) {
        s_debDraw->m_cache->fontShadow(on);
    } else {
        DevFont::fontLayerShadow(this, on);
    }
}

void CacheDraw::DFONT_FLUSH::flush(DebDraw*) {
    WinView::getView(false)->fontFlush(m_on);
}

void FontLayer::fontFlush(bool on) {
    if (DebDraw::isNotRender()) {
        s_debDraw->m_cache->fontFlush(on);
    } else {
        DevFont::fontLayerFlush(this, on);
    }
}

void CacheDraw::DFONT_SCALE::flush(DebDraw*) {
    WinView::getView(false)->fontScale(m_x, m_y);
}

void FontLayer::fontScale(float x, float y) {
    if (DebDraw::isNotRender()) {
        s_debDraw->m_cache->fontScale(x, y);
    } else {
        DevFont::fontLayerScale(this, x, y);
    }
}

bool DeviceNx::m_onceInitialize;
mtl::ALLOC_HANDLE device_detail::hMemFile;

// The unit's internal statics its static initializer builds: the compiler merges them into one .bss block
// (lbl_7100ECDF40, 0x4E0 bytes, ordered by size, then by definition). Proposed names, not the original's: the symbols
// leave them unnamed (lbl_7100ECDF40 holds them all; the offsets are into it).
namespace {
mm::mtl::FixStr<64> s_name08;  // +0x8 (Device::isAllReady/isColdStartReady read it)
mm::mtl::FixStr<64> s_name4C;  // +0x4C
}  // namespace

mm::mtl::FixedList<unsigned int, 512> DevFileJob::s_jobs;

namespace {
DevSettingNx::LangCode s_langCodes[15] = {  // +0x2E8 (DevSettingNx::getLang)
    DevSettingNx::LangCode(LangType(0), "ja"),     DevSettingNx::LangCode(LangType(1), "en-US"),
    DevSettingNx::LangCode(LangType(2), "fr"),     DevSettingNx::LangCode(LangType(3), "de"),
    DevSettingNx::LangCode(LangType(4), "it"),     DevSettingNx::LangCode(LangType(5), "es"),
    DevSettingNx::LangCode(LangType(6), "zh-CN"),  DevSettingNx::LangCode(LangType(7), "ko"),
    DevSettingNx::LangCode(LangType(8), "nl"),     DevSettingNx::LangCode(LangType(9), "pt"),
    DevSettingNx::LangCode(LangType(10), "ru"),    DevSettingNx::LangCode(LangType(11), "zh-TW"),
    DevSettingNx::LangCode(LangType(12), "en-GB"), DevSettingNx::LangCode(LangType(13), "fr-CA"),
    DevSettingNx::LangCode(LangType(14), "es-419"),
};
mm::mtl::FixStr<64> s_sasakiFontName;  // +0x90 (DevGraphNx::entrySasakiFont keeps the name here)
MemoryAutoReleaser s_memoryReleaser;   // +0x0
mm::mtl::FixStr<128> s_pathD4;   // +0xD4
mm::mtl::FixStr<128> s_path158;  // +0x158
mm::mtl::FixStr<128> s_path1DC;  // +0x1DC
mm::mtl::FixStr<128> s_dvdRoot;  // +0x260 (DevFileTh::getDvdRoot returns it outside rom mount mode)
mm::mtl::FixStr<256> s_path3D8;  // +0x3D8
}  // namespace

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100ECDDE0). 1.0.0's ml::setRomMountMode/
// isRomMountMode store and read it; 3.0.1 inlines them. DevFileNxTh::initializeSDK sets it once "rom" is mounted.
// The original keeps it out of the unit's merged .bss block (at its own address, 0x7100ECDDE0, among the
// definition-ordered globals), which clang's GlobalMerge does only for a global kept by `used`.
__attribute__((used)) static bool s_romMountMode;

void Device::initializeSDK(const InitParam& param) {
    DeviceNx::initializeSDK(param);
}

void DeviceNx::initializeSDK(const Device::InitParam& param) {
    if (!m_onceInitialize) {
        nn::oe::Initialize();
        unsigned long size = param.m_fileMemSize;
        unsigned long align = param.m_fileMemAlign;
        unsigned long mem = reinterpret_cast<unsigned long>(malloc(size + align));
        device_detail::hMemFile =
            mtl::MemManager::create(reinterpret_cast<void*>((mem + align - 1) & -align), size, "sdkFileMem", true);
        nn::fs::SetAllocator(device_detail::allocateFile, device_detail::deallocateFile);
        DevFileNxTh::initializeSDK(param);
        nn::account::Initialize();
        nn::time::Initialize();
        nn::hid::InitializeMouse();
        nn::hid::InitializeKeyboard();
        DevFileNxTh::initializeSave();
        m_onceInitialize = true;
    }
}

bool Device::isAllReady() {
    if (!sys()->isLoggedIn()) {
        return false;
    }
    bool ready = true;
    for (reslist<WorkObj*>::iterator it = sys()->wkGetChild()->begin(); it != sys()->wkGetChild()->end(); ++it) {
        bool loggedIn = (*it)->isLoggedIn();
        if (!loggedIn) {
            s_name08 = (*it)->m_name;
        }
        ready &= loggedIn;
    }
    return ready;
}

bool Device::isColdStartReady() {
    if (!sys()->isLoggedIn()) {
        return false;
    }
    bool ready = true;
    for (reslist<WorkObj*>::iterator it = sys()->wkGetChild()->begin(); it != sys()->wkGetChild()->end(); ++it) {
        if (static_cast<DevBase*>(*it)->m_devState & 1) {
            bool loggedIn = (*it)->isLoggedIn();
            if (!loggedIn) {
                s_name4C = (*it)->m_name;
            }
            ready &= loggedIn;
        }
    }
    return ready;
}

bool Device::wkStandbyLogin() {
    if (WorkCpu::isInitialized()) {
        return false;
    }
    m_langInfo = new (MlMem::getProductMem(), nullptr, 0, 4, false) LanguageInfo();
    LanguageInfo::initialize(MlMem::getProductMem());
    WorkUtil::createWork<TUnk_B777B8>("DeviceException", this, false);
    createDevice();
    wkSetEvent(EVT(9));
    m_groupHandle = WorkCpu::createGroupHandle(1);
    WorkCpu::entryJobThread(m_groupHandle, jobUpdate, 0, this, nullptr, WorkCpu::getRenderCPUID(), true, false);
    return WorkObj::wkStandbyLogin();
}

unsigned int Device::jobUpdate(void*, void*) {
    Device* dev = get();
    if (dev != nullptr) {
        for (mm::mtl::FixedList<Job, 16>::iterator it = dev->m_jobs.begin(); it != dev->m_jobs.end(); ++it) {
            it->m_func(it->m_arg);
        }
    }
    return 0;
}

bool Device::wkStandbyLogout() {
    if (m_child.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
        WorkCpu::releaseGroupHandle(m_groupHandle);
        if (m_langInfo != nullptr) {
            delete m_langInfo;
            m_langInfo = nullptr;
        }
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

Device* Device::create() {
    return WorkUtil::createWork<DeviceNx>("DeviceNx", mm::mtl::PtrSingleton<WorkControl>::get(), false);
}

FontLayer::FontLayer() {
    DevFont* font = mm::mtl::PtrSingleton<DevFont>::get();
    DevFontLayer* layer;
    if (font != nullptr) {
        layer = WorkUtil::createWork<DevFontLayer>("DevFontLayer", font, false);
        layer->m_layer = this;
    } else {
        layer = nullptr;
    }
    m_devLayer = layer;
}

inline void DevFontLayer::resetQue() {
    m_shadowCol = mm::Col4(0.0f, 0.0f, 0.0f, 0.0f);
    m_col = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
    m_queNum = 0;
    if (DevGraph::get() != nullptr) {
        m_que = static_cast<const LAYER_QUE**>(DevGraph::get()->allocWork(m_queMax * sizeof(LAYER_QUE*)));
    }
}

inline DevFontLayer::DevFontLayer(const char* name, WorkObj* parent)
    : WorkObj(name, parent, 0), m_que(nullptr), m_scaleX(1.0f), m_scaleY(1.0f), m_style(static_cast<FONT_STYLE>(0)),
      m_layer(nullptr), m_shadow(false), m_done(false), m_queMax(0x400), m_cmd4Value(0) {
    resetQue();
}

template <typename T>
inline T* DevFontLayer::newQue() {
    if (m_que == nullptr) {
        return nullptr;
    }
    return static_cast<T*>(DevGraph::get()->allocWork(sizeof(T)));
}

inline void DevFontLayer::pushQue(const LAYER_QUE* que) {
    m_que[m_queNum++] = que;
}

inline void DevFontLayer::queColor(const mm::Col4& col) {
    if (m_que != nullptr) {
        QUE_COL* que = newQue<QUE_COL>();
        que->m_type = 1;
        que->m_col = col;
        pushQue(que);
        m_col = col;
    }
}

inline void DevFontLayer::queShadowColor(const mm::Col4& col) {
    if (m_que != nullptr) {
        QUE_COL* que = newQue<QUE_COL>();
        que->m_type = 2;
        que->m_col = col;
        pushQue(que);
        m_shadowCol = col;
    }
}

inline void DevFontLayer::queScale(float x, float y) {
    if (m_que != nullptr) {
        QUE_SCALE* que = newQue<QUE_SCALE>();
        que->m_type = 3;
        que->m_x = x;
        que->m_y = y;
        pushQue(que);
        m_scaleX = x;
        m_scaleY = y;
    }
}

inline void DevFontLayer::queStyle(FONT_STYLE style) {
    if (m_que != nullptr) {
        QUE_STYLE* que = newQue<QUE_STYLE>();
        que->m_type = 5;
        que->m_style = style;
        pushQue(que);
        m_style = style;
    }
}

inline void DevFontLayer::queShadow(bool on) {
    if (m_que != nullptr) {
        QUE_SHADOW* que = newQue<QUE_SHADOW>();
        que->m_type = 6;
        que->m_on = on;
        pushQue(que);
    }
}

inline DevFontLayer* DevFont::findFontLayer(const FontLayer* layer) {
    DevFont* font = mm::mtl::PtrSingleton<DevFont>::get();
    if (font == nullptr) {
        return nullptr;
    }
    for (reslist<WorkObj*>::iterator it = font->wkGetChild()->begin(); it != font->wkGetChild()->end(); ++it) {
        DevFontLayer* fontLayer = static_cast<DevFontLayer*>(*it);
        if (fontLayer == nullptr) {
            continue;
        }
        if (fontLayer->m_layer == layer) {
            return fontLayer;
        }
    }
    return layer->m_devLayer;
}

inline DevFontLayer* DevFont::createFontLayer(const FontLayer* layer) {
    DevFont* font = mm::mtl::PtrSingleton<DevFont>::get();
    if (font == nullptr) {
        return nullptr;
    }
    DevFontLayer* fontLayer = WorkUtil::createWork<DevFontLayer>("DevFontLayer", font, false);
    fontLayer->m_layer = layer;
    return fontLayer;
}

inline void DevFont::doneFontLayer(const FontLayer* layer) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr) {
        fontLayer->m_done = true;
    }
}

void DevFont::fontLayer(const FontLayer* layer, int x, int y, const char* text) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr && fontLayer->m_que != nullptr) {
        unsigned int size = strlen(text) + 1;
        char* str = static_cast<char*>(DevGraph::get()->allocWork(size));
        memcpy(str, text, size);
        DevFontLayer::QUE_FONT* que = fontLayer->newQue<DevFontLayer::QUE_FONT>();
        que->m_type = 0;
        que->m_x = x;
        que->m_y = y;
        fontLayer->pushQue(que);
    }
}

void DevFont::fontLayerColor(const FontLayer* layer, const mm::Col4& col) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr) {
        fontLayer->queColor(col);
    }
}

void DevFont::fontLayerScale(const FontLayer* layer, float x, float y) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr) {
        fontLayer->queScale(x, y);
    }
}

void DevFont::fontLayerStyle(const FontLayer* layer, FONT_STYLE style) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr) {
        fontLayer->queStyle(style);
    }
}

void DevFont::fontLayerShadow(const FontLayer* layer, bool on) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr) {
        fontLayer->queShadow(on);
    }
}

void DevFont::fontLayerFlush(const FontLayer* layer, bool on) {
    DevFontLayer* fontLayer = findFontLayer(layer);
    if (fontLayer != nullptr) {
        fontLayer->flush(on);
        s_debDraw->restoreShader();
    }
}

void DevFontLayer::flush(bool on) {
    if (m_que != nullptr) {
        LAYER_QUE* end = newQue<LAYER_QUE>();
        end->m_type = 7;
        pushQue(end);
        const RenderContext* ctx;
        renderQue(ctx, m_que);
        m_queNum = 0;
        if (!on) {
            queColor(m_col);
            queShadowColor(m_shadowCol);
        }
    }
}

DebDraw* DebDraw::getOnly(unsigned int) {
    return s_debDraw;
}

void DevFont::wkUpdate() {
    for (reslist<IDevFontInfo*>::iterator it = m_infos.begin(); it != m_infos.end(); ++it) {
        (*it)->fn_slot7();
    }
    for (reslist<IDevFontInfo*>::iterator it = m_infos.begin(); it != m_infos.end(); ++it) {
        if ((*it)->fn_slot10()) {
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
            m_infos.erase(it);
            break;
        }
    }
}

bool DevFont::wkStandbyLogin() {
    if (dg::s_bIgnore) {
        return WorkObj::wkStandbyLogin();
    }
    if (Device::isColdStartReady() && DevGraph::get() != nullptr && DevGraph::get()->isLoggedIn()) {
        m_infos.create(8, m_mem);
        createFont();
        createFontLayer(this);
        return WorkObj::wkStandbyLogin();
    }
    return false;
}

bool DevFont::wkStandbyLogout() {
    doneFontLayer(this);
    if (m_child.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
        releaseFont();
        for (reslist<IDevFontInfo*>::iterator it = m_infos.begin(); it != m_infos.end(); ++it) {
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
        }
        m_infos.clear();
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

void DevFont::wkTail() {
    for (reslist<WorkObj*>::iterator it = wkGetChild()->begin(); it != wkGetChild()->end(); ++it) {
        static_cast<DevFontLayer*>(*it)->resetQue();
    }
}

void DevFontLayer::wkUpdate() {
    if (m_done) {
        wkSetEvent(EVT(0));
    }
}

bool DevFontLayer::wkStandbyLogout() {
    if (m_child.size() == 0 && m_done) {
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

void DevFontLayer::wkTail() {
    resetQue();
}

void DebDraw::fontColor(const mm::Col4& col) {
    m_cache->fontColor(col);
}

void DebDraw::font(int x, int y, const char* text) {
    m_cache->font(x, y, text);
}

// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100EC7160, lbl_7100EC7260). A cylinder's
// Proposed names, not the original's (lbl_7100EC7160, lbl_7100EC7260): top and bottom rims (16 points around the y axis at y 1 and -1), filled by the constructor; 1.0.0's
// DebDraw::cylinder (dropped from 3.0.1) draws them
static mm::Vec3 s_cylinderT[16];
static mm::Vec3 s_cylinderB[16];

DebDraw::DebDraw()
    : m_flags(0), pad_01c(1.0f), pad_020(-1), pad_024(0), pad_028(0), pad_140(0), m_lineWidth(1), pad_148(0), pad_14c(0.0f),
      pad_150(0), m_zComp(true), m_zWrite(true), pad_170(-1), pad_178(nullptr), pad_1f8(-1), pad_200(0),
      pad_208(nullptr), m_cache(nullptr), m_cacheOnRender(false) {
    s_debDraw = this;
    m_cache = new (MlMem::getProductMem(), nullptr, 0, 4, false) CacheDraw(MlMem::getDebugMem(), 0x20000);
    m_col = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
    m_mtx = mm::Mat44::identity;
    m_pos = mm::Vec3::zero;
    pad_160 = mm::Vec3::zero;
    for (int i = 0; i < 16; i++) {
        float angle = i * 0.3926991f;
        float s = sinf(angle);
        float c = cosf(angle);
        s_cylinderB[i].x = s;
        s_cylinderT[i].x = s;
        s_cylinderB[i].y = -1.0f;
        s_cylinderB[i].z = c;
        s_cylinderT[i].y = 1.0f;
        s_cylinderT[i].z = c;
    }
    m_prmAlloc.create(MlMem::getDebugMem(), 0x400);
    m_prmList.create(0x400, MlMem::getDebugMem());
}

DebDraw::~DebDraw() {
    if (m_cache != nullptr) {
        delete m_cache;
        m_cache = nullptr;
    }
    s_debDraw = nullptr;
}

void DebDraw::setForceRenderQueue(bool on) {
    CacheDraw* cache = m_cache;
    m_cacheOnRender = on;
    cache->m_forceRenderQueue = on;
    if (on || cache->m_suspendSwap != 0) {
        return;
    }
    // closes the odd bank's open group
    unsigned int bank = WorkCpu::getOdd();
    CacheDraw::BUF* buf = &cache->m_buf[bank];
    if (buf->m_top < buf->m_cur) {
        buf->m_groupNum++;
        buf->m_group[buf->m_groupNum].m_end = buf->m_cur;
        buf->m_group[buf->m_groupNum].m_begin = buf->m_cur;
        buf->m_group[buf->m_groupNum].m_prim = cache->m_prim;
    }
}

int DebDraw::getCacheDrawWID() {
    if (s_debDraw != nullptr) {
        return s_debDraw->m_cache->m_wid;
    }
    return -1;
}

CacheDraw* DebDraw::getCacheDraw() {
    s_debDraw->m_cache->m_prim = -2;
    return s_debDraw->m_cache;
}

void DebDraw::setCurrentPrio(int prio) {
    if (s_debDraw != nullptr) {
        s_debDraw->m_cache->m_prim = prio;
    }
}

void DebDraw::flushPrio(int prio, const mm::Mat44& view, const mm::Mat44& proj) {
    if (s_debDraw != nullptr) {
        s_debDraw->m_cache->flush(prio, view, proj);
    }
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

// the cache gets the colour opaque, the draw keeps the alpha
void DebDraw::setCol(const mm::Col3& col, float a) {
    CacheDraw* cache = m_cache;
    mm::Col4 opaque;
    opaque.r = col.r;
    opaque.g = col.g;
    opaque.b = col.b;
    opaque.a = 1.0f;
    if (cache->setCol(opaque)) {
        return;
    }
    m_col.r = col.r;
    m_col.g = col.g;
    m_col.b = col.b;
    m_col.a = a;
    if (m_col.r < 0.0f) {
        m_col.r = 0.0f;
    }
    if (m_col.g < 0.0f) {
        m_col.g = 0.0f;
    }
    if (m_col.b < 0.0f) {
        m_col.b = 0.0f;
    }
    if (m_col.a < 0.0f) {
        m_col.a = 0.0f;
    }
    if (m_col.r > 1.0f) {
        m_col.r = 1.0f;
    }
    if (m_col.g > 1.0f) {
        m_col.g = 1.0f;
    }
    if (m_col.b > 1.0f) {
        m_col.b = 1.0f;
    }
    if (m_col.a > 1.0f) {
        m_col.a = 1.0f;
    }
    m_flags &= ~4;
}

void DebDraw::setCol(float r, float g, float b, float a) {
    setCol(mm::Col4(r, g, b, a));
}

unsigned int DebDrawCmd::thInitialize(void* p, void*) {
    DebDrawCmd* self = static_cast<DebDrawCmd*>(p);
    self->m_size = 0xC00000;
    self->m_vtx = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    self->m_vtx->createVertexBuff(self->m_size, sizeof(VERTEX));
    self->pad_2f0 = false;
    return 0;
}

DebDrawCmd::~DebDrawCmd() {
    s_destroyVtx = m_vtx;
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDestroy, &s_destroyVtx, nullptr, nullptr, false,
                       static_cast<WKCPU_SYNC>(0));
}

unsigned int DebDrawCmd::thDestroy(void* p, void*) {
    grlib::CGLibVtxVertex** vtx = static_cast<grlib::CGLibVtxVertex**>(p);
    if (*vtx != nullptr) {
        delete *vtx;
        *vtx = nullptr;
    }
    return 0;
}

void DebDrawCmd::fastSetup() {
    pad_156 = false;
    if (pad_2f0) {
        pad_2d8 = m_size / 2;
        m_ofs = pad_2d8;
        pad_2f0 = false;
    } else {
        pad_2d8 = 0;
        m_ofs = pad_2d8;
        pad_2f0 = true;
    }
}

void DebDrawCmd::add(const mm::Vec3& p0, const mm::Vec3& p1) {
    if (m_cache->add(p0, p1)) {
        return;
    }
    mm::Vec3 tmp0;
    mm::Vec3 tmp1;
    const mm::Vec3* q0 = &p0;
    const mm::Vec3* q1 = &p1;
    if (m_flags & 8) {
        transform(p0, tmp0);
        q0 = &tmp0;
        transform(p1, tmp1);
        q1 = &tmp1;
    }
    if (!(m_flags & 2)) {
        if (m_flags & 0x20000) {
            putVtx(*q0, m_col);
            putVtx(*q1, m_col);
        }
        pad_140 += 2;
    }
}

void DebDrawCmd::add(const mm::Pnt<int>& p0, const mm::Pnt<int>& p1) {
    putVtx(p0.x, p0.y, pad_14c, m_col);
    putVtx(p1.x, p1.y, pad_14c, m_col);
    pad_140 += 2;
}

void DebDrawCmd::add(int x0, int y0, int x1, int y1) {
    putVtx(x0, y0, pad_14c, m_col);
    putVtx(x1, y1, pad_14c, m_col);
    pad_140 += 2;
}

void DebDrawCmd::add(const mm::Vec3& p) {
    if (m_cache->add(p)) {
        return;
    }
    mm::Vec3 tmp;
    const mm::Vec3* q = transform(&p, tmp);
    putVtx(*q, m_col);
    pad_140++;
}

void DebDrawCmd::add(const mm::Pnt<int>& p) {
    putVtx(p.x, p.y, pad_14c, m_col);
    pad_140++;
}

void DebDrawCmd::add(float x, float y, float z) {
    add(mm::Vec3(x, y, z));
}

void DebDrawCmd::add(int x, int y, int z) {
    putVtx(x, y, z, m_col);
    pad_140++;
}

void DebDrawCmd::add(int x, int y) {
    putVtx(x, y, pad_14c, m_col);
    pad_140++;
}

void DebDrawCmd::add(const mm::Vec3& p, const mm::Col4& col) {
    mm::Vec3 tmp;
    const mm::Vec3* q = transform(&p, tmp);
    putVtx(*q, col);
    pad_140++;
}

void DebDrawCmd::add(const mm::Vec3& p, const mm::Col3& col) {
    mm::Vec3 tmp;
    const mm::Vec3* q = transform(&p, tmp);
    putVtx(*q, mm::Col4(col.r, col.g, col.b, m_col.a));
    pad_140++;
}

void DebDrawCmd::add(int x, int y, const mm::Col4& col) {
    putVtx(x, y, pad_14c, col);
    pad_140++;
}

void DebDrawCmd::add(int x, int y, const mm::Col3& col) {
    putVtx(x, y, pad_14c, mm::Col4(col.r, col.g, col.b, m_col.a));
    pad_140++;
}

void DebDrawCmd::add(const mm::Vec3& p, const mm::Vec3& uv, const mm::Col4& col) {
    putVtx(p, col, uv.x, uv.y);
    pad_140++;
}

// tells the DevFontLayer serving it that it is done (wkUpdate then sends event 0)
FontLayer::~FontLayer() {
    DevFont::doneFontLayer(this);
}

void FontLayer::fontSetMaxQue(unsigned int max) {
    if (mm::mtl::PtrSingleton<DevFont>::get() != nullptr) {
        DevFont::findFontLayer(this)->m_queMax = max;
    }
}

unsigned int FontLayer::fontGetHeight() const {
    DevFontLayer* fontLayer = DevFont::findFontLayer(this);
    if (fontLayer != nullptr) {
        DevGraph* dev = DevGraph::get();
        if (dev != nullptr) {
            return dev->fontGetHeightSys(fontLayer->m_style, fontLayer->m_scaleY);
        }
    }
    return 0;
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

mm::mtl::FixedVector<LangType, 15>& DevSetting::getLangList(mm::mtl::FixedVector<LangType, 15>& list) {
    list.clear();
    DevSetting* dev = get();
    if (dev != nullptr) {
        return dev->m_impl->getLangList(list);
    }
    return list;
}

void DevSetting::setAutoSleepExtended(SleepExtendType type) {
    DevSetting* dev = get();
    if (dev != nullptr) {
        dev->m_impl->setAutoSleepExtended(type);
    }
}

unsigned int DevKeyboard::getVkHold() {
    DevKeyboard* dev = mm::mtl::PtrSingleton<DevKeyboard>::get();
    if (dev != nullptr) {
        return dev->m_vkHold;
    }
    return 0;
}

// clearKey's stores go to fields no other code of 3.0.1 reaches (their names are unknown)
void DevKeyboard::clearKey() {
    DevKeyboard* dev = mm::mtl::PtrSingleton<DevKeyboard>::get();
    if (dev != nullptr) {
        dev->m_vkHold = 0;
        dev->pad_1c8 = 0;
        dev->pad_1b8 = 0;
        dev->pad_258 = 0;
        dev->pad_250 = 0;
    }
}

void DevPad::wkUpdate() {}

namespace dev_touch_detail {
mm::Vec2 s_initPos(-1.0f, -1.0f);
}  // namespace dev_touch_detail

void DevTouch::itUp(unsigned int id, float, float) {
    for (Touch* it = m_touch.begin(); it != m_touch.end(); ++it) {
        if (it->m_id == id) {
            m_touch.erase(it);
            return;
        }
    }
}

void DevTouch::updateDevice() {}

void DevTouch::wkUpdate() {
    updateDevice();
    long clock;
    if (DevClock::getClockNow(clock)) {
        for (Touch* it = m_touch.begin(); it != m_touch.end(); ++it) {
            if (it->m_clock != 0) {
                long elapsed = clock - it->m_clock;
                it->m_time = DevClock::getClock2Sec(elapsed);
            } else {
                it->m_clock = clock;
            }
        }
    }
}

bool DevTouch::wkStandbyLogin() {
    if (createDevice()) {
        return WorkObj::wkStandbyLogin();
    }
    return false;
}

bool DevTouch::wkStandbyLogout() {
    if (m_child.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
        releaseDevice();
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

bool DevFontNx::createFont() {
    return true;
}

void DevFontNx::wkUpdate() {
    DevFont::wkUpdate();
}

int DevGraphNx::getRootWidthSys() {
    return WorkRoot::getWidth();
}

int DevGraphNx::getRootHeightSys() {
    return WorkRoot::getHeight();
}

float DevGraphNx::getCostSys() const {
    unsigned int us = static_cast<unsigned int>(mm::mtl::PtrSingleton<grlib::CGLibManager>::get()->getGpuTimeStamp()) / 1000;
    return us * 0.000001f / getFrameSyncSec() * 100.0f + 3.0f;
}

void DevGraphNx::grSetViewportSys(const mm::Rect<int>& rect, int) {
    mm::Rect<int> r = rect;
    grlib::LibMainStateViewPort viewport;
    viewport.x = r.x;
    viewport.y = r.y;
    viewport.width = r.w;
    viewport.height = r.h;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    grlib::CGLibState::setOnlyViewport(viewport);
}

void DevGraphNx::grSetScissorSys(const mm::Rect<int>& rect) {
    mm::Rect<int> r = rect;
    grlib::LibMainStateViewPort viewport;
    viewport.x = r.x;
    viewport.y = r.y;
    viewport.width = r.w;
    viewport.height = r.h;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    grlib::CGLibState::setOnlyScissor(viewport);
}

void DevGraphNx::renderBeginSys() {
    if (get() != nullptr) {
        setRenderState(static_cast<RSTAT>(0));
        if (DevGraph* dev = get()) {
            grlib::CGLibColorCtl::clearMainFrameBuffer(dev->m_clearCol);
        }
    }
}

void DevGraphNx::renderEndSys() {
    if (get() != nullptr) {
        setRenderState(static_cast<RSTAT>(1));
    }
}

void DevGraphNx::renderSyncSys() {
    if (get() == nullptr || ((m_flags & 1) | m_updateStop)) {
        return;
    }
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thSync, this, nullptr, nullptr, false, static_cast<WKCPU_SYNC>(1));
    for (;;) {
        float time;
        DevClock::getTimeNow(time, WorkCpu::getBeginClock(true));
        if (getFrameSyncSec() * 0.997f < time) {
            break;
        }
    }
}

unsigned int DevGraphNx::thSync(void*, void*) {
    mm::mtl::PtrSingleton<grlib::CGLibManager>::get()->swap();
    setRenderState(static_cast<RSTAT>(2));
    return 0;
}

void DevGraphNx::resetSizeSys(short, short) {}

unsigned int DevGraphNx::fontGetWidthSys(const char* text, FONT_STYLE, float scale) {
    WriteStr str;
    str.set_font(&static_cast<DevGraphNx*>(get())->m_font);
    str.set_scale(scale, scale);
    return str.calc_string_width(text);
}

unsigned int DevGraphNx::fontGetHeightSys(FONT_STYLE, float scale) {
    WriteStr str;
    str.set_font(&static_cast<DevGraphNx*>(get())->m_font);
    return str.get_origin_size() * scale;
}

void DevGraphNx::fontDrawSys(short x, short y, float scaleH, float scaleV, const char* text, const mm::Col4* col, bool) {
    WriteStr str;
    str.set_font(&static_cast<DevGraphNx*>(get())->m_font);
    str.set_pos(x, y);
    str.set_scale(scaleH, scaleV);
    if (col != nullptr) {
        str.set_color(Color(col->r * 255.0f, col->g * 255.0f, col->b * 255.0f, col->a * 255.0f));
    }
    str.print(text, false);
}

void DevGraphNx::wkUpdate() {}

void DevGraphNx::wkRender() {}

bool DevGraphNx::wkStandbyLogin() {
    if (!DevGraph::wkStandbyLogin()) {
        return false;
    }
    if (!WorkRoot::isWinDestroy()) {
        WorkCpu::runThread(WorkCpu::getRenderCPUID(), thInitialize, this, nullptr, nullptr, false,
                           static_cast<WKCPU_SYNC>(0));
        DebDrawCmd* cmd = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) DebDrawCmd();
        WorkCpu::runThread(WorkCpu::getRenderCPUID(), DebDrawCmd::thInitialize, cmd, nullptr, nullptr, false,
                           static_cast<WKCPU_SYNC>(0));
    }
    return true;
}

unsigned int DevGraphNx::thInitialize(void*, void*) {
    return initGL();
}

unsigned int DevGraphNx::thDestroy(void*, void*) {
    mm::mtl::PtrSingleton<grlib::CGLibManager>::get()->deviceRelease();
    return true;
}

bool DevGraphNx::initGL() {
    bool result = mm::mtl::PtrSingleton<grlib::CGLibManager>::get()->deviceInit();
    DevFileParamTh param;
    int size;
    param.m_hMem = MlMem::getProductMem();
    param.m_path = s_sasakiFontName.m_str;
    void* data = DevFileTh::readFileBlock(param, &size, nullptr);
    DevGraphNx* dev = static_cast<DevGraphNx*>(get());
    dev->m_fontData = data;
    if (data != nullptr) {
        dev->m_font.construct(data, size);
    }
    return result;
}

bool DevGraphNx::wkStandbyLogout() {
    if (m_child.size() == 0 && mm::mtl::PtrSingleton<WinProcRoot>::get() == nullptr &&
        mm::mtl::PtrSingleton<WinViewRoot>::get() == nullptr) {
        if (m_fontData != nullptr) {
            m_font.destroy();
            if (m_fontData != nullptr) {
                mtl::MemManager::deallocate(m_fontData, 0, false);
                m_fontData = nullptr;
            }
        }
        if (s_debDraw != nullptr) {
            delete s_debDraw;
        }
        grlib::CGLibManager* lib = mm::mtl::PtrSingleton<grlib::CGLibManager>::get();
        if (lib != nullptr && lib->isRelease()) {
            WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDestroy, this, nullptr, nullptr, false,
                               static_cast<WKCPU_SYNC>(0));
            return false;
        }
        return DevGraph::wkStandbyLogout();
    }
    return false;
}

void DevGraphNx::entrySasakiFont(const char* name) {
    s_sasakiFontName = name;
}

bool pad_detail::g_IsQuitRequired;
nn::os::ThreadType pad_detail::g_thread;
nn::os::TimerEventType pad_detail::g_TimerEvent;
alignas(0x1000) unsigned char pad_detail::g_ThreadStack1[0x2000];

namespace pad_detail {
// the lock around the vibration node update (the thread function and initializeVibration share it; the names are
// not the original's)
static CriticalSection& getVibrationSection() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100ECDE48, guard lbl_7100ECDE70)
    static CriticalSection section;
    return section;
}
}  // namespace pad_detail

void pad_detail::VibrationNodeThreadFunction(void*) {
    while (!g_IsQuitRequired) {
        nn::os::WaitTimerEvent(&g_TimerEvent);
        CS lock(getVibrationSection());
        nn::hid::VibrationNode::Update();
    }
    nn::os::StopTimerEvent(&g_TimerEvent);
}

void DevPadNx::Impl::stateInitialize(float) {
    nn::hid::InitializeNpad();
    initPad();
    pad_detail::g_IsQuitRequired = false;
    nn::os::InitializeTimerEvent(&pad_detail::g_TimerEvent, nn::os::EventClearMode_AutoClear);
    nn::os::CreateThread(&pad_detail::g_thread, pad_detail::VibrationNodeThreadFunction, nullptr,
                         pad_detail::g_ThreadStack1, sizeof(pad_detail::g_ThreadStack1), 16);
    nn::os::StartThread(&pad_detail::g_thread);
    nn::os::StartPeriodicTimerEvent(&pad_detail::g_TimerEvent, nn::hid::VibrationNode::DefaultVibrationSampleInterval,
                                    nn::hid::VibrationNode::DefaultVibrationSampleInterval);
    m_stateId = 2;
    m_state.set(this, &Impl::stateUpdate);
}

void DevPadNx::Impl::stateUpdate(float) {
    if (m_stateId == 2) {
        updateNpad();
    }
}

void DevPadNx::Impl::stateFinalize(float) {
    pad_detail::g_IsQuitRequired = true;
    nn::os::WaitThread(&pad_detail::g_thread);
    nn::os::DestroyThread(&pad_detail::g_thread);
    nn::os::FinalizeTimerEvent(&pad_detail::g_TimerEvent);
    for (int i = 0; i < m_padCount; ++i) {
        stopVibration(getPad(i, i < 4));
    }
    for (VibPlayerData& player : m_players) {
        if (player.m_data != nullptr) {
            player.m_player.Stop();
            if (player.m_data != nullptr) {
                mtl::MemManager::deallocate(player.m_data, 0, false);
                player.m_data = nullptr;
            }
        }
        player.m_size = 0;
        player.m_id = -1;
    }
    m_state.m_invoker = nullptr;
}

DevPadNx::~DevPadNx() {}

bool DevPadNx::isLocalConnect(int pad) const {
    return m_impl->getPadData(pad).m_connect;
}

int DevPadNx::getLocalStyle(int pad) const {
    return m_impl->getPadData(pad).m_style;
}

int DevPadNx::getLocalUserSelectPadID() const {
    return m_impl->getUserSelectPadID();
}

unsigned int DevPadNx::getLocalBtn(int pad) const {
    return m_impl->getPadData(pad).m_btn;
}

float DevPadNx::getLocalALX(int pad) const {
    return m_impl->getPadData(pad).m_alx;
}

float DevPadNx::getLocalALY(int pad) const {
    return m_impl->getPadData(pad).m_aly;
}

float DevPadNx::getLocalARX(int pad) const {
    return m_impl->getPadData(pad).m_arx;
}

float DevPadNx::getLocalARY(int pad) const {
    return m_impl->getPadData(pad).m_ary;
}

void DevPadNx::playLocalVibration(int pad, const PadVibrationInfo& info) {
    m_impl->playVibration(m_impl->getPadData(pad), info);
}

void DevPadNx::loadLocalVibration(unsigned int id, void* file, unsigned long size) {
    Impl::VibPlayerData& player = m_impl->m_players[id];
    if (player.m_data == nullptr) {
        player.m_id = id;
        player.m_data = mtl::MemManager::allocate(WorkRoot::getMemTMP(), size, 0x20, false, "no name", 0);
        player.m_size = size;
        memcpy(player.m_data, file, size);
        player.m_player.Load(player.m_data, size);
        player.m_player.SetLoop(false);
    }
}

void DevPadNx::stopLocalVibration(int pad) {
    m_impl->stopVibration(m_impl->getPadData(pad));
}

void DevPadNx::setUserSelectControllerID(unsigned int id) {
    DevPadNx* dev = static_cast<DevPadNx*>(get());
    if (dev != nullptr) {
        dev->m_impl->setUserSelectController(id);
    }
}

int DevPadNx::getLocalConnectPadCount() {
    DevPadNx* dev = static_cast<DevPadNx*>(get());
    if (dev != nullptr) {
        return dev->m_impl->m_connectPadCount;
    }
    return 0;
}

void DevPadNx::updateDevice(float dt) {
    const mm::mtl::Delegate<void(float)>& state = m_impl->m_state;
    if (state.isValid()) {
        state(dt);
    }
}

bool DevPadNx::createDevice() {
    return true;
}

void DevPadNx::releaseDevice() {
    m_impl->release();
}

void* device_detail::allocateFile(unsigned long size) {
    return mtl::MemManager::allocate(hMemFile, size, 4, false, "no name", 0);
}

void device_detail::deallocateFile(void* ptr, unsigned long) {
    mtl::MemManager::deallocate(ptr, 0, false);
}

bool DevFileNxTh::m_mountRom;
bool DevFileNxTh::m_mountSave;
bool DevFileNxTh::m_validuser;
nn::account::UserHandle DevFileNxTh::m_appuser;
int DevFileNxTh::m_AocListupBuffer[16];
void* DevFileNxTh::m_mountAoc[16];

void DevFileNxTh::initializeSave() {
    nn::account::Uid uid = {};
    if (nn::account::OpenPreselectedUser(&m_appuser).IsSuccess()) {
        m_validuser = true;
        NN_ASSERT(nn::account::GetUserId(&uid, m_appuser).IsSuccess());
    }
    if (uid._data[0] == 0 && uid._data[1] == 0) {
        uid = nn::account::Uid();
        int count = 0;
        if (nn::account::ListAllUsers(&count, &uid, 1).IsFailure() || count == 0) {
#line 465 "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../source\\device/nx/th_dev_file_nx.cpp"
            NN_LOG("error: user account not exist!!\n");
            return;
        }
    }
    if (!nn::fs::IsSaveDataExisting(uid)) {
        if (nn::fs::ResultUsableSpaceNotEnough::Includes(nn::fs::EnsureSaveData(uid))) {
            return;
        }
    }
    nn::Result result = nn::fs::MountSaveData("save", uid);
    if (result.IsFailure()) {
        nn::diag::detail::AbortImpl("", "", "", 0, &result, "");
    }
    m_mountSave = true;
}

void DevFileNxTh::finalizeSDK() {
    if (m_mountSave) {
        nn::fs::Unmount("save");
    }
    if (m_mountRom) {
        nn::fs::Unmount("rom");
    }
    if (m_validuser) {
        nn::account::CloseUser(m_appuser);
    }
    for (int i = 0; i < 16; i++) {
        mm::mtl::FixStr<16> name;
        if (m_mountAoc[i] != nullptr) {
            name.format("aoc%d", m_AocListupBuffer[i]);
            nn::fs::Unmount(name.m_str);
            free(m_mountAoc[i]);
            m_mountAoc[i] = nullptr;
        }
    }
}

MemoryAutoReleaser::~MemoryAutoReleaser() {
    if (m_ptr != nullptr) {
        free(m_ptr);
    }
}

DevFileNxTh::DevFileNxTh(mtl::ALLOC_HANDLE handle)
    : m_alloc(handle), pad_18(0), m_impl(new (handle, nullptr, 0, 4, false) Impl()) {
    __atomic_store_n(&m_impl->pad_17FC, 0, __ATOMIC_SEQ_CST);
    __atomic_store_n(&m_impl->pad_17F8, false, __ATOMIC_SEQ_CST);
}

DevFileNxTh::~DevFileNxTh() {}

bool DevFileNxTh::initialize() {
    if (pad_18 == 0) {
        for (unsigned long i = 1; i < m_impl->m_params.size(); i++) {
            m_impl->m_params[i].m_owner = this;
            Thread* thread = Thread::create("rfLoadThread", false, thFileLoader, &m_impl->m_params[i], 0x10000,
                                            WorkCpu::getSubWorkCPUID(), -3);
            if (thread != nullptr) {
                m_impl->m_params[i].m_thread = thread;
                thread->resume();
            }
        }
        pad_18 = 1;
    }
    return true;
}

bool DevFileNxTh::finalize() {
    switch (pad_18) {
    case 1:
        __atomic_store_n(&m_impl->pad_17F8, true, __ATOMIC_SEQ_CST);
        for (unsigned long i = 1; i < m_impl->m_params.size(); i++) {
            if (m_impl->m_params[i].m_thread != nullptr) {
                m_impl->m_params[i].m_thread->setSignalEvent(true);
            }
        }
        pad_18 = 2;
        break;
    case 2:
        if (__atomic_load_n(&m_impl->pad_17FC, __ATOMIC_SEQ_CST) == 0) {
            pad_18 = 3;
        }
        break;
    case 3:
        for (unsigned long i = 1; i < m_impl->m_params.size(); i++) {
            if (m_impl->m_params[i].m_thread != nullptr) {
                m_impl->m_params[i].m_thread->release();
            }
        }
        pad_18 = 4;
        break;
    }
    return pad_18 == 4;
}

const char* DevFileNxTh::getMediaRootPath() const {
    return s_romMountMode ? "rom:" : s_dvdRoot.m_str;
}

const char* DevFileTh::getDvdRoot() {
    return s_romMountMode ? "rom:" : s_dvdRoot.m_str;
}

void DevFileNxTh::getMediaPath(mm::mtl::FixStr<256>& out, const char* path) {
    mm::mtl::FixStr<256> result;
    if (DevFileTh::getMediaType(path) == 0) {
        result = s_romMountMode ? "rom:" : s_dvdRoot.m_str;
        mm::mtl::FixStr<128> name(path);
        for (int i = 0; i < result.m_nLen; i++) {
            if (result.m_str[i] == '\\') {
                result.m_str[i] = '/';
            }
        }
        if (result.m_nLen != 0 && name.m_str[0] != '/' && result.m_str[result.m_nLen - 1] != '/') {
            result += "/";
        }
        result += name.m_str;
    } else {
        result = path;
    }
    out = result;
}

DevFileJobTh* DevFileNxTh::createLoader(mtl::ALLOC_HANDLE handle) {
    return new (handle, nullptr, 0, 4, false) DevFileJobTh();
}

DevFileWriterTh* DevFileNxTh::createWriter(mtl::ALLOC_HANDLE handle) {
    return new (handle, nullptr, 0, 4, false) DevFileWriterNx;
}

DevFileJobTh* DevFileNxTh::createFileValid(mtl::ALLOC_HANDLE handle) {
    return new (handle, nullptr, 0, 4, false) DevFileJobValidNxTh();
}

bool DevFileNxTh::readBlock(FileHandleTh* handle, const char* path) {
    void* buf = mtl::MemManager::allocate(WorkRoot::getMemTMP(), 0x20000, 4, false, "no name", 0);
    bool result = readBlockSlice(handle, path, buf, 0x20000);
    if (buf != nullptr) {
        mtl::MemManager::deallocate(buf, 0, false);
    }
    return result;
}

void DevFileTh::makeMediaFileName(mm::mtl::FixStr<256>& out, const char* root, const char* path) {
    if (getMediaType(path) != 0) {
        out = path;
        return;
    }
    out = root;
    if (out.m_nLen != 0) {
        for (int i = 0; i < out.m_nLen; i++) {
            if (out.m_str[i] == '\\') {
                out.m_str[i] = '/';
            }
        }
        int last = out.m_nLen - 1;
        if (out.m_str[last] == '/') {
            out.m_str[last] = '\0';
            out.m_nLen = last;
        }
    }
    if (path[0] == '\\' || path[0] == '/') {
        out += path;
    } else {
        out += "/";
        out += path;
    }
    for (int i = 0; i < out.m_nLen; i++) {
        if (out.m_str[i] == '\\') {
            out.m_str[i] = '/';
        }
    }
}

int DevFileNxTh::addressAlignment() {
    return 0x10;
}

bool DevFileNxTh::rfOpen(FileHandleTh* handle, const char* path) {
    OpenReadParam& param = get()->m_impl->m_params[handle->m_channel];
    mm::threading::WriteLockGuard lock(param.m_lock);
    DevFileTh::makeMediaFileName(param.m_path, path, handle->m_path);
    if (!param.m_isOpen) {
        if (!nn::fs::OpenFile(&param.m_handle, param.m_path.m_str, 1).IsSuccess()) {
            return false;
        }
        param.m_isOpen = true;
        param.pad_10D = false;
        param.pad_10E = false;
        param.pad_110 = false;
    }
    return true;
}

bool DevFileNxTh::rfClose(FileHandleTh* handle) {
    OpenReadParam& param = get()->m_impl->m_params[handle->m_channel];
    mm::threading::WriteLockGuard lock(param.m_lock);
    if (param.pad_10F) {
        __atomic_store_n(&handle->m_canceled, true, __ATOMIC_SEQ_CST);
        handle->m_listener = nullptr;
        param.pad_110 = true;
        return false;
    }
    if (param.pad_10D) {
        param.pad_10D = false;
    }
    nn::fs::CloseFile(param.m_handle);
    param.m_isOpen = false;
    return true;
}

void DevFileNxTh::tail() {
    for (OpenReadParam* param = m_impl->m_params.begin(); param != m_impl->m_params.end(); param++) {
        if (!param->pad_10D || param->pad_118 == nullptr) {
            continue;
        }
        mm::threading::WriteLockGuard lock(param->m_lock);
        if (!__atomic_load_n(&param->pad_118->m_canceled, __ATOMIC_SEQ_CST)) {
            FileHandleTh* handle = param->pad_118;
            if (handle->m_readSize != 0 && handle->m_readSize == handle->m_size) {
                param->pad_10D = false;
                if (handle->m_outData != nullptr) {
                    *handle->m_outData = handle->m_data;
                }
                if (handle->m_outSize != nullptr) {
                    *handle->m_outSize = handle->m_size;
                }
                if (IWorkEvent* listener = handle->m_listener) {
                    EventFileTh event;
                    event.m_kind = 2;
                    event.m_handle = handle;
                    event.m_allocHandle = handle->m_allocHandle;
                    event.m_allocator = handle->m_allocator;
                    event.m_path = handle->m_path;
                    event.m_data = handle->m_data;
                    event.m_result = handle->m_size;
                    event.pad_38 = handle->pad_68;
                    listener->OnFileEvent(&event);
                }
                param->pad_118 = nullptr;
            }
        } else if (!param->pad_10F) {
            if (param->pad_110) {
                nn::fs::CloseFile(param->m_handle);
                param->pad_110 = false;
            }
            FileHandleTh* handle = param->pad_118;
            param->m_isOpen = false;
            param->pad_10D = false;
            if (handle->m_outData != nullptr) {
                *handle->m_outData = nullptr;
            }
            if (handle->m_outSize != nullptr) {
                *handle->m_outSize = -1;
            }
            if (IWorkEvent* listener = handle->m_listener) {
                EventFileTh event;
                event.m_kind = 4;
                event.m_handle = handle;
                event.m_allocHandle = handle->m_allocHandle;
                event.m_allocator = handle->m_allocator;
                event.m_path = handle->m_path;
                event.m_data = handle->m_data;
                event.m_result = handle->m_size;
                event.pad_38 = handle->pad_68;
                listener->OnFileEvent(&event);
            }
            param->pad_118 = nullptr;
        }
    }
}

bool DevFileNxTh::rfIsUsedChannel(unsigned int channel) {
    return m_impl->m_params[channel].m_isOpen;
}

bool DevFileNxTh::deleteFileBlock(const char* name) {
    mm::mtl::FixStr<256> path;
    getMediaPath(path, name);
    return nn::fs::DeleteFile(path.m_str).IsSuccess();
}

bool DevFileJobValidNxTh::asyncUpdate() {
    mm::mtl::FixStr<256> path;
    DevFileNxTh::getMediaPath(path, m_handle->m_path);
    nn::fs::DirectoryEntryType type;
    if (nn::fs::GetEntryType(&type, path.m_str).IsSuccess()) {
        m_handle->m_state = 9;
        m_result = 2;
        return true;
    }
    m_handle->m_state = 10;
    m_result = -1;
    return false;
}

bool DevFileArchiver::getFileInfo(MEDIA media, const char* path, FileInfoResult& result) const {
    const MediaArchives& list = m_medias[media];
    for (Archive* const* it = list.m_archives.begin(); it != list.m_archives.end(); ++it) {
        const Archive* archive = *it;
        int id = archive->m_dictionary.exactMatchSearch(path);
        if (id >= 0) {
            result.m_media = media;
            result.m_entry = archive->m_files[id];
            result.m_archiveName = archive->m_name84;
            return true;
        }
    }
    return false;
}

DevFileBlackListNxTh::~DevFileBlackListNxTh() {
    if (m_buffer != nullptr) {
        mtl::MemManager::deallocate(m_buffer, 0, false);
        m_buffer = nullptr;
    }
}

bool DevFileTh::isInitialized() {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        if (dev->m_impl == nullptr) {
            return false;
        }
        return dev->m_impl->m_initialized;
    }
    return false;
}

void* DevFileUtilNx::zlibAlloc(void*, unsigned int items, unsigned int size) {
    unsigned int total = items * size;
    void* ptr = mtl::MemManager::allocate(WorkRoot::getMemTMP(), total, 4, false, "no name", 0);
    if (size != 0 && ptr != nullptr) {
        memset(ptr, 0, size);
    }
    return ptr;
}

void DevFileUtilNx::zlibFree(void*, void* ptr) {
    mtl::MemManager::deallocate(ptr, 0, false);
}

namespace detail {
FileLoader::~FileLoader() {
    if (m_buffer != nullptr) {
        mtl::MemManager::deallocate(m_buffer, 0, false);
        m_buffer = nullptr;
    }
    if (m_isOpen) {
        m_isOpen = false;
        nn::fs::CloseFile(m_handle);
    }
}

void FileLoader::readFile() {
    if (!m_isOpen) {
        return;
    }
    long fileSize = 0;
    long size = nn::fs::GetFileSize(&fileSize, m_handle).IsSuccess() ? fileSize : -1;
    if (size < 1) {
        return;
    }
    m_size = size;
    m_buffer = malloc(size + 1);
    if (m_buffer == nullptr) {
        return;
    }
    if (nn::fs::ReadFile(m_handle, 0, m_buffer, size).IsFailure()) {
        if (m_buffer != nullptr) {
            mtl::MemManager::deallocate(m_buffer, 0, false);
            m_buffer = nullptr;
        }
        m_size = 0;
    }
}
}  // namespace detail

DevFileArchiveNx::DevFileArchiveNx(mtl::ALLOC_HANDLE handle)
    : m_alloc(handle), pad_18(0), m_impl(new (handle, nullptr, 0, 4, false) Param()) {
    __atomic_store_n(&m_impl->pad_17FC, 0, __ATOMIC_SEQ_CST);
    __atomic_store_n(&m_impl->pad_17F8, false, __ATOMIC_SEQ_CST);
}

DevFileArchiveNx::~DevFileArchiveNx() {
    m_impl->finalize();
}

bool DevFileArchiveNx::initialize() {
    if (pad_18 == 0) {
        for (unsigned long i = 1; i < m_impl->m_params.size(); i++) {
            Thread* thread = Thread::create("rfLoadThread", false, thFileLoader, &m_impl->m_params[i], 0x10000,
                                            WorkCpu::getSubWorkCPUID(), -3);
            if (thread != nullptr) {
                m_impl->m_params[i].m_owner = this;
                m_impl->m_params[i].m_thread = thread;
                thread->resume();
            }
        }
        pad_18 = 1;
    }
    return true;
}

unsigned int DevFileArchiveNx::thFileLoader(void* arg) {
    DevFileArchiveNx* owner = static_cast<DevFileArchiveNx*>(static_cast<OpenReadParam*>(arg)->m_owner);
    __atomic_fetch_add(&owner->m_impl->pad_17FC, 1, __ATOMIC_SEQ_CST);
    while (!DevFileTh::isInitialized()) {
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(100));
    }
    owner->thUpdate(arg);
    __atomic_fetch_sub(&owner->m_impl->pad_17FC, 1, __ATOMIC_SEQ_CST);
    return 0;
}

bool DevFileArchiveNx::finalize() {
    switch (pad_18) {
    case 1:
        __atomic_store_n(&m_impl->pad_17F8, true, __ATOMIC_SEQ_CST);
        for (unsigned long i = 1; i < m_impl->m_params.size(); i++) {
            if (m_impl->m_params[i].m_thread != nullptr) {
                m_impl->m_params[i].m_thread->setSignalEvent(true);
            }
        }
        pad_18 = 2;
        break;
    case 2:
        if (__atomic_load_n(&m_impl->pad_17FC, __ATOMIC_SEQ_CST) == 0) {
            pad_18 = 3;
        }
        break;
    case 3:
        for (unsigned long i = 1; i < m_impl->m_params.size(); i++) {
            if (m_impl->m_params[i].m_thread != nullptr) {
                m_impl->m_params[i].m_thread->release();
            }
        }
        pad_18 = 4;
        break;
    }
    return pad_18 == 4;
}

const char* DevFileArchiveNx::getMediaRootPath() const {
    return s_romMountMode ? "rom:" : s_dvdRoot.m_str;
}

DevFileJobTh* DevFileArchiveNx::createLoader(mtl::ALLOC_HANDLE handle) {
    return new (handle, nullptr, 0, 4, false) DevFileJobTh();
}

DevFileWriterTh* DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE) {
    return nullptr;
}

DevFileJobTh* DevFileArchiveNx::createFileValid(mtl::ALLOC_HANDLE handle) {
    return new (handle, nullptr, 0, 4, false) DevFileJobValidArcNxTh();
}

void DevFileArchiveNx::normalizeFileName(mm::mtl::FixStr<256>& name) {
    for (long i = 0; i < name.m_nLen; i++) {
        if (name.m_str[i] == '\\') {
            name.m_str[i] = '/';
        }
    }
    if (name.m_str[0] != '/') {
        name.insert(0, 1, '/');
    }
    int pos = name.findLast('/');
    if (pos == -1) {
        pos = name.findLast('\\');
    }
    int start = pos == -1 ? 0 : pos;
    if (start < name.m_nLen) {
        for (long i = start; i < name.m_nLen; i++) {
            if (static_cast<unsigned char>(name.m_str[i]) > 0x80) {
                return;
            }
        }
        for (long i = start; i < name.m_nLen; i++) {
            if (name.m_str[i] >= 'A' && name.m_str[i] <= 'Z') {
                name.m_str[i] += 0x20;
            }
        }
    }
}

bool DevFileArchiveNx::rfOpen(FileHandleTh* handle, const char* path) {
    OpenReadParam& param = get()->m_impl->m_params[handle->m_channel];
    mm::threading::WriteLockGuard lock(param.m_lock);
    DevFileTh::makeMediaFileName(param.m_path, path, handle->m_path);
    mm::mtl::FixStr<256> name(handle->m_path);
    normalizeFileName(name);
    DevFileArchiver::FileInfoResult result;
    bool found = mm::mtl::PtrSingleton<DevFileArchiver>::get()->getFileInfo(static_cast<MEDIA>(0), name.m_str, result);
    if (result.m_entry.pad_14 == -1 || !found) {
        return false;
    }
    if (result.m_entry.pad_10 & 1) {
        return false;
    }
    if (param.m_isOpen) {
        return true;
    }
    mm::mtl::FixStr<256> archivePath;
    DevFileTh::makeMediaFileName(archivePath, path, result.m_archiveName.m_str);
    if (nn::fs::OpenFile(&param.m_handle, archivePath.m_str, 1).IsFailure()) {
        return false;
    }
    param.m_isOpen = true;
    param.pad_10D = false;
    param.pad_10E = false;
    param.pad_110 = false;
    param.pad_190 = result.m_entry.pad_0;
    return true;
}

bool DevFileArchiveNx::rfIsBusy(FileHandleTh* handle) {
    DevFileArchiveNx* dev = get();
    if (handle == nullptr) {
        for (unsigned int i = 0; i < dev->m_impl->m_params.size(); i++) {
            OpenReadParam& param = dev->m_impl->m_params[i];
            mm::threading::ReadLockGuard lock(param.m_lock);
            if (!param.pad_10D || !param.m_isOpen) {
                continue;
            }
            return true;
        }
    } else {
        OpenReadParam& param = dev->m_impl->m_params[handle->m_channel];
        mm::threading::ReadLockGuard lock(param.m_lock);
        if (param.m_isOpen) {
            return param.pad_10D;
        }
    }
    return false;
}

// the result is false either way
bool DevFileArchiveNx::rfClose(FileHandleTh* handle) {
    OpenReadParam& param = get()->m_impl->m_params[handle->m_channel];
    mm::threading::WriteLockGuard lock(param.m_lock);
    if (param.pad_10F) {
        __atomic_store_n(&handle->m_canceled, true, __ATOMIC_SEQ_CST);
        handle->m_listener = nullptr;
        param.pad_110 = true;
    } else {
        if (param.pad_10D) {
            param.pad_10D = false;
        }
        nn::fs::CloseFile(param.m_handle);
        param.m_isOpen = false;
    }
    return false;
}

}  // namespace ml

// instantiated for ml::DevFileArchiveNx::getFilesBlock and getFileSize (not written yet)
template mm::mtl::FixStr<256> mm::mtl::FixStr<256>::operator+(const char*) const;

namespace ml {

bool DevFileArchiveNx::rfIsUsedChannel(unsigned int channel) {
    return m_impl->m_params[channel].m_isOpen;
}

void DevFileArchiveNx::tail() {
    for (OpenReadParam* param = m_impl->m_params.begin(); param != m_impl->m_params.end(); param++) {
        if (!param->pad_10D || param->pad_118 == nullptr) {
            continue;
        }
        mm::threading::WriteLockGuard lock(param->m_lock);
        if (!__atomic_load_n(&param->pad_118->m_canceled, __ATOMIC_SEQ_CST)) {
            FileHandleTh* handle = param->pad_118;
            if (handle->m_readSize != 0 && handle->m_readSize == handle->m_size) {
                param->pad_10D = false;
                if (handle->m_outData != nullptr) {
                    *handle->m_outData = handle->m_data;
                }
                if (handle->m_outSize != nullptr) {
                    *handle->m_outSize = handle->m_size;
                }
                if (IWorkEvent* listener = handle->m_listener) {
                    EventFileTh event;
                    event.m_kind = 2;
                    event.m_handle = handle;
                    event.m_allocHandle = handle->m_allocHandle;
                    event.m_allocator = handle->m_allocator;
                    event.m_path = handle->m_path;
                    event.m_data = handle->m_data;
                    event.m_result = handle->m_size;
                    event.pad_38 = handle->pad_68;
                    listener->OnFileEvent(&event);
                }
                param->pad_118 = nullptr;
            }
        } else if (!param->pad_10F) {
            if (param->pad_110) {
                nn::fs::CloseFile(param->m_handle);
                param->pad_110 = false;
            }
            FileHandleTh* handle = param->pad_118;
            param->pad_10D = false;
            if (handle->m_outData != nullptr) {
                *handle->m_outData = nullptr;
            }
            if (handle->m_outSize != nullptr) {
                *handle->m_outSize = -1;
            }
            if (IWorkEvent* listener = handle->m_listener) {
                EventFileTh event;
                event.m_kind = 4;
                event.m_handle = handle;
                event.m_allocHandle = handle->m_allocHandle;
                event.m_allocator = handle->m_allocator;
                event.m_path = handle->m_path;
                event.m_data = handle->m_data;
                event.m_result = handle->m_size;
                event.pad_38 = handle->pad_68;
                listener->OnFileEvent(&event);
            }
            param->pad_118 = nullptr;
        }
    }
}

// lbl_7100ECDE30: DevFileTh::initializePath stores its bool argument; Impl::initialize starts the archive accessors
// only when set (the name is not the original's; `used` keeps it at its own address as in the original)
__attribute__((used)) static bool s_useArchive;

unsigned int DevFileTh::INVALID_FILE_CHANNEL;

unsigned int DevFileTh::Impl::thFileLoader(void* arg) {
    Impl* impl = static_cast<Impl*>(arg);
    __atomic_fetch_add(&impl->m_loaderCount, 1, __ATOMIC_SEQ_CST);
    nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(100));
    while (!__atomic_load_n(&impl->m_stop, __ATOMIC_SEQ_CST)) {
        if (DevFileTh::isInitialized()) {
            impl->thUpdate();
        }
    }
    __atomic_fetch_sub(&impl->m_loaderCount, 1, __ATOMIC_SEQ_CST);
    return 0;
}

void DevFileTh::Impl::releaseRequest(DevFileJobTh* job) {
    FileHandleTh* handle = job->m_handle;
    handle->releaseData();
    delete job;
    m_handles.deallocate(handle);
}

bool DevFileTh::Impl::initialize() {
    bool result = true;
    for (int i = 0; i < 8; i++) {
        if (m_accessors[i] != nullptr && !m_accessorReady.test(i)) {
            if (m_accessors[i]->initialize()) {
                m_accessorReady.set(i);
            } else {
                result = false;
            }
        }
    }
    if (s_useArchive) {
        for (int i = 0; i < 8; i++) {
            if (m_archives[i] != nullptr) {
                result &= m_archives[i]->initialize();
            }
        }
    }
    if (!result) {
        return false;
    }
    loadBootArchive();
    m_initialized = true;
    return true;
}

bool DevFileTh::Impl::finalize() {
    bool result = true;
    for (int i = 0; i < 8; i++) {
        if (m_archives[i] != nullptr) {
            result &= m_archives[i]->finalize();
        }
    }
    for (int i = 0; i < 8; i++) {
        if (m_accessors[i] != nullptr) {
            result &= m_accessors[i]->finalize();
        }
    }
    return result;
}

void DevFileTh::Impl::updateCancel() {
    for (mm::mtl::FixedList<DevFileJobTh*, 640>::iterator it = m_jobs[0].begin(); it != m_jobs[0].end();) {
        DevFileJobTh* job = *it;
        if (job->m_cancel) {
            it = m_jobs[0].erase(m_jobs[0].find(job));
            releaseRequest(job);
        } else {
            ++it;
        }
    }
}

void DevFileTh::Impl::appendRequest(DevFileJobTh* job) {
    CS lock(m_jobCs);
    bool inserted = false;
    for (mm::mtl::FixedList<DevFileJobTh*, 640>::iterator it = m_jobs[0].begin(); it != m_jobs[0].end(); ++it) {
        FileHandleTh* queued = (*it)->m_handle;
        if (job->m_handle < queued) {
            m_jobs[0].insert(it, job);
            inserted = true;
            break;
        }
    }
    if (!inserted) {
        m_jobs[0].push_back(job);
    }
    m_jobCond.notify_one();
}

FileHandleTh* DevFileTh::Impl::writeFile(const char* path, IWorkEvent* listener, const void* data, int size, int arg) {
    CS lock(m_jobCs);
    DevFileAccessor* accessor = m_accessors[DevFileTh::getMediaType(path)];
    if (accessor == nullptr || !accessor->isValid()) {
        return nullptr;
    }
    FileHandleTh* handle;
    {
        CS lock2(m_jobCs);
        handle = m_handles.allocate();
        if (handle != nullptr) {
            handle->initWriter(path, const_cast<void*>(data), size, arg, listener);
            handle->pad_1f4 = true;
        }
    }
    if (handle == nullptr) {
        return nullptr;
    }
    if (arg < 0) {
        arg = 0;
        __atomic_store_n(&handle->pad_1f9, true, __ATOMIC_SEQ_CST);
    }
    handle->pad_14 = arg;
    if (handle->m_size == 0) {
        handle->m_size = 0;
    }
    if (handle->pad_14 > 0 || handle->m_size > 0) {
        __atomic_store_n(&handle->pad_1f5, true, __ATOMIC_SEQ_CST);
    }
    DevFileWriterTh* writer = accessor->createWriter(m_alloc);
    writer->m_handle = handle;
    appendRequest(writer);
    return handle;
}

bool DevFileTh::Impl::rfClose(FileHandleTh* handle) {
    CS lock(m_handleCs);
    MEDIA media = DevFileTh::getMediaType(handle->m_path);
    DevFileAccessor* accessor =
        __atomic_load_n(&handle->pad_1fc, __ATOMIC_SEQ_CST) ? m_archives[media] : m_accessors[media];
    if (accessor != nullptr) {
        accessor->rfClose(handle);
        handle->clear();
    }
    return false;
}
}  // namespace ml

// instantiated for ml::DevFileTh::Impl::thUpdate, ml::DevFileTh::Impl::updateCancel (not written yet)
template mm::mtl::FixedList<ml::DevFileJobTh*, 640>::iterator mm::mtl::FixedList<ml::DevFileJobTh*, 640>::erase(mm::mtl::FixedList<ml::DevFileJobTh*, 640>::iterator);

namespace ml {

void DevPerfNx::resumeApplication() {}

void DevTouchNx::updateDevice() {
    m_impl->update(this);
}

bool DevTouchNx::createDevice() {
    nn::hid::InitializeTouchScreen();
    return true;
}

void DevTouchNx::releaseDevice() {}

DevSettingNx::~DevSettingNx() {}

void DevSettingNx::initialize() {
    LangType lang = getLang();
    if (lang == 15) {
#line 40 "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../source\\device/nx/dev_setting_nx.cpp"
        NN_LOG("getLang() is DEV_LANG_INVALID!!\n");
    } else {
        DevSetting::m_defaultLang = lang;
    }
}

void DevSettingNx::finalize() {}

// the language a code names, 15 for none; a Chinese code matches zh-CN as zh-Hans and zh-TW as zh-Hant (getLang's
// and getLangList's inline loop; the name is not the original's)
static inline LangType findLangType(const char* code) {
    for (const DevSettingNx::LangCode& entry : s_langCodes) {
        if (strcmp(code, entry.m_code) == 0) {
            return entry.m_lang;
        }
        if (code[0] == 'z' && code[1] == 'h' && entry.m_code[0] == 'z' && entry.m_code[1] == 'h') {
            if (entry.m_code[3] == 'C') {
                if (strcmp(code, "zh-Hans") == 0) {
                    return entry.m_lang;
                }
            } else {
                if (strcmp(code, "zh-Hant") == 0) {
                    return entry.m_lang;
                }
            }
        }
    }
    return LangType(15);
}

LangType DevSettingNx::getLang() const {
    nn::settings::LanguageCode lang = nn::oe::GetDesiredLanguage();
    const char* code = lang.string;
    switch (g_devLangMode) {
    case 1:
        code = strcmp(lang.string, "ja") == 0 ? lang.string : "en-GB";
        break;
    case 0:
        if (strcmp(lang.string, "ja") == 0 || strncmp(lang.string, "zh-", 3) == 0) {
            code = "en-GB";
        }
        break;
    }
    return findLangType(code);
}

mm::mtl::FixedVector<LangType, 15>& DevSettingNx::getLangList(mm::mtl::FixedVector<LangType, 15>& list) const {
    list.clear();
    nn::settings::GetAvailableLanguageCodeCount();
    nn::settings::LanguageCode codes[15];
    int count = nn::settings::GetAvailableLanguageCodes(codes, 15);
    for (int i = 0; i < count; ++i) {
        LangType lang = findLangType(codes[i].string);
        if (lang != 15) {
            list.push_back(lang);
        }
    }
    return list;
}

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

DeviceNx::~DeviceNx() {
    if (m_onceInitialize) {
        delete mm::mtl::PtrSingleton<DevPerf>::get();
        if (mm::mtl::PtrSingleton<DevSetting>::get() != nullptr) {
            mm::mtl::PtrSingleton<DevSetting>::get()->m_impl->finalize();
        }
        delete mm::mtl::PtrSingleton<DevSetting>::get();
        nn::time::Finalize();
        m_onceInitialize = false;
    }
}

void DeviceNx::createDevicePort(const char*) {}

// the flag is unused (the original passes only the handle on)
void DevFileTh::cancel(FileHandleTh* handle, bool) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        dev->m_impl->cancelRequest(handle);
    }
}

DevFileTh::~DevFileTh() {}

void DevFileTh::wkUpdate() {}

bool DevFileTh::wkStandbyLogin() {
    if (!Device::isColdStartReady()) {
        return false;
    }
    if (!isInitialized()) {
        DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
        if (dev == nullptr || !dev->m_impl->initialize()) {
            return false;
        }
    }
    return WorkObj::wkStandbyLogin();
}

bool DevFileTh::wkStandbyLogout() {
    if (m_child.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
        DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
        if (dev != nullptr && !dev->m_impl->finalize()) {
            return false;
        }
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

void DevFileTh::wkTail() {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        dev->m_impl->tail();
    }
}

void DevFileTh::icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE) {}

bool DevFileTh::icbError(ml::CERR_STRUCT*) {
    return true;
}

void DevFileTh::registArchive(MEDIA media, const char* path, const char* name, const char* root) {
    if (mm::mtl::PtrSingleton<DevFileTh>::get() == nullptr) {
        dvfl_detail::ReserveArchiveParam param;
        param.m_media = media;
        param.m_path = path;
        param.m_name = name;
        param.m_root = root;
        dvfl_detail::g_reserveArchives.push_back(param);
        return;
    }
    DevFileParamTh param;
    param.m_hMem = WorkRoot::getMemTMP();
    param.m_path = path;
    param.m_align = 0x10;
    int size = 0;
    void* data = readFileBlock(param, &size, nullptr);
    if (data != nullptr && size > 0) {
        mm::mtl::PtrSingleton<DevFileArchiver>::get()->addArchive(media, data, size, root, name);
        operator delete(data);
    }
}

FileHandleTh* DevFileTh::readFile(const DevFileParamTh& param) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_impl->readFile(param);
    }
    return nullptr;
}

FileHandleTh* DevFileTh::writeFile(const char* path, IWorkEvent* listener, const void* data, int size, int arg) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_impl->writeFile(path, listener, data, size, arg);
    }
    return nullptr;
}

int DevFileTh::getRealName(const char* path, mm::mtl::FixStr<256>& out) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev == nullptr) {
        return -1;
    }
    MEDIA media = getMediaType(path);
    if (media >= 1 && media <= 3) {
        return -1;
    }
    for (const dvfl_detail::LoadMediaParam* it = dvfl_detail::g_loadMedia.begin(); it != dvfl_detail::g_loadMedia.end();
         ++it) {
        const dvfl_detail::LoadMediaParam& load = *it;
        auto getSize = [&](DevFileAccessor* accessor) -> int {
            if (accessor == nullptr) {
                return -1;
            }
            return accessor->getFileSize(path, nullptr, load.m_path.m_str);
        };
        if (*(dev->m_impl->m_archives + load.m_media) != nullptr) {
            int size = getSize(*(dev->m_impl->m_archives + load.m_media));
            if (size >= 0) {
                makeMediaFileName(out, load.m_path.m_str, path);
                return size;
            }
        }
        DevFileAccessor* accessor = *(dev->m_impl->m_accessors + load.m_media);
        if (accessor != nullptr && accessor->isValid()) {
            int size = accessor->getFileSize(path, nullptr, load.m_path.m_str);
            if (size >= 0) {
                makeMediaFileName(out, load.m_path.m_str, path);
                return size;
            }
        }
    }
    return -1;
}

void* DevFileTh::checkValidFile(const char* path, IWorkEvent* listener) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_impl->checkValidFile(path, listener);
    }
    return nullptr;
}

bool DevFileTh::checkValidFileBlock(const char* path) {
    return getFileSize(path, nullptr) >= 0;
}

namespace dvfl_detail {
mm::mtl::FixedVector<ReserveArchiveParam, 16> g_reserveArchives;
mm::mtl::FixedVector<LoadMediaParam, 16> g_loadMedia;
mm::mtl::FixedVector<IDevFileEvent*, 8> g_FileEventListener;
}  // namespace dvfl_detail

void DevFileTh::addMediaPath(MEDIA media, const char* path, int prio) {
    if (path != nullptr && path[0] != '\0') {
        dvfl_detail::addMediaPath(media, path, prio);
    }
}

FileHandleTh* DevFileTh::rfOpen(const DevFileParamTh& param) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_impl->rfOpen(param);
    }
    return nullptr;
}

inline bool DevFileTh::Impl::rfRead(FileHandleTh* handle, const DevFileParamTh& param) {
    CS lock(m_handleCs);
    unsigned int channel = handle->m_channel;
    MEDIA media = DevFileTh::getMediaType(handle->m_path);
    if (channel == DevFileTh::INVALID_FILE_CHANNEL) {
        return false;
    }
    DevFileAccessor* accessor =
        __atomic_load_n(&handle->pad_1fc, __ATOMIC_SEQ_CST) ? m_archives[media] : m_accessors[media];
    if (accessor == nullptr || !handle->pad_1f4) {
        return false;
    }
    return accessor->rfRead(handle, param);
}

bool DevFileTh::rfRead(FileHandleTh* handle, const DevFileParamTh& param) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_impl->rfRead(handle, param);
    }
    return false;
}

inline bool DevFileTh::Impl::rfIsBusy(FileHandleTh* handle) {
    CS lock(m_handleCs);
    unsigned int channel = handle->m_channel;
    MEDIA media = DevFileTh::getMediaType(handle->m_path);
    if (channel == DevFileTh::INVALID_FILE_CHANNEL) {
        return false;
    }
    DevFileAccessor* accessor =
        __atomic_load_n(&handle->pad_1fc, __ATOMIC_SEQ_CST) ? m_archives[media] : m_accessors[media];
    if (accessor == nullptr) {
        return false;
    }
    return accessor->rfIsBusy(handle);
}

bool DevFileTh::rfIsBusy(FileHandleTh* handle) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        Impl* impl = dev->m_impl.operator->();
        if (handle != nullptr) {
            return impl->rfIsBusy(handle);
        }
    }
    return false;
}

int DevFileTh::rfClose(FileHandleTh* handle) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        dev->m_impl->rfClose(handle);
    }
    return 0;
}

void DevFileTh::flushSave() {
    if (DevFileNxTh::m_mountSave) {
        nn::fs::CommitSaveData("save");
    }
}

bool DevFileTh::isNowSaving() {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        return dev->m_nowSaving;
    }
    return false;
}

bool DevFileTh::entryCb(IWorkEvent* listener) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        dev->m_impl->m_eventCb = listener;
        return true;
    }
    return false;
}

bool DevFileTh::removeCb(IWorkEvent*) {
    DevFileTh* dev = mm::mtl::PtrSingleton<DevFileTh>::get();
    if (dev != nullptr) {
        dev->m_impl->m_eventCb = nullptr;
        return true;
    }
    return false;
}

// reads the request's file from the first medium that has it, into a temporary buffer of 0x80000 bytes
bool DevFileReaderTh::asyncUpdate() {
    PathUtil::getFilePtrFromPath(m_handle->m_path);
    void* buffer = mtl::MemManager::allocate(WorkRoot::getMemTMP(), 0x80000, 0x1000, false, "no name", 0);
    bool read = false;
    for (Entry* it = m_entries.begin(); it != m_entries.end(); ++it) {
        m_handle->m_readSize = 0;
        if (it->m_accessor->readBlockSlice(m_handle, it->m_path, buffer, 0x80000)) {
            read = true;
            break;
        }
        if (m_cancel) {
            break;
        }
    }
    if (buffer != nullptr) {
        mtl::MemManager::deallocate(buffer, 0, false);
    }
    if (m_cancel) {
        __atomic_store_n(&m_handle->m_canceled, true, __ATOMIC_SEQ_CST);
        m_handle->m_state = 4;
        return false;
    }
    if (read) {
        __atomic_store_n(&m_handle->m_done, true, __ATOMIC_SEQ_CST);
        m_handle->m_state = 2;
        m_result = 2;
        return true;
    }
    __atomic_store_n(&m_handle->m_failed, true, __ATOMIC_SEQ_CST);
    m_handle->m_state = 4;
    m_result = -1;
    return false;
}

void* EventFileTh::moveFileData() {
    if (m_handle != nullptr) {
        return m_handle->moveData();
    }
    return nullptr;
}

FileResTh::FileResTh()
    : m_handle(nullptr), m_data(nullptr), m_size(-1), m_ownsData(true) {
    m_state = 0;
    m_allocator = nullptr;
    m_timeStamp = 0;
}

FileResTh::~FileResTh() {
    release();
}

bool FileResTh::isExist() const {
    return m_data != nullptr;
}

void FileResTh::release() {
    if (m_handle != nullptr) {
        m_handle->m_listener = nullptr;
        if (m_handle != nullptr) {
            DevFileTh::cancel(m_handle, false);
            m_handle = nullptr;
        }
    }
    if (m_ownsData && m_data != nullptr) {
        if (m_allocator != nullptr) {
            m_allocator->deallocate(m_data);
            m_data = nullptr;
            m_allocator = nullptr;
        } else {
            mtl::MemManager::deallocate(m_data, 0, false);
            m_data = nullptr;
        }
    }
    m_size = -1;
    m_state = 0;
    m_timeStamp = 0;
}

bool FileResTh::OnFileEvent(EventFileTh* event) {
    int state;
    if (event->m_kind == 2) {
        m_data = m_handle->moveData();
        m_size = m_handle->m_size;
        m_extra = m_handle->m_extra;
        m_timeStamp = m_handle->m_timeStamp;
        m_allocator = m_handle->m_allocator;
        state = 2;
    } else {
        m_size = -2;
        state = 3;
    }
    m_state = state;
    m_handle = nullptr;
    return true;
}

void FileResTh::setMem(void* data, int size, const char* path, bool ownsData) {
    m_ownsData = ownsData;
    m_data = data;
    m_size = size;
    SetName(PathUtil::getFilePtrFromPath(path));
}

DevFileArchiver::DevFileArchiver(mtl::ALLOC_HANDLE handle) : m_handle(handle), m_dicAllocator(handle) {
    for (int i = 0; i < 8; i++) {
        m_medias[i].m_media = static_cast<MEDIA>(i);
        m_medias[i].m_valid = true;
    }
}

DevFileArchiver::~DevFileArchiver() {
    for (int i = 0; i < 8; i++) {
        for (Archive** it = m_medias[i].m_archives.begin(); it != m_medias[i].m_archives.end(); ++it) {
            if (*it != nullptr) {
                delete *it;
            }
        }
        m_medias[i].m_archives.clear();
    }
}
}  // namespace ml

// instantiated for ml::DevFileArchiver::addArchive (not written yet); brings restoreBlock, restoreNinfo, reallocArray
template void ml::DevFileDictionary<int, ml::DevFileDicAllocator, -1, -2, true>::loadFromMemory(void*, unsigned long, void*, unsigned long);

namespace ml {

int DevPad::getPadMax() {
    return 11;
}

bool DevPad::isInitialized() {
    DevPad* dev = get();
    if (dev == nullptr) {
        return false;
    }
    return dev->isLoggedIn();
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

bool DevPad::wkStandbyLogin() {
    if (!dg::s_bIgnore && !createDevice()) {
        return false;
    }
    return WorkObj::wkStandbyLogin();
}

bool DevPad::wkStandbyLogout() {
    if (m_child.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
        releaseDevice();
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

void DevPad::viBeginFrame() {
    updateLocal();
}

namespace dg {
int s_nVSync = -1;
int s_nVSyncOld = -1;
bool s_bIgnore;
}  // namespace dg

void DevGraph::wkStandby() {
    WorkObj::wkStandby();
    ErrViewer::standby();
}

void DevGraph::wkUpdate() {
    ErrViewer::update();
}

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

void DevGraph::fontDraw(short x, short y, float scaleH, float scaleV, const char* text, const mm::Col4* col,
                        const mm::Col4* backCol, bool flag) {
    DevGraph* dev = get();
    if (dev == nullptr || dev->pad_228.h == 0 || dev->pad_228.w == 0) {
        return;
    }
    if (backCol != nullptr && backCol->a > 0.0f) {
        DebDraw* draw = DebDraw::get(-1);
        draw->setZComp(false);
        draw->setZWrite(false);
        draw->setCol(*backCol);
        draw->renderRectFill(x, y, fontGetWidth(text, static_cast<FONT_STYLE>(0), scaleH),
                             get() != nullptr ? get()->fontGetHeightSys(static_cast<FONT_STYLE>(0), scaleV) : 0);
    }
    get()->fontDrawSys(x, y, scaleH, scaleV, text, col, flag);
}

void DevGraph::grSetClearCol(const mm::Col4& col) {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->m_clearCol = col;
        dev->m_clearDepth = 1.0f;
    }
}

void DevGraph::addOuterRender(void (*render)()) {
    DevGraph* dev = get();
    if (dev != nullptr) {
        for (int i = 0; i < 4; i++) {
            if (dev->m_outerRender[i] == nullptr) {
                dev->m_outerRender[i] = render;
                break;
            }
        }
    }
}

void DevGraph::removeOuterRender(void (*render)()) {
    DevGraph* dev = get();
    if (dev != nullptr) {
        for (int i = 0; i < 4; i++) {
            if (dev->m_outerRender[i] == render) {
                dev->m_outerRender[i] = nullptr;
                break;
            }
        }
    }
}

void DevGraph::grInitContext() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->grInitContextSys();
        get()->m_que->flushViewport();
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

void DevGraph::renderBegin() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->cmdOpenDisplayListSys(0, false, false);
        grlib::CGLibManager* lib = mm::mtl::PtrSingleton<grlib::CGLibManager>::get();
        if (lib != nullptr) {
            lib->begin();
        }
        if (s_debDraw != nullptr) {
            s_debDraw->fastSetup();
        }
        get()->renderBeginSys();
    }
}

void DevGraph::renderEnd() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        for (int i = 0; i < 4; ++i) {
            if (dev->m_outerRender[i] != nullptr) {
                dev->m_outerRender[i]();
            }
        }
        dev->renderEndSys();
        grlib::CGLibManager* lib = mm::mtl::PtrSingleton<grlib::CGLibManager>::get();
        if (lib != nullptr) {
            lib->end();
        }
        cmdCloseDisplayList();
    }
}

void DevGraph::setRenderState(RSTAT state) {
    // lbl_7100EC7110, guard lbl_7100EC7138 (only setRenderState uses it). Proposed name, not the original's
    static CriticalSection s_cs;
    CS lock(s_cs);
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->m_renderState = state;
    }
}

void DevGraph::wkTail() {
    cmdTermDisplayListSys();
    m_que->flip();
    cmdSetupDisplayListSys();
    if (dg::s_nVSync != dg::s_nVSyncOld) {
        dg::s_nVSyncOld = dg::s_nVSync;
    }
    ErrViewer::tail();
    grlib::CGLibManager* lib = mm::mtl::PtrSingleton<grlib::CGLibManager>::get();
    if (lib != nullptr) {
        lib->tail();
    }
}

bool DevGraph::wkStandbyLogin() {
    if (!WorkCpu::isInitialized()) {
        return false;
    }
    m_que = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) DevGraphQue();
    m_work.m_que = m_que->createQue(0x600000);
    if (mm::mtl::PtrSingleton<grlib::CGLibManager>::get() == nullptr) {
        new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) grlib::CGLibManager();
    }
    pad_1f8 = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
    m_viewport = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
    pad_218 = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
    pad_228 = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
    pad_238 = mm::Rect<int>(0, 0, getRootWidth(), getRootHeight());
    ErrViewer::create();
    return WorkObj::wkStandbyLogin();
}

GraphQue* DevGraphQue::createQue(unsigned int size) {
    GraphQue* que = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) GraphQue(this, size);
    m_ques.push_back(que);
    return que;
}

void DevGraph::renderSync() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        dev->renderSyncSys();
        DebDraw::swap();
    }
}

void DebDraw::swap() {
    if (s_debDraw == nullptr) {
        return;
    }
    CacheDraw* cache = s_debDraw->m_cache;
    if (cache->m_suspendSwap == 0) {
        // closes the odd bank's open group
        CacheDraw::BUF* buf = cache->getBuf(true);
        if (buf->m_top < buf->m_cur) {
            buf->m_groupNum++;
            buf->m_group[buf->m_groupNum].m_end = buf->m_cur;
            buf->m_group[buf->m_groupNum].m_begin = buf->m_cur;
            buf->m_group[buf->m_groupNum].m_prim = cache->m_prim;
        }
    }
    cache = s_debDraw->m_cache;
    if (cache->m_suspendSwap == 0) {
        // empties the bank recorded next (every pass resets the current group, as the original does)
        CacheDraw::BUF* buf = cache->getBuf(false);
        buf->m_cur = buf->m_top;
        buf->m_groupNum = 0;
        buf->m_group[0].m_begin = nullptr;
        buf->m_group[0].m_end = nullptr;
        buf->m_group[0].m_prim = -1;
        for (int i = 0; i < 0x1ff; i++) {
            buf->m_group[buf->m_groupNum].m_end = nullptr;
            buf->m_group[buf->m_groupNum].m_begin = nullptr;
            buf->m_group[buf->m_groupNum].m_prim = -1;
        }
    }
    cache->m_fontScaleX = 1.0f;
    cache->m_fontScaleY = 1.0f;
    cache->m_zWrite = true;
}

void DevGraph::cb(RCB rcb) {
    if (get() == nullptr) {
        return;
    }
    for (reslist<DevGraphCB*>::iterator it = get()->m_cbList.begin(); it != get()->m_cbList.end(); ++it) {
        DevGraphCB* cb = *it;
        switch (static_cast<int>(rcb)) {
        case 0:
            cb->viBeginFrame();
            break;
        case 1:
            cb->viBeforeDrawDone();
            break;
        case 2:
            cb->viAfterDrawDone();
            break;
        case 3:
            cb->viAfterSync();
            break;
        case 4:
            cb->viAfterRenderCall();
            break;
        default:
            break;
        }
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

float DevGraph::getFrameSyncSec() {
    int vsync = dg::s_nVSync;
    float sec = getVSyncSec();
    if (vsync != 0) {
        return sec * dg::s_nVSync;
    }
    return sec + sec;
}

float DevGraph::getCost() {
    DevGraph* dev = get();
    if (dev != nullptr) {
        return dev->getCostSys();
    }
    return 0.0f;
}

void DebDraw::renderRectFill(int x, int y, int w, int h) {
    if (m_cache->renderRectFill(mm::Rect<int>(x, y, w, h))) {
        return;
    }
    renderRectFill(mm::Rect<int>(x, y, w, h));
}

bool DebDraw::getScreenPos(mm::Vec3& out, const mm::Vec3& pos) {
    mm::Vec3 view;
    view = mulPos(pad_040, pos - m_pos);
    if (view.z >= 0.0f) {
        return false;
    }
    float x = view.x * pad_100.m[0][0] + view.y * pad_100.m[1][0] + view.z * pad_100.m[2][0] + pad_100.m[3][0];
    float y = view.x * pad_100.m[0][1] + view.y * pad_100.m[1][1] + view.z * pad_100.m[2][1] + pad_100.m[3][1];
    float z = view.x * pad_100.m[0][2] + view.y * pad_100.m[1][2] + view.z * pad_100.m[2][2] + pad_100.m[3][2];
    float w = view.x * pad_100.m[0][3] + view.y * pad_100.m[1][3] + view.z * pad_100.m[2][3] + pad_100.m[3][3];
    x /= w;
    y /= w;
    z /= w;
    out.x = (x + 1.0f) * (DevGraph::get()->pad_228.w * 0.5f);
    out.y = (1.0f - y) * (DevGraph::get()->pad_228.h * 0.5f);
    out.z = z;
    return true;
}

void DebDraw::renderRect(int x, int y, int w, int h) {
    if (m_cache->renderRect(mm::Rect<int>(x, y, w, h))) {
        return;
    }
    renderRect(mm::Rect<int>(x, y, w, h));
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
DevGraph::DevGraph(const char* name, WorkObj* parent) : DevBase(name, parent, 8) {
    pad_310 = false;
    m_renderState = static_cast<RSTAT>(2);
    m_clearCol = mm::Col4::black;
    m_clearDepth = 1.0f;
    m_cbList.create(16, WorkUtil::getWorkMem());
    m_work.m_que = nullptr;
    m_work.pad_8 = 0;
    m_que = nullptr;
    m_frameSpd = 1.0f;
    for (int i = 0; i < 4; i++) {
        m_outerRender[i] = nullptr;
    }
}

DevGraph::~DevGraph() {}
}  // namespace ml

namespace mm {
Sphere::~Sphere() {}
}  // namespace mm

namespace ml {
DevGraphCB::DevGraphCB() {
    DevGraph* dev = DevGraph::get();
    if (dev != nullptr) {
        dev->m_cbList.push_back(this);
    }
}

GraphQue::~GraphQue() {
    if (m_buf[0] != nullptr) {
        mtl::MemManager::deallocate(m_buf[0], 0, false);
        m_buf[0] = nullptr;
    }
}
}  // namespace ml

template ml::reslist<ml::IDevFontInfo*>::~reslist();

template ml::reslist<ml::DevGraphCB*>::~reslist();

template ml::reslist<ml::GraphQue*>::~reslist();

namespace ml {

DevGraphCB::~DevGraphCB() {
    DevGraph* dev = DevGraph::get();
    if (dev != nullptr) {
        reslist<DevGraphCB*>& list = dev->m_cbList;
        reslist<DevGraphCB*>::iterator end = list.end();
        reslist<DevGraphCB*>::iterator it = list.begin();
        while (it != end) {
            reslist<DevGraphCB*>::iterator cur = it++;
            if (*cur == this) {
                list.erase(cur);
            }
        }
    }
}
}  // namespace ml

template ml::_reslist_base<ml::GraphQue*>::~_reslist_base();

namespace ml {
}  // namespace ml
