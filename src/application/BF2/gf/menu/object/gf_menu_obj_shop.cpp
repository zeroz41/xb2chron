#include "classes/gf/GfMenuObjShop.h"
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

namespace gf {

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
    if (!m_sleepFadeStarted) {
        GfMenuFade::setFade(2, 30, mm::Col4::black);
        m_sleepFadeStarted = true;
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

}  // namespace gf
