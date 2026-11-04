#include "classes/gf/GfMenuObjShop.h"
#include "classes/gf/GfMenuObjShop.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_RANDOM_INN.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObjShop/SellFilterListener.h"
#include "classes/gf/GfMenuObjShop/CommonListener.h"
#include "classes/gf/GfMenuObjShop/InnActListener.h"
#include "gf/GfGameUtilShop.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/gf/GfMenuObjShop/SellFilterListener.h"
#include "classes/gf/GfMenuObjBlWeapon2.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/UIStr.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Col4.h"
#include "ui/EventData.h"
#include "gf/GfDataBlade.h"
#include "gf/GfGameUtilCloudSea.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfQuestReward.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C4748). The item type of each sell
// filter (m_filters' values index it).
static const unsigned int s_filterItemType[13] = {0, 12, 7, 11, 10, 14, 9, 3, 2, 1, 6, 5, 8};

void GfMenuObjShop::finalize() {
    for (int i = 0; i < 26; ++i) {
        m_numbers[i] = nullptr;
    }
    GfMenuObject::finalize();
}

void GfMenuObjShop::update() {
    m_seq.update();
    if (m_refreshItemList) {
        refreshItemList();
        m_refreshItemList = false;
    }
    if (m_stockNumDirty) {
        refreshStock();
        m_stockNumDirty = false;
    }
    GfMenuObject::update();
}

void GfMenuObjShop::open(GfMenuCallContext* context, const OpenParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x77));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0Short = param.m_shopId;
        if (GfMenuObjUtil::isValidExpansion(3) && GfMenuManager::isOpenCampMenu()) {
            event.m_paramShort[2] = param.m_option;
        }
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x77, acc.m_handle);
        GfMenuAdapterManager::addActiveCategory(1);
    }
}

void GfMenuObjShop::close(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x77)) {
        ui::UIObjectAcc acc(context->m_handle);
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuAdapterManager::delActiveCategory(1);
        }
    }
}

void GfMenuObjShop::dispBlade(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x77));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x46;
        event.m_param0 = disp;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjShop::changeCraft() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x77));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x47;
            event.m_param0 = GfMenuReference::getReferenceShopID();
            GfMenuObject::sendEvent(acc.searchChild("LAY_exc_task_list"), event, 0.0f);
        }
    }
}

bool GfMenuObjShop::seqEndDialog() {
    if (m_dialog != 0) {
        ui::EventData event;
        event.m_type = 0x42;
        GfMenuObject::sendEvent(m_dialog, event, 0.0f);
    }
    return true;
}

bool GfMenuObjShop::seqWaitLoadBlWeapon() {
    m_blWeaponContext->reset();
    if (GfMenuObjBlWeapon2::attach(m_blWeaponContext)) {
        m_seq.addJob(&GfMenuObjShop::seqWaitEndBlWeapon);
        return true;
    }
    return false;
}

void GfMenuObjShop::setFilterIndex() {
    unsigned int filter = m_filters[m_filterIndex];
    ui::UIObjectAcc text(m_handle, "TXT_store_sell_index");
    if (text.m_object != nullptr) {
        ui::UIStr str(GfDataBdat::getFP(0x11D), GfMenuObjUtil::getMsgIDFromList(0x14B, filter + 1));
        text.setText(str);
    }
}

bool GfMenuObjShop::seqWaitSleepFade() {
    if (!m_seqStarted) {
        GfMenuFade::setFade(2, 30, mm::Col4::black);
        m_seqStarted = true;
        return false;
    }
    return !GfMenuManager::isFading();
}

bool GfMenuObjShop::seqIntervalSleep() {
    if (m_sleepInterval == 0) {
        m_sleepInterval = 1;
    }
    return --m_sleepInterval == 0;
}

bool GfMenuObjShop::seqWaitFSClose() {
    return !GfMenuManager::isOpenFullScreen();
}

void GfMenuObjShop::addCallContextResult(unsigned int result, unsigned int param) {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::addResultCallContext(main.m_handle, result, param);
}

void GfMenuObjShop::sendEnableEvent(unsigned int handle) {
    if (handle == 0) {
        handle = ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
    }
    ui::EventData event;
    event.m_type = 0x40;
    GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendExitEvent(unsigned int handle) {
    if (handle == 0) {
        handle = ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
    }
    ui::EventData event;
    event.m_type = 0x41;
    GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendCloseEvent(unsigned int handle) {
    if (handle == 0) {
        handle = ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
    }
    ui::EventData event;
    event.m_type = 0x22;
    GfMenuObject::sendEvent(handle, event, 0.0f);
}

bool GfMenuObjShop::seqEnd() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfSequentialPlay::pauseOff();
    if (m_result != 0) {
        addCallContextResult(m_result, m_resultParam);
    }
    GfMenuObject::termCallContext(main.m_handle);
    return true;
}

bool GfMenuObjShop::seqWaitEndBlWeapon() {
    if (!m_blWeaponContext->isTerm()) {
        return false;
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    sendEnableEvent(main.searchChild("LAY_store_action"));
    return true;
}

void GfMenuObjShop::refreshStock() {
    ui::UIObjectAcc stock(m_handle, "LAY_stock_num");
    unsigned int type = GfMenuReference::getReferenceItemType();
    bool disp = false;
    if (m_mode == 0) {
        if (type != 0 && m_useFilterItemType && m_filterIndex != 0) {
            type = s_filterItemType[m_filters[m_filterIndex]];
        }
        disp = type == 2 || type == 3;
    } else if (m_mode == 3) {
        disp = type == 3;
    }
    stock.setDisp(disp);
    mm::Pnt<short> pos;
    stock.getPos(pos);
    pos.y = m_stockNumOffsetY + (m_mode == 3 ? -39 : 0);
    stock.setPos(pos);
}

int GfMenuObjShop::getSpecialShop(unsigned int shopId) {
    if (shopId != 0) {
        unsigned char* fp = GfDataBdat::getFP(0xF4);
        if (fp != nullptr) {
            unsigned short scenario = GfDataUtil::getScenarioFlag();
            int top = Bdat::getIdTop(fp);
            for (int i = 0; i < Bdat::getIdCount(fp); ++i) {
                int id = top + i;
                unsigned short flag = Bdat::getVal(fp, "scenario_flag", id);
                if (flag == 0 || flag == scenario) {
                    unsigned short shop = Bdat::getVal(fp, "shop_id", id);
                    if (shop != 0 && shop == shopId) {
                        return id;
                    }
                }
            }
        }
    }
    return 0;
}

void GfMenuObjShop::CommonListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        m_ctrl = -1;
        break;
    case 3:
        if (event.m_param0 == 2) {
            m_owner->sendExitEvent(0);
            acc.setDisp(false);
        }
        break;
    case 0x21: {
        acc.setDisp(true);
        {
            ui::UIObjectAcc bg(acc.m_handle, "IMG_common_bg");
            bg.startAnimation("fade_in", false);
        }
        acc.setDispChild(true, "LAY_index");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_up_down"; param.m_motion = "fade_in_up";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_index");
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        m_ctrl = ctrl;
        break;
    }
    case 0x22: {
        {
            ui::UIObjectAcc bg(acc.m_handle, "IMG_common_bg");
            bg.startAnimation("fade_out", false);
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_up_down"; param.m_motion = "fade_out_up";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_index");
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        m_ctrl = ctrl;
        break;
    }
    }
    UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::refreshFilterIcon() {
    ui::UIObjectAcc filter(m_handle, "LAY_store_sell_filter");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_filters.size(); ++i) {
        bool select = i == m_filterIndex;
        name.format("IMG_store_sell_filter_icon@%02d", i + 1);
        ui::UIObjectAcc icon(filter.searchChild(name.m_str));
        if (select) {
            icon.setMulColor("sys_select");
        } else {
            icon.loadDefColor();
        }
    }
}

void GfMenuObjShop::setupSellItemList() {
    GfMenuItemList::ItemBoxSetup setup;
    unsigned int filter = m_filters[m_filterIndex];
    setFilterIndex();
    setup.m_setup.m_pageRowSize = m_sellObjList->getSize();
    setup.m_setup.m_pageScroll = true;
    setup.pad_28 = 0;
    setup.pad_29 = 0;
    setup.pad_2A = 1;
    setup.pad_2B = 1;
    if (filter != 0) {
        setup.m_type = s_filterItemType[filter];
        m_sellItemList->setupFromBox(setup);
    } else {
        ui::UIListInfoBase::SetupParam param;
        param = setup.m_setup;
        m_sellItemList->setup(getAllocator(ALLOCATOR(0)), param);
        for (int i = 1; i < 13; ++i) {
            setup.m_type = s_filterItemType[i];
            m_sellItemList->addListFromBox(setup);
        }
    }
}

void GfMenuObjShop::SellFilterListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (m_owner->m_filterIndex != index) {
            m_owner->m_filterIndex = index;
            ui::EventData change;
            change.m_type = 0x45;
            GfMenuObject::sendEvent(acc.getParentHandle(), change, 0.0f);
        }
        m_owner->refreshFilterIcon();
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonTab();
        }
        break;
    }
    case 0x21:
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, m_owner->m_filterIndex, m_owner->m_filters.size());
        GfMenuObject::enableInput(acc.m_handle);
        break;
    case 0x22:
        // a separate case, not merged with case 1: the block layout (case 0x21 falls into the exit) needs it
        GfMenuObject::disableInput(acc.m_handle);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjShop::InnActListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        m_owner->m_selectList->setIndex(index);
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        return;
    }
    case 0x40:
        if (m_owner->m_selectList != nullptr && m_owner->m_selectList->getSize() != 0) {
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_selectList);
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_owner->m_cursor = ui::UICtrlCursorSelect::create(acc.searchChild("LAY_inn_action_cursor"), setting,
                                                               m_owner->m_selectList);
            if (m_owner->m_cursor != nullptr) {
                m_owner->m_cursor->setDisp(true);
            }
        }
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        m_owner->setGuideText(0x1F);
        m_owner->m_switchInnCloudSea = false;
        return;
    case 8: {
        int index = event.m_param0;
        int action = event.m_param1;
        if (action == 1) {
            if (index == m_owner->m_selectList->getSize() - 1) {
                GfMenuObjUtil::playSECommonDecide();
            } else {
                unsigned int money = GfDataUtil::getMoney();
                if (money < (*(m_owner->m_numbers + (index + 3)))->m_value) {
                    GfMenuObjUtil::playSECommon(2);
                    break;
                }
                m_owner->m_result = 1;
                m_owner->m_resultParam = 0;
                GfMenuObjUtil::playSE(0x18);
                GfGameUtilShop::execPayInn(m_owner->m_shopId, m_owner->m_numbers[index + 3]->m_value, index > 0);
                if (index > 0) {
                    m_owner->m_switchInnCloudSea = true;
                }
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjShop::seqStartSleepFade);
                GfMenuObjUtil::playSECommonDecide();
            }
        } else if (action == 2) {
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        m_owner->sendCloseEvent(0);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        if (m_owner->m_cursor != nullptr) {
            m_owner->m_cursor->release();
            m_owner->m_cursor = nullptr;
        }
        ui::UIObjectAcc(acc.searchSibiling("LAY_inn_action_cursor")).setDisp(false);
        break;
    }
    }
    UIObjectListener::reciveEvent(event, handle);
}

bool GfMenuObjShop::seqStartLevelUp() {
    if (m_switchInnCloudSea) {
        GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(GfGameUtilCloudSea::getCloudSea() == 0));
        m_switchInnCloudSea = false;
    }
    GfMenuManager::openFullScreen(5, true, true);
    m_seq.addJob(&GfMenuObjShop::seqWaitFSClose);
    m_seq.addJob(&GfMenuObjShop::seqEnd);
    return true;
}

void GfMenuObjShop::setGuideText(unsigned int id) {
    if (m_guideTextId != id) {
        ui::UIObjectAcc guide(m_handle, "TXT_common_guide");
        unsigned int name = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x146), "name", id));
        guide.setText(ui::UIStr(GfDataBdat::getFP(0x118), name));
        guide.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        param.m_time = 0.2f;
        GfMenuObjUtil::startCtrl(guide.m_handle, param, nullptr);
        m_guideTextId = id;
    }
}

bool GfMenuObjShop::seqStartSleepFade() {
    GfSequentialPlay::pauseOn(0x59);
    SCOM_ACHIEV_INC::addTotalCount(0x23, 1);
    SCOM_ACHIEV_INC::create(0x23, 1, 0);
    SCOM_FIELD_VOICE::createExitInn();
    SCOM_RANDOM_INN::setRandom();
    m_seq.addJob(&GfMenuObjShop::seqWaitSleepFade);
    m_seq.addJob(&GfMenuObjShop::seqIntervalSleep);
    m_seq.addJob(&GfMenuObjShop::seqStartLevelUp);
    m_sleepInterval = 0;
    m_seqStarted = false;
    return true;
}

bool GfMenuObjShop::seqItemGet() {
    if (m_itemGetState != 1) {
        return true;
    }
    if (!m_seqStarted) {
        m_callContext->reset();
        if (m_mode == 3) {
            if (m_getItemId != 0) {
                ui::UIListInfoBase::SetupParam param;
                m_itemList->setup(getAllocator(ALLOCATOR(0)), param);
                MenuItemInfo info;
                info.m_id = m_getItemId;
                info.m_type = GfItemUtil::getType(m_getItemId);
                info.m_count = 1;
                m_itemList->addItem(info, false);
                m_callContext->reset();
                GfMenuObjCommonText::openGetItem(m_callContext, m_itemList);
                m_getItemId = 0;
            }
        } else if (m_mode == 1) {
            if (m_itemList->getSize() != 0) {
                m_callContext->reset();
                GfMenuObjCommonText::openGetItem(m_callContext, m_itemList);
            }
        }
        if (!m_callContext->isActive()) {
            m_seqStarted = false;
            return true;
        }
        GfMenuObjUtil::playSE(10);
        m_seqStarted = true;
    }
    if (!m_callContext->isTerm()) {
        return false;
    }
    m_seqStarted = false;
    if (m_mode == 1) {
        m_refreshItemList = true;
        m_stockNumDirty = false;
    }
    return true;
}

bool GfMenuObjShop::getExcTaskRewardItem(unsigned int task, mm::mtl::FixedVector<unsigned short, 4>& items) {
    unsigned char* bdat = GfDataBdat::getFP(0xF2);
    if (bdat == nullptr || !GfMenuBdat::isValidBdatID(bdat, task)) {
        return false;
    }
    unsigned short id = Bdat::getVal(bdat, "Reward", task);
    if (!id) {
        return false;
    }
    GfQuestReward reward;
    if (!GfQuestUtil::getReward(reward, id, false)) {
        return false;
    }
    for (int i = 8; i < 12; ++i) {
        unsigned short item = reward.m_items[i].m_value;
        if (item != 0) {
            items.push_back(item);
            if (items.size() == items.capacity()) {
                break;
            }
        }
    }
    return !items.empty();
}

bool GfMenuObjShop::getExcTaskReward(unsigned int task, unsigned int& value, GfMenuItemList* list, bool& hide) {
    unsigned char* bdat = GfDataBdat::getFP(0xF2);
    if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, task)) {
        hide = static_cast<unsigned short>(Bdat::getVal(bdat, "HideReward", task)) != 0;
        list->clear();
        unsigned short id = Bdat::getVal(bdat, "Reward", task);
        if (id) {
            {
                GfMenuItemList::QuestRewardSetup setup;
                setup.m_setup.m_pageRowSize = 4;
                setup.m_reward = id;
                list->setupFromQuestReward(setup);
            }
            GfQuestReward reward;
            if (GfQuestUtil::getReward(reward, id, false)) {
                value = reward.m_items[0].m_value;
                if (value != 0) {
                    return true;
                }
                return list->getSize() != 0;
            }
        }
    }
    return false;
}

}  // namespace gf
