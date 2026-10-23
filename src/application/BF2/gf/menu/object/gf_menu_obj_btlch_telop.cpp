#include "classes/gf/TUnk_B607D8.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

TUnk_B607D8::TUnk_B607D8(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_ctrl(-1), m_number(), m_wave(0) {
    m_number = GfMenuReferenceNumber::create();
}

TUnk_B607D8::~TUnk_B607D8() {
    m_number = nullptr;
}

// initialize (0x71003B0A14) is not here yet: see the report

void TUnk_B607D8::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B607D8::update() {
    if (m_ctrl != -1 && !GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
        m_ctrl = -1;
    }
    m_seq.update();
    GfMenuObject::update();
}

// the open and close calls, the listener's reciveEvent (0x71003B0FC4) and the sequence's other jobs are not here
// yet: see the report

bool TUnk_B607D8::fn_71003B1DA4() {
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

bool TUnk_B607D8::fn_71003B219C() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x22;
    GfMenuObject::sendEvent(main.m_handle, event, 0.0f);
    return true;
}

bool TUnk_B607D8::fn_71003B2558() {
    if (m_ctrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
            return false;
        }
        m_ctrl = -1;
    }
    return true;
}

bool TUnk_B607D8::fn_71003B259C() {
    return true;
}

bool TUnk_B607D8::fn_71003B26B4() {
    return true;
}

}  // namespace gf
