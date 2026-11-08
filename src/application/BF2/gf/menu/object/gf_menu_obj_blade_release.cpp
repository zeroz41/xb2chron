#include "classes/gf/GfMenuFullScreen.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfPartySelect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjBladeRelease.h"
#include "classes/gf/GfMenuObjBladeRelease/MainListener.h"
#include "classes/gf/GfMenuObjBladeRelease/ListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "gf/GfDataBlade.h"
#include "gf/GfGameUtil.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Vec2.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjBladeRelease::GfMenuObjBladeRelease(unsigned int handle)
    : GfMenuObject(handle), pad_28(nullptr), m_bladeList(nullptr), m_list(nullptr), m_cursor(nullptr),
      m_context(nullptr), m_subContext(nullptr), m_seq(this), m_seqStep(false), m_subSeq(this), m_itemList(nullptr),
      pad_458(false), m_idList(nullptr), pad_468(false), pad_46C(-1), m_driverList(nullptr), m_hasRex(false),
      m_sortType(0), pad_4C8(0), m_voice(nullptr), m_voicePlayed(false) {
    m_itemList = GfMenuItemList::create();
    m_idList = GfMenuIDList::create();
    m_driverList = GfMenuDriverList::create();
    m_context = GfMenuCallContext::create();
    m_subContext = GfMenuCallContext::create();
}

GfMenuObjBladeRelease::~GfMenuObjBladeRelease() {
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (pad_28 != nullptr) {
        pad_28->release();
        pad_28 = nullptr;
    }
}

void GfMenuObjBladeRelease::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    {
#line 145
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_bladeList = GfMenuBladeList::create();
    {
        GfMenuBladeList::ReleasbleSetup setup;
        setup.m_pageRowSize = 3;
        setup.m_pageColumnSize = 5;
        m_bladeList->clear();
        m_bladeList->setupFromReleasble(setup);
    }
    GfMenuReference::setReferenceBladeID(0, 0);
    {
    ui::UIObjectAcc list(acc.m_handle, "LAY_list_bl");
    {
        mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = allocator;
        m_list = ui::UISelectObjList::create(create);
    }
    m_list->pickupObject(list.m_handle, "LAY_list_bl@%02d", 1);
    {
        ui::UICtrlCursorSelect::CursorSetting setting;
        setting.setType(0);
        setting.m_dockType = 0;
        setting.m_waitAnim = "loop";
        m_cursor = ui::UICtrlCursorSelect::create(list.searchChild("IMG_list_bl_cursor"), setting, m_list);
    }
    for (unsigned int i = 0; i < m_list->getSize(); i++) {
        name.format("IMG_list_bl_face@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 3, m_bladeList, i, false);
        name.format("IMG_list_bl_info_elem@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x2A, m_bladeList, i, false);
        name.format("IMG_list_bl_info_wpn@%02d", i + 1);
        GfMenuCharDataAdapter* adapter =
            GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x29, m_bladeList, i, false);
        if (adapter != nullptr) {
            name.format("IMG_list_bl_info_wpn_base@%02d", i + 1);
            adapter->m_rowHandle = list.searchChild(name.m_str);
        }
        name.format("IMG_list_bl_info_role@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x42, m_bladeList, i, false);
        name.format("IMG_list_bl_info_mer@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x53, m_bladeList, i, false);
        name.format("IMG_list_bl_info_dr@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeListOwnerDriver(list.searchChild(name.m_str), 3, m_bladeList, i, false);
        name.format("IMG_list_bl_lock@%02d", i + 1);
        adapter = GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x5A, m_bladeList, i, true);
        if (adapter != nullptr) {
            adapter->setDispAlphaMode(true);
        }
    }
    GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_list_bl_scroll_bar"), m_bladeList,
                                          "IMG_list_bl_scroll_bar_base", true);
    {
#line 230
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::setFSInputObject(1, list.m_handle);
    GfMenuObject::sendOpenEvent(list.m_handle, 0, 0.0f);
    }
    {
        ui::UIObjectAcc layout(acc.m_handle, "LAY_bl_img");
        ui::UIObjectAcc image(layout.m_handle, "IMG_bl_img");
        GfMenuCharDataAdapter::createFromReferenceBlade(layout.searchChild("IMG_bl_img"), 0x36, 0, false);
        image.setAlpha(0.0f);
        image.setStreamImage2nd();
    }
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_idList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    GfPartySelect::getDriverList(m_drivers, GfPartySelect::LIST_TYPE(2), 0);
    unsigned short* it = m_drivers.begin();
    while (it != m_drivers.end()) {
        if (*it == 1) {
            if (GfGameManager::isRexAwakening()) {
                m_hasRex = true;
                it = m_drivers.erase(it);
                continue;
            }
            if (*it == 1) {
                m_hasRex = true;
            }
        } else if (!(*it == 2 || *it == 3 || *it == 6)) {
            it = m_drivers.erase(it);
            continue;
        }
        ++it;
    }
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = m_drivers.size();
        m_driverList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    GfMenuObject::initialize();
}


void GfMenuObjBladeRelease::finalize() {
    if (m_voice != nullptr) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
    }
    GfMenuObject::finalize();
}

void GfMenuObjBladeRelease::update() {
    m_seq.update();
    m_subSeq.update();
    GfMenuObject::update();
}

void GfMenuObjBladeRelease::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
    } else if (event.m_type == 2) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
    } else if (event.m_type == 0x101) {
        if (GfMenuReference::getReferenceBladeID(0) != 0) {
            m_owner->m_subSeq.clear();
            m_owner->m_subSeq.addJob(&GfMenuObjBladeRelease::seqOpenImage);
        }
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

void GfMenuObjBladeRelease::ListListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        {
            ui::UIObjectAcc sort(m_owner->m_handle, "LAY_sort");
            unsigned short id = GfMenuObjSort::getSortID(1, 0);
            GfMenuObjSort::setSortLabelText(id, sort.searchChild("TXT_sort_label"));
            m_owner->m_sortType = 0;
            m_owner->m_bladeList->sort(id, false);
        }
        GfMenuObjCmnStatus::openBlStatus(1, -1);
        m_index = 0;
        break;
    }
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int last = event.m_param1;
            m_owner->m_bladeList->setIndex(index);
            unsigned int page = index - m_owner->m_bladeList->getRowOffset() * m_owner->m_bladeList->getColumnSize();
            m_owner->m_list->setIndex(page);
            unsigned int blade = m_owner->m_bladeList->getContents(index).m_blade;
            bool different = GfMenuObjUtil::isBladeDifferentImage(blade, GfMenuReference::getReferenceBladeID(0));
            GfMenuReference::setReferenceBladeID(0, blade);
            if (different) {
                ui::UIObjectAcc image(m_owner->m_handle, "IMG_bl_img");
                int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
                if (ctrl != -1) {
                    GfMenuObjUtil::stopCtrl(ctrl);
                }
                image.setAlpha(0.0f);
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                ui::EventData open;
                open.m_type = 0x101;
                GfMenuObject::sendEvent(main.m_handle, open, 0.0f);
            }
            if (last != -1 && index != last) {
                GfMenuObjUtil::playSECommonCursor();
            }
            if (blade == 0) {
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
            } else {
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
            }
        }
        m_index = index;
        break;
    }
    case 8: {
        int index = event.m_param0;
        switch (event.m_param1) {
        case 1:
            if (index < m_owner->m_bladeList->getSize()) {
                GfMenuBladeList* list = m_owner->m_bladeList;
                unsigned int blade = list->getContents(list->getIndex(false)).m_blade;
                if (!GfDataBlade::isActivateMercenaryTeam(blade) &&
                    !(GfMenuObjUtil::isBladeHana(blade) && GfMenuObjUtil::isBladeHanaInMercenary())) {
                    GfMenuObjMainMenu2::setCloseKeyEnable(false);
                    GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
                    m_owner->m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
                    GfMenuObject::disableFSInput();
                    m_owner->m_cursor->setDisp(false);
                    break;
                }
            }
            GfMenuObjUtil::playSECommon(2);
            break;
        case 2:
            GfMenuObjCmnStatus::closeBlStatus();
            GfMenuObject::returnFSSubLayer(m_owner);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObjUtil::playSECommonCancel();
            break;
        case 0xC: {
            unsigned int blade;
            if (index < m_owner->m_bladeList->getSize() && (blade = GfMenuReference::getReferenceBladeID(0)) != 0 &&
                GfMenuObjUtil::isValidBlade(blade)) {
                if (GfDataBlade::isBladeLock(blade)) {
                    GfMenuObjUtil::setBladeFavorite(blade, false);
                    GfMenuObjUtil::playSECommonCancel();
                } else {
                    GfMenuObjUtil::setBladeFavorite(blade, true);
                    GfMenuObjUtil::playSECommonDecide();
                }
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
                break;
            }
            GfMenuObjUtil::playSECommon(2);
            break;
        }
        case 0x10:
            if (index < m_owner->m_bladeList->getSize()) {
                GfMenuBladeList* list = m_owner->m_bladeList;
                unsigned int blade = list->getContents(list->getIndex(false)).m_blade;
                if (GfMenuObjUtil::isBladeReleasable(blade, nullptr)) {
                    GfMenuObjMainMenu2::setCloseKeyEnable(false);
                    GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
                    m_owner->m_seqStep = false;
                    m_owner->m_seq.clear();
                    m_owner->m_seq.addJob(&GfMenuObjBladeRelease::seqConfirmRelease);
                    GfMenuObject::disableFSInput();
                    m_owner->m_cursor->setDisp(false);
                    break;
                }
                if (GfDataBlade::isActivateDriver(blade)) {
                    GfMenuManager::openCommonWindow(0xAE);
                    break;
                }
                if (GfDataBlade::isReleaseLock(blade) || GfMenuObjUtil::isBladeLastOne(blade, nullptr) ||
                    blade == GfDataBlade::getStartCommonBlade()) {
                    GfMenuManager::openCommonWindow(0xAD);
                    break;
                }
                if (GfDataBlade::isBladeLock(blade)) {
                    GfMenuManager::openCommonWindow(0x10B);
                    break;
                }
            }
            GfMenuObjUtil::playSECommon(2);
            break;
        case 0x11: {
            ui::UIObjectAcc label(m_owner->m_handle, "TXT_sort_label");
            GfMenuObjSort::open(acc.m_handle, label.m_handle, 1, m_owner->m_sortType);
            GfMenuObject::disableInput(handle);
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            break;
        }
        case 0x12:
            GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::swapBlStatus());
            break;
        }
        break;
    }
    case 0x21: {
        int param = event.m_param0;
        GfMenuObject::resetInputSelection(acc.m_handle);
        unsigned int size = m_owner->m_bladeList->getSize();
        int pad = 0;
        if (size % 5 != 0) {
            pad = 5 - size % 5;
        }
        unsigned int count = size + pad;
        GfMenuObject::setupInputSelection(acc.m_handle, m_owner->m_bladeList->getIndex(false), count);
        m_index = m_owner->m_bladeList->getIndex(false);
        GfMenuObject::setupPadLineSelection(acc.m_handle, 5);
        GfMenuObject::enableFSInput(1);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        if (param != 1) {
            GfMenuObjOperationInfo::setGuideText(0x21, 0);
            GfMenuObjMainMenu2::setSubIndexText(0x14);
        }
        GfMenuObjOperationInfo::changeText(handle, 0x12, false);
        m_owner->m_cursor->setDisp(true);
        break;
    }
    case 0x22:
        break;
    case 0x148: {
        GfMenuObject::enableInput(handle);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        if (event.m_param1 != 0) {
            unsigned short id = GfMenuObjSort::getSortID(1, event.m_param0);
            if (id == 4 || id == 5 || id == 6) {
                m_owner->m_bladeList->sort(id, true);
            } else {
                m_owner->m_bladeList->sort(id, false);
            }
            m_owner->m_sortType = event.m_param0;
            unsigned int blade = m_owner->m_bladeList->getContents(m_index).m_blade;
            bool different = GfMenuObjUtil::isBladeDifferentImage(blade, GfMenuReference::getReferenceBladeID(0));
            GfMenuReference::setReferenceBladeID(0, blade);
            if (different) {
                ui::UIObjectAcc image(m_owner->m_handle, "IMG_bl_img");
                int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
                if (ctrl != -1) {
                    GfMenuObjUtil::stopCtrl(ctrl);
                }
                image.setAlpha(0.0f);
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                ui::EventData open;
                open.m_type = 0x101;
                GfMenuObject::sendEvent(main.m_handle, open, 0.0f);
            }
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
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBladeRelease::seqOpenImage() {
    ui::UIObjectAcc image(m_handle, "IMG_bl_img");
    if (image.isStreaming()) {
        image.setAlpha(0.0f);
        return false;
    }
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    acc.setLayout(image.m_handle, "bl_img01");
    GfMenuObjUtil::ImageParam imageParam;
    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
        mm::Vec2 scale;
        image.getScale(scale);
        scale.x = imageParam.m_scale * scale.x;
        scale.y = imageParam.m_scale * scale.y;
        image.setScale(scale);
        GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    param.m_startFlags = 8;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
    image.setAlpha(0.0f);
    return true;
}

bool GfMenuObjBladeRelease::seqConfirmRelease() {
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x11);
        m_seqStep = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        m_seq.addJob(&GfMenuObjBladeRelease::seqEffReleaseA);
        m_seq.addJob(&GfMenuObjBladeRelease::seqEffReleaseB);
        m_seq.addJob(&GfMenuObjBladeRelease::seqExecRelease);
        m_seq.addJob(&GfMenuObjBladeRelease::seqConfirmBoosterGet);
        m_seq.addJob(&GfMenuObjBladeRelease::seqResumeRelease);
    } else {
        m_seq.addJob(&GfMenuObjBladeRelease::seqResumeRelease);
    }
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOpen() {
    if (!m_seqStep) {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        m_idList->clear();
        m_idList->addContents(MenuID{1, 0});
        if (!GfMenuObjUtil::isScenarioBlade(info.m_blade) && info.m_blade != GfDataBlade::getStartCommonBlade() &&
            !m_drivers.empty() && GfItemUtil::getItemBoxCount(0x6340) != 0 &&
            !GfDataBlade::isFreeEngage(info.m_blade) &&
            (m_drivers.size() != 1 || m_drivers.begin()[0] != info.m_creator)) {
            m_idList->addContents(MenuID{2, 0});
        }
        m_context->reset();
        GfMenuObjCommonText::openSubMenu(m_context, m_idList, GfMenuObjCommonText::SubMenuOption{1, 0, 1, 0});
        m_seqStep = true;
        pad_46C = -1;
        return false;
    }
    if (!m_context->m_results.empty()) {
        GfMenuCallContext::GfMenuResult result;
        if (m_context->popResult(result) && result.m_value == 0) {
            pad_46C = result.m_id;
        }
    }
    if (!m_context->isTerm()) {
        return false;
    }
    if (pad_46C == 0xFFFFFFFF) {
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuEnd);
        return true;
    }
    switch (m_idList->getContents(pad_46C).m_id) {
    case 1:
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpenCustomize);
        break;
    case 2: {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        if (GfMenuObjUtil::isBladeLastOneInSlot(info.m_blade, nullptr)) {
            m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuErrorOvdOnly);
        } else if (GfDataBlade::getCreator(info.m_blade) == 1 && GfMenuObjUtil::isBladeLastOne(info.m_blade, nullptr)) {
            m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuErrorOvdLastOne);
        } else {
            m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuDrChange);
        }
        break;
    }
    case 3:
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuConfSetRex);
        break;
    case 4:
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuConfRemoveRex);
        break;
    default:
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuEnd);
        break;
    }
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqEffReleaseA() {
    ui::UIObjectAcc image(m_handle, "IMG_bl_img");
    int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
    if (!m_seqStep) {
        unsigned int blade = m_bladeList->getContents(m_bladeList->getIndex(false)).m_blade;
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x40000000;
        param.m_bright = 1.0f;
        param.m_time = 1.0f;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        m_voice = SCOM_FIELD_VOICE::createReleaseBlade(blade);
        m_voicePlayed = false;
        m_seqStep = true;
        return false;
    }
    if (!m_voicePlayed && m_voice != nullptr && GfMenuObjUtil::isVoiceSkip()) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
        if (GfMenuObjUtil::isBusyCtrl(ctrl)) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x40000000;
            param.m_bright = 1.0f;
            param.m_time = 0.2f;
            GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        }
        m_voicePlayed = true;
    }
    if (!GfMenuObjUtil::isBusyCtrl(ctrl) && GfGameVoice::getResult(m_voice) > 2) {
        m_voice = nullptr;
        m_seqStep = false;
        return true;
    }
    return false;
}

bool GfMenuObjBladeRelease::seqEffReleaseB() {
    ui::UIObjectAcc acc(m_handle, "LAY_bl_img");
    int ctrl = GfMenuObjUtil::getCtrlID(acc.m_handle);
    if (!m_seqStep) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = m_voicePlayed ? 0.2f : 1.0f;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_seqStep = true;
        return false;
    }
    if (!m_voicePlayed && GfMenuObjUtil::isVoiceSkip()) {
        if (GfMenuObjUtil::isBusyCtrl(ctrl)) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.2f;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        m_voicePlayed = true;
    }
    if (GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    ui::UIObjectAcc image(m_handle, "IMG_bl_img");
    image.setAddColor("black");
    m_voicePlayed = false;
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqExecRelease() {
    // Proposed name, not the original's (lbl_7100EA71B8): the boosters the released blade gives back
    static mm::mtl::FixedVector<GfItem, 1024> s_items;
    unsigned int blade = m_bladeList->getContents(m_bladeList->getIndex(false)).m_blade;
    s_items.clear();
    GfGameUtil::execBoosterAddForReleaseBlade(s_items, blade);
    {
        ui::UIListInfoBase::SetupParam param;
        unsigned int count = s_items.size();
        param.m_pageRowSize = count == 0 ? 1 : count;
        m_itemList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    MenuItemInfo info;
    for (unsigned int i = 0; i < s_items.size(); i++) {
        info.m_id = s_items[i].m_item;
        info.m_type = GfItemUtil::getType(info.m_id);
        info.m_count = 1;
        m_itemList->addItem(info, false);
    }
    GfGameUtil::execActivateUnuseForBlade(blade, true);
    GfMenuObjPopup::removeBlade(blade);
    for (unsigned int i = 0; i < m_bladeList->getSize(); i++) {
        if (m_bladeList->getContents(i).m_blade == blade) {
            GfMenuBladeList* list = m_bladeList;
            list->m_list.erase(list->m_list.begin() + i);
            list->subSize(1);
            list->m_changed = true;
            break;
        }
    }
    GfMenuReference::setReferenceBladeID(0, 0);
    return true;
}

bool GfMenuObjBladeRelease::seqConfirmBoosterGet() {
    if (m_itemList->getSize() != 0) {
        if (!m_seqStep) {
            m_context->reset();
            GfMenuObjCommonText::openGetItem(m_context, m_itemList);
            m_seqStep = true;
            return false;
        }
        if (!m_context->isTerm()) {
            return false;
        }
        m_seqStep = false;
    }
    return true;
}

bool GfMenuObjBladeRelease::seqResumeRelease() {
    ui::UIObjectAcc list(m_handle, "LAY_list_bl");
    GfMenuObject::sendOpenEvent(list.m_handle, 0, 0.0f);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    ui::UIObjectAcc image(m_handle, "LAY_bl_img");
    image.setDisp(true);
    image.setAlpha(1.0f);
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuEnd() {
    ui::UIObjectAcc list(m_handle, "LAY_list_bl");
    GfMenuObject::sendOpenEvent(list.m_handle, 1, 0.0f);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOpenCustomize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_list_bl"), 0, 0);
    GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_index"), 0, 0);
    const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
    GfMenuObjCharSelect::openBladeCustomize(acc.m_handle, info.m_blade, GfMenuFullScreen::getLayerGroup(m_fsLayer) + 1);
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuWaitLoadCustomize);
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuErrorOvdOnly() {
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0xDD);
        m_seqStep = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuErrorOvdLastOne() {
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0xDE);
        m_seqStep = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuDrChange() {
    if (!m_seqStep) {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        MenuDriverInfo driver;
        driver.m_driver = 0;
        unsigned int owner = info.m_creator;
        m_driverList->clear();
        // m_drivers[i] read twice: the loop test folds the first index check away, the second one stays
        for (unsigned int i = 0; i < m_drivers.size(); i++) {
            if (m_drivers[i] != owner) {
                driver.m_driver = m_drivers[i];
                m_driverList->addContents(driver);
            }
        }
        m_context->reset();
        GfMenuObjCommonText::openDrChange(m_context, owner, m_driverList);
        m_seqStep = true;
        return false;
    }
    if (!m_context->isTerm()) {
        return false;
    }
    GfMenuCallContext::GfMenuResult result;
    if (!m_context->m_results.empty() && m_context->popResult(result) && result.m_value == 0) {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        if (GfDataBlade::isActivateDriver(info.m_blade)) {
            int slot = GfDataBlade::getDriverSetID(info.m_blade);
            if (slot != -1) {
                SCOM_PARTY_ADD::removeBlade(info.m_creator, slot, true);
            }
        }
        m_driverList->setIndex(result.m_id);
        unsigned int blade = info.m_blade;
        GfDataBlade::setCreator(blade, m_driverList->getContents(m_driverList->getIndex(false)).m_driver);
        GfItemUtil::addItemBox(0x6340, -1);
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOwnerChange);
    } else {
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    }
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuConfSetRex() {
    if (!m_seqStep) {
        m_context->reset();
        GfMenuObjCommonText::open(m_context, 0xC5, 0);
        m_seqStep = true;
        return false;
    }
    if (!m_context->isTerm()) {
        return false;
    }
    GfMenuCallContext::GfMenuResult result;
    if (!m_context->m_results.empty() && m_context->popResult(result) && result.m_value == 0 && result.m_id == 0) {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        if (GfDataBlade::isActivateDriver(info.m_blade)) {
            int slot = GfDataBlade::getDriverSetID(info.m_blade);
            if (slot != -1) {
                SCOM_PARTY_ADD::removeBlade(info.m_creator, slot, true);
            }
        }
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOwnerChange);
    } else {
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    }
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuConfRemoveRex() {
    if (!m_seqStep) {
        m_context->reset();
        GfMenuObjCommonText::open(m_context, 0xC6, 0);
        m_seqStep = true;
        return false;
    }
    if (!m_context->isTerm()) {
        return false;
    }
    GfMenuCallContext::GfMenuResult result;
    if (!m_context->m_results.empty() && m_context->popResult(result) && result.m_value == 0 && result.m_id == 0) {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        if (GfDataBlade::getSetDriver(info.m_blade) == 1) {
            int slot = GfDataBlade::getDriverSetID(info.m_blade);
            if (slot != -1) {
                SCOM_PARTY_ADD::removeBlade(1, slot, true);
            }
        }
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOwnerChange);
    } else {
        m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    }
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOwnerChange() {
    if (!m_seqStep) {
        const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
        m_idList->getContents(pad_46C);
        unsigned int owner = info.m_creator;
        unsigned int driver = m_driverList->getContents(m_driverList->getIndex(false)).m_driver;
        m_context->reset();
        GfMenuObjCommonText::openOwnerChange(m_context, owner, driver);
        m_seqStep = true;
        return false;
    }
    if (!m_context->isTerm()) {
        return false;
    }
    m_bladeList->updateOwner();
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuEnd);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuWaitLoadCustomize() {
    if (GfMenuManager::isSwitchingFullScreen()) {
        return false;
    }
    m_subContext->reset();
    if (!GfMenuObjCharSelect::attach(m_subContext)) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuWaitEndCustomize);
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    acc.setDispChild(false, "LAY_bl_img");
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuWaitEndCustomize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (!m_subContext->m_results.empty()) {
        GfMenuCallContext::GfMenuResult result;
        m_subContext->popResult(result);
    }
    if (!m_subContext->isTerm()) {
        return false;
    }
    GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_bl_img"), 0, 0);
    GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_list_bl"), 0, 0);
    GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_index"), 0, 0);
    m_seq.addWait(5);
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuEnd);
    GfMenuObjOperationInfo::setGuideText(0x21, 0);
    GfMenuObjMainMenu2::setSubIndexText(0x14);
    return true;
}

}  // namespace gf
