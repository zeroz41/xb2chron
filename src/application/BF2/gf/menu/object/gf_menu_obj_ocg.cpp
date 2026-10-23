#include "classes/gf/TUnk_B63AE0.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

TUnk_B63AE0::TUnk_B63AE0(unsigned int handle)
    : GfMenuObject(handle), m_count(0), m_seq(this), m_ctrl(-1), m_animHandle(0), m_number0(), m_number1(),
      m_result(0) {
    m_number0 = GfMenuReferenceNumber::create();
    m_number1 = GfMenuReferenceNumber::create();
}

// the destructor (0x7100448C54, 0x7100448DE0) is not here yet: see the report

// initialize (0x7100449078) is not here yet: see the report

void TUnk_B63AE0::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B63AE0::update() {
    m_seq.update();
    GfMenuObject::update();
}

// the listeners' reciveEvent (0x71004495A0, 0x7100449BD0), the open and close calls and the sequence's other jobs
// (0x7100448DE0-0x7100449078, 0x71004498C4, 0x7100449E78, 0x710044A3AC) are not here yet: see the report

bool TUnk_B63AE0::fn_710044A304() {
    if (m_ctrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
            return false;
        }
        m_ctrl = -1;
    }
    return true;
}

bool TUnk_B63AE0::fn_710044A348() {
    bool done = true;
    if (m_animHandle != 0) {
        ui::UIObjectAcc anim(m_animHandle);
        if (anim.isPlayingAnimation()) {
            done = false;
        } else {
            m_animHandle = 0;
        }
    }
    return done;
}

bool TUnk_B63AE0::fn_710044A5DC() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    ui::EventData event;
    event.m_type = 0x101;
    GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
    return true;
}

}  // namespace gf
