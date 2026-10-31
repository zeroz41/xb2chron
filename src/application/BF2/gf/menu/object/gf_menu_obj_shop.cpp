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
        fn_710047688C();
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
        if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuManager::fn_710035DC94()) {
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

void GfMenuObjShop::fn_7100477960() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
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

void GfMenuObjShop::fn_710047688C() {
    ui::UIObjectAcc stock(m_handle, "LAY_stock_num");
    unsigned int type = GfMenuReference::fn_710036934C();
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
            unsigned short scenario = GfDataBlade::fn_7100231884();
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

}  // namespace gf
