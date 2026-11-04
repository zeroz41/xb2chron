#include "classes/gf/GfMenuObjHitonowa.h"
#include "classes/gf/GfReqSmallCom.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjHitonowa.h"
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
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Pnt.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfMenuIDList.h"
#include "gf/GfDataBlade.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/AssetData.h"
#include "gf/GfDataNpc.h"

namespace gf {

unsigned int GfMenuObjHitonowa::s_CurLevel;

void GfMenuObjHitonowa::setBootFromEvent() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(0x12F, param);
}

void GfMenuObjHitonowa::setFaceStream(ui::UIObjectAcc& image, unsigned int id) {
    image.resetStreamImageEx();
    unsigned int value = 0;
    int kind = getNpcChange(id, value);
    if (kind == 1) {
        image.setStreamImage2nd();
    } else if (kind == 2) {
        image.setStreamImage3rd();
    }
}

void GfMenuObjHitonowa::setupGame() {
    s_CurLevel = GfGameManager::getHitonowaLevel();
    GfMenuLocation::startNpcNavigate(0);
}

void GfMenuObjHitonowa::finalize() {
    GfMenuObject::finalize();
}

unsigned int getNpcGroup(unsigned int id) {
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

void GfMenuObjHitonowa::update() {
    m_seq.update();
    m_seq2.update();
    GfMenuObject::update();
}

void GfMenuObjHitonowa::dispLevel() {
    ui::UIObjectAcc level(m_handle, "LAY_level");
    level.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    GfMenuObjUtil::setPresetCtrl_Fadein(3, param, -1);
    param.m_setDefault = true;
    param.m_startFlags = 8;
    GfMenuObjUtil::startCtrl(level.m_handle, param, nullptr);
    bool max = s_CurLevel == 6;
    level.setDispChild(true, "TXT_level_num");
    ui::UIObjectAcc(level.m_handle, "TXT_level_num").setAlpha(max ? 0.0f : 1.0f);
    level.setDispChild(true, "TXT_level_max");
    ui::UIObjectAcc(level.m_handle, "TXT_level_max").setAlpha(max ? 1.0f : 0.0f);
}

// the list kinds refreshNew and updateQuestIcon walk (lbl_71009C1D58; the name is not the original's)
static const unsigned int s_newIconKinds[] = {1, 2, 3};

void GfMenuObjHitonowa::refreshNew() {
    for (int i = 0; i < 3; i++) {
        unsigned int kind = s_newIconKinds[i];
        GfMenuIDList* ids = m_idLists[kind];
        for (unsigned int j = 0; j < ids->getSize(); j++) {
            unsigned int id = ids->getContents(j).m_id;
            ui::UIObjectAcc icon(m_selectLists[kind]->getObject(j), "TXT_icon_new");
            icon.setAlpha(GfDataNpc::isHitonowaNewFlag(id) ? 0.0f : 1.0f);
        }
    }
}

bool GfMenuObjHitonowa::seqStartEntry() {
    m_seq.addJob(&GfMenuObjHitonowa::seqMoveEntry);
    return true;
}

bool GfMenuObjHitonowa::seqDialogEnd() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x102;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

void GfMenuObjHitonowa::ConfirmListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
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

bool GfMenuObjHitonowa::seqWaitStreamingImg() {
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

bool GfMenuObjHitonowa::seqCtrlWait() {
    if (m_busyCtrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_busyCtrl)) {
            return false;
        }
        m_busyCtrl = -1;
    }
    return true;
}

bool GfMenuObjHitonowa::seqStartImage() {
    ui::UIObjectAcc acc(m_handle, "LAY_image");
    ui::EventData event;
    event.m_type = 0x101;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

bool GfMenuObjHitonowa::seqWaitStreamingImgFirst() {
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

bool GfMenuObjHitonowa::seqImageVoiceA() {
    m_voice = GfGameVoice::playVoice("702870101");
    return true;
}

bool GfMenuObjHitonowa::seqImageVoiceB() {
    m_voice = GfGameVoice::playVoice("703750201");
    return true;
}

bool GfMenuObjHitonowa::seqImageVoiceC() {
    m_voice = GfGameVoice::playVoice("704670105");
    return true;
}

bool GfMenuObjHitonowa::seqImageVoiceD() {
    m_voice = GfGameVoice::playVoice("701580101");
    return true;
}

bool GfMenuObjHitonowa::seqVoiceWait() {
    if (m_voice != nullptr) {
        if (GfGameVoice::getResult(m_voice) < 3) {
            return false;
        }
        m_voice = nullptr;
    }
    return true;
}

void GfMenuObjHitonowa::BgListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
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

bool GfMenuObjHitonowa::seqCloseTelop() {
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

bool GfMenuObjHitonowa::seqDispResult() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    unsigned int id = m_ids[m_cursor];
    dispResult(object.m_handle, id);
    ui::UIObjectAcc result(m_handle, "LAY_result");
    GfMenuObject::enableInput(result.m_handle);
    GfMenuObjOperationInfo::add(result.m_handle, 0, 0, 0);
    m_resultDone = false;
    SCOM_FIELD_VOICE::createHitonowaGet();
    return true;
}

bool GfMenuObjHitonowa::seqConfirmGet() {
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

bool GfMenuObjHitonowa::seqStartLevelMax() {
    m_busyCtrl = openTelop(3);
    return true;
}

bool GfMenuObjHitonowa::seqLevelMaxFadeIn() {
    return true;
}

bool GfMenuObjHitonowa::seqAnimWait() {
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

bool GfMenuObjHitonowa::seqOpenImage() {
    m_resultDone = false;
    ui::UIObjectAcc acc(m_handle, "LAY_image");
    GfMenuObject::sendOpenEvent(acc.m_handle, 1, 0.0f);
    return true;
}

bool GfMenuObjHitonowa::seqWaitImage() {
    return m_resultDone;
}

bool GfMenuObjHitonowa::seqStartLevelUp() {
    m_busyCtrl = openTelop(2);
    return true;
}

bool GfMenuObjHitonowa::seqReturn() {
    m_seq.addJob(&GfMenuObjHitonowa::seqWaitStreaming2);
    m_seq.addJob(&GfMenuObjHitonowa::seqReturnMain);
    return true;
}

bool GfMenuObjHitonowa::seqReturnMain() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

bool GfMenuObjHitonowa::seqNextLost() {
    delNpc(0, m_ids[m_cursor]);
    refreshComplete();
    if (++m_cursor < m_list->getSize()) {
        m_seq.addJob(&GfMenuObjHitonowa::seqMoveLost);
    } else {
        m_seq.addJob(&GfMenuObjHitonowa::seqReturn);
    }
    return true;
}

bool GfMenuObjHitonowa::seqNextEntry() {
    if (++m_cursor < m_list->getSize()) {
        m_seq.addJob(&GfMenuObjHitonowa::seqMoveEntry);
    } else {
        m_seq.addJob(&GfMenuObjHitonowa::seqReturn);
    }
    return true;
}
}  // namespace gf

// instantiated for gf::GfMenuObjHitonowa::delNpc (not written yet)
template mm::mtl::Vector<fw::AssetCsvb*>::iterator mm::mtl::Vector<fw::AssetCsvb*>::erase(fw::AssetCsvb**);

namespace gf {

}  // namespace gf
