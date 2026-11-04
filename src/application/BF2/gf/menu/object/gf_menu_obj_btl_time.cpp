#include "classes/gf/GfMenuObjBtlTime.h"
#include "classes/gf/GfMenuObjBtlTime/TimeListener.h"
#include "classes/gf/GfMenuObjBtlTime/EtherListener.h"
#include "classes/gf/GfMenuObjBtlTime/ScoreListener.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

// An inferred helper (no symbol: inlined everywhere; the name is not the original's): the handle of `handle`'s child
// of that name. reset's accessors take the top stack slots as an inlined callee's do.
static inline unsigned int searchChildOf(unsigned int handle, const char* name) {
    ui::UIObjectAcc parent(handle);
    return parent.searchChild(name);
}

GfMenuObjBtlTime::GfMenuObjBtlTime(unsigned int handle) : GfMenuObject(handle), m_seq(this), m_seq2(this), m_etherBox(0) {}

GfMenuObjBtlTime::~GfMenuObjBtlTime() {}

void GfMenuObjBtlTime::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x87, main.m_handle);
    {
        ui::UIObjectAcc time(m_handle, "LAY_time");
        {
#line 86
            TimeListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TimeListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(time.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuBattleAdapter::create(time.searchChild("TXT_time"), 0x19);
        GfMenuBattleAdapter::create(time.searchChild("TXT_time_shadow"), 0x19);
    }
    if (GfMenuObjUtil::isValidExpansion(1) && !GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuAdapterManager::beginCategory(4);
        {
            ui::UIObjectAcc ether(m_handle, "LAY_ether");
            {
#line 106
                EtherListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EtherListener(this);
                listener->m_RefCount = 1;
                ui::UIEventManager::get()->registObjectListener(ether.m_handle, listener);
                if (listener != nullptr) {
                    listener->release();
                }
            }
            GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(ether.searchChild("TXT_ether_num"), 0x1A);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            adapter = GfMenuBattleAdapter::create(ether.searchChild("TXT_ether_num_shadow"), 0x1A);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            mm::mtl::FixStr<32> name;
            for (int i = 0; i < 3; i++) {
                name.format("IMG_ether_box_icon@%02d", i + 1);
                ui::UIObjectAcc icon(ether.m_handle, name.m_str);
                adapter = GfMenuBattleAdapter::create(icon.m_handle, 0x1D);
                if (adapter != nullptr) {
                    adapter->setNumberInterpolateMode(0.25f);
                    adapter->m_index = i;
                    GfMenuObject::addNumberEventCondition(ether.m_handle, name.m_str, 1, i, 1.0f);
                }
            }
        }
        {
            ui::UIObjectAcc score(m_handle, "LAY_score");
            {
#line 145
                ScoreListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ScoreListener(this);
                listener->m_RefCount = 1;
                ui::UIEventManager::get()->registObjectListener(score.m_handle, listener);
                if (listener != nullptr) {
                    listener->release();
                }
            }
            GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(score.searchChild("TXT_score_num"), 0x1B);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            adapter = GfMenuBattleAdapter::create(score.searchChild("TXT_score_num_shadow"), 0x1B);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            adapter = GfMenuBattleAdapter::create(score.searchChild("TXT_score_num_slash_num"), 0x1B);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            adapter = GfMenuBattleAdapter::create(score.searchChild("TXT_score_num_slash_num_sw"), 0x1B);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            adapter = GfMenuBattleAdapter::create(score.searchChild("TXT_score_num_slash_max"), 0x1C);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
            adapter = GfMenuBattleAdapter::create(score.searchChild("TXT_score_num_slash_max_sw"), 0x1C);
            if (adapter != nullptr) {
                adapter->setNumberInterpolateMode(0.25f);
            }
        }
        GfMenuAdapterManager::endCategory();
    }
    GfMenuObject::initialize();
    reset();
}

void GfMenuObjBtlTime::reset() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x103;
        GfMenuObject::sendEvent(searchChildOf(acc.m_handle, "LAY_time"), event, 0.0f);
        if (GfMenuObjUtil::isValidExpansion(1)) {
            GfMenuObject::sendEvent(searchChildOf(acc.m_handle, "LAY_ether"), event, 0.0f);
        }
        if (GfMenuObjUtil::isValidExpansion(1)) {
            GfMenuObject::sendEvent(searchChildOf(acc.m_handle, "LAY_score"), event, 0.0f);
        }
    }
}

void GfMenuObjBtlTime::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBtlTime::update() {
    m_seq.update();
    m_seq2.update();
    GfMenuObject::update();
}

void GfMenuObjBtlTime::open(unsigned int part, int param) {
    if (part == 0 || (!GfMenuObjUtil::isValidExpansion(3) && GfMenuObjUtil::isValidExpansion(1))) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            unsigned int handle = getTypeObject(acc.m_handle, part, false);
            if (handle != 0) {
                ui::EventData event;
        event.m_type = 0x21;
                event.m_param0 = param;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            }
        }
    }
}

unsigned int GfMenuObjBtlTime::getTypeObject(unsigned int handle, unsigned int part, bool always) {
    ui::UIObjectAcc acc(handle);
    switch (part) {
    case 0:
        return acc.searchChild("LAY_time");
    case 1:
        if (always || GfGameManager::isBattleArenaActive()) {
            return acc.searchChild("LAY_ether");
        }
        break;
    case 2:
        if (always || GfGameManager::isBattleArenaActive()) {
            return acc.searchChild("LAY_score");
        }
        break;
    }
    return 0;
}

void GfMenuObjBtlTime::close(unsigned int part) {
    if (part == 0 || (!GfMenuObjUtil::isValidExpansion(3) && GfMenuObjUtil::isValidExpansion(1))) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            unsigned int handle = getTypeObject(acc.m_handle, part, false);
            if (handle != 0) {
                ui::EventData event;
        event.m_type = 0x22;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            }
        }
    }
}

void GfMenuObjBtlTime::openFromChallengeBattle() {
    if (!GfMenuObjUtil::isValidExpansion(1)) {
        return;
    }
    open(0, 0);
    open(1, 0);
    if (GfGameManager::getBattleArenaMenuInfo()->m_kind == 1) {
        open(2, 0);
    } else if (GfGameManager::getBattleArenaMenuInfo()->m_kind == 3) {
        open(2, 1);
    } else {
        close(2);
    }
}

void GfMenuObjBtlTime::closeAll() {
    close(0);
    if (GfMenuObjUtil::isValidExpansion(1)) {
        close(1);
    }
    if (GfMenuObjUtil::isValidExpansion(1)) {
        close(2);
    }
}

void GfMenuObjBtlTime::noticeNewRecord() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        unsigned int handle = getTypeObject(acc.m_handle, 0, false);
        if (handle != 0) {
            ui::EventData event;
        event.m_type = 0x100;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjBtlTime::noticeTimeLimit() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        unsigned int handle = getTypeObject(acc.m_handle, 0, false);
        if (handle != 0) {
            ui::EventData event;
        event.m_type = 0x101;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjBtlTime::TimeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(false);
        acc.setSuspend(true);
        m_open = 0;
        State state = {-1, 0};
        m_state = state;
        m_first = 1;
        break;
    }
    case 3:
        if (event.m_param0 == 2 && m_open == 0) {
            acc.setSuspend(true);
        }
        break;
    case 0x21:
        if (m_open != 1) {
            float delay = (m_first == 1 && GfGameManager::isBattleArenaActive()) ? 0.5f : 0.0f;
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 1;
            param.m_out = 0;
            param.m_slot = m_state.m_ctrl;
            param.m_startFlag4 = true;
            param.m_eventId = 1;
            param.m_delay = delay;
            int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            if (ctrl != -1) {
                m_open = 1;
                m_state.m_ctrl = ctrl;
            }
            acc.setDispChild(false, "LAY_time_new_record");
            m_owner->m_seq.clear();
            m_state.m_closePending = 0;
            acc.setSuspend(false);
            m_first = 0;
        } else if (m_state.m_closePending != 0) {
            acc.setDispChild(false, "LAY_time_new_record");
            m_owner->m_seq.clear();
            m_state.m_closePending = 0;
        }
        break;
    case 0x22:
        if (m_open != 0) {
            if (!m_owner->m_seq.m_jobs.empty()) {
                m_state.m_closePending = 1;
                break;
            }
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 1;
            param.m_out = 1;
            param.m_slot = m_state.m_ctrl;
            param.m_startFlag4 = true;
            param.m_eventId = 2;
            int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            if (ctrl != -1) {
                m_open = 0;
                m_state.m_ctrl = ctrl;
            }
            m_owner->m_seq.clear();
            acc.setDispChild(false, "LAY_time_new_record");
            m_state.m_closePending = 0;
        }
        break;
    case 0x100:
        if (m_open != 0) {
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjBtlTime::seqNewRecordFadeIn);
        }
        break;
    case 0x101: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x2000000;
        param.m_color = GfMenuObjUtil::getPresetColor("tgt_cursor_lv01");
        param.m_reserve = true;
        param.m_curve = 3;
        param.m_startFlags = 8;
        param.m_time = 1.0f;
        GfMenuObjUtil::startCtrl(acc.searchChild("LAY_time_info"), param, nullptr);
        break;
    }
    case 0x102:
        if (m_state.m_closePending != 0) {
            GfMenuObjBtlTime::close(0);
        }
        break;
    case 0x103: {
        ui::UIObjectAcc info(acc.m_handle, "LAY_time_info");
        GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(info.m_handle));
        m_first = 1;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBtlTime::seqNewRecordFadeIn() {
    ui::UIObjectAcc record(m_handle, "LAY_time_new_record");
    record.setDisp(true);
    {
        ui::UIObjectAcc text(record.m_handle, "TXT_time_new_record");
        text.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(record.searchChild("TXT_time_new_record"), param, nullptr);
    }
    {
        ui::UIObjectAcc eff(record.m_handle, "IMG_time_new_record_eff");
        eff.startAnimation("start", false);
    }
    m_seq.addWait(5);
    m_seq.addJob(&GfMenuObjBtlTime::seqNewRecordSE);
    m_seq.addJob(&GfMenuObjBtlTime::seqNewRecordWait);
    return true;
}

// An inferred helper (no symbol: inlined; the name is not the original's): stops and hides the owner's
// TXT_ether_box_get. Its accessor takes the top stack slot as an inlined callee's does.
static inline void hideEtherBoxGet(unsigned int handle) {
    ui::UIObjectAcc get(handle, "TXT_ether_box_get");
    if (get.m_object != nullptr) {
        GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(get.m_handle));
        get.setDisp(false);
    }
}

void GfMenuObjBtlTime::EtherListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        m_open = 0;
        m_ctrl = -1;
        break;
    case 3:
        if (event.m_param0 == 2 && m_open == 0) {
            acc.setSuspend(true);
        }
        break;
    case 0xC: {
        int box = event.m_param0 + 1;
        mm::mtl::FixStr<32> name;
        name.format("IMG_ether_box_icon_eff@%02d", box);
        ui::UIObjectAcc eff(acc.m_handle, name.m_str);
        if (eff.isDisp()) {
            name.format("LAY_ether_box_icon@%02d", box);
            ui::UIObjectAcc icon(acc.m_handle, name.m_str);
            name.format("LAY_ether_box_loop@%02d", box);
            ui::UIObjectAcc loop(acc.m_handle, name.m_str);
            icon.setDisp(false);
            loop.setAlpha(1.0f);
        }
        break;
    }
    case 0xD: {
        int state = event.m_param0;
        if (event.m_param1 != 1) {
            break;
        }
        int box = event.m_param2;
        mm::mtl::FixStr<32> name;
        name.format("IMG_ether_box_icon@%02d", box + 1);
        ui::UIObjectAcc icon(acc.m_handle, name.m_str);
        name.format("IMG_ether_box_icon_eff@%02d", box + 1);
        ui::UIObjectAcc eff(acc.m_handle, name.m_str);
        if (icon.m_object != nullptr && eff.m_object != nullptr) {
            if (state == 1) {
                icon.setAlpha(0.0f);
                eff.setDisp(true);
                eff.startAnimation("get", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, eff.m_handle, box);
                GfMenuObjUtil::playSE("dlc_se_btl_chbtl006");
                m_owner->m_etherBox = box;
                m_owner->m_seq2.clear();
                m_owner->m_seq2.addJob(&GfMenuObjBtlTime::seqGetBoxStart);
            } else if (state == 2) {
                name.format("LAY_ether_box_icon@%02d", box + 1);
                ui::UIObjectAcc lay(acc.m_handle, name.m_str);
                name.format("LAY_ether_box_loop@%02d", box + 1);
                ui::UIObjectAcc loop(acc.m_handle, name.m_str);
                icon.setAlpha(1.0f);
                eff.setDisp(false);
                lay.setDisp(true);
                loop.setAlpha(0.0f);
            }
        }
        break;
    }
    case 0x21:
        if (m_open != 1) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 1;
            param.m_out = 0;
            param.m_slot = m_ctrl;
            param.m_startFlag4 = true;
            param.m_eventId = 1;
            param.m_delay = GfGameManager::isBattleArenaActive() ? 0.5f : 0.0f;
            int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            if (ctrl != -1) {
                m_open = 1;
                m_ctrl = ctrl;
            }
            m_owner->m_etherBox = 0;
            hideEtherBoxGet(m_owner->m_handle);
            acc.setSuspend(false);
        }
        break;
    case 0x22: {
        if (m_open == 0) {
            break;
        }
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 1;
        param.m_out = 1;
        param.m_slot = m_ctrl;
        param.m_startFlag4 = true;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        if (ctrl != -1) {
            m_open = 0;
            m_ctrl = ctrl;
        }
        hideEtherBoxGet(m_owner->m_handle);
        break;
    }
    case 0x103: {
        mm::mtl::FixStr<32> name;
        for (int i = 1; i < 4; i++) {
            name.format("LAY_ether_box_icon@%02d", i);
            ui::UIObjectAcc lay(acc.m_handle, name.m_str);
            name.format("IMG_ether_box_icon@%02d", i);
            ui::UIObjectAcc icon(acc.m_handle, name.m_str);
            name.format("IMG_ether_box_icon_eff@%02d", i);
            ui::UIObjectAcc eff(acc.m_handle, name.m_str);
            name.format("LAY_ether_box_loop@%02d", i);
            ui::UIObjectAcc loop(acc.m_handle, name.m_str);
            lay.setDisp(true);
            eff.setDisp(false);
            icon.setAlpha(1.0f);
            icon.startAnimation("percent", true);
            loop.setAlpha(0.0f);
        }
        m_owner->m_etherBox = 0;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBtlTime::seqGetBoxStart() {
    {
        ui::UIObjectAcc get(m_handle, "TXT_ether_box_get");
        if (get.m_object != nullptr) {
            GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(get.m_handle));
            get.setDisp(false);
        }
    }
    ui::UIObjectAcc get(m_handle, "TXT_ether_box_get");
    get.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_l";
    param.m_startFlags = 8;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(get.m_handle, param, nullptr);
    m_seq2.addJob(&GfMenuObjBtlTime::seqGetBoxWait);
    return true;
}

void GfMenuObjBtlTime::ScoreListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        m_open = 0;
        m_ctrl = -1;
        break;
    case 3:
        if (event.m_param0 == 2 && m_open == 0) {
            acc.setSuspend(true);
        }
        break;
    case 0x21:
        if (m_open != 1) {
            int kind = event.m_param0;
            acc.setDispChild(kind == 0, "LAY_score_index_score");
            acc.setDispChild(kind == 1, "LAY_score_index_kill");
            acc.setDispChild(kind == 0, "LAY_score_num");
            acc.setDispChild(kind == 1, "LAY_score_num_max");
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 0;
            param.m_out = 0;
            param.m_slot = m_ctrl;
            param.m_startFlag4 = true;
            param.m_eventId = 1;
            param.m_delay = GfGameManager::isBattleArenaActive() ? 0.5f : 0.0f;
            int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            if (ctrl != -1) {
                m_open = 1;
                m_ctrl = ctrl;
            }
            acc.setSuspend(false);
        }
        break;
    case 0x22:
        if (m_open != 0) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 0;
            param.m_out = 1;
            param.m_slot = m_ctrl;
            param.m_startFlag4 = true;
            param.m_eventId = 2;
            int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            if (ctrl != -1) {
                m_open = 0;
                m_ctrl = ctrl;
            }
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBtlTime::seqNewRecordSE() {
    GfMenuObjUtil::playSE(0x22);
    return true;
}

bool GfMenuObjBtlTime::seqNewRecordWait() {
    ui::UIObjectAcc eff(m_handle, "IMG_time_new_record_eff");
    if (eff.isPlayingAnimation()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBtlTime::seqNewRecordFadeOut);
    return true;
}

bool GfMenuObjBtlTime::seqNewRecordFadeOut() {
    ui::UIObjectAcc record(m_handle, "LAY_time_new_record");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_out_r";
    param.m_startFlags = 10;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(record.searchChild("TXT_time_new_record"), param, nullptr);
    m_seq.addJob(&GfMenuObjBtlTime::seqNewRecordFadeWait);
    return true;
}

bool GfMenuObjBtlTime::seqNewRecordFadeWait() {
    ui::UIObjectAcc text(m_handle, "TXT_time_new_record");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(text.m_handle))) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBtlTime::seqNewRecordEnd);
    return true;
}

bool GfMenuObjBtlTime::seqNewRecordEnd() {
    ui::UIObjectAcc record(m_handle, "LAY_time_new_record");
    record.setDisp(false);
    ui::EventData event;
    event.m_type = 0x102;
    GfMenuObject::sendEvent(searchChildOf(m_handle, "LAY_time"), event, 0.0f);
    return true;
}

bool GfMenuObjBtlTime::seqGetBoxWait() {
    ui::UIObjectAcc get(m_handle, "TXT_ether_box_get");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(get.m_handle))) {
        return false;
    }
    m_seq2.addWait(60);
    m_seq2.addJob(&GfMenuObjBtlTime::seqGetBoxEnd);
    return true;
}

bool GfMenuObjBtlTime::seqGetBoxEnd() {
    ui::UIObjectAcc get(m_handle, "TXT_ether_box_get");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_out_r";
    param.m_startFlags = 10;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(get.m_handle, param, nullptr);
    return true;
}

}  // namespace gf
