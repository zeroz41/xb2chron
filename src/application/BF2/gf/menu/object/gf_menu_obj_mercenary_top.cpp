#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/gf/GfMenuObjMercenaryTop/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/gf/GfMenuObjMercenaryTop/MainListener.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "ui/EventData.h"

namespace gf {

void GfMenuObjMercenaryTop::registOpenParam(OpenParam const& openParam) {
    GfMenuTypes::Param param;
    param.m_menuId = openParam.m_value;
    GfMenuFullScreen::registLayerParam(0x34, param);
}

void GfMenuObjMercenaryTop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryTop::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjMercenaryTop::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 2:
    case 0x22: {
        if (!m_owner->m_canClose) {
            acc.setTerm();
            break;
        }
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x24: {
        GfMenuObject::disableInput(acc.searchChild("LAY_zone"));
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->m_canClose = false;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryTop::seqExit() {
    if (m_exitHandle != 0) {
        ui::EventData event;
        event.m_type = 0x100;
        GfMenuObject::sendEvent(m_exitHandle, event, 0.0f);
        m_exitHandle = 0;
    }
    return true;
}

}  // namespace gf
