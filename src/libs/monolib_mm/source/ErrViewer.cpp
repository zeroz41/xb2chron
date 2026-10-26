#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/ErrViewer.h"
#include "classes/ml/DevClock.h"
#include "classes/ml/DevGraph.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/WorkCpu.h"
#include "ml/MlMem.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"

namespace ml {

int ErrViewer::s_nHandle;

ErrViewer::ErrViewer()
    : m_state(0),
      m_deniedClock(0),
      m_active(false),
      m_destroyRequest(false),
      m_terminated(false),
      m_errorDisp(false),
      m_homeMenuDenied(false),
      m_ownedMemSize(0),
      m_ownedMem(nullptr) {
    m_cs = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) CriticalSection();
    s_nHandle = 0;
    WorkCpu::addBackgroundListener(this);
}

ErrViewer::~ErrViewer() {
    if (m_errorDisp) {
        WorkControl::pause(false, "SYS:ERR");
    }
    WorkCpu::removeBackgroundListener(this);
    if (m_cs != nullptr) {
        delete m_cs;
        m_cs = nullptr;
    }
}

void ErrViewer::upErrViewer() {}

void ErrViewer::standby() {
    ErrViewer* self = get();
    if (self == nullptr) {
        return;
    }
    switch (self->m_state) {
    case 0:
        self->setup();
        self->m_active = true;
        DevGraph::addOuterRender(fnRender);
        self->m_state++;
    case 1:
        self->upErrViewer();
        if (self->m_destroyRequest) {
            CS lock(*self->m_cs);
            for (mm::mtl::FixedList<ERRINFO*, 32>::iterator it = self->m_errList.begin(); it != self->m_errList.end();
                 ++it) {
                ERRINFO*& info = *it;
                if (info->m_mem != nullptr) {
                    mtl::MemManager::deallocate(info->m_mem, 0, false);
                    info->m_mem = nullptr;
                }
                if (info != nullptr) {
                    delete info;
                    info = nullptr;
                }
            }
            self->m_errList.clear();
            self->m_state++;
        }
        break;
    case 2:
        DevGraph::removeOuterRender(fnRender);
        self->m_active = false;
        self->term();
        self->m_terminated = true;
        self->m_state++;
        break;
    }
    self->callbackError(ERR_CALL_STANDBY);
}

void ErrViewer::fnRender() {
    ErrViewer* self = get();
    if (self != nullptr && ((self->m_active && !self->m_destroyRequest) || self->m_homeMenuDenied)) {
        self->callbackError(ERR_CALL_RENDER);
    }
}

void ErrViewer::callbackError(ERR_CALL call) {
    if (!isExistError()) {
        return;
    }
    CS lock(*m_cs);
    ERRINFO* info = *m_errList.begin();
    if (info->m_call == call && info->m_listener != nullptr && !info->m_listener->icbError(info->m_handle) &&
        info->m_dispTimeInit > 0) {
        info->m_dispTime = info->m_dispTimeInit;
    }
}

void ErrViewer::tail() {
    ErrViewer* self = get();
    if (self == nullptr) {
        return;
    }
    self->callbackError(ERR_CALL_TAIL);
    if (self->m_homeMenuDenied) {
        float time;
        DevClock::getTimeNow(time, self->m_deniedClock);
        if (time >= 3.0f) {
            self->m_homeMenuDenied = false;
        }
    }
}

void ErrViewer::update() {
    ErrViewer* self = get();
    if (self != nullptr) {
        self->callbackError(ERR_CALL_UPDATE);
    }
}

ErrViewer* ErrViewer::create() {
    ErrViewer* self = get();
    if (self == nullptr) {
        self = new (MlMem::getProductMem(), nullptr, 0, 4, false) ErrViewer();
    }
    return self;
}

bool ErrViewer::destroy() {
    ErrViewer* self = get();
    if (self == nullptr) {
        return true;
    }
    if (!self->m_destroyRequest) {
        self->m_destroyRequest = true;
    }
    if (!self->m_terminated) {
        return false;
    }
    delete self;
    return true;
}

void ErrViewer::setup() {}

void ErrViewer::term() {
    if (m_ownedMem != nullptr) {
        mtl::MemManager::deallocate(m_ownedMem, 0, false);
        m_ownedMem = nullptr;
    }
}

void ErrViewer::bkgHomeMenu(bool) {}

void ErrViewer::bkgHomeMenuDenied() {
    if (!WorkCpu::isHomeMenuEnable()) {
        DevClock::getClockNow(m_deniedClock);
        m_homeMenuDenied = true;
    }
}

}  // namespace ml
