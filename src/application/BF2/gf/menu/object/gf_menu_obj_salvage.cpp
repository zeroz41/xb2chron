#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjSalvage.h"
#include "classes/gf/GfMenuObjSalvage/ResultListener.h"
#include "classes/gf/GfMenuObjSalvage/RecordListener.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuBtlchAdapter.h"
#include "mm/Rect.h"
#include "mm/Pnt.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/Delegate.h"

namespace gf {

namespace {
// the rating animation per ResultParam::m_rank (proposed name, not the original's: the symbols leave it unnamed,
// lbl_7100B64640)
const char* s_rankAnims[] = {"rank_1", "rank_2", "rank_3", "rank_4"};
// the record kinds by GfMenuObjSalvage::m_newRecords bit (proposed name, not the original's: the symbols leave it
// unnamed, lbl_7100B64660)
const char* s_recordKinds[] = {"time", "ether", "score"};
}  // namespace

// 2.0.0's symbols name it
bool GfMenuObjSalvage::s_BtlchNewRecord;

GfMenuObjSalvage::GfMenuObjSalvage(unsigned int handle)
    : GfMenuObject(handle), m_param(), m_seq(this), m_appeared(false), m_time(), m_newRecords(0) {
    m_time = GfMenuReferenceNumber::create();
}

GfMenuObjSalvage::~GfMenuObjSalvage() {
    m_time = nullptr;
}

void GfMenuObjSalvage::openResult(GfMenuCallContext* context, const ResultParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x53));
    if (GfMenuObjUtil::checkCCStart(context)) {
        if (param.m_unk2 == 1 && !GfMenuObjUtil::isValidExpansion(1)) {
            if (context != nullptr) {
                context->abort();
            }
        } else {
            ui::UIObjectAcc result(acc.searchChild("LAY_result"));
            ui::EventData event;
            event.m_type = 0x21;
            event.m_paramShort[0] = param.m_rank;
            event.m_paramShort[1] = param.m_unk2;
            if (event.m_paramShort[1] == 1) {
                event.m_paramShort[0] = 1;
            }
            GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x53, result.m_handle);
        }
    }
}

void GfMenuObjSalvage::openBtlchRecord(GfMenuCallContext* context) {
    if (GfMenuObjUtil::isValidExpansion(1) && GfGameManager::isBattleArenaActive()) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x53));
        if (GfMenuObjUtil::checkCCStart(context)) {
            ui::UIObjectAcc record(acc.searchChild("LAY_record"));
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(record.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x53, record.m_handle);
        }
    } else if (context != nullptr) {
        context->abort();
    }
}

void GfMenuObjSalvage::setBtlchNewRecord(bool flag) {
    if (GfMenuObjUtil::isValidExpansion(1)) {
        s_BtlchNewRecord = flag;
    }
}

void GfMenuObjSalvage::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (main.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x53, main.m_handle);
        {
            ui::UIObjectAcc result(main.m_handle, "LAY_result");
#line 170
            ResultListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ResultListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_result"), listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuAdapterManager::beginCategory(4);
        {
            ui::UIObjectAcc record(main.m_handle, "LAY_record");
            {
#line 179
                RecordListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RecordListener(this);
                listener->m_RefCount = 1;
                ui::UIEventManager::get()->registObjectListener(record.m_handle, listener);
                if (listener != nullptr) {
                    listener->release();
                }
            }
            {
                ui::UIObjectAcc time(m_handle, "LAY_result@01");
                GfMenuBtlchAdapter::createFromReference(time.searchChild("TXT_time"), 0xE, m_time, true);
                GfMenuBtlchAdapter::createFromReference(time.searchChild("TXT_time_shadow"), 0xE, m_time, true);
            }
            {
                ui::UIObjectAcc ether(m_handle, "LAY_result@02");
                GfMenuBattleAdapter::create(ether.searchChild("TXT_ether_num"), 0x1A);
                GfMenuBattleAdapter::create(ether.searchChild("TXT_ether_num_shadow"), 0x1A);
                mm::mtl::FixStr<32> name;
                for (int i = 0; i < 3; i++) {
                    name.format("IMG_ether_box_icon@%02d", i + 1);
                    ui::UIObjectAcc icon(ether.m_handle, name.m_str);
                    GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(icon.m_handle, 0x1D);
                    if (adapter != nullptr) {
                        adapter->m_index = i;
                        icon.startAnimation("percent", true);
                        GfMenuObject::addNumberEventCondition(record.m_handle, name.m_str, 1, i, 1.0f);
                    }
                }
            }
            {
                ui::UIObjectAcc score(m_handle, "LAY_result@03");
                GfMenuBattleAdapter::create(score.searchChild("TXT_score_num"), 0x1B);
                GfMenuBattleAdapter::create(score.searchChild("TXT_score_num_shadow"), 0x1B);
            }
        }
        GfMenuAdapterManager::endCategory();
        GfMenuObject::initialize();
    }
}

void GfMenuObjSalvage::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjSalvage::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjSalvage::ResultListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
        m_ctrlSlot = -1;
    } else if (event.m_type == 0x21) {
        m_owner->m_param.m_rank = event.m_paramShort[0];
        m_owner->m_param.m_unk2 = event.m_paramShort[1];
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjSalvage::seqResultAppear);
        m_owner->m_appeared = false;
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjSalvage::seqResultAppear() {
    ui::UIObjectAcc rating(m_handle, "IMG_result_rating");
    if (!m_appeared) {
        ui::UIObjectAcc result(m_handle, "LAY_result");
        result.setDisp(true);
        result.setDispChild(m_param.m_unk2 == 0, "LAY_result_index_normal");
        result.setDispChild(m_param.m_unk2 == 1, "LAY_result_index_bch");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        GfMenuObjUtil::startCtrl(result.m_handle, param, "LAY_result_index");
        rating.startAnimation(s_rankAnims[m_param.m_rank], false);
        m_appeared = true;
        GfMenuObjUtil::playJingle(0xF);
        return false;
    }
    if (rating.isPlayingAnimation()) {
        return false;
    }
    m_appeared = false;
    m_seq.addJob(&GfMenuObjSalvage::seqResultLeave);
    return true;
}

void GfMenuObjSalvage::RecordListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 8:
        if (event.m_param1 == 1) {
            m_owner->m_inputClosed = true;
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::close();
        }
        break;
    case 0xC: {
        int number = event.m_param0 + 1;
        mm::mtl::FixStr<32> name;
        name.format("IMG_ether_box_icon_eff@%02d", number);
        ui::UIObjectAcc eff(acc.m_handle, name.m_str);
        if (eff.isDisp()) {
            name.format("LAY_ether_box_icon@%02d", number);
            ui::UIObjectAcc icon(acc.m_handle, name.m_str);
            name.format("LAY_ether_box_loop@%02d", number);
            ui::UIObjectAcc loop(acc.m_handle, name.m_str);
            icon.setDisp(false);
            loop.setAlpha(1.0f);
        }
        break;
    }
    case 0xD: {
        int kind = event.m_param0;
        if (event.m_param1 == 1) {
            int index = event.m_param2;
            mm::mtl::FixStr<32> name;
            int number = index + 1;
            name.format("IMG_ether_box_icon@%02d", number);
            ui::UIObjectAcc icon(acc.m_handle, name.m_str);
            name.format("IMG_ether_box_icon_eff@%02d", number);
            ui::UIObjectAcc eff(acc.m_handle, name.m_str);
            if (icon.m_object != nullptr && eff.m_object != nullptr) {
                if (kind == 1) {
                    icon.setAlpha(0.0f);
                    eff.setDisp(true);
                    eff.startAnimation("get", false);
                    GfMenuObject::hookAnimationEvent(acc.m_handle, eff.m_handle, index);
                } else if (kind == 2) {
                    name.format("LAY_ether_box_icon@%02d", number);
                    ui::UIObjectAcc box(acc.m_handle, name.m_str);
                    name.format("LAY_ether_box_loop@%02d", number);
                    ui::UIObjectAcc loop(acc.m_handle, name.m_str);
                    icon.setAlpha(1.0f);
                    eff.setDisp(false);
                    box.setDisp(true);
                    loop.setAlpha(0.0f);
                }
            }
        }
        break;
    }
    case 0x21:
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjSalvage::seqRecordInfoOpen);
        m_owner->m_appeared = false;
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjSalvage::seqResultLeave() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    if (!m_appeared) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(result.m_handle, param, nullptr);
        m_appeared = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(result.m_handle))) {
        return false;
    }
    m_seq.addJob(&GfMenuObjSalvage::seqResultEnd);
    return true;
}

bool GfMenuObjSalvage::seqResultEnd() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    GfMenuObject::termCallContext(result.m_handle);
    return true;
}

bool GfMenuObjSalvage::seqCtrlWait() {
    if (m_ctrlSlot != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_ctrlSlot)) {
            return false;
        }
        m_ctrlSlot = -1;
    }
    return true;
}

bool GfMenuObjSalvage::seqNewRecordFadeIn() {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
        if (m_newRecords & (1 << i)) {
            const char* kind = s_recordKinds[i];
            name.format("LAY_%s_new_record", kind);
            ui::UIObjectAcc layout(m_handle, name.m_str);
            layout.setDisp(true);
            {
                name.format("TXT_%s_new_record", kind);
                ui::UIObjectAcc text(layout.m_handle, name.m_str);
                text.setDisp(true);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_startFlags = 8;
                param.m_setDefault = true;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_r";
                GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
            }
            name.format("IMG_%s_new_record_eff", kind);
            ui::UIObjectAcc eff(layout.m_handle, name.m_str);
            eff.startAnimation("start", false);
        }
    }
    return true;
}

bool GfMenuObjSalvage::seqNewRecordSE() {
    GfMenuObjUtil::playSE("dlc_se_btl_chbtl004");
    return true;
}

bool GfMenuObjSalvage::seqNewRecordWait() {
    mm::mtl::FixStr<32> name;
    if (m_newRecords & 1) {
        name.format("IMG_%s_new_record_eff", "time");
        ui::UIObjectAcc eff(m_handle, name.m_str);
        if (eff.isPlayingAnimation()) {
            return false;
        }
    }
    if (m_newRecords & 2) {
        name.format("IMG_%s_new_record_eff", "ether");
        ui::UIObjectAcc eff(m_handle, name.m_str);
        if (eff.isPlayingAnimation()) {
            return false;
        }
    }
    if (m_newRecords & 4) {
        name.format("IMG_%s_new_record_eff", "score");
        ui::UIObjectAcc eff(m_handle, name.m_str);
        if (eff.isPlayingAnimation()) {
            return false;
        }
    }
    return true;
}

bool GfMenuObjSalvage::seqRecordStartConfirm() {
    ui::UIObjectAcc record(m_handle, "LAY_record");
    GfMenuObject::enableInput(record.m_handle);
    GfMenuObjOperationInfo::open(record.m_handle, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideDisp(false);
    return true;
}

bool GfMenuObjSalvage::seqRecordWaitConfirm() {
    return m_inputClosed;
}

bool GfMenuObjSalvage::seqRecordFadeout() {
    ui::UIObjectAcc record(m_handle, "LAY_record");
    record.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_out_r";
    param.m_startFlags = 10;
    param.m_setDefault = true;
    m_ctrlSlot = GfMenuObjUtil::startCtrl(record.m_handle, param, nullptr);
    GfMenuObjUtil::playSECommonDecide();
    m_seq.addJob(&GfMenuObjSalvage::seqCtrlWait);
    m_seq.addJob(&GfMenuObjSalvage::seqRecordEnd);
    return true;
}

bool GfMenuObjSalvage::seqRecordEnd() {
    ui::UIObjectAcc record(m_handle, "LAY_record");
    mm::mtl::FixStr<32> name;
    for (int i = 1; i < 4; i++) {
        name.format("LAY_ether_box_icon@%02d", i);
        ui::UIObjectAcc box(record.m_handle, name.m_str);
        name.format("IMG_ether_box_icon@%02d", i);
        ui::UIObjectAcc icon(record.m_handle, name.m_str);
        name.format("IMG_ether_box_icon_eff@%02d", i);
        ui::UIObjectAcc eff(record.m_handle, name.m_str);
        name.format("LAY_ether_box_loop@%02d", i);
        ui::UIObjectAcc loop(record.m_handle, name.m_str);
        name.format("IMG_ether_box_loop@%02d", i);
        ui::UIObjectAcc loopImage(record.m_handle, name.m_str);
        box.setDisp(true);
        eff.setDisp(false);
        icon.setAlpha(1.0f);
        icon.startAnimation("percent", true);
        loop.setDisp(true);
        loop.setAlpha(0.0f);
        loopImage.startAnimationFromIndex(3, false);
    }
    record.setDispChild(false, "LAY_time_new_record");
    record.setDispChild(false, "LAY_ether_new_record");
    record.setDispChild(false, "LAY_score_new_record");
    GfMenuObject::termCallContext(record.m_handle);
    m_time->m_value = 0;
    return true;
}
}  // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjSalvage, 12>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjSalvage, 12>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
