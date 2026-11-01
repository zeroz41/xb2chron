#include "classes/gf/GfMenuObjBattleTelop.h"
#include "classes/gf/GfMenuObjBattleTelop/MainListener.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf {

namespace {
// lbl_7100B5FD58: MainListener's telop layouts by the open event's index (0: none). The name is not the original's
const char* const s_telopLayouts[] = {nullptr, "TXT_unit"};
}  // namespace

void GfMenuObjBattleTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBattleTelop::update() {
    GfMenuObject::update();
}

inline int GfMenuObjBattleTelop::MainListener::startFade(unsigned int handle, int slot, unsigned int out, int eventId) {
    GfMenuObjUtil::PresetCtrlParam param;
    param.m_preset = 1;
    param.m_out = out;
    param.m_startFlag4 = true;
    param.m_slot = slot;
    param.m_eventId = eventId;
    return GfMenuObjUtil::startPresetCtrl(handle, param);
}

inline void GfMenuObjBattleTelop::MainListener::closeAttachedTelop(unsigned int id) {
    ui::UIObjectAcc telop(GfMenuObject::getAttachedObject(id));
    if (telop.m_object != nullptr) {
        ui::EventData close;
        close.m_type = 0x22;
        GfMenuObject::sendEvent(telop.searchChild("LAY_telop"), close, 0.0f);
    }
}

void GfMenuObjBattleTelop::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_ctrl = -1;
        m_state = State();
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::registTimer(acc.m_handle, 1, 2.0f, false);
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
        }
        break;
    case 0xB:
        if (event.m_param0 == 1) {
            closeAttachedTelop(0x4E);
        }
        break;
    case 0x21: {
        unsigned short index = event.m_param0Short;
        if (index == 0) {
            break;
        }
        m_state.m_active = 1;
        if (m_owner->m_telop != 0) {
            ui::UIObjectAcc(m_owner->m_telop).setDisp(false);
        }
        m_owner->m_telop = acc.searchChild(s_telopLayouts[index]);
        {
            ui::UIObjectAcc telop(m_owner->m_telop);
            if (telop.m_object == nullptr) {
                break;
            }
            telop.setDisp(true);
        }
        if (m_state.m_shown == 0) {
            acc.setDisp(true);
            int ctrl = startFade(acc.m_handle, m_ctrl, 0, 1);
            if (ctrl != -1) {
                GfMenuObject::releaseTimer(acc.m_handle);
                m_ctrl = ctrl;
            }
            m_state.m_shown = 1;
        }
        break;
    }
    case 0x22:
        m_state.m_active = 0;
        if (m_state.m_shown != 0) {
            startFade(acc.m_handle, m_ctrl, 1, 2);
            m_state.m_shown = 0;
        }
        GfMenuObject::releaseTimer(acc.m_handle);
        break;
    }
}

}  // namespace gf
