#include "classes/gf/GfMenuObjQuestReward.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuQuestAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestID.h"
#include "mm/mtl/FixStr.h"
#include <string.h>

namespace gf {

GfMenuObjQuestReward::GfMenuObjQuestReward(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjQuestReward::~GfMenuObjQuestReward() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjQuestReward::open(GfMenuCallContext* context, bool flag) {
    if (context != nullptr && GfMenuObjUtil::checkCCNext(context, 0x21)) {
        ui::UIObjectAcc acc(context->m_handle);
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = flag;
        event.m_param1 = 0;
        GfMenuObject::sendEvent(context->m_handle, event, 0.0f);
    }
}

void GfMenuObjQuestReward::create(GfMenuCallContext* context, const OpenParam& param, bool flag) {
    if (!GfMenuObjUtil::checkCCStart(context)) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x21));
    if (acc.m_object == nullptr) {
        return;
    }
    ui::UIObjectAcc reward(acc.searchChild("LAY_reward"));
    ui::UIObjectAcc window(reward.duplicate(param.m_handle));
#line 63
    RewardListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RewardListener();
    memset(listener->pad_0C, 0, sizeof(listener->pad_0C));
    memset(listener->pad_20, 0, sizeof(listener->pad_20));
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(window.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    ui::EventData event(0);
#line 68
    OpenParam* open = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) OpenParam();
    *open = param;
    event.m_type = 0x101;
    event.m_paramPtr = open;
    GfMenuObject::sendEvent(window.m_handle, event, 0.0f);
    GfMenuObject::startCallContext(context, 0x21, window.m_handle);
    if (flag) {
        GfMenuObjQuestReward::open(context, false);
    }
}

void GfMenuObjQuestReward::RewardListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x101: {
        OpenParam* param = static_cast<OpenParam*>(event.m_paramPtr);
        if (param != nullptr) {
            m_items = GfMenuItemList::create();
            m_quest = param->m_quest;
            m_number = param->m_number;
            m_kind = param->pad_C;
            m_fade = false;
            if (param->pad_C == 1) {
                GfMenuMissionAdapter::createFromReference(
                    acc.searchChild("TXT_reward_point_l3_num@01"), 9,
                    param->m_number, false);
                GfMenuMissionAdapter::createFromReference(
                    acc.searchChild("TXT_reward_point_l3_num@02"), 0xB,
                    param->m_number, false);
                GfMenuMissionAdapter::createFromReference(
                    acc.searchChild("TXT_reward_point_l3_num@03"), 0x10,
                    param->m_number, false);
                acc.setDispChild(false, "TXT_reward_point_l3_idx@03");
                acc.setDispChild(true, "TXT_reward_point_l3_idx_mer@03");
            } else {
                GfMenuQuestAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@01"),
                                                        static_cast<GfMenuReferenceQuest*>(param->m_quest.get()),
                                                        0x26, false);
                GfMenuQuestAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@02"),
                                                        static_cast<GfMenuReferenceQuest*>(param->m_quest.get()),
                                                        0x27, false);
                GfMenuQuestAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@03"),
                                                        static_cast<GfMenuReferenceQuest*>(param->m_quest.get()),
                                                        0x28, false);
            }
            acc.setDispChild(true, "LAY_reward_point_l3");
            mm::mtl::FixStr<32> name;
            for (int i = 0; i < 4; i++) {
                name.format("TXT_reward_item_name@%02d", i + 1);
                GfMenuItemAdapter* item = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, m_items, i, false);
                if (item != nullptr) {
                    name.format("LAY_reward_item@%02d", i + 1);
                    item->m_rowHandle = acc.searchChild(name.m_str);
                }
                name.format("TXT_reward_item_num@%02d", i + 1);
                GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 3, m_items, i, false);
                name.format("IMG_reward_item_icon@%02d", i + 1);
                GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, m_items, i, false);
            }
            delete param;
        }
        break;
    }
    case 1:
        acc.setDisp(false);
        break;
    case 2:
        if (m_items != nullptr) {
            m_items->release();
            m_items = nullptr;
        }
        acc.setTerm();
        break;
    case 3:
        if (event.m_param0 == 3) {
            m_quest = nullptr;
            acc.setTerm();
        }
        break;
    case 0x21: {
        m_fade = event.m_param0 == 1;
        if (m_kind == 0) {
            GfMenuItemList::QuestRewardSetup setup;
            QuestID quest;
            static_cast<GfMenuReferenceQuest*>(m_quest.operator->())->getQuest(quest);
            QuestID prt = GfDataQuest::getListPRTQuestID(quest);
            if (!prt.empty()) {
                quest = prt;
            }
            setup.m_setup.m_pageRowSize = 4;
            setup.m_reward = GfDataQuest::getListRewardSetA(quest);
            if (GfQuestInfo::isQuestFin(quest)) {
                if (GfQuestInfo::getState(quest) == 2) {
                    setup.m_reward = GfDataQuest::getListRewardSetA(quest);
                } else {
                    setup.m_reward = GfDataQuest::getListRewardSetB(quest);
                }
            }
            m_items->clear();
            m_items->setupFromQuestReward(setup);
        } else if (m_kind == 1) {
            GfMenuItemList::MissionRewardSetup setup;
            setup.m_reward = m_number->m_value;
            setup.m_setup.m_pageRowSize = 4;
            m_items->clear();
            m_items->setupFromMissionReward(setup);
        }
        if (m_fade) {
            GfMenuObjUtil::CtrlParam param;
            param.m_setDefault = true;
            param.m_methods = 1;
            param.m_time = 0.1f;
            param.m_eventId = 1;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        } else {
            acc.setDisp(true);
        }
        break;
    }
    case 0x22: {
        int param0 = event.m_param0;
        if (m_fade) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.1f;
            param.m_setDefault = true;
            param.m_startFlags = 10;
            param.m_eventId = param0 == 1 ? 3 : 2;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        } else {
            acc.setDisp(false);
            if (param0 == 1) {
                m_quest = nullptr;
                acc.setTerm();
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjQuestReward::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x21, acc.m_handle);
        GfMenuObject::initialize();
        acc.setSuspend(true);
    }
}

GfMenuObjQuestReward::RewardListener::~RewardListener() {}

void GfMenuObjQuestReward::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjQuestReward::update() {
    GfMenuObject::update();
}

}  // namespace gf
