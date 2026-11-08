#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfMenuObjQuestLog.h"
#include "gf/GfMenuSequence.h"
#include "classes/gf/GfMenuObjQuestLog.h"
#include "classes/gf/GfMenuObjQuestLog/TitleListener.h"
#include "classes/gf/GfMenuObjQuestLog/LogListener.h"
#include "classes/gf/GfMenuObjQuestLog/OrderListener.h"
#include "classes/gf/GfMenuObjQuestLog/CompleteListener.h"
#include "classes/gf/GfMenuObjQuestLog.h"
#include "classes/gf/GfMenuObjQuestLog/CompleteListener.h"
#include "classes/gf/GfMenuObjQuestLog/LogListener.h"
#include "classes/gf/GfMenuObjQuestLog/OrderListener.h"
#include "classes/gf/GfMenuObjQuestLog/TitleListener.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjQuestReward.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIEventManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuQuestAdapter.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/IGfMenuReferenceItem.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "gf/QuestTaskParam.h"
#include "gf/GfQuestTask.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfItemUtil.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjQuestLog::GfMenuObjQuestLog(unsigned int handle)
    : GfMenuObject(handle), m_refs(), pad_58(), m_logOpened(), pad_5A(), m_listVisible(), m_titleSeq(this), m_logSeq(this), m_orderSeq(this), pad_940(false),
      pad_948(false), m_rewardContext(nullptr), m_taskCount(0), pad_95C() {}

GfMenuObjQuestLog::~GfMenuObjQuestLog() {
    for (int i = 0; i < 6; ++i) {
        m_refs[i] = nullptr;
    }
    if (m_rewardContext != nullptr) {
        m_rewardContext->release();
        m_rewardContext = nullptr;
    }
}

void GfMenuObjQuestLog::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (main.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x20, main.m_handle);
        m_refs[0] = GfMenuReferenceQuest::create();
        m_refs[1] = GfMenuReferenceQuest::create();
        m_refs[2] = GfMenuReferenceQuest::create();
        m_refs[3] = GfMenuReferenceNumber::create();
        m_refs[4] = GfMenuReferenceNumber::create();
        m_refs[5] = GfMenuReferenceItem::create();
        getRef<GfMenuReferenceQuest>(2)->m_quest = QuestID();
        {
            ui::UIObjectAcc title(main.m_handle, "LAY_title");
            GfMenuQuestAdapter::createFromReference(
                title.searchChild("TXT_title"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[0].get())), 0,
                false);
#line 145
            TitleListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TitleListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(title.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        {
            ui::UIObjectAcc log(main.m_handle, "LAY_log");
            GfMenuQuestAdapter* task = GfMenuQuestAdapter::createFromReference(
                log.searchChild("TXT_log_info_task"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[1].get())), 0x2E,
                false);
            if (task != nullptr) {
                task->m_reference =
                    mm::mtl::IntrusivePtr<GfMenuReferenceNumber>(static_cast<GfMenuReferenceNumber*>(m_refs[3].get()));
            }
            GfMenuQuestAdapter* itemNum = GfMenuQuestAdapter::createFromReference(
                log.searchChild("TXT_log_info_task_item_num"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[1].get())), 0x2F,
                true);
            if (itemNum != nullptr) {
                itemNum->m_reference =
                    mm::mtl::IntrusivePtr<GfMenuReferenceNumber>(static_cast<GfMenuReferenceNumber*>(m_refs[3].get()));
            }
            GfMenuQuestAdapter* itemMax = GfMenuQuestAdapter::createFromReference(
                log.searchChild("TXT_log_info_task_item_max"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[1].get())), 0x30,
                false);
            if (itemMax != nullptr) {
                itemMax->m_reference =
                    mm::mtl::IntrusivePtr<GfMenuReferenceNumber>(static_cast<GfMenuReferenceNumber*>(m_refs[3].get()));
            }
            GfMenuQuestAdapter* cond = GfMenuQuestAdapter::createFromReference(
                log.searchChild("IMG_log_cond"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[1].get())), 0x35,
                false);
            if (cond != nullptr) {
                cond->m_reference =
                    mm::mtl::IntrusivePtr<GfMenuReferenceNumber>(static_cast<GfMenuReferenceNumber*>(m_refs[3].get()));
            }
            GfMenuItemAdapter::createFromReference(
                log.searchChild("TXT_log_info_task_item"), 0,
                mm::mtl::IntrusivePtr<IGfMenuReferenceItem>(static_cast<IGfMenuReferenceItem*>(m_refs[5].get())), false);
            if (GfMenuObjUtil::isValidExpansion(3)) {
                GfMenuItemAdapter::createFromReference(
                    log.searchChild("IMG_log_info_task_item_icon"), 2,
                    mm::mtl::IntrusivePtr<IGfMenuReferenceItem>(static_cast<IGfMenuReferenceItem*>(m_refs[5].get())),
                    false);
            }
            GfMenuReferenceAdapter* page = GfMenuReferenceAdapter::create(
                log.searchChild("TXT_log_info_task_page_num"),
                mm::mtl::IntrusivePtr<GfMenuReferenceNumber>(static_cast<GfMenuReferenceNumber*>(m_refs[3].get())), true);
            if (page != nullptr) {
                page->m_offset = 1;
            }
            GfMenuReferenceAdapter::create(
                log.searchChild("TXT_log_info_task_page_max"),
                mm::mtl::IntrusivePtr<GfMenuReferenceNumber>(static_cast<GfMenuReferenceNumber*>(m_refs[4].get())), true);
#line 189
            LogListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LogListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(log.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuObject::addNumberEventCondition(log.m_handle, "TXT_log_info_task_item_num", 1, 0);
            ui::UIObjectAcc base(log.m_handle, "IMG_log_base");
            base.startAnimation("log_fade_in", false);
            log.setDispChild(true, "LAY_log_index@01");
        }
        {
            ui::UIObjectAcc order(main.m_handle, "LAY_order");
#line 211
            OrderListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) OrderListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(order.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        {
            ui::UIObjectAcc complete(main.m_handle, "LAY_complete");
            GfMenuQuestAdapter::createFromReference(
                complete.searchChild("TXT_comp_ret_win_title"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[2].get())), 0,
                false);
            GfMenuQuestAdapter::createFromReference(
                complete.searchChild("TXT_comp_ret_win_result"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[2].get())), 2,
                false);
            GfMenuQuestAdapter::createFromReference(
                complete.searchChild("IMG_comp_ret_thumb"),
                mm::mtl::IntrusivePtr<GfMenuReferenceQuest>(static_cast<GfMenuReferenceQuest*>(m_refs[2].get())), 0x39,
                false);
#line 231
            CompleteListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) CompleteListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(complete.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuObject::initialize();
    }
}

void GfMenuObjQuestLog::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjQuestLog::order(GfMenuCallContext* context, QuestID id) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
        if (main.m_object != nullptr) {
            ui::UIObjectAcc order(main.searchChild("LAY_order"));
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = id.m_id;
            GfMenuObject::sendEvent(order.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x20, order.m_handle);
        }
    }
}

void GfMenuObjQuestLog::openLog() {
    ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
    if (main.m_object != nullptr) {
        ui::UIObjectAcc log(main.searchChild("LAY_log"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(log.m_handle, event, 0.0f);
    }
}

void GfMenuObjQuestLog::closeLog() {
    ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
    if (main.m_object != nullptr) {
        ui::UIObjectAcc log(main.searchChild("LAY_log"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(log.m_handle, event, 0.0f);
    }
}

void GfMenuObjQuestLog::updateTask() {
    ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
    if (main.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x104;
        GfMenuObject::sendEvent(main.searchChild("LAY_log"), event, 0.0f);
    }
}

void GfMenuObjQuestLog::lockLogOpen() {
    GfMenuFlag::set1(0x20, 1);
}

void GfMenuObjQuestLog::unlockLogOpen() {
    GfMenuFlag::set1(0x20, 0);
}

bool GfMenuObjQuestLog::seqLogTaskComplete() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    GfMenuObjUtil::startCtrl(log.m_handle, param, "TXT_log_complete");
    m_logSeq.addAnimJob(log.searchChild("IMG_log_complete_eff"), "clear");
    return true;
}

bool GfMenuObjQuestLog::seqTitleEndWait() {
    ui::UIObjectAcc base(m_handle, "IMG_title_base");
    if (base.isPlayingAnimation()) {
        return false;
    }
    base.setDisp(false);
    return true;
}

bool GfMenuObjQuestLog::seqLogStart() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    GfMenuObject::enableInput(log.m_handle);
    return true;
}

bool GfMenuObjQuestLog::seqLogNextWaitInfo() {
    ui::UIObjectAcc info(m_handle, "LAY_log_info");
    return !GfMenuObjUtil::isBusyCtrl(m_infoCtrl);
}

bool GfMenuObjQuestLog::seqLogNextEnd() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    GfMenuObject::enableInput(log.m_handle);
    return true;
}

bool GfMenuObjQuestLog::seqOrderWait() {
    ui::UIObjectAcc text(m_handle, "TXT_order");
    return !GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(text.m_handle));
}

void GfMenuObjQuestLog::complete(GfMenuCallContext* context, QuestID id) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
        if (main.m_object != nullptr) {
            ui::UIObjectAcc complete(main.searchChild("LAY_complete"));
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = id.m_id;
            GfMenuObject::sendEvent(complete.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x20, complete.m_handle);
        }
    }
}

void GfMenuObjQuestLog::completeTask(const QuestTaskParam& param) {
    ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
    if (main.m_object != nullptr) {
        ui::UIObjectAcc log(main.searchChild("LAY_log"));
        ui::EventData event;
        event.m_type = 0x102;
        event.m_param0 = param.m_questId.m_id;
        event.m_param1 = param.m_task;
        GfMenuObject::sendEvent(log.m_handle, event, 0.0f);
    }
}

void GfMenuObjQuestLog::update() {
    m_titleSeq.update();
    m_logSeq.update();
    m_orderSeq.update();
    QuestID id;
    getRef<GfMenuReferenceQuest>(1)->getQuest(id);
    GfGameScene* scene = GfGameScene::sys();
    if (scene != nullptr) {
        QuestID current = scene->getQuestIdForTaskLog();
        if (!(id == current)) {
            getRef<GfMenuReferenceQuest>(1)->m_quest = scene->getQuestIdForTaskLog();
            ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x20));
            if (main.m_object != nullptr) {
                ui::EventData event;
                event.m_type = 0x101;
                GfMenuObject::sendEvent(main.searchChild("LAY_log"), event, 0.0f);
            }
        }
    }
    {
        ui::UIObjectAcc detail(m_handle, "LAY_log_to_detail_main");
        detail.setAlpha(GfGameManager::isEnableOpenMainMenu() ? 1.0f : 0.5f);
    }
    GfMenuObject::update();
}

void GfMenuObjQuestLog::setupLog() {
    QuestID id;
    getRef<GfMenuReferenceQuest>(1)->getQuest(id);
    m_listVisible = QuestListAcc::get()->getListVisible(id) == 1;
    if (m_logOpened) {
        ui::UIObjectAcc detail(m_handle, "LAY_log_to_detail");
        detail.setDisp(m_listVisible);
        GfMenuManager::setEnableQuestOpen(m_listVisible);
    }
    unsigned int count;
    unsigned int complete;
    GfQuestInfo::getQuestTaskInfo(count, complete, id);
    m_taskCount = count;
    for (unsigned int i = 0; i < m_taskCount; ++i) {
        QuestTaskParam param(id, i, TASK_STATE(0));
        if (GfQuestInfo::getTaskHide(param) == 1) {
            --count;
        }
    }
    getRef<GfMenuReferenceNumber>(3)->m_value = 0;
    GfMenuReferenceNumber* tasks = getRef<GfMenuReferenceNumber>(4);
    tasks->m_value = count;
}

void GfMenuObjQuestLog::setupLogClear() {
    QuestID id;
    getRef<GfMenuReferenceQuest>(1)->getQuest(id);
    QuestTaskParam param(id, getRef<GfMenuReferenceNumber>(3)->m_value, TASK_STATE(0));
    bool complete = GfQuestTask::isCompleteFlag(param);
    ui::UIObjectAcc image(m_handle, "IMG_log_complete");
    image.setImageIndex(!complete);
}

void GfMenuObjQuestLog::setupLogItem() {
    QuestID id;
    GfQuestTaskLogResult result;
    getRef<GfMenuReferenceQuest>(1)->getQuest(id);
    QuestTaskParam param(id, getRef<GfMenuReferenceNumber>(3)->m_value, TASK_STATE(0));
    GfQuestUtil::getMsgQuestTaskLog(result, param);
    unsigned int item = result.m_count2;
    unsigned int type = GfItemUtil::getType(item);
    GfMenuReferenceItem* ref = getRef<GfMenuReferenceItem>(5);
    ref->m_item.m_type = type;
    ref->m_item.m_id = item;
    ref->m_item.m_entry.m_handle = 0;
    ref->m_item.m_count = 1;
    ui::UIObjectAcc taskItem(m_handle, "LAY_log_info_task_item");
    taskItem.setDisp(result.m_count != 0);
}

bool GfMenuObjQuestLog::seqLogOut() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    if (!pad_940) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_startFlag4 = true;
        param.m_slot = GfMenuObjUtil::getCtrlID(log.m_handle);
        GfMenuObjUtil::startPresetCtrl(log.m_handle, param);
        pad_940 = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(log.m_handle))) {
        return false;
    }
    pad_940 = false;
    return true;
}

void GfMenuObjQuestLog::TitleListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
    } else if (event.m_type == 0x21) {
        QuestID id(event.m_param0);
        m_owner->getRef<GfMenuReferenceQuest>(0)->m_quest = id;
        m_owner->m_titleSeq.clear();
        m_owner->m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleStart);
        acc.setDisp(true);
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjQuestLog::seqTitleStart() {
    ui::UIObjectAcc acc(m_handle, "IMG_title_base");
    QuestID id;
    getRef<GfMenuReferenceQuest>(0)->getQuest(id);
    int category = QuestListAcc::get()->getListQuestCategory(id);
    bool layer3 = GfMenuObjUtil::isValidExpansion(3);
    if (!layer3 || pad_948) {
        if (category == 1) {
            acc.startAnimation("start_scenario", false);
            m_titleSeq.addWait(0x14);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInText);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInScenario);
            m_titleSeq.addWait(0x77);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeOutScenario);
        } else {
            acc.startAnimation("start", false);
            m_titleSeq.addWait(0x14);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInText);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInNormal);
            m_titleSeq.addWait(0x77);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeOutNormal);
        }
    } else {
        if (category == 1) {
            acc.startAnimation("start_scenario", false);
            m_titleSeq.addWait(9);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqCompleteJingle);
            m_titleSeq.addWait(10);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInText);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInScenario);
            m_titleSeq.addWait(0x77);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeOutScenario);
        } else {
            acc.startAnimation("start", false);
            m_titleSeq.addWait(9);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqCompleteJingle);
            m_titleSeq.addWait(10);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInText);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeInNormal);
            m_titleSeq.addWait(0x77);
            m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleFadeOutNormal);
        }
    }
    m_titleSeq.addJob(&GfMenuObjQuestLog::seqTitleEndWait);
    if (pad_948) {
        m_titleSeq.addJob(&GfMenuObjQuestLog::seqOrderActivation);
    }
    acc.setDisp(true);
    return true;
}

bool GfMenuObjQuestLog::seqLogNext() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    // the task reference is asserted held and not used further (operator-> only)
    getRef<GfMenuReferenceNumber>(3);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    param.m_setDefault = true;
    m_infoCtrl = GfMenuObjUtil::startCtrl(log.m_handle, param, "LAY_log_info");
    setupLogClear();
    setupLogItem();
    m_logSeq.addJob(&GfMenuObjQuestLog::seqLogNextWaitInfo);
    m_logSeq.addJob(&GfMenuObjQuestLog::seqLogNextEnd);
    return true;
}

bool GfMenuObjQuestLog::seqLogClose() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    log.setDispChild(false, "LAY_log_info");
    log.setDispChild(false, "LAY_log_to_detail");
    log.setDispChild(false, "LAY_log_index@02");
    log.setDispChild(true, "LAY_log_index@01");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    param.m_setDefault = true;
    param.m_startFlags = 8;
    m_infoCtrl = GfMenuObjUtil::startCtrl(log.m_handle, param, "LAY_log_index@01");
    m_logSeq.addAnimJob(log.searchChild("IMG_log_base"), "info_fade_out");
    m_logSeq.addJob(&GfMenuObjQuestLog::seqLogCloseEnd);
    return true;
}

bool GfMenuObjQuestLog::seqLogCloseEnd() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    if (!pad_5A) {
        GfMenuObject::enableInput(log.m_handle);
    } else {
        m_logSeq.addJob(&GfMenuObjQuestLog::seqLogOut);
    }
    m_logOpened = false;
    return true;
}

bool GfMenuObjQuestLog::seqCompleteStart() {
    ui::UIObjectAcc(m_handle, "IMG_complete_base").startAnimation("start", false);
    ui::UIObjectAcc(m_handle, "IMG_complete_eff").startAnimation("start", false);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "sample";
    param.m_motion = "fadein";
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_complete");
    m_orderSeq.addWait(0x36);
    m_orderSeq.addJob(&GfMenuObjQuestLog::seqCompleteWaitCtrl);
    return true;
}

bool GfMenuObjQuestLog::seqCompleteJingle() {
    GfMenuObjUtil::playJingle(7);
    return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInText() {
    GfMenuObjUtil::CtrlParam param;
    param.m_time = 0.2f;
    param.m_methods = 1;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title");
    if (!pad_948 && !GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuObjUtil::playJingle(7);
    }
    return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInScenario() {
    GfMenuObjUtil::CtrlParam param;
    param.m_time = 0.2f;
    param.m_methods = 1;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title_sub_scenario");
    return true;
}

bool GfMenuObjQuestLog::seqTitleFadeOutScenario() {
    GfMenuObjUtil::CtrlParam param;
    param.m_time = 0.2f;
    param.m_methods = 2;
    param.m_startFlags = 2;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title");
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title_sub_scenario");
    return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInNormal() {
    GfMenuObjUtil::CtrlParam param;
    param.m_time = 0.2f;
    param.m_methods = 1;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title_sub_normal");
    return true;
}

bool GfMenuObjQuestLog::seqTitleFadeOutNormal() {
    GfMenuObjUtil::CtrlParam param;
    param.m_time = 0.2f;
    param.m_methods = 2;
    param.m_startFlags = 2;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title");
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_title_sub_normal");
    return true;
}

bool GfMenuObjQuestLog::seqLogIn() {
    ui::UIObjectAcc log(m_handle, "LAY_log");
    if (!pad_940) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 0;
        param.m_out = 0;
        param.m_startFlag4 = true;
        param.m_slot = GfMenuObjUtil::getCtrlID(log.m_handle);
        GfMenuObjUtil::startPresetCtrl(log.m_handle, param);
        pad_940 = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(log.m_handle))) {
        return false;
    }
    pad_940 = false;
    m_logSeq.addJob(&GfMenuObjQuestLog::seqLogStart);
    return true;
}

bool GfMenuObjQuestLog::seqOrderActivation() {
    if (!pad_940) {
        GfMenuManager::openCommonWindow(1);
        pad_940 = true;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        QuestID id;
        getRef<GfMenuReferenceQuest>(2)->getQuest(id);
        GfQuestManager::setCurrentQuest(id);
    }
    ui::UIObjectAcc order(m_handle, "LAY_order");
    ui::EventData event;
    event.m_type = 0x103;
    GfMenuObject::sendEvent(order.m_handle, event, 0.0f);
    pad_940 = false;
    return true;
}

void GfMenuObjQuestLog::OrderListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
    } else if (event.m_type == 0x21) {
        m_owner->pad_948 = true;
        ui::EventData open;
        open.m_type = 0x21;
        open.m_param0 = event.m_param0;
        GfMenuObject::sendEvent(acc.searchSibiling("LAY_title"), open, 0.0f);
        m_owner->getRef<GfMenuReferenceQuest>(2)->m_quest = QuestID(event.m_param0);
        bool layer3 = GfMenuObjUtil::isValidExpansion(3);
        m_owner->m_orderSeq.clear();
        if (!layer3) {
            m_owner->m_orderSeq.addWait(0x4B);
            m_owner->m_orderSeq.addJob(&GfMenuObjQuestLog::seqOrderStart);
        } else {
            m_owner->m_orderSeq.addWait(0xE);
            m_owner->m_orderSeq.addJob(&GfMenuObjQuestLog::seqOrderJingle);
            m_owner->m_orderSeq.addWait(0x2D);
            m_owner->m_orderSeq.addJob(&GfMenuObjQuestLog::seqOrderStart);
        }
        acc.setDisp(true);
    } else if (event.m_type == 0x103) {
        m_owner->getRef<GfMenuReferenceQuest>(2)->m_quest = QuestID();
        GfMenuObject::termCallContext(acc.m_handle);
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjQuestLog::seqOrderJingle() {
    GfMenuObjUtil::playJingle(6);
    return true;
}

bool GfMenuObjQuestLog::seqOrderStart() {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "sample";
    param.m_motion = "fadein";
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_order");
    bool layer3 = GfMenuObjUtil::isValidExpansion(3);
    m_orderSeq.addWait(0x37);
    m_orderSeq.addJob(&GfMenuObjQuestLog::seqOrderWaitCtrl);
    if (!layer3) {
        GfMenuObjUtil::playJingle(6);
    }
    return true;
}

void GfMenuObjQuestLog::CompleteListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else if (event.m_param0 == 2) {
            m_owner->getRef<GfMenuReferenceQuest>(2)->m_quest = QuestID();
            GfMenuObject::termCallContext(acc.m_handle);
            acc.setDisp(false);
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_comp_result");
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjUtil::playSECommonDecide();
        }
        break;
    case 0x21: {
        if (m_owner->m_rewardContext == nullptr) {
            m_owner->m_rewardContext = GfMenuCallContext::create();
            GfMenuObjQuestReward::OpenParam param;
            param.m_quest = m_owner->m_refs[2];
            param.m_handle = acc.searchChild("LAY_comp_ret_reward");
            GfMenuObjQuestReward::create(m_owner->m_rewardContext, param, false);
        }
        m_owner->pad_948 = false;
        ui::EventData open;
        open.m_type = 0x21;
        open.m_param0 = event.m_param0;
        GfMenuObject::sendEvent(acc.searchSibiling("LAY_title"), open, 0.0f);
        m_owner->getRef<GfMenuReferenceQuest>(2)->m_quest = QuestID(event.m_param0);
        m_owner->m_orderSeq.clear();
        m_owner->m_orderSeq.addWait(0x4B);
        m_owner->m_orderSeq.addJob(&GfMenuObjQuestLog::seqCompleteStart);
        GfMenuObjQuestReward::open(m_owner->m_rewardContext, false);
        acc.setDisp(true);
        break;
    }
    case 0x103: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_comp_result");
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjQuestLog::seqOrderWaitCtrl() {
    ui::UIObjectAcc text(m_handle, "TXT_order");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(text.m_handle))) {
        return false;
    }
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_zoom";
    param.m_motion = "fade_out";
    param.m_startFlags = 10;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_order");
    m_orderSeq.addJob(&GfMenuObjQuestLog::seqOrderWait);
    if (GfMenuObjUtil::isValidExpansion(3)) {
        SCOM_FIELD_VOICE::createQuestOrderIra();
    }
    return true;
}

bool GfMenuObjQuestLog::seqCompleteWaitCtrl() {
    ui::UIObjectAcc text(m_handle, "TXT_complete");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(text.m_handle))) {
        return false;
    }
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_zoom";
    param.m_motion = "fade_out";
    param.m_startFlags = 10;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_complete");
    m_orderSeq.addJob(&GfMenuObjQuestLog::seqCompleteWait);
    return true;
}

bool GfMenuObjQuestLog::seqCompleteWait() {
    if (ui::UIObjectAcc(m_handle, "IMG_complete_baae").isPlayingAnimation()) {
        return false;
    }
    if (ui::UIObjectAcc(m_handle, "IMG_complete_eff").isPlayingAnimation()) {
        return false;
    }
    ui::UIObjectAcc complete(m_handle, "LAY_complete");
    ui::EventData event;
    event.m_type = 0x103;
    GfMenuObject::sendEvent(complete.m_handle, event, 0.0f);
    if (GfMenuObjUtil::isValidExpansion(3)) {
        SCOM_FIELD_VOICE::createQuestCompleteIra();
    }
    return true;
}

}  // namespace gf
