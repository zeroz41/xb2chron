#include "classes/gf/GfMenuObjCampMenu.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjShop.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataBlade.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuFlag.h"
#include "mm/Col4.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "gf/GfDataUtil.h"
#include "gf/GfGameUtilDiff.h"

namespace gf {

// 2.0.0's symbols name it (lbl_7100EAA1D0)
int GfMenuObjCampMenu::s_SelectResult;

GfMenuObjCampMenu::GfMenuObjCampMenu(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_jobStarted(false), m_driverList0(nullptr), m_driverList1(nullptr),
      m_selectList(nullptr), m_cursor(nullptr), m_context(nullptr), m_voice(nullptr), m_sound(0) {
    m_driverList0 = GfMenuDriverList::create();
    m_driverList1 = GfMenuDriverList::create();
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_selectList = ui::UISelectObjList::create(create);
    m_context = GfMenuCallContext::create();
}

GfMenuObjCampMenu::~GfMenuObjCampMenu() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_driverList1 != nullptr) {
        m_driverList1->release();
        m_driverList1 = nullptr;
    }
    if (m_driverList0 != nullptr) {
        m_driverList0->release();
        m_driverList0 = nullptr;
    }
}

int GfMenuObjCampMenu::getSelectResult() {
    return s_SelectResult;
}

void GfMenuObjCampMenu::returnFromEvent() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_menu"), 0, 0.0f);
        s_SelectResult = 0;
    }
}

void GfMenuObjCampMenu::closeShopToTalk() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.searchChild("LAY_shop"), event, 0.0f);
        s_SelectResult = 0;
    }
}

void GfMenuObjCampMenu::enableCraftChrChange() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc child(acc.m_handle, "LAY_chr_change");
        GfMenuObject::enableInput(child.m_handle);
    }
}

void GfMenuObjCampMenu::disableCraftChrChange() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc child(acc.m_handle, "LAY_chr_change");
        GfMenuObject::disableInput(child.m_handle);
    }
}

void GfMenuObjCampMenu::setCampTalkNew() {
    GfMenuFlag::set1(0x54, 0);
}

void GfMenuObjCampMenu::finalize() {
    GfMenuObject::detachExternalCall(0x8D);
    GfMenuObject::finalize();
}

void GfMenuObjCampMenu::update() {
    m_seq.update();
    if (m_voice != nullptr && GfGameVoice::getResult(m_voice) >= 3) {
        m_voice = nullptr;
    }
    GfMenuObject::update();
}

void GfMenuObjCampMenu::refreshNotice() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    main.setDispChild(false, "IMG_select_sleep_notice");
    main.setDispChild(false, "IMG_select_craft_notice");
    main.setDispChild(false, "IMG_select_talk_notice");
    mm::mtl::FixStr<32> name;
    bool craft = false;
    for (unsigned int i = 0; i < m_driverList0->getSize(); i++) {
        bool notice = hasNewCraft(m_driverList0->getContents(i).m_driver);
        name.format("IMG_craft_item_notice@%02d", i + 1);
        main.setDispChild(notice, name.m_str);
        craft |= notice;
    }
    main.setDispChild(craft, "IMG_select_craft_notice");
    if (GfGameFlag::getLocal(1, 0xC6C9) == 0) {
        main.setDispChild(true, "IMG_select_talk_notice");
    }
    if (GfMenuFlag::get1(0x54) == 0) {
        main.setDispChild(true, "IMG_select_talk_notice");
    }
}

bool GfMenuObjCampMenu::seqConfirmSleep() {
    if (!m_jobStarted) {
        GfMenuManager::openCommonWindow(0x11F);
        m_jobStarted = true;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    if (static_cast<unsigned short>(GfMenuManager::getCommonWindowResult()) != 0) {
        ui::UIObjectAcc menu(m_handle, "LAY_menu");
        ui::EventData event;
        event.m_type = 0x100;
        GfMenuObject::sendEvent(menu.m_handle, event, 0.0f);
    } else {
        {
            ui::UIObjectAcc menu(m_handle, "LAY_menu");
            GfMenuObject::sendCloseEvent(menu.m_handle, 0, 0.0f);
            GfMenuObjOperationInfo::remove(menu.m_handle, 0, 0, 0);
        }
        ui::UIObjectAcc sleep(m_handle, "LAY_sleep");
        GfMenuObject::sendOpenEvent(sleep.m_handle, 0, 0.0f);
    }
    m_jobStarted = false;
    return true;
}

bool GfMenuObjCampMenu::seqConfirmExit() {
    if (!m_jobStarted) {
        GfMenuManager::openCommonWindow(0x11E);
        m_jobStarted = true;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    {
        ui::UIObjectAcc menu(m_handle, "LAY_menu");
        ui::EventData event;
        event.m_type = 0x100;
        event.m_param0 = static_cast<unsigned short>(GfMenuManager::getCommonWindowResult()) == 0;
        GfMenuObject::sendEvent(menu.m_handle, event, 0.0f);
    }
    m_jobStarted = false;
    return true;
}

bool GfMenuObjCampMenu::seqClose() {
    m_seq.addJob(&GfMenuObjCampMenu::seqCloseSpecialFadeOut);
    m_seq.addJob(&GfMenuObjCampMenu::seqCloseSpecialFadeWait);
    if (GfGameUtilDiff::isEnableAutoSave()) {
        m_seq.addJob(&GfMenuObjCampMenu::seqAutoSave);
        m_seq.addJob(&GfMenuObjCampMenu::seqAutoSaveWait);
    }
    m_seq.addJob(&GfMenuObjCampMenu::seqCloseSpecial);
    return true;
}

void GfMenuObjCampMenu::CraftListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_driverList0->setIndex(index);
            m_owner->m_selectList->setIndex(index);
            m_owner->m_cursor->setDisp(true);
            m_owner->refreshCraftInfo();
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 0x22: {
        GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_craft_base"), 0, 0);
        int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_craft_select"), 2, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        m_owner->m_cursor->setDisp(false);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_driverList0);
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuDriverList* list = m_owner->m_driverList0;
            unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
            if (driver != 0) {
                if (m_owner->m_voice != nullptr) {
                    GfGameVoice::playStop(m_owner->m_voice);
                    m_owner->m_voice = nullptr;
                }
                m_owner->m_voice = SCOM_FIELD_VOICE::createCraftSelect(driver);
            }
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_shop"), 0, 0.0f);
            GfMenuObject::sendCloseEvent(acc.m_handle, 1, 0.0f);
            GfMenuObjUtil::playSECommonDecide();
        } else if (event.m_param1 == 2) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_menu"), 1, 0.0f);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    case 0x21: {
        acc.setDisp(true);
        unsigned int count = acc.countChild("LAY_craft_item@%02d", 1);
        mm::mtl::FixStr<32> name;
        m_owner->m_selectList->clear();
        for (unsigned int i = 0; i < count; i++) {
            unsigned int size = m_owner->m_driverList0->getSize();
            name.format("LAY_craft_item@%02d", i + 1);
            if (i < size) {
                m_owner->m_selectList->addObject(acc.searchChild(name.m_str));
            }
            acc.setDispChild(i < size, name.m_str);
        }
        mm::Rect<short> center;
        mm::Rect<short> range;
        acc.getLayoutRect("character_center", center);
        acc.getLayoutRect("character_range", range);
        GfMenuObjUtil::placeObjectH(m_owner->m_selectList,
                                    mm::Pnt<short>(center.x + center.w / 2, center.y + center.h / 2),
                                    range.x - center.x);
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_craft_base"), 0, 0);
        int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_craft_select"), 1, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        m_owner->m_cursor->setDisp(false);
        m_owner->refreshNotice();
        m_owner->refreshCraftInfo();
        break;
    }
    }
}

void GfMenuObjCampMenu::refreshCraftInfo() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    ShopInfo info;
    if (getDriverShopInfo(m_driverList0->getContents(m_driverList0->getIndex(false)).m_driver, info)) {
        GfMenuReference::setReferenceShopID(info.m_shopId);
        if (info.m_summaryMsg != 0) {
            ui::UIObjectAcc text(main.m_handle, "TXT_craft_info");
            text.setText(ui::UIStr(GfDataBdat::getFP(0x13C), info.m_summaryMsg));
        }
    }
}

void GfMenuObjCampMenu::SleepListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21:
        GfMenuObjOperationInfo::close();
        m_owner->m_jobStarted = false;
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqWaitSleepFade);
        m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqStartLevelUp);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjCampMenu::seqWaitSleepFade() {
    if (!m_jobStarted) {
        GfMenuFade::setFade(2, 30, mm::Col4::black);
        m_jobStarted = true;
        return false;
    }
    return !GfMenuManager::isFading();
}

bool GfMenuObjCampMenu::seqStartLevelUp() {
    GfMenuManager::openFullScreen(5, true, true);
    m_seq.addJob(&GfMenuObjCampMenu::seqWaitFSClose);
    if (GfGameUtilDiff::isEnableAutoSave()) {
        m_seq.addJob(&GfMenuObjCampMenu::seqAutoSave);
        m_seq.addJob(&GfMenuObjCampMenu::seqAutoSaveWait);
    }
    m_seq.addJob(&GfMenuObjCampMenu::seqEndSleep);
    m_jobStarted = false;
    return true;
}

void GfMenuObjCampMenu::ShopListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 2) {
            if (m_mode == 1) {
                s_SelectResult = 1;
                if (GfDataUtil::getScenarioFlag() > 0x2AFE && GfDataUtil::getScenarioFlag() < 0x2B01) {
                    m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqCloseSpecialFadeOut);
                    m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqCloseSpecialFadeWait);
                    if (GfGameUtilDiff::isEnableAutoSave()) {
                        m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqAutoSave);
                        m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqAutoSaveWait);
                    }
                    m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqCloseSpecial);
                }
                GfMenuObjOperationInfo::close();
            }
            GfMenuReference::setReferenceDriverID(0, 0);
        }
        break;
    case 0x21: {
        GfMenuObjShop::OpenParam param;
        param.m_shopId = m_owner->refreshShopInfo();
        param.m_option = true;
        m_owner->m_context->reset();
        GfMenuObjShop::open(m_owner->m_context, param);
        m_owner->m_jobStarted = false;
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjCampMenu::seqWaitShop);
        acc.setDisp(true);
        int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_shop_header"), 1, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        if (static_cast<unsigned int>(m_owner->m_driverList0->getSize()) > 1) {
            GfMenuObject::sendOpenEvent(acc.searchChild("LAY_chr_change"), 0, 0.0f);
        }
        m_mode = 0;
        break;
    }
    case 0x22: {
        if (m_mode == 0) {
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_craft"), 0, 0.0f);
        }
        int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_shop_header"), 2, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        if (static_cast<unsigned int>(m_owner->m_driverList0->getSize()) > 1) {
            GfMenuObject::sendCloseEvent(acc.searchChild("LAY_chr_change"), 0, 0.0f);
        }
        break;
    }
    case 0x101:
        m_mode = 1;
        break;
    case 0x102: {
        unsigned int index = event.m_param0;
        m_owner->m_driverList0->setIndex(index);
        m_owner->refreshShopInfo();
        GfMenuObjShop::changeCraft();
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

unsigned int GfMenuObjCampMenu::refreshShopInfo() {
    ui::UIObjectAcc shop(m_handle, "LAY_shop");
    unsigned int driver = m_driverList0->getContents(m_driverList0->getIndex(false)).m_driver;
    ShopInfo info;
    if (getDriverShopInfo(driver, info)) {
        {
            ui::UIObjectAcc guide(shop.m_handle, "TXT_shop_header_guide");
            ui::UIObjectAcc guideSw(shop.m_handle, "TXT_shop_header_guide_sw");
            guide.setText(ui::UIStr(GfDataBdat::getFP(0x13C), info.m_summaryMsg));
            guideSw.setText(ui::UIStr(GfDataBdat::getFP(0x13C), info.m_summaryMsg));
        }
        GfMenuReference::setReferenceDriverID(0, driver);
        GfMenuReference::setReferenceShopID(info.m_shopId);
        return info.m_shopId;
    }
    return 0;
}

bool GfMenuObjCampMenu::seqWaitShop() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (m_context->isTerm()) {
        GfMenuObject::sendCloseEvent(main.searchChild("LAY_shop"), 0, 0.0f);
        m_jobStarted = false;
        return true;
    }
    return false;
}

bool GfMenuObjCampMenu::seqCloseSpecialFadeOut() {
    GfMenuFade::setFade(1, 15, mm::Col4::black);
    return true;
}

bool GfMenuObjCampMenu::seqCloseSpecialFadeWait() {
    return !GfMenuManager::isFading();
}

bool GfMenuObjCampMenu::seqAutoSave() {
    mm::mtl::PtrSingleton<GfFieldTime>::sys()->setTime(7, 0);
    GfGameManager::reqestEventAutoSave();
    return true;
}

bool GfMenuObjCampMenu::seqAutoSaveWait() {
    return true;
}

bool GfMenuObjCampMenu::seqCloseSpecial() {
    mm::mtl::PtrSingleton<ui::UIManager>::sys()->terminateLayer(m_fsLayer, true);
    m_jobStarted = false;
    return true;
}

void GfMenuObjCampMenu::ChrChangeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjCampMenu* owner = m_owner;
            owner->refreshChrChange(owner->m_driverList1->getIndex(false));
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_driverList1);
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            m_owner->m_driverList1->setIndex(index);
            m_owner->refreshChrChange(index);
            ui::EventData parent;
            parent.m_type = 0x102;
            parent.m_param0 = index;
            GfMenuObject::sendEventToParent(acc.m_handle, parent, 0.0f);
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonTab();
            }
        }
        break;
    }
    case 0x21: {
        acc.setDisp(true);
        m_owner->m_driverList1->setIndex(0);
        m_owner->m_driverList1->setIndex(m_owner->m_driverList0->getIndex(false));
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_owner->refreshChrChange(-1);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_r";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        break;
    }
    }
}

bool GfMenuObjCampMenu::getDriverShopInfo(unsigned int driver, ShopInfo& shop) {
    unsigned char* fp = GfDataBdat::getFP(0x10E);
    if (fp != nullptr) {
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            unsigned short id = Bdat::getIdTop(fp) + i;
            if (static_cast<unsigned short>(Bdat::getVal(fp, "driver_id", id)) ==
                driver) {
                shop.m_shopId = static_cast<unsigned short>(Bdat::getVal(fp, "shop_id", id));
                shop.m_summaryMsg =
                    static_cast<unsigned short>(Bdat::getVal(fp, "summary_msg", id));
                return true;
            }
        }
    }
    return false;
}

bool GfMenuObjCampMenu::seqWaitFSClose() {
    return !GfMenuManager::isOpenFullScreen();
}

bool GfMenuObjCampMenu::seqEndSleep() {
    mm::mtl::PtrSingleton<ui::UIManager>::sys()->terminateLayer(m_fsLayer, true);
    m_jobStarted = false;
    return true;
}

}  // namespace gf
