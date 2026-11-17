#include "classes/gf/GfMenuObjShop.h"
#include "classes/gf/GfMenuObjShop.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_RANDOM_INN.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuIDList.h"
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
#include "gf/GfQuestTask.h"
#include "gf/GfRecipeOrbUtil.h"
#include "classes/gf/GfMenuObjShop/NumSelectListener.h"
#include "gf/GfShopUtil.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfDataItem.h"
#include "classes/gf/GfMenuObjShop/OrbListListener.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuObjShop/SubListener.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C4748). The item type of each sell
// filter (m_filters' values index it).
static const unsigned int s_filterItemType[13] = {0, 12, 7, 11, 10, 14, 9, 3, 2, 1, 6, 5, 8};

GfMenuObjShop::GfMenuObjShop(unsigned int handle)
    : GfMenuObject(handle), m_shopId(0), pad_34(0), m_guideTextId(0), m_selectList(nullptr), m_sellItemList(nullptr),
      m_sellObjList(nullptr), m_useFilterItemType(false), m_refreshItemList(false), m_stockNumDirty(false),
      m_filterIndex(0), m_cursor(nullptr), pad_D0(0), pad_D8(nullptr), pad_E0(nullptr), pad_E8(nullptr),
      m_getItemId(0), pad_14C(0), m_seq(this), m_seqStarted(false), pad_4F0(nullptr), pad_504(-1),
      pad_548(QuestID(), 0, 0, TASK_STATE(0)), pad_568(0), m_blWeaponContext(nullptr), m_callContext(nullptr),
      m_sellHandle(), pad_588(false), pad_589(false) {
    pad_130.setAllocator(getAllocator(ALLOCATOR(0)));
    for (int i = 0; i < 8; ++i) {
        pad_508[i] = nullptr;
    }
    m_callContext = GfMenuCallContext::create();
}

GfMenuObjShop::~GfMenuObjShop() {
    pad_238 = nullptr;
    for (int i = 0; i < 26; ++i) {
        m_numbers[i] = nullptr;
    }
    if (pad_150 != nullptr) {
        pad_150->release();
        pad_150 = nullptr;
    }
    if (pad_158 != nullptr) {
        pad_158->release();
        pad_158 = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (pad_F0 != nullptr) {
        pad_F0->release();
        pad_F0 = nullptr;
    }
    if (pad_E8 != nullptr) {
        pad_E8->release();
        pad_E8 = nullptr;
    }
    if (pad_E0 != nullptr) {
        pad_E0->release();
        pad_E0 = nullptr;
    }
    if (pad_D8 != nullptr) {
        pad_D8->release();
        pad_D8 = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_sellItemList != nullptr) {
        m_sellItemList->release();
        m_sellItemList = nullptr;
    }
    if (m_sellObjList != nullptr) {
        m_sellObjList->release();
        m_sellObjList = nullptr;
    }
    if (pad_4E8 != nullptr) {
        pad_4E8->release();
        pad_4E8 = nullptr;
    }
    if (pad_4F0 != nullptr) {
        pad_4F0->release();
        pad_4F0 = nullptr;
    }
    for (int i = 0; i < 8; ++i) {
        if (pad_508[i] != nullptr) {
            pad_508[i]->release();
            pad_508[i] = nullptr;
        }
    }
    if (m_blWeaponContext != nullptr) {
        m_blWeaponContext->release();
        m_blWeaponContext = nullptr;
    }
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
}

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

void GfMenuObjShop::sendOpenEvent(unsigned int handle, int param) {
    if (handle == 0) {
        handle = ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
    }
    ui::EventData event;
    event.m_type = 0x21;
    event.m_param0 = param;
    GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendReturnEvent(unsigned int handle, int param) {
    if (handle != 0) {
        ui::EventData event;
        event.m_type = 0x42;
        event.m_param0 = param;
        GfMenuObject::sendEvent(handle, event, 0.0f);
    }
}

void GfMenuObjShop::reqRefreshItemList() {
    m_refreshItemList = true;
    m_stockNumDirty = true;
}

void GfMenuObjShop::openOrbError(unsigned int error) {
    switch (error) {
    case 1:
        GfMenuManager::openCommonWindow(0xAF);
        break;
    case 2:
        GfMenuManager::openCommonWindow(0xB0);
        break;
    }
}

unsigned int GfMenuObjShop::getShopSubActLayer(unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (m_mode) {
    case 0:
        return acc.searchChild("LAY_store_action");
    case 1:
        return acc.searchChild("LAY_exc_task_list");
    case 2:
        return acc.searchChild("LAY_inn_action");
    case 3:
        return acc.searchChild("LAY_orb_item_list");
    }
    return 0;
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

void GfMenuObjShop::setupExcItem() {
    ui::UIObjectAcc acc(m_handle, "LAY_exc_objective");
    mm::mtl::FixStr<32> name;
    GfMenuItemList::ItemShopExcSetup setup;
    setup.m_id = pad_150->getContents(pad_150->getIndex(false)).m_id;
    setup.m_setup.m_pageRowSize = 5;
    pad_158->clear();
    pad_158->setupFromShopExcTask(setup);
    unsigned int owned = 0;
    unsigned int need = 0;
    for (unsigned int i = 0; i < pad_158->getSize(); i++) {
        const MenuItemInfo& item = pad_158->getContents(i);
        m_numbers[17 + i]->setValue(GfMenuItemUtil::getItemNum(item.m_type, item.m_id));
        m_numbers[i + 17]->m_min = 0;
        m_numbers[i + 17]->m_max = 999;
        int have = m_numbers[i + 17]->m_value;
        need += item.m_count;
        owned += have >= item.m_count ? item.m_count : have;
        name.format("TXT_exc_obj_item_cost@%02d", i + 1);
        ui::UIObjectAcc cost(acc.m_handle, name.m_str);
        if (cost.m_object != nullptr) {
            if (m_numbers[i + 17]->m_value < item.m_count) {
                GfMenuObjUtil::setColMulandAdd(cost.m_handle, "txt_warning");
            } else {
                GfMenuObjUtil::setColDefault(cost.m_handle);
            }
        }
    }
    unsigned int got = owned > need ? need : owned;
    m_numbers[6]->m_max = need;
    m_numbers[6]->m_value = got;
    m_numbers[7]->m_value = need;
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

void GfMenuObjShop::SubListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_ctrl = -1;
        break;
    case 3: {
        // the end of its fade (the control's event id): 1 enables the mode's action layer, 2 exits it
        int id = event.m_param0;
        GfMenuObjShop* owner = m_owner;
        unsigned int layer = owner->getShopSubActLayer(acc.m_handle);
        if (id == 1) {
            owner->sendEnableEvent(layer);
        } else {
            owner->sendExitEvent(layer);
            if (m_owner->m_cursor != nullptr) {
                m_owner->m_cursor->release();
                m_owner->m_cursor = nullptr;
            }
        }
        return;
    }
    case 0x21: {
        acc.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        if (m_owner->m_mode == 0 || m_owner->m_mode == 2) {
            param.m_methods = 1;
            param.m_curve = 1;
            param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_l");
        } else {
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_setDefault = true;
            param.m_startFlags = 8;
        }
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        mm::mtl::FixStr<32> name;
        switch (m_owner->m_mode) {
        case 0:
            acc.setDispChild(true, "LAY_store_action");
            acc.setDispChild(false, "LAY_store_list");
            acc.setDispChild(false, "LAY_store_action_cursor");
            GfMenuObjUtil::setColDefault(acc.searchChild("TXT_store_action_buy"));
            GfMenuObjUtil::setColDefault(acc.searchChild("TXT_store_action_sell"));
            m_owner->m_filterIndex = 0;
            m_owner->setGuideText(0x1E);
            break;
        case 1:
            m_owner->m_sellObjList->clear();
            m_owner->m_sellObjList->pickupObject(acc.m_handle, "LAY_exc_task@%02d", 1);
            for (unsigned int i = 0; i < m_owner->m_sellObjList->getSize(); ++i) {
                name.format("IMG_exc_task_select@%02d", i + 1);
                acc.setDispChild(false, name.m_str);
            }
            m_owner->refreshExcReward();
            break;
        case 2: {
            {
                ui::UIObjectAcc back(acc.m_handle, "LAY_inn_select_item_back");
                m_owner->m_selectList->clear();
                m_owner->m_selectList->addObject(acc.searchChild("LAY_inn_select_item@01"));
                bool enable = GfGameUtilCloudSea::isEnableChangeInn();
                {
                    ui::UIObjectAcc item(acc.m_handle, "LAY_inn_select_item@02");
                    item.setDisp(enable);
                    if (enable) {
                        acc.setLayout(back.m_handle, "inn_tag3");
                        m_owner->m_selectList->addObject(item.m_handle);
                    } else {
                        acc.setLayout(back.m_handle, "inn_tag2");
                    }
                }
                m_owner->m_selectList->addObject(back.m_handle);
                m_owner->m_selectList->setIndex(m_owner->m_selectList->getSize() - 1);
            }
            acc.setDispChild(false, "LAY_inn_action_cursor");
            break;
        }
        case 3: {
            m_owner->m_sellObjList->clear();
            m_owner->m_sellObjList->pickupObject(acc.m_handle, "LAY_orb_item@%02d", 1);
            {
                GfMenuItemList::ItemBoxSetup setup;
                setup.m_setup.m_pageRowSize = m_owner->m_sellObjList->getSize();
                setup.m_setup.m_pageScroll = true;
                setup.m_type = 9;
                m_owner->pad_E8->setupFromBox(setup);
            }
            m_owner->pad_E8->setIndex(0);
            unsigned short sortId = GfMenuObjSort::getSortID(8, 0);
            m_owner->pad_E8->sort(sortId, false);
            for (unsigned int i = 0; i < m_owner->m_sellObjList->getPageRowSize(); ++i) {
                name.format("IMG_orb_item_select@%02d", i + 1);
                acc.setDispChild(false, name.m_str);
            }
            m_owner->m_numbers[6]->m_min = 0;
            m_owner->m_numbers[6]->m_max = 999;
            for (int i = 8; i < 15; ++i) {
                m_owner->m_numbers[i]->setValue(0);
                m_owner->m_numbers[i]->m_min = 0;
                m_owner->m_numbers[i]->m_max = 999;
            }
            ui::UIObjectAcc list(acc.m_handle, "LAY_orb_item_list");
            if (m_owner->pad_E8->getSize() == 0) {
                GfMenuObject::setupInputSelection(list.m_handle, -1, 0);
            } else {
                m_owner->m_sellObjList->clear();
                m_owner->m_sellObjList->pickupObject(acc.m_handle, "LAY_orb_item@%02d", 1);
                if (m_owner->m_cursor != nullptr) {
                    m_owner->m_cursor->release();
                    m_owner->m_cursor = nullptr;
                }
                GfMenuObject::resetInputSelection(list.m_handle);
                GfMenuObject::setupInputSelectionFromList(list.m_handle, *m_owner->pad_E8);
            }
            m_owner->updateOrbRecipe();
            break;
        }
        }
        GfMenuObjShop* owner = m_owner;
        owner->m_refreshItemList = true;
        owner->m_stockNumDirty = false;
        m_ctrl = ctrl;
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        if (m_owner->m_mode == 0 || m_owner->m_mode == 2) {
            param.m_methods = 2;
            param.m_curve = 1;
            param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_out_l");
        } else {
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_setDefault = true;
            param.m_startFlags = 10;
        }
        param.m_startFlags |= 2;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        if (m_owner->m_mode == 0) {
            acc.setDispChild(false, "LAY_store_action_cursor");
        } else if (m_owner->m_mode == 2) {
            acc.setDispChild(false, "LAY_inn_action_cursor");
        }
        m_ctrl = ctrl;
        break;
    }
    }
    UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::refreshExcReward() {
    if (pad_150 == nullptr) {
        return;
    }
    ui::UIObjectAcc item(m_handle, "LAY_exc_reward_item");
    ui::UIObjectAcc quest(m_handle, "LAY_exc_reward_quest");
    unsigned int task = pad_150->getContents(pad_150->getIndex(false)).m_id;
    unsigned int value;
    bool hide = false;
    if (getExcTaskReward(task, value, m_itemList, hide)) {
        m_numbers[23]->setValue(value);
        item.setDisp(!hide);
        quest.setDisp(false);
    } else {
        unsigned char* fp = GfDataBdat::getFP(0xF2);
        if (fp != nullptr && GfMenuBdat::isValidBdatID(fp, task)) {
            value = static_cast<unsigned char>(Bdat::getVal(fp, "AddFlagValue", task));
            item.setDisp(false);
            quest.setDisp(!hide);
            unsigned int limit;
            unsigned int count;
            unsigned int itemCount;
            unsigned int itemLimit;
            if (!pad_548.m_questId.empty() && GfQuestTask::getTaskCount(pad_548, limit, count, itemCount, itemLimit)) {
                m_numbers[24]->setMax(limit);
                m_numbers[24]->setValue(count);
                m_numbers[25]->setValue(limit);
            }
        } else {
            item.setDisp(false);
            quest.setDisp(false);
        }
    }
    ui::UIObjectAcc(m_handle, "TXT_exc_reward_quest_index").setDisp(quest.isDisp());
    ui::UIObjectAcc(m_handle, "TXT_exc_reward_item_index").setDisp(item.isDisp());
    if (GfMenuObjUtil::isValidExpansion(3) && GfMenuManager::isOpenCampMenu()) {
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_item").setDisp(false);
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_quest").setDisp(false);
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_secret").setDisp(false);
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_camp").setDisp(true);
        bool normal = true;
        if (m_itemList->getSize() != 0) {
            normal = m_itemList->getContents(0).m_type != 10;
        }
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_camp_normal").setDisp(normal);
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_camp_pouch").setDisp(!normal);
    } else {
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_secret").setDisp(hide);
        ui::UIObjectAcc(m_handle, "LAY_exc_reward_camp").setDisp(false);
    }
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

void GfMenuObjShop::NumSelectListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            acc.setDispChild(true, "IMG_num_select_cursor");
        } else if (event.m_param0 == 2) {
            if (m_mode == 0 && m_owner->pad_34 == 1 && m_count > 0) {
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                GfMenuObject::sendCloseEvent(main.m_handle, 0, 0.0f);
            } else if (m_owner->pad_D0 != 0) {
                ui::EventData data;
                data.m_type = 0x42;
                GfMenuObject::sendEvent(m_owner->pad_D0, data, 0.0f);
            }
        }
        break;
    case 6: {
        int count = event.m_param0;
        ItemPrice price;
        GfItemUtil::getPrice(price, m_item, m_owner->m_shopId);
        m_owner->m_numbers[2]->m_value = count;
        bool buy = m_mode == 0;
        m_owner->m_numbers[3]->setValue((!buy ? price.m_sellPrice : price.m_price) * count);
        GfMenuObjUtil::playSE(0x19);
        m_count = count;
        break;
    }
    case 8: {
        if (event.m_param1 == 1) {
            if (m_count < 1) {
                break;
            }
            if (m_mode == 0) {
                m_owner->m_result = 1;
                m_owner->m_resultParam = 0;
                GfMenuObjUtil::playSE(0x18);
                GfShopUtil::execBuy(m_item, m_count, m_owner->m_shopId);
                MenuItemInfo item;
                item.m_id = m_item;
                item.m_type = GfItemUtil::getType(item.m_id);
                item.m_count = m_count;
                m_owner->m_sellItemList->addItem(item, false);
            } else {
                GfItemHandle sell =
                    GfMenuItemUtil::canCountStack(GfItemUtil::getType(m_item)) ? GfItemHandle() : m_owner->m_sellHandle;
                GfShopUtil::execSell(m_item, m_count, m_owner->m_shopId, sell);
                MenuItemInfo item;
                item.m_id = m_item;
                item.m_type = GfItemUtil::getType(item.m_id);
                item.m_count = m_count;
                if (GfMenuItemUtil::canCountStack(GfItemUtil::getType(m_item))) {
                    m_owner->m_sellItemList->decItem(item, false);
                } else {
                    item.m_entry = sell;
                    m_owner->m_sellItemList->decItemH(item, false);
                }
                GfMenuObjUtil::playSE(0x18);
            }
            GfMenuObjShop* owner = m_owner;
            owner->m_refreshItemList = true;
            owner->m_stockNumDirty = true;
        } else if (event.m_param1 == 2) {
            m_count = 0;
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startPresetCtrl(acc.searchChild("LAY_num_select_main"), param);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        acc.setDispChild(false, "IMG_num_select_cursor");
        break;
    }
    case 0x21: {
        unsigned int id = event.m_param0;
        m_item = id;
        m_count = 0;
        m_mode = event.m_param3;
        acc.setDisp(true);
        {
            ui::UIObjectAcc main(acc.searchChild("LAY_num_select_main"));
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 0;
            param.m_eventId = 1;
            int ctrl = GfMenuObjUtil::startPresetCtrl(main.m_handle, param);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        {
            mm::mtl::FixStr<32> name;
            name.format("TXT_num_select_index@%02d", 1);
            acc.setDispChild(m_mode == 0, name.m_str);
            name.format("TXT_num_select_index@%02d", 2);
            acc.setDispChild(m_mode == 1, name.m_str);
        }
        ItemPrice price;
        GfItemUtil::getPrice(price, id, m_owner->m_shopId);
        unsigned int max;
        if (m_mode == 0) {
            if (m_owner->pad_34 == 1) {
                max = 1;
            } else {
                int stock = GfItemUtil::getEnableStock(id);
                int have = GfItemUtil::getItemBoxCount(id);
                if (GfDataItem::getItemType(id) == 2) {
                    max = GfItemUtil::getEnableStock(id) - GfItemUtil::getCountByType(ItemType::Type(2));
                } else {
                    max = stock - have;
                }
                if (GfDataUtil::getMoney() < price.m_price * max) {
                    max = GfDataUtil::getMoney() / price.m_price;
                }
            }
        } else if (!GfMenuItemUtil::canCountStack(GfItemUtil::getType(id))) {
            max = 1;
        } else {
            max = GfItemUtil::getItemBoxCount(id);
            if (GfDataUtil::getMoney() + price.m_sellPrice * max > 999999999) {
                unsigned int room = 999999999 - GfDataUtil::getMoney();
                max = room / price.m_sellPrice;
                if (room % price.m_sellPrice != 0) {
                    max++;
                }
            }
        }
        m_max = max;
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelection(handle, 0, max + 1);
        m_owner->m_numbers[2]->m_value = 0;
        m_owner->m_numbers[3]->m_value = 0;
        m_owner->m_numbers[3]->m_max = 999999999;
        m_owner->pad_D8->setIndex(0);
        m_owner->setGuideText(0x3E);
        break;
    }
    }
    UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::OrbListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            m_owner->pad_E8->setIndex(index);
            unsigned int page = m_owner->pad_E8->getIndex(true);
            m_owner->m_sellObjList->setIndex(page);
            GfMenuItemList* list = m_owner->pad_E8;
            unsigned int orb = GfRecipeOrbUtil::getEquipOrb(list->getContents(list->getIndex(false)).m_id);
            MenuItemInfo& item = m_owner->pad_238->m_item;
            item.m_type = 3;
            item.m_id = orb;
            item.m_count = 1;
            item.m_entry.m_handle = 0;
            m_owner->updateOrbRecipe();
            m_owner->reqRefreshItemList();
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        return;
    }
    case 8: {
        bool close;
        switch (event.m_param1) {
        case 1: {
            GfMenuItemList* list = m_owner->pad_E8;
            int error = GfMenuItemUtil::canCreateOrb(list->getContents(list->getIndex(false)).m_id);
            if (error != 0) {
                GfMenuObjUtil::playSECommon(2);
                m_owner->openOrbError(error);
                return;
            }
            switch (m_owner->m_recipeInfo.m_recipeType) {
            case 0: {
                unsigned int recipe = acc.searchSibiling("LAY_orb_rcp");
                GfMenuObjUtil::playSECommonDecide();
                if (recipe != 0) {
                    if (m_owner->pad_F0->getSize() != 0) {
                        m_owner->pad_F0->setIndex(0);
                    }
                    ui::EventData enable;
                    enable.m_type = 0x40;
                    GfMenuObject::sendEvent(recipe, enable, 0.0f);
                }
                break;
            }
            case 1: {
                unsigned int recipe = acc.searchSibiling("LAY_orb_rcp");
                GfMenuObjUtil::playSECommonDecide();
                if (recipe != 0) {
                    if (m_owner->pad_F0->getSize() != 0) {
                        m_owner->pad_F0->setIndex(0);
                    }
                    ui::EventData enable;
                    enable.m_type = 0x40;
                    GfMenuObject::sendEvent(recipe, enable, 0.0f);
                }
                break;
            }
            case 2:
                GfMenuManager::openCommonWindow(0xA3);
                m_owner->m_dialog = acc.m_handle;
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjShop::seqWaitOrbCreate);
                m_owner->m_seq.addJob(&GfMenuObjShop::seqItemGet);
                m_owner->m_seq.addJob(&GfMenuObjShop::seqEndDialog);
                GfMenuObjUtil::playSECommonDecide();
                break;
            default:
                GfMenuObjUtil::playSECommonDecide();
                return;
            }
            close = false;
            break;
        }
        case 2:
            if (m_owner->pad_34 == 2) {
                return;
            }
            GfMenuObjUtil::playSECommonCancel();
            close = true;
            break;
        case 0x11:
            GfMenuObjSort::open(acc.m_handle, acc.searchChild("TXT_orb_item_sort_label"), 8, m_owner->pad_14C);
            close = false;
            break;
        default:
            return;
        }
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        if (m_owner->m_cursor != nullptr) {
            m_owner->m_cursor->release();
            m_owner->m_cursor = nullptr;
        }
        acc.setDispChild(false, "IMG_orb_item_cursor");
        if (close) {
            m_owner->sendCloseEvent(0);
        }
        return;
    }
    case 0x40: {
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        m_owner->setGuideText(0x3F);
        m_owner->updateOrbRecipe();
        m_owner->reqRefreshItemList();
        m_owner->sendOpenEvent(acc.searchSibiling("LAY_orb_rcp"), 0);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 2, m_owner->pad_34 != 2);
        break;
    }
    case 0x42:
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 2, m_owner->pad_34 != 2);
        return;
    case 0x148:
        GfMenuObject::enableInput(handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        if (m_owner->pad_14C != event.m_param0) {
            unsigned short sortId = GfMenuObjSort::getSortID(8, event.m_param0);
            m_owner->pad_E8->sort(sortId, false);
            m_owner->pad_14C = event.m_param0;
        }
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->pad_E8);
        return;
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

bool GfMenuObjShop::seqWaitOrbCreate() {
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    if (static_cast<unsigned short>(GfMenuManager::getCommonWindowResult()) != 0) {
        m_itemGetState = 2;
    } else {
        unsigned int item = pad_E8->getContents(pad_E8->getIndex(false)).m_id;
        mm::mtl::FixedVector<OrbRecipe, 128> items;
        bool enable;
        if (m_recipeInfo.m_recipeType == 2) {
            enable = GfRecipeOrbUtil::isEnableRecipe(m_recipeInfo.m_recipe);
            if (enable) {
                const mm::mtl::FixedVector<RecipeInfo::Item, 8>& results = m_recipeInfo.getResultItems();
                for (unsigned int i = 0; i < results.size(); i++) {
                    OrbRecipe recipe;
                    recipe.m_item = results[i].m_item;
                    recipe.m_number = results[i].m_number;
                    items.push_back(recipe);
                }
            }
        } else {
            for (unsigned int i = 0; i < pad_F0->getSize(); i++) {
                if (pad_130[i] != 0) {
                    OrbRecipe recipe;
                    recipe.m_item = pad_F0->getContents(i).m_id;
                    recipe.m_number = pad_130[i];
                    items.push_back(recipe);
                }
            }
            enable = GfRecipeOrbUtil::isEnabaleOrbRecipe(m_recipeInfo.m_recipe, items);
        }
        if (enable) {
            GfRecipeOrbUtil::execOrbRecipe(item, &items);
            MenuItemInfo info = pad_E8->getContents(pad_E8->getIndex(false));
            info.m_count = 1;
            m_getItemId = GfRecipeOrbUtil::getEquipOrb(info.m_id);
            pad_E8->decItem(info, false);
            {
                ui::UIObjectAcc list(m_handle, "LAY_orb_item_list");
                resetInputSelection(list.m_handle);
                setupInputSelectionFromList(list.m_handle, *pad_E8);
            }
            m_result = 1;
            m_resultParam = 0;
            GfMenuObjUtil::playSE(0x1a);
        }
        m_itemGetState = 1;
    }
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

void GfMenuObjShop::refreshOrbRecipeOperation() {
    ui::UIObjectAcc acc(m_handle, "LAY_orb_rcp");
    if (acc.m_object == nullptr) {
        return;
    }
    pad_F0->getIndex(false);
    if (pad_130.size() == 0) {
        return;
    }
    unsigned int max = m_numbers[7]->m_value;
    unsigned int total = m_numbers[6]->m_value;
    short number = pad_130[pad_F0->getIndex(false)];
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, total == max);
    bool add = total < max && number < pad_F0->getContents(pad_F0->getIndex(false)).m_count;
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, add);
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, number > 0);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 8; i++) {
        if (i >= pad_F0->getSize()) {
            break;
        }
        short set = pad_130[pad_F0->getPageIndex(i)];
        short count = pad_F0->getContents(pad_F0->getPageIndex(i)).m_count;
        bool more = total < max && set < count;
        name.format("IMG_orb_rcp_item_set_r@%02d", i + 1);
        {
            ui::UIObjectAcc right(acc.m_handle, name.m_str);
            right.setAlpha(more ? 1.0f : 0.5f);
        }
        bool less = set > 0;
        name.format("IMG_orb_rcp_item_set_l@%02d", i + 1);
        {
            ui::UIObjectAcc left(acc.m_handle, name.m_str);
            left.setAlpha(less ? 1.0f : 0.5f);
        }
    }
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
