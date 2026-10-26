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
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "gf/QuestTaskParam.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjQuestLog::GfMenuObjQuestLog(unsigned int handle)
    : GfMenuObject(handle), m_quests(), pad_58(), m_titleSeq(this), m_logSeq(this), m_orderSeq(this), pad_940(false),
      pad_948(false), pad_950(nullptr), pad_958(nullptr) {}

GfMenuObjQuestLog::~GfMenuObjQuestLog() {
    for (int i = 0; i < 6; ++i) {
        m_quests[i] = nullptr;
    }
    if (pad_950 != nullptr) {
        pad_950->release();
        pad_950 = nullptr;
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

}  // namespace gf
