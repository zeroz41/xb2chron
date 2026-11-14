#include "classes/gf/GfMenuObjBalloon.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfMenuStrLinker.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/gf/GfReqManager.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataItem.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfReqCommand.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"
#include "mm/mtl/Delegate.h"

namespace gf {

GfMenuObjBalloon::~GfMenuObjBalloon() {
    m_getItems.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
    m_values.clear();
    if (m_moneyList != nullptr) {
        m_moneyList->release();
        m_moneyList = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
}

void GfMenuObjBalloon::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBalloon::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjBalloon::seqSave() {
    m_saveRequest = GfReqCommand::reqSaveForLastGame(SAVESLOT(0x16));
    GfMenuObjFade::dispSaving(true, 0);
    return true;
}

bool GfMenuObjBalloon::seqSaveWait() {
    if (GfReqManager::isValid(m_saveRequest)) {
        return false;
    }
    GfMenuObjFade::dispSaving(false, 0);
    m_saveRequest = -1;
    GfMenuObject::addResultCallContext(ui::UIObjectAcc(m_handle, "LAY_select").m_handle, 2, 0);
    return true;
}

bool GfMenuObjBalloon::canGetExpReward() {
    if (m_moneyType != 0) {
        unsigned char* bdat = GfDataBdat::getFP(0xDD);
        unsigned int row = m_moneyType;
        mm::mtl::FixStr<32> column;
        if (bdat == nullptr) {
            return false;
        }
        for (int i = 1; i <= 3; i++) {
            column.format("ItemID%d", i);
            unsigned int id = static_cast<unsigned short>(Bdat::getVal(bdat, column.m_str, row));

            column.format("ItemNumber%d", i);
            signed char num = Bdat::getVal(bdat, column.m_str, row);
            int count;
            if (GfMenuItemUtil::canCountStack(GfDataItem::getItemType(id))) {
                count = GfItemUtil::getItemBoxCount(id);
            } else {
                count = GfItemUtil::getCountByType(static_cast<ItemType::Type>(GfDataItem::getItemType(id)));
            }
            if (static_cast<unsigned int>(count + num) > static_cast<unsigned int>(GfItemUtil::getEnableStock(id))) {
                return false;
            }
        }
    }
    if (m_money != 0 && GfDataHana::getEther() + m_money > 999999999) {
        return false;
    }
    return true;
}

void GfMenuObjBalloon::AutoTalkListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x100: {
        unsigned short text = event.m_param0;
        ui::UIObjectAcc talk(acc.searchDuplicatedChild("LAY_auto_talk", event.m_param3));
        if (talk.m_object != nullptr) {
            {
                ui::UIObjectAcc msg(talk.m_handle, "TXT_auto_talk_msg");
                GfMenuObject::setText(msg.m_handle, text);
            }
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_emotion";
            param.m_motion = "fade_in";
            GfMenuObjUtil::startCtrl(talk.m_handle, param, nullptr);
        }
        break;
    }
    case 0x103: {
        ui::UIObjectAcc talk(acc.searchDuplicatedChild("LAY_auto_talk", event.m_param3));
        if (talk.m_object != nullptr) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_emotion";
            param.m_motion = "fade_out";
            param.m_startFlags = 1;
            GfMenuObjUtil::startCtrl(talk.m_handle, param, nullptr);
            GfMenuObject::termCallContext(talk.m_handle);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBalloon::close(GfMenuCallContext* context, bool flag) {
    if (!context->isActive()) {
        return;
    }
    if (context->isTerm()) {
        return;
    }
    unsigned int handle = 0;
    switch (context->m_objectId) {
    case 2:
    case 3:
        handle = GfMenuObject::getAttachedObject(2);
        break;
    case 4:
        handle = GfMenuObject::getAttachedObject(4);
        break;
    case 5:
        handle = GfMenuObject::getAttachedObject(5);
        break;
    case 7:
        handle = GfMenuObject::getAttachedObject(7);
        break;
    case 8:
        handle = GfMenuObject::getAttachedObject(8);
        break;
    case 9:
        handle = GfMenuObject::getAttachedObject(9);
        break;
    }
    unsigned int target = context->m_handle;
    if (ui::UIUtil::isValid(target)) {
        GfMenuObject::nextCallContext(context, 6);
        ui::EventData event;
        event.m_type = 0x103;
        event.m_param2 = flag;
        event.m_param3 = ui::UIObjectAcc(target).getDuplicateIndex();
        GfMenuObject::sendEvent(handle, event, 0.0f);
    }
}

void GfMenuObjBalloon::nextEvent(GfMenuCallContext* context, const NextParam& param) {
    if (context->isActive() && (context->m_objectId & ~1u) == 2) {
        unsigned int handle = GfMenuObject::getAttachedObject(2);
        unsigned int target = context->m_handle;
        if (ui::UIUtil::isValid(target)) {
            GfMenuObject::nextCallContext(context, 3);
            unsigned short text = GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_msgId));
            ui::EventData event;
            event.m_type = 0x104;
            event.m_param0 = text;
            event.m_param3 = ui::UIObjectAcc(target).getDuplicateIndex();
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjBalloon::openEventSelectBox(GfMenuCallContext* context, const OpenSelectBoxParam& param) {
    if (context->getState() == 0 && param.m_selectIds.size() != 0) {
        unsigned int handle = GfMenuObject::getAttachedObject(7);
        unsigned short text = GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_msgId));
        for (int i = 0; i < (int)param.m_selectIds.size(); i++) {
            GfMenuCallManager::sys()->m_strLinker.addSelectString(ui::UIStr(param.m_selectBdat, param.m_selectIds[i]));
        }
        if (context != nullptr) {
            GfMenuObject::startCallContext(context, 7, handle);
        }
        ui::EventData event;
        event.m_type = 0x105;
        event.m_param0 = text;
        GfMenuObject::sendEvent(handle, event, 0.0f);
        ui::UIObjectAcc(handle).setSuspend(false);
    }
}

void GfMenuObjBalloon::openEventSelectMoney(GfMenuCallContext* context, const OpenSelectMoneyParam& param) {
    if (GfMenuObjUtil::checkCCStart(context) && param.m_selectIds.size() != 0) {
        unsigned int handle = GfMenuObject::getAttachedObject(8);
        if (context != nullptr) {
            GfMenuObject::startCallContext(context, 8, handle);
        }
        ui::EventData event;
#line 2939
        OpenSelectMoneyParam* copy = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) OpenSelectMoneyParam();
        *copy = param;
        event.m_type = 0x21;
        event.m_paramPtr = copy;
        GfMenuObject::sendEvent(handle, event, 0.0f);
        ui::UIObjectAcc(handle).setSuspend(false);
    }
}

void GfMenuObjBalloon::openEventSelectExp(GfMenuCallContext* context, const OpenSelectExpParam& param) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        if (param.m_values.size() == 0) {
            context->abort();
            return;
        }
        unsigned int handle = GfMenuObject::getAttachedObject(8);
        if (context != nullptr) {
            GfMenuObject::startCallContext(context, 8, handle);
        }
        ui::EventData event;
#line 2977
        OpenSelectExpParam* copy = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) OpenSelectExpParam();
        *copy = param;
        event.m_type = 0x21;
        event.m_paramPtr = copy;
        event.m_param2 = 1;
        GfMenuObject::sendEvent(handle, event, 0.0f);
        ui::UIObjectAcc(handle).setSuspend(false);
    }
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBalloon>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
