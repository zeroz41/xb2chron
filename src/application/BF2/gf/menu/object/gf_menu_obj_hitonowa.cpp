#include "classes/gf/GfMenuObjHitonowa.h"
#include "classes/gf/GfReqSmallCom.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjHitonowa.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/gf/GfMenuManager.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIStr.h"
#include "classes/fw/SoundManager.h"
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
#include "gf/GfDataHitonowa.h"
#include "algorithm"
#include "classes/gf/GfMenuQuestList.h"
#include "classes/gf/GfMenuReferenceNumber.h"

namespace gf {

inline bool GfMenuObjHitonowa::CompareEntry::operator()(const unsigned int& a, const unsigned int& b) const {
    return GfDataHitonowa::getEntryOn(a) < GfDataHitonowa::getEntryOn(b);
}

unsigned int GfMenuObjHitonowa::s_CurLevel;

GfMenuObjHitonowa::GfMenuObjHitonowa(unsigned int handle)
    : GfMenuObject(handle), pad_68(), m_roll(nullptr), pad_78(), m_levelNum(), m_nextNum(), pad_90(false), pad_94(0),
      m_resultDone(false), m_ids(), m_list(nullptr), m_seq(this), m_seq2(this), m_questList(nullptr), pad_AB0(),
      m_kind(0), m_listItems(nullptr), m_listCursor(nullptr), m_statusFadeOut(false), m_resultFadeOut(false),
      pad_ED2(false), pad_ED3(false), m_voice(nullptr) {
    ui::UIListInfoBase::SetupParam param;
    param.m_pageRowSize = 10;
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    for (int i = 0; i < 4; ++i) {
        m_idLists[i] = GfMenuIDList::create();
        if (m_idLists[i] != nullptr) {
            m_idLists[i]->setup(getAllocator(ALLOCATOR(0)), param);
        }
        m_selectLists[i] = ui::UISelectObjList::create(create);
        m_refNums[i] = GfMenuReferenceNumber::create();
    }
    m_listItems = ui::UISelectObjList::create(create);
    m_levelNum = GfMenuReferenceNumber::create();
    m_nextNum = GfMenuReferenceNumber::create();
    m_questList = GfMenuQuestList::create();
}

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

int GfMenuObjHitonowa::getNpcChange(unsigned int id, unsigned int& value) {
    unsigned char* fp = GfDataBdat::getFP(0x10F);
    if (fp == nullptr) {
        return id;
    }
    value = id;
    int result = 0;
    bool found = false;
    for (int i = 0; i < Bdat::getIdCount(fp); ++i) {
        int row = Bdat::getIdTop(fp) + i;
        unsigned int base = static_cast<unsigned short>(Bdat::getVal(fp, "base_npc", row));
        unsigned short condA = Bdat::getVal(fp, "cond_a", row);
        unsigned short npcA = Bdat::getVal(fp, "npc_a", row);
        if (base == id) {
            if (npcA != 0 && condA != 0 && GfGameCond::isGameCond(condA)) {
                value = npcA;
                result = 1;
            } else {
                unsigned short condB = Bdat::getVal(fp, "cond_b", row);
                unsigned short npcB = Bdat::getVal(fp, "npc_b", row);
                if (npcB != 0 && condB != 0 && GfGameCond::isGameCond(condB)) {
                    value = npcB;
                    result = 2;
                }
            }
            found = true;
        } else if (npcA == id) {
            if (condA == 0 || GfGameCond::isGameCond(condA)) {
                result = 1;
            } else {
                result = 0;
                value = base;
            }
            found = true;
        } else {
            unsigned short condB = Bdat::getVal(fp, "cond_b", row);
            unsigned short npcB = Bdat::getVal(fp, "npc_b", row);
            if (npcB == id) {
                if (condB == 0 || GfGameCond::isGameCond(condB)) {
                    result = 2;
                } else {
                    result = 0;
                    value = base;
                }
                found = true;
            }
        }
    }
    if (found) {
        return result;
    }
    if (GfDataNpc::isDispHitonowa(value)) {
        unsigned char* fp2 = GfDataBdat::getFP(0x110);
        if (fp2 != nullptr) {
            for (int i = 0; i < Bdat::getIdCount(fp2); ++i) {
                unsigned short base = Bdat::getVal(fp2, "base_npc", Bdat::getIdTop(fp2) + i);
                if (base == value) {
                    result = 1;
                }
            }
        }
    }
    return result;
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

void GfMenuObjHitonowa::dispResult(unsigned int handle, unsigned int id) {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    int slot = GfMenuObjUtil::getCtrlID(result.m_handle);
    if (slot != -1) {
        GfMenuObjUtil::stopCtrl(slot);
    }
    unsigned char* bdat;
    unsigned int msg;
    {
        ui::UIObjectAcc text(result.m_handle, "TXT_result_name");
        bool found = GfDataNpc::getName(bdat, msg, id);
        text.setDisp(found);
        if (found) {
            text.setText(ui::UIStr(bdat, msg));
        }
    }
    {
        ui::UIObjectAcc text(result.m_handle, "TXT_result_job");
        bool found = GfDataNpc::getJobMsg(bdat, msg, id);
        text.setDisp(found);
        if (found) {
            text.setText(ui::UIStr(bdat, msg));
        }
    }
    {
        ui::UIObjectAcc text(result.m_handle, "TXT_result_text");
        bool found = GfDataNpc::getResultMsg(bdat, msg, id);
        text.setDisp(found);
        if (found) {
            text.setText(ui::UIStr(bdat, msg));
        }
    }
    GfMenuObjUtil::setDockPos(result.m_handle, handle, 4, true);
    GfMenuObjUtil::addPos(result.m_handle, 0, 32);
    if (!m_resultFadeOut) {
        result.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(result.m_handle, param, nullptr);
        m_resultFadeOut = true;
    }
}

int GfMenuObjHitonowa::openTelop(unsigned int kind) {
    ui::UIObjectAcc telop(m_handle, "LAY_telop");
    telop.setDisp(true);
    telop.setAlpha(1.0f);
    {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.1f;
        GfMenuObjUtil::startCtrl(telop.m_handle, param, "LAY_telop_mask");
    }
    {
        ui::UIObjectAcc base(telop.m_handle, "IMG_telop_base");
        if (kind == 3) {
            base.startAnimation("start_max", false);
            m_animObject = base.m_handle;
        } else {
            base.startAnimation(kind == 1 ? "start_failed" : "start_success", false);
        }
    }
    int ctrl = -1;
    for (unsigned int i = 0; i < 4; i++) {
        mm::mtl::FixStr<32> name;
        name.format("TXT_telop@%02d", i + 1);
        ui::UIObjectAcc text(m_handle, name.m_str);
        if (kind == i) {
            text.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            ctrl = GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
        } else {
            text.setDisp(false);
        }
    }
    switch (kind) {
    case 0:
        GfMenuObjUtil::playSE(0x27);
        break;
    case 1:
        GfMenuObjUtil::playSE(0x32);
        break;
    case 2:
        GfMenuObjUtil::playJingle(0xd);
        break;
    case 3:
        GfMenuObjUtil::playJingle(0xc);
        break;
    }
    return ctrl;
}

void GfMenuObjHitonowa::setupEvent() {
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_list = ui::UISelectObjList::create(create);
    }
    const unsigned int kinds[] = {1, 2, 3, 0};
    if (pad_94 == 0) {
        for (int k = 0; k < 4; k++) {
            unsigned int kind = kinds[k];
            for (unsigned int i = 0; i < m_idLists[kind]->getSize(); i++) {
                unsigned int id = m_idLists[kind]->getContents(i).m_id;
                if (kind != 0) {
                    bool found = false;
                    for (unsigned int j = 0; j < m_ids.size(); j++) {
                        if (id == m_ids[j]) {
                            found = true;
                            break;
                        }
                    }
                    ui::UIObjectAcc(m_selectLists[kind]->getObject(i)).setAlpha(found ? 1.0f : 0.0f);
                    if (found) {
                        ui::UIObjectAcc icon(m_selectLists[kind]->getObject(i), "TXT_icon_new");
                        icon.setAlpha(0.0f);
                    }
                } else {
                    for (unsigned int j = 0; j < m_ids.size(); j++) {
                        if (id == m_ids[j]) {
                            ui::UIObjectAcc(m_selectLists[kind]->getObject(i)).setAlpha(0.0f);
                            break;
                        }
                    }
                }
            }
        }
        for (unsigned int j = 0; j < m_ids.size(); j++) {
            for (int k = 0; k < 4; k++) {
                unsigned int kind = kinds[k];
                if (kind == 0) {
                    continue;
                }
                for (unsigned int i = 0; i < m_idLists[kind]->getSize(); i++) {
                    if (m_idLists[kind]->getContents(i).m_id == m_ids[j]) {
                        m_list->addObject(m_selectLists[kind]->getObject(i));
                    }
                }
            }
        }
    } else if (pad_94 == 1) {
        for (int k = 0; k < 4; k++) {
            unsigned int kind = kinds[k];
            for (unsigned int i = 0; i < m_idLists[kind]->getSize(); i++) {
                unsigned int id = m_idLists[kind]->getContents(i).m_id;
                if (kind != 0) {
                    for (unsigned int j = 0; j < m_ids.size(); j++) {
                        if (id == m_ids[j]) {
                            ui::UIObjectAcc(m_selectLists[kind]->getObject(i)).setAlpha(0.0f);
                            break;
                        }
                    }
                } else {
                    float alpha = 0.0f;
                    for (unsigned int j = 0; j < m_ids.size(); j++) {
                        if (id == m_ids[j]) {
                            alpha = 1.0f;
                            break;
                        }
                    }
                    ui::UIObjectAcc(m_selectLists[kind]->getObject(i)).setAlpha(alpha);
                }
            }
        }
        for (unsigned int j = 0; j < m_ids.size(); j++) {
            for (int k = 0; k < 4; k++) {
                unsigned int kind = kinds[k];
                if (kind != 0) {
                    continue;
                }
                for (unsigned int i = 0; i < m_idLists[kind]->getSize(); i++) {
                    if (m_idLists[kind]->getContents(i).m_id == m_ids[j]) {
                        m_list->addObject(m_selectLists[kind]->getObject(i));
                    }
                }
            }
        }
    } else if (pad_94 == 2) {
        for (int k = 0; k < 4; k++) {
            unsigned int kind = kinds[k];
            if (kind == 0) {
                continue;
            }
            for (unsigned int i = 0; i < m_idLists[kind]->getSize(); i++) {
                unsigned int id = m_idLists[kind]->getContents(i).m_id;
                bool found = false;
                for (unsigned int j = 0; j < m_ids.size(); j++) {
                    if (id == m_ids[j]) {
                        found = true;
                        break;
                    }
                }
                ui::UIObjectAcc(m_selectLists[kind]->getObject(i)).setAlpha(0.0f);
            }
        }
        for (unsigned int j = 0; j < m_ids.size(); j++) {
            for (int k = 0; k < 4; k++) {
                unsigned int kind = kinds[k];
                if (kind == 0) {
                    continue;
                }
                for (unsigned int i = 0; i < m_idLists[kind]->getSize(); i++) {
                    if (m_idLists[kind]->getContents(i).m_id == m_ids[j]) {
                        ui::UIObjectAcc icon(m_selectLists[kind]->getObject(i), "TXT_icon_new");
                        icon.setAlpha(0.0f);
                        m_list->addObject(m_selectLists[kind]->getObject(i));
                    }
                }
            }
        }
    }
    {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        unsigned int count = main.countChild("LAY_location@%02d", 1);
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < count; i++) {
            name.format("LAY_location_num@%02d", i + 1);
            ui::UIObjectAcc num(main.m_handle, name.m_str);
            num.setAlpha(0.0f);
        }
    }
    m_cursor = 0;
}

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

void GfMenuObjHitonowa::unselectComplete(unsigned int handle) {
    ui::UIObjectAcc object(handle);
    int slot = GfMenuObjUtil::getCtrlID(handle);
    if (slot != -1) {
        ui::UIObjectAcc parent(object.getParentHandle());
        object.setIgnoreSize(false);
        object.setDispPriority(8);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x80000000;
        param.m_time = 0.3f;
        param.m_curve = 1;
        param.m_slot = slot;
        m_busyCtrl = GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
        ui::UIObjectAcc face(object.m_handle, "LAY_icon_face");
        GfMenuObjUtil::CtrlParam scale;
        scale.m_methods = 0x80000;
        scale.m_curve = 1;
        scale.m_scale = 1.0f;
        scale.m_time = 0.3f;
        GfMenuObjUtil::startCtrl(face.m_handle, scale, nullptr);
    }
}

bool GfMenuObjHitonowa::seqWaitStreaming() {
    for (int kind = 0; kind < 4; kind++) {
        for (unsigned int i = 0; i < m_selectLists[kind]->getSize(); i++) {
            ui::UIObjectAcc face(m_selectLists[kind]->getObject(i), "IMG_icon_face");
            if (face.isStreamImage() && face.isStreaming()) {
                return false;
            }
        }
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObjUtil::setCommonFadeIn(main.m_handle, 1, 0);
    return true;
}

bool GfMenuObjHitonowa::seqStartGet() {
    m_busyCtrl = openTelop(0);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(30);
    m_seq.addJob(&GfMenuObjHitonowa::seqCloseTelop);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addJob(&GfMenuObjHitonowa::seqMoveGet);
    return true;
}

bool GfMenuObjHitonowa::seqStartLost() {
    m_busyCtrl = openTelop(1);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(30);
    m_seq.addJob(&GfMenuObjHitonowa::seqCloseTelop);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addJob(&GfMenuObjHitonowa::seqMoveLost);
    return true;
}

bool GfMenuObjHitonowa::seqStartEntry() {
    m_seq.addJob(&GfMenuObjHitonowa::seqMoveEntry);
    return true;
}

bool GfMenuObjHitonowa::seqWaitNavi() {
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        GfMenuIDList* list = m_idLists[m_kind];
        unsigned int id = list->getContents(list->getIndex(false)).m_id;
        if (GfMenuLocation::getNpcNavigateID() == id) {
            GfMenuLocation::startNpcNavigate(0);
        } else {
            list = m_idLists[m_kind];
            GfMenuLocation::startNpcNavigate(list->getContents(list->getIndex(false)).m_id);
        }
    }
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

bool GfMenuObjHitonowa::seqChangeGet() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    ui::UIObjectAcc frame(object.m_handle, "IMG_icon_frame");
    frame.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "sample";
    param.m_motion = "fadein";
    param.m_setDefault = true;
    param.m_startFlags = 8;
    m_busyCtrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
    GfMenuObjUtil::playSE(0x12);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjHitonowa::seqDispResult);
    m_seq.addJob(&GfMenuObjHitonowa::seqConfirmGet);
    m_seq.addJob(&GfMenuObjHitonowa::seqInGet);
    return true;
}

bool GfMenuObjHitonowa::seqInGet() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_zoom_2";
    param.m_motion = "fade_out";
    param.m_setDefault = true;
    param.m_startFlags = 10;
    m_busyCtrl = GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjHitonowa::seqNextGet);
    return true;
}

bool GfMenuObjHitonowa::seqDispGet() {
    unsigned int count = 0;
    for (unsigned int i = 0; i < m_selectLists[0]->getSize(); i++) {
        ui::UIObjectAcc acc(m_selectLists[0]->getContents(i));
        float alpha;
        acc.getAlpha(alpha);
        if (alpha == 0.0f) {
            acc.setDisp(true);
            acc.setAlpha(1.0f);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_emotion";
            param.m_motion = "fade_in";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            param.m_delay = count * 0.1f;
            m_busyCtrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            acc.setAlpha(0.0f);
            count++;
        }
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

bool GfMenuObjHitonowa::seqWaitStreaming2() {
    for (int kind = 0; kind < 4; kind++) {
        for (unsigned int i = 0; i < m_selectLists[kind]->getSize(); i++) {
            ui::UIObjectAcc face(m_selectLists[kind]->getObject(i), "IMG_icon_face");
            if (face.isStreamImage() && face.isStreaming()) {
                return false;
            }
        }
    }
    return true;
}

bool GfMenuObjHitonowa::seqReturnMain() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

bool GfMenuObjHitonowa::seqChangeLost() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    ui::UIObjectAcc frame(object.m_handle, "IMG_icon_frame");
    frame.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x40000000;
    param.m_bright = 1.0f;
    param.m_time = 0.5f;
    param.m_curve = 1;
    m_busyCtrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addJob(&GfMenuObjHitonowa::seqChangeLost2);
    GfMenuObjUtil::playSE(0x1a);
    return true;
}

bool GfMenuObjHitonowa::seqChangeLost2() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    ui::UIObjectAcc frame(object.m_handle, "IMG_icon_frame");
    frame.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x40000002;
    param.m_time = 1.0f;
    param.m_curve = 2;
    m_busyCtrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjHitonowa::seqInLost);
    return true;
}

bool GfMenuObjHitonowa::seqInLost() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_zoom_2";
    param.m_motion = "fade_out";
    param.m_setDefault = true;
    param.m_startFlags = 10;
    m_busyCtrl = GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjHitonowa::seqNextLost);
    GfMenuObjUtil::playSE(0x38);
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

bool GfMenuObjHitonowa::seqMoveEntry() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    object.setDisp(true);
    object.setAlpha(1.0f);
    object.setScale(mm::Vec2(0.0f, 0.0f));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x80000;
    param.m_scale = 2.6f;
    param.m_curve = 1;
    param.m_time = 0.2f;
    m_busyCtrl = GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
    GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(30);
    m_seq.addJob(&GfMenuObjHitonowa::seqInEntry);
    GfMenuObjUtil::playSE(0x37);
    return true;
}

bool GfMenuObjHitonowa::seqInEntry() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    ui::UIObjectAcc newText(object.m_handle, "TXT_icon_new");
    ui::UIObjectAcc newIcon(object.m_handle, "LAY_icon_new");
    newText.setAlpha(1.0f);
    newIcon.setAddColor("white");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x40000000;
    param.m_time = 0.5f;
    param.m_setDefault = true;
    m_busyCtrl = GfMenuObjUtil::startCtrl(newIcon.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addWait(45);
    m_seq.addJob(&GfMenuObjHitonowa::seqMoveEntry2);
    dispStatus(object.m_handle, m_ids[m_cursor], getNpcGroup(m_ids[m_cursor]));
    mm::mtl::PtrSingleton<fw::SoundManager>::get()->playSe(0x33, nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
    return true;
}

bool GfMenuObjHitonowa::seqMoveEntry2() {
    ui::UIObjectAcc object(m_list->getObject(m_cursor));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x80000;
    param.m_scale = 1.0f;
    param.m_curve = 1;
    param.m_time = 0.2f;
    m_busyCtrl = GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
    GfMenuObjUtil::startCtrl(object.m_handle, param, nullptr);
    m_seq.addJob(&GfMenuObjHitonowa::seqCtrlWait);
    m_seq.addJob(&GfMenuObjHitonowa::seqNextEntry);
    // slides LAY_status out once (inlined in the original: its locals sit above this function's)
    [&] {
        ui::UIObjectAcc status(m_handle, "LAY_status");
        if (m_statusFadeOut) {
            GfMenuObjUtil::CtrlParam fade;
            fade.m_methods = 0x10000000;
            fade.m_motionLib = "cmn_fade_motion_lr";
            fade.m_motion = "fade_out_l";
            fade.m_setDefault = true;
            fade.m_startFlags = 10;
            fade.m_eventId = 2;
            GfMenuObjUtil::startCtrl(status.m_handle, fade, nullptr);
            GfMenuObjUtil::playSE(0xe);
            m_statusFadeOut = false;
        }
    }();
    GfMenuObjUtil::playSE(0x38);
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

// instantiated for gf::GfMenuObjHitonowa::delNpc (not written yet); 2.0.0's symbols name the element type
template mm::mtl::Vector<gf::MenuID>::iterator mm::mtl::Vector<gf::MenuID>::erase(gf::MenuID*);

namespace gf {

}  // namespace gf

// initialize's std::sort (not written yet) instantiates the libc++ sort core for the id lists.
template void std::__sort<gf::GfMenuObjHitonowa::CompareEntry&, unsigned int*>(unsigned int*, unsigned int*,
                                                                              gf::GfMenuObjHitonowa::CompareEntry&);

template bool gf::GfMenuSequence<gf::GfMenuObjHitonowa, 16>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjHitonowa, 16>>(const mm::mtl::Delegate<bool()>*);
