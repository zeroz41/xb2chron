#include "classes/gf/TUnk_B62AA0.h"
#include "classes/gf/GfReqSmallCom.h"
#include "gf/GfMenuObjUtil.h"
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
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Pnt.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfMenuIDList.h"
#include "gf/GfDataBlade.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/AssetData.h"

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

unsigned int TUnk_B62AA0::fn_710041E870(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0xA8);
    unsigned short cond = Bdat::getVal(fp, "Condition2", id);
    if (cond != 0 && GfGameCond::isGameCond(cond)) {
        return static_cast<unsigned short>(Bdat::getVal(fp, "AreaNumber3", id));
    }
    cond = Bdat::getVal(fp, "Condition1", id);
    if (cond != 0 && GfGameCond::isGameCond(cond)) {
        return static_cast<unsigned short>(Bdat::getVal(fp, "AreaNumber2", id));
    }
    return static_cast<unsigned short>(Bdat::getVal(fp, "AreaNumber1", id));
}

void TUnk_B62AA0::update() {
    m_seq.update();
    m_seq2.update();
    GfMenuObject::update();
}

void TUnk_B62AA0::fn_710041F864() {
    ui::UIObjectAcc level(m_handle, "LAY_level");
    level.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    GfMenuObjUtil::setPresetCtrl_Fadein(3, param, -1);
    param.m_setDefault = true;
    param.m_startFlags = 8;
    GfMenuObjUtil::startCtrl(level.m_handle, param, nullptr);
    bool max = s_gameValue == 6;
    level.setDispChild(true, "TXT_level_num");
    ui::UIObjectAcc(level.m_handle, "TXT_level_num").setAlpha(max ? 0.0f : 1.0f);
    level.setDispChild(true, "TXT_level_max");
    ui::UIObjectAcc(level.m_handle, "TXT_level_max").setAlpha(max ? 1.0f : 0.0f);
}

// the list kinds fn_710042113C and fn_7100420B00 walk (lbl_71009C1D58; the name is not the original's)
static const unsigned int s_newIconKinds[] = {1, 2, 3};

void TUnk_B62AA0::fn_710042113C() {
    for (int i = 0; i < 3; i++) {
        unsigned int kind = s_newIconKinds[i];
        GfMenuIDList* ids = m_idLists[kind];
        for (unsigned int j = 0; j < ids->getSize(); j++) {
            unsigned int id = ids->getContents(j).m_id;
            ui::UIObjectAcc icon(m_selectLists[kind]->getObject(j), "TXT_icon_new");
            icon.setAlpha(GfDataBlade::fn_710024DF88(id) ? 0.0f : 1.0f);
        }
    }
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

bool TUnk_B62AA0::fn_7100424978() {
    ui::UIObjectAcc image(m_handle, "IMG_image@01");
    if (image.isStreaming()) {
        return false;
    }
    ui::UIObjectAcc layout(m_handle, "LAY_image");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 1;
    param.m_curve = 1;
    param.m_time = GfMenuObjUtil::getPresetCtrlTime(6);
    m_busyCtrl = GfMenuObjUtil::startCtrl(layout.m_handle, param, nullptr);
    return true;
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

bool TUnk_B62AA0::fn_7100424AD8() {
    ui::UIObjectAcc image(m_handle, "IMG_image@01");
    if (image.isStreaming()) {
        return false;
    }
    {
        ui::UIObjectAcc telop(m_handle, "TXT_telop@04");
        telop.setDisp(false);
        ui::UIObjectAcc base(m_handle, "IMG_telop_base");
        base.startAnimation("end_max", false);
    }
    ui::UIObjectAcc layout(m_handle, "LAY_image");
    layout.setDisp(true);
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

bool TUnk_B62AA0::fn_7100424D68() {
    int ctrl;
    {
        ui::UIObjectAcc telop(m_handle, "LAY_telop");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.2f;
        ctrl = GfMenuObjUtil::startCtrl(telop.m_handle, param, nullptr);
    }
    m_busyCtrl = ctrl;
    return true;
}

bool TUnk_B62AA0::fn_710042537C() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    unsigned int id = m_ids[m_cursor];
    fn_710041F998(object.m_handle, id);
    ui::UIObjectAcc result(m_handle, "LAY_result");
    GfMenuObject::enableInput(result.m_handle);
    GfMenuObjOperationInfo::add(result.m_handle, 0, 0, 0);
    m_resultDone = false;
    fn_7100569228();
    return true;
}

bool TUnk_B62AA0::fn_7100425440() {
    if (!m_resultDone) {
        return false;
    }
    ui::UIObjectAcc result(m_handle, "LAY_result");
    if (m_resultFadeOut) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(result.m_handle, param, nullptr);
        m_resultFadeOut = false;
    }
    return true;
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

bool TUnk_B62AA0::fn_7100426A30() {
    fn_710041F0A8(0, m_ids[m_cursor]);
    fn_710041EB48();
    if (++m_cursor < m_list->getSize()) {
        m_seq.addJob(&TUnk_B62AA0::fn_7100426270);
    } else {
        m_seq.addJob(&TUnk_B62AA0::fn_7100425F78);
    }
    return true;
}

bool TUnk_B62AA0::fn_7100427230() {
    if (++m_cursor < m_list->getSize()) {
        m_seq.addJob(&TUnk_B62AA0::fn_7100426B44);
    } else {
        m_seq.addJob(&TUnk_B62AA0::fn_7100425F78);
    }
    return true;
}
}  // namespace gf

// instantiated for gf::TUnk_B62AA0::fn_710041F0A8 (not written yet)
template mm::mtl::Vector<fw::AssetCsvb*>::iterator mm::mtl::Vector<fw::AssetCsvb*>::erase(fw::AssetCsvb**);

namespace gf {

}  // namespace gf
