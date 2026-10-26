#include "classes/gf/TUnk_B62AA0.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"
#include "gf/GfMenuTypes.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjOperationInfo.h"

namespace gf {

unsigned int TUnk_B62AA0::s_gameValue;

void TUnk_B62AA0::fn_710041D238() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(0x12F, param);
}

void TUnk_B62AA0::fn_710041D268(ui::UIObjectAcc& image, unsigned int id) {
    image.fn_710069201C();
    int value = 0;
    int kind = fn_710041D2C8(id, &value);
    if (kind == 1) {
        image.setStreamImage2nd();
    } else if (kind == 2) {
        image.fn_7100691FD0();
    }
}

void TUnk_B62AA0::fn_710041D544() {
    s_gameValue = GfGameManager::fn_71002AC8E0();
    GfMenuLocation::fn_7100356980(0);
}

void TUnk_B62AA0::finalize() {
    GfMenuObject::finalize();
}

bool TUnk_B62AA0::fn_71004238EC() {
    m_seq.addJob(&TUnk_B62AA0::fn_7100426B44);
    return true;
}

bool TUnk_B62AA0::fn_7100423AE0() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x102;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

void TUnk_B62AA0::TUnk_B62B10::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 8) {
        if (event.m_param1 == 1) {
            m_owner->m_resultDone = true;
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

bool TUnk_B62AA0::fn_7100424A40() {
    if (m_busyCtrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_busyCtrl)) {
            return false;
        }
        m_busyCtrl = -1;
    }
    return true;
}

bool TUnk_B62AA0::fn_7100424A84() {
    ui::UIObjectAcc acc(m_handle, "LAY_image");
    ui::EventData event;
    event.m_type = 0x101;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

bool TUnk_B62AA0::fn_7100424BB4() {
    m_voice = GfGameVoice::playVoice("702870101");
    return true;
}

bool TUnk_B62AA0::fn_7100424BE4() {
    m_voice = GfGameVoice::playVoice("703750201");
    return true;
}

bool TUnk_B62AA0::fn_7100424C14() {
    m_voice = GfGameVoice::playVoice("704670105");
    return true;
}

bool TUnk_B62AA0::fn_7100424C44() {
    m_voice = GfGameVoice::playVoice("701580101");
    return true;
}

bool TUnk_B62AA0::fn_7100424C74() {
    if (m_voice != nullptr) {
        if (GfGameVoice::getResult(m_voice) < 3) {
            return false;
        }
        m_voice = nullptr;
    }
    return true;
}

void TUnk_B62AA0::TUnk_B62B88::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 0, 0);
        break;
    case 2:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setTerm();
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool TUnk_B62AA0::fn_7100425E60() {
    m_busyCtrl = fn_710041FBC8(3);
    return true;
}

bool TUnk_B62AA0::fn_7100425E8C() {
    return true;
}

bool TUnk_B62AA0::fn_7100425E94() {
    if (m_animObject == 0) {
        return true;
    }
    ui::UIObjectAcc acc(m_animObject);
    if (acc.isPlayingAnimation()) {
        return false;
    }
    m_animObject = 0;
    return true;
}

bool TUnk_B62AA0::fn_7100425EF8() {
    m_resultDone = false;
    ui::UIObjectAcc acc(m_handle, "LAY_image");
    GfMenuObject::sendOpenEvent(acc.m_handle, 1, 0.0f);
    return true;
}

bool TUnk_B62AA0::fn_7100425F44() {
    return m_resultDone;
}

bool TUnk_B62AA0::fn_7100425F4C() {
    m_busyCtrl = fn_710041FBC8(2);
    return true;
}

bool TUnk_B62AA0::fn_7100425F78() {
    m_seq.addJob(&TUnk_B62AA0::fn_710042603C);
    m_seq.addJob(&TUnk_B62AA0::fn_710042621C);
    return true;
}

bool TUnk_B62AA0::fn_710042621C() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

}  // namespace gf
