#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfMenuObjMercenaryForm/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/ApplyListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/BlImgListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/FormListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/PresetListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/UnitListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/StartListener.h"
#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "gf/GfDataBlade.h"
#include "mm/mtl/FixStr.h"
#include <algorithm>
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "ui/EventData.h"
#include "mm/mtl/Vector.h"

namespace gf {

GfMenuObjMercenaryForm::GfMenuObjMercenaryForm(unsigned int handle)
    : GfMenuObject(handle), m_teamId(0), m_unitBlades(nullptr), m_listBlades(nullptr), m_unitSelect(nullptr),
      m_unitCursor(nullptr), m_listSelect(nullptr), m_listCursor(nullptr), m_presetSelect(nullptr),
      m_presetCursor(nullptr), m_context(nullptr), m_numbers(), pad_100(0), m_waitFrames(0), m_seq(this),
      m_seqStep(false), m_subSeq(this), m_bladeIds(), pad_8F0(false), m_voice(nullptr), m_leaveVoice(-1),
      m_leaveRequest(false), m_voiceStopped(false) {
    for (int i = 0; i < 8; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
    }
    m_context = GfMenuCallContext::create();
}

GfMenuObjMercenaryForm::~GfMenuObjMercenaryForm() {
    for (int i = 0; i < 8; i++) {
        m_numbers[i] = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_presetBlades[i] != nullptr) {
            m_presetBlades[i]->release();
            m_presetBlades[i] = nullptr;
        }
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_presetCursor != nullptr) {
        m_presetCursor->release();
        m_presetCursor = nullptr;
    }
    if (m_presetSelect != nullptr) {
        m_presetSelect->release();
        m_presetSelect = nullptr;
    }
    if (m_listCursor != nullptr) {
        m_listCursor->release();
        m_listCursor = nullptr;
    }
    if (m_listSelect != nullptr) {
        m_listSelect->release();
        m_listSelect = nullptr;
    }
    if (m_unitCursor != nullptr) {
        m_unitCursor->release();
        m_unitCursor = nullptr;
    }
    if (m_unitSelect != nullptr) {
        m_unitSelect->release();
        m_unitSelect = nullptr;
    }
    if (m_listBlades != nullptr) {
        m_listBlades->release();
        m_listBlades = nullptr;
    }
    if (m_unitBlades != nullptr) {
        m_unitBlades->release();
        m_unitBlades = nullptr;
    }
    if (m_formSelect != nullptr) {
        m_formSelect->release();
        m_formSelect = nullptr;
    }
    if (m_formCursor != nullptr) {
        m_formCursor->release();
        m_formCursor = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_presetLists[i] != nullptr) {
            m_presetLists[i]->release();
            m_presetLists[i] = nullptr;
        }
    }
}

void GfMenuObjMercenaryForm::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryForm::update() {
    if (!m_seq.m_jobs.empty()) {
        if (m_leaveRequest && GfMenuObjUtil::isVoiceSkip()) {
            m_seqStep = false;
            m_seq.clear();
            m_seq.addJob(&GfMenuObjMercenaryForm::seqLeaveBlade);
            if (m_leaveVoice != -1) {
                GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_leaveVoice));
                m_leaveVoice = -1;
            }
            m_leaveRequest = false;
        }
    }
    m_seq.update();
    m_subSeq.update();
    if (m_waitFrames != 0) {
        m_waitFrames--;
    }
    GfMenuObject::update();
}


bool GfMenuObjMercenaryForm::seqLeaveBlade() {
    ui::UIObjectAcc image(m_handle, "LAY_bl_img");
    bool done;
    if (!m_seqStep) {
        {
            ui::EventData event;
            event.m_type = 0x101;
            GfMenuObject::sendEvent(image.m_handle, event, 0.0f);
        }
        mm::mtl::FixStr<32> motion;
        for (unsigned int i = 0; i < m_unitSelect->getSize(); i++) {
            motion.format("mnu090_anim_sub_%d", i + 1);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = motion.m_str;
            param.m_motion = "end";
            GfMenuObjUtil::startCtrl(m_unitSelect->getObject(i), param, nullptr);
        }
        {
            ui::UIObjectAcc effect(m_handle, "IMG_start_eff");
            effect.setDisp(true);
            effect.startAnimation("end", false);
        }
        done = false;
        m_seqStep = true;
        m_leaveRequest = false;
    } else {
        if (m_leaveVoice != -1 && GfMenuObjUtil::isVoiceSkip()) {
            GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_leaveVoice));
            m_leaveVoice = -1;
        }
        if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.m_handle))) {
            m_seq.addJob(&GfMenuObjMercenaryForm::seqDepartureEnd);
            done = true;
            m_seqStep = false;
        } else {
            done = false;
        }
    }
    return done;
}

void GfMenuObjMercenaryForm::setDetailBladePos(unsigned int handle) {
    ui::UIObjectAcc detail(m_handle, "LAY_form_bl_detail_bl");
    if (handle == 0) {
        detail.setDisp(false);
    } else {
        ui::UIObjectAcc blade(handle);
        mm::Rect<short> rect;
        blade.getRect(rect, 1);
        mm::Pnt<short> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        detail.setPos(pos);
        detail.setDisp(true);
    }
}

void GfMenuObjMercenaryForm::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 2: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

inline void GfMenuObjMercenaryForm::sendOpenOrFormMain(unsigned int handle, int param) {
    unsigned int target = handle != 0 ? handle : ui::UIObjectAcc(m_handle, "LAY_form_main").m_handle;
    ui::EventData open;
    open.m_type = 0x21;
    open.m_param0 = param;
    GfMenuObject::sendEvent(target, open, 0.0f);
}

inline void GfMenuObjMercenaryForm::sendCloseOrFormMain(unsigned int handle) {
    unsigned int target = handle != 0 ? handle : ui::UIObjectAcc(m_handle, "LAY_form_main").m_handle;
    ui::EventData close;
    close.m_type = 0x22;
    GfMenuObject::sendEvent(target, close, 0.0f);
}

void GfMenuObjMercenaryForm::FormListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        pad_0C = 0;
        pad_10 = 0;
        GfMenuObjOperationInfo::setGuideText(0x25, 0);
        GfMenuObjCmnStatus::openBlStatus(0, -1);
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 2) {
            m_owner->sendOpenOrFormMain(acc.searchSibiling("LAY_leader"), 0);
        }
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x102: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObjCmnStatus::closeBlStatus();
        break;
    }
    case 0x103: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->sendOpenOrFormMain(acc.searchChild("LAY_form_list_bl"), 1);
        GfMenuObjOperationInfo::setGuideText(0x25, 0);
        GfMenuObjCmnStatus::openBlStatus(0, -1);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::UnitListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, 0, 6);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_unitBlades->setIndex(index);
            m_owner->m_unitSelect->setIndex(index);
            if (index < m_owner->m_unitBlades->getSize()) {
                GfMenuReference::setReferenceBladeID(0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
            } else {
                GfMenuReference::setReferenceBladeID(0, 0);
            }
            m_owner->setDetailBladePos(m_owner->m_unitSelect->getSelectObject());
            m_owner->updateBladeCount(false, false);
            unsigned int blade = m_owner->m_unitBlades->getContents(index).m_blade;
            if (blade == 0) {
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
            } else {
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
            }
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8: {
        int index = event.m_param0;
        if (event.m_param1 == 10) {
            if (index < m_owner->m_unitBlades->getSize()) {
                {
                    GfMenuBladeList* list = m_owner->m_unitBlades;
                    list->m_list.erase(list->m_list.begin() + (unsigned int)index);
                    list->subSize(1);
                    list->m_changed = true;
                }
                if (index < m_owner->m_unitBlades->getSize()) {
                    GfMenuReference::setReferenceBladeID(0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
                } else {
                    GfMenuReference::setReferenceBladeID(0, 0);
                }
                m_owner->updateBladeCount(false, false);
                m_owner->refreshBladeList();
                if (m_owner->m_unitBlades->getSize() == 0) {
                    GfMenuObject::disableFSInput();
                    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
                    m_owner->m_unitCursor->setDisp(false);
                    m_owner->sendOpenOrFormMain(acc.searchSibiling("LAY_form_list_bl"), 0);
                }
                unsigned int blade = GfMenuReference::getReferenceBladeID(0);
                if (blade == 0) {
                    GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
                } else {
                    bool valid = GfMenuObjUtil::isValidBlade(blade);
                    GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                    if (valid) {
                        GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                    }
                }
                GfMenuObjUtil::playSECommonCancel();
            }
        } else if (event.m_param1 == 12) {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            if (blade != 0 && GfMenuObjUtil::isValidBlade(blade)) {
                if (!GfDataBlade::isBladeLock(blade)) {
                    GfMenuObjUtil::setBladeFavorite(blade, true);
                    GfMenuObjUtil::playSECommonDecide();
                } else {
                    GfMenuObjUtil::setBladeFavorite(blade, false);
                    GfMenuObjUtil::playSECommonCancel();
                }
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
            }
        }
        break;
    }
    case 9:
        if (event.m_param0 == 2) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->m_unitCursor->setDisp(false);
            m_owner->updateBladeCount(false, true);
            m_owner->sendOpenOrFormMain(acc.searchSibiling("LAY_form_list_bl"), 0);
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    case 0x21: {
        GfMenuObject::enableFSInput(1);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        m_owner->m_unitCursor->setDisp(true);
        GfMenuReference::setReferenceBladeID(0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
        unsigned int blade = m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade;
        if (blade == 0) {
            GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
        } else {
            bool valid = GfMenuObjUtil::isValidBlade(blade);
            GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
            if (valid) {
                GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
            }
        }
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_form_apply"), 0, 0.0f);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::refreshBladeList() {
    ui::UIObjectAcc acc(m_handle, "LAY_form_list_bl");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_listBlades->getPageSize(); i++) {
        const MenuBladeInfo& info = m_listBlades->getContents(m_listBlades->getPageIndex(i));
        bool selectable = GfMenuObjUtil::isBladeSelectable(info.m_blade, nullptr);
        name.format("IMG_form_list_bl_face@%02d", i + 1);
        {
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            unsigned short* last = m_bladeIds.end();
            if (selectable || std::find(m_bladeIds.begin(), last, static_cast<unsigned short>(info.m_blade)) != last) {
                face.setMulColor("white");
            } else {
                face.setMulColor("gray");
            }
        }
        bool member = false;
        for (unsigned int j = 0; j < m_unitBlades->getSize(); j++) {
            if (m_unitBlades->getContents(j).m_blade == info.m_blade) {
                member = true;
                break;
            }
        }
        name.format("IMG_form_list_bl_check@%02d", i + 1);
        {
            ui::UIObjectAcc check(acc.m_handle, name.m_str);
            check.setDisp(member);
        }
    }
}

// ListListener is not here yet

bool GfMenuObjMercenaryForm::chkUnitBladeList(unsigned int blade) {
    for (unsigned int i = 0; i < m_unitBlades->getSize(); i++) {
        if (m_unitBlades->getContents(i).m_blade == blade) {
            return true;
        }
        if (GfMenuObjUtil::isBladeHana(blade) && GfMenuObjUtil::isBladeHana(m_unitBlades->getContents(i).m_blade)) {
            return true;
        }
    }
    return false;
}

bool GfMenuObjMercenaryForm::seqConfirmHana() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x10F);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
            if (!chkUnitBladeList(blade)) {
                MenuBladeInfo info;
                info.m_blade = blade;
                info.m_creator = GfDataBlade::getCreator(blade);
                m_unitBlades->addContents(info);
                updateBladeCount(false, true);
                SCOM_FIELD_VOICE::createMercenariesIn(info.m_blade);
            }
        }
        sendOpenOrFormMain(acc.searchSibiling("LAY_form_list_bl"), 0);
        done = true;
        m_seqStep = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqConfirmRemoveBladeSet() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
        if (GfMenuObjUtil::isBladeHana(blade)) {
            GfMenuManager::openCommonWindow(0x10F);
        } else {
            GfMenuManager::openCommonWindow(199);
        }
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            unsigned int leave = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
            unsigned short* last = m_bladeIds.end();
            if (std::find(m_bladeIds.begin(), last, static_cast<unsigned short>(leave)) == last) {
                m_bladeIds.push_back(leave);
            }
            unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
            if (!chkUnitBladeList(blade)) {
                MenuBladeInfo info;
                info.m_blade = blade;
                info.m_creator = GfDataBlade::getCreator(blade);
                m_unitBlades->addContents(info);
                updateBladeCount(false, true);
                SCOM_FIELD_VOICE::createMercenariesIn(info.m_blade);
            }
        }
        sendOpenOrFormMain(acc.searchSibiling("LAY_form_list_bl"), 0);
        done = true;
        m_seqStep = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqReturnMissionSelect() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x9F);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            if (m_bladeIds.size() != 0) {
                m_seq.addJob(&GfMenuObjMercenaryForm::seqRevertBladeSet);
            } else {
                GfMenuObject::returnFSSubLayer(this);
            }
        } else {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            sendOpenOrFormMain(acc.searchSibiling("LAY_form_list_bl"), 0);
        }
        done = true;
        m_seqStep = false;
    }
    return done;
}

void GfMenuObjMercenaryForm::PresetListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 6:
        if (event.m_param0 != -1) {
            m_owner->m_idList->setIndex(event.m_param0);
            m_owner->m_presetSelect->setIndex(m_owner->m_idList->getIndex(true));
            int row = m_owner->m_idList->getRowOffset();
            for (int i = 0; i < 3; i++) {
                GfDataMercenaries::Preset* preset = GfDataMercenaries::getPreset(row + i);
                GfMenuBladeList* list = m_owner->m_presetLists[i];
                MenuBladeInfo info;
                list->clear();
                for (int j = 0; j < 6; j++) {
                    info.m_blade = preset->m_blades[j];
                    info.m_creator = info.m_blade != 0 ? GfDataBlade::getCreator(info.m_blade) : 0;
                    list->addContents(info);
                }
                m_owner->m_numbers[i + 4]->m_value = row + i + 1;
            }
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->m_seq.clear();
            if (m_load == 0) {
                m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetSave);
            } else {
                m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetLoad);
            }
        } else if (event.m_param1 == 2) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->sendCloseOrFormMain(acc.m_handle);
            m_owner->sendOpenOrFormMain(acc.searchSibiling("LAY_form_menu"), 0);
        }
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObject::enableFSInput(3);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        m_load = event.m_param0;
        m_owner->m_idList->setIndex(0);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_idList);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::ApplyListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(true);
        ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
        base.startAnimation("non", false);
        acc.setDispChild(false, "LAY_form_apply_caption");
        m_open = 0;
        break;
    }
    case 0xC:
        if (m_open == 1) {
            ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
            base.startAnimation("loop", false);
        }
        break;
    case 0x21:
        if (m_open == 0) {
            ui::UIObjectAcc caption(acc.m_handle, "LAY_form_apply_caption");
            caption.setDisp(true);
            caption.setAlpha(1.0f);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(caption.m_handle, param, nullptr);
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
                base.startAnimation("start", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
            }
            acc.setDisp(true);
            m_open = 1;
        }
        break;
    case 0x22: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
        base.startAnimation("non", false);
        {
            ui::UIObjectAcc caption(acc.m_handle, "LAY_form_apply_caption");
            int slot = GfMenuObjUtil::getCtrlID(caption.m_handle);
            if (slot != -1) {
                GfMenuObjUtil::stopCtrl(slot);
            }
            caption.setDisp(false);
        }
        m_open = 0;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryForm::seqPresetSave() {
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x43);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            unsigned int index = m_idList->getIndex(true);
            GfMenuBladeList* list = m_presetLists[index];
            GfDataMercenaries::Preset* preset = GfDataMercenaries::getPreset(index);
            MenuBladeInfo info;
            list->clear();
            for (unsigned int i = 0; i < 6; i++) {
                if (i >= m_unitBlades->getSize()) {
                    break;
                }
                preset->m_blades[i] = m_unitBlades->getContents(i).m_blade;
                info.m_blade = preset->m_blades[i];
                info.m_creator = info.m_blade != 0 ? GfDataBlade::getCreator(info.m_blade) : 0;
                list->addContents(info);
            }
        }
        m_seq.addWait(30);
        m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetEnd);
        done = true;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqPresetLoad() {
    GfDataMercenaries::Preset* preset = GfDataMercenaries::getPreset(m_idList->getIndex(true));
    MenuBladeInfo info;
    m_unitBlades->clear();
    for (int i = 0; i < 6; i++) {
        unsigned int blade = preset->m_blades[i];
        if (blade != 0 && !GfMenuObjUtil::isBladeSelectable(blade, nullptr)) {
            blade = 0;
        }
        info.m_blade = blade;
        info.m_creator = blade != 0 ? GfDataBlade::getCreator(blade) : 0;
        m_unitBlades->addContents(info);
    }
    m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetEnd);
    return true;
}

// LeaderListener is not here yet

void GfMenuObjMercenaryForm::BlImgListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        break;
    case 0x21:
        if (GfMenuReference::getReferenceBladeID(0) != 0) {
            acc.setDisp(true);
            acc.setAlpha(1.0f);
            m_owner->m_subSeq.clear();
            m_owner->m_subSeq.addJob(&GfMenuObjMercenaryForm::seqOpenImage);
        }
        break;
    case 0x22: {
        ui::UIObjectAcc image(acc.m_handle, "IMG_leader_bl_img");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_r";
        param.m_startFlags = 2;
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        break;
    }
    case 0x100: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu090_anim_leader";
        param.m_motion = "start";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjUtil::playSE(0xF);
        break;
    }
    case 0x101: {
        acc.setScale(mm::Vec2(1.0f, 1.0f));
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu090_anim_leader";
        param.m_motion = "end";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjUtil::playSE("se_fld_allmap_503");
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

// seqConfirmStart is not here yet (the closest candidate is 4 words off)

bool GfMenuObjMercenaryForm::seqOpenImage() {
    ui::UIObjectAcc image(m_handle, "IMG_leader_bl_img");
    bool done;
    if (!image.isStreaming()) {
        ui::UIObjectAcc layout(m_handle, "LAY_bl_img");
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        layout.setLayout(image.m_handle, "character");
        GfMenuObjUtil::ImageParam imageParam;
        if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            image.getScale(scale);
            scale.x *= imageParam.m_scale;
            scale.y *= imageParam.m_scale;
            image.setScale(scale);
            GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
        }
        image.setAlpha(1.0f);
        GfMenuObjUtil::CtrlParam fade;
        fade.m_methods = 0x10000000;
        fade.m_motionLib = "cmn_fade_motion_lr";
        fade.m_motion = "fade_in_r";
        fade.m_startFlags = 8;
        fade.m_setDefault = true;
        GfMenuObjUtil::startCtrl(image.m_handle, fade, nullptr);
        image.setAlpha(0.0f);
        GfMenuObjUtil::playSE("se_fld_allmap_503");
        done = true;
    } else {
        image.setAlpha(0.0f);
        done = false;
    }
    return done;
}

void GfMenuObjMercenaryForm::StartListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21: {
        // the selected team blade moves to the top (its copy's slot is reused by the names below)
        {
            MenuBladeInfo info = m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false));
            {
                GfMenuBladeList* list = m_owner->m_unitBlades;
                unsigned int index = list->getIndex(false);
                list->m_list.erase(list->m_list.begin() + index);
                list->subSize(1);
                list->m_changed = true;
            }
            GfMenuBladeList* list = m_owner->m_unitBlades;
            if (list->getSize() == 0) {
                list->addContents(info);
            } else {
                list->m_list.insert(list->m_list.begin(), info);
                list->addSize(1);
                list->m_changed = true;
            }
        }
        mm::mtl::FixStr<32> name;
        m_owner->m_unitSelect->clear();
        for (unsigned int i = 0; i < 5; i++) {
            if (i < m_owner->m_unitBlades->getSize() - 1) {
                name.format("LAY_mis_start_bl@%02d", i + 1);
                m_owner->m_unitSelect->addObject(acc.searchChild(name.m_str));
            }
            acc.setDispChild(false, name.m_str);
        }
        acc.setDisp(true);
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqDepartureStart);
        break;
    }
    case 0x22: {
        GfMenuObjMercenaryTop::OpenParam param;
        param.m_value = 0;
        GfMenuObjMercenaryTop::registOpenParam(param);
        GfMenuObject::returnFSSubLayer(acc.m_handle, 2);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryForm::seqDepartureStart() {
    m_seqStep = false;
    m_seq.addJob(&GfMenuObjMercenaryForm::seqApperBlade);
    m_voice = SCOM_FIELD_VOICE::createMercenariesLeader(GfMenuReference::getReferenceBladeID(0));
    m_voiceStopped = false;
    return true;
}

bool GfMenuObjMercenaryForm::seqApperBlade() {
    if (m_voice != nullptr) {
        if (GfMenuObjUtil::isVoiceSkip()) {
            GfGameVoice::playStop(m_voice);
            m_voice = nullptr;
            m_voiceStopped = true;
        } else if (m_voice != nullptr) {
            if (GfGameVoice::getResult(m_voice) >= 3) {
                m_voice = nullptr;
            } else {
                return false;
            }
        }
    }
    ui::UIObjectAcc image(m_handle, "LAY_bl_img");
    bool done;
    if (!m_seqStep) {
        {
            ui::EventData event;
            event.m_type = 0x100;
            GfMenuObject::sendEvent(image.m_handle, event, 0.0f);
        }
        {
            ui::UIObjectAcc start(m_handle, "LAY_start");
            mm::mtl::FixStr<32> name;
            mm::mtl::FixStr<32> motion;
            for (unsigned int i = 0; i < m_unitSelect->getSize(); i++) {
                unsigned int blade = m_unitBlades->getContents(i + 1).m_blade;
                name.format("IMG_mis_start_bl@%02d", i + 1);
                {
                    ui::UIObjectAcc face(start.m_handle, name.m_str);
                    start.setLayout(face.m_handle, "mnu090_anim_sub_1");
                    GfMenuObjUtil::ImageParam imageParam;
                    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
                        mm::Vec2 scale;
                        face.getScale(scale);
                        scale.x *= imageParam.m_scale;
                        scale.y *= imageParam.m_scale;
                        face.setScale(scale);
                        GfMenuObjUtil::addPos(face.m_handle, imageParam.m_x, imageParam.m_y);
                    }
                }
                motion.format("mnu090_anim_sub_%d", i + 1);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = motion.m_str;
                param.m_motion = "start";
                GfMenuObjUtil::startCtrl(m_unitSelect->getObject(i), param, nullptr);
            }
        }
        done = false;
        m_leaveRequest = false;
        m_seqStep = true;
    } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.m_handle))) {
        if (!m_voiceStopped) {
            m_leaveVoice = SCOM_FIELD_VOICE::createMercenariesStart(m_unitBlades->getContents(0).m_blade);
            m_leaveRequest = true;
            m_seq.addWait(60);
        }
        m_seq.addJob(&GfMenuObjMercenaryForm::seqLeaveBlade);
        done = true;
        m_seqStep = false;
    } else {
        done = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqDepartureEnd() {
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x25);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        ui::UIObjectAcc start(m_handle, "LAY_start");
        sendCloseOrFormMain(start.m_handle);
        unsigned int teamId = GfMenuReference::getReferenceTeamID();
        unsigned int mission = GfMenuReference::getReferenceMissionID();
        for (unsigned int i = 0; i < m_unitBlades->getSize(); i++) {
            GfGameMercenaries::addTeamMember(teamId, m_unitBlades->getContents(i).m_blade);
        }
        GfGameMercenaries::orderMission(teamId, mission);
        done = true;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqPresetEnd() {
    ui::UIObjectAcc preset(m_handle, "LAY_preset");
    sendCloseOrFormMain(preset.m_handle);
    sendOpenOrFormMain(preset.searchSibiling("LAY_form_menu"), 0);
    return true;
}

bool GfMenuObjMercenaryForm::seqRevertBladeSet() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(200);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        GfMenuObject::returnFSSubLayer(this);
        done = true;
        m_seqStep = false;
    }
    return done;
}
}  // namespace gf

// instantiated for gf::GfMenuObjMercenaryForm::StartListener::reciveEvent (not written yet)
template mm::mtl::Vector<gf::MenuBladeInfo>::iterator mm::mtl::Vector<gf::MenuBladeInfo>::insert(gf::MenuBladeInfo*, gf::MenuBladeInfo const&);

namespace gf {

}  // namespace gf
