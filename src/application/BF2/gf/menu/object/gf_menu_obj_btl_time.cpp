#include "classes/gf/TUnk_B60928.h"
#include "classes/gf/TUnk_B60928/TUnk_B60970.h"
#include "classes/gf/TUnk_B60928/TUnk_B60998.h"
#include "classes/gf/TUnk_B60928/TUnk_B609C0.h"
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
// of that name. fn_71003B48B8's accessors take the top stack slots as an inlined callee's do.
static inline unsigned int searchChildOf(unsigned int handle, const char* name) {
    ui::UIObjectAcc parent(handle);
    return parent.searchChild(name);
}

TUnk_B60928::TUnk_B60928(unsigned int handle) : GfMenuObject(handle), m_seq(this), m_seq2(this), m_etherBox(0) {}

TUnk_B60928::~TUnk_B60928() {}

void TUnk_B60928::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x87, main.m_handle);
    {
        ui::UIObjectAcc time(m_handle, "LAY_time");
        {
#line 86
            TUnk_B60970* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B60970(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(time.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuBattleAdapter::create(time.searchChild("TXT_time"), 0x19);
        GfMenuBattleAdapter::create(time.searchChild("TXT_time_shadow"), 0x19);
    }
    if (GfMenuObjUtil::fn_710048FD30(1) && !GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuAdapterManager::beginCategory(4);
        {
            ui::UIObjectAcc ether(m_handle, "LAY_ether");
            {
#line 106
                TUnk_B60998* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B60998(this);
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
                TUnk_B609C0* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B609C0(this);
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
    fn_71003B48B8();
}

void TUnk_B60928::fn_71003B48B8() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x103;
        GfMenuObject::sendEvent(searchChildOf(acc.m_handle, "LAY_time"), event, 0.0f);
        if (GfMenuObjUtil::fn_710048FD30(1)) {
            GfMenuObject::sendEvent(searchChildOf(acc.m_handle, "LAY_ether"), event, 0.0f);
        }
        if (GfMenuObjUtil::fn_710048FD30(1)) {
            GfMenuObject::sendEvent(searchChildOf(acc.m_handle, "LAY_score"), event, 0.0f);
        }
    }
}

void TUnk_B60928::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B60928::update() {
    m_seq.update();
    m_seq2.update();
    GfMenuObject::update();
}

void TUnk_B60928::fn_71003B4AD8(int part, unsigned int param) {
    if (part == 0 || (!GfMenuObjUtil::fn_710048FD30(3) && GfMenuObjUtil::fn_710048FD30(1))) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            unsigned int handle = fn_71003B4B7C(acc.m_handle, part, false);
            if (handle != 0) {
                ui::EventData event;
        event.m_type = 0x21;
                event.m_param0 = param;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            }
        }
    }
}

unsigned int TUnk_B60928::fn_71003B4B7C(unsigned int handle, int part, bool always) {
    ui::UIObjectAcc acc(handle);
    switch (part) {
    case 0:
        return acc.searchChild("LAY_time");
    case 1:
        if (always || GfGameManager::fn_71002AC580()) {
            return acc.searchChild("LAY_ether");
        }
        break;
    case 2:
        if (always || GfGameManager::fn_71002AC580()) {
            return acc.searchChild("LAY_score");
        }
        break;
    }
    return 0;
}

void TUnk_B60928::fn_71003B4C24(int part) {
    if (part == 0 || (!GfMenuObjUtil::fn_710048FD30(3) && GfMenuObjUtil::fn_710048FD30(1))) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            unsigned int handle = fn_71003B4B7C(acc.m_handle, part, false);
            if (handle != 0) {
                ui::EventData event;
        event.m_type = 0x22;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            }
        }
    }
}

void TUnk_B60928::fn_71003B4CC0() {
    if (!GfMenuObjUtil::fn_710048FD30(1)) {
        return;
    }
    fn_71003B4AD8(0, 0);
    fn_71003B4AD8(1, 0);
    if (GfGameManager::fn_71002AC5D8()->m_kind == 1) {
        fn_71003B4AD8(2, 0);
    } else if (GfGameManager::fn_71002AC5D8()->m_kind == 3) {
        fn_71003B4AD8(2, 1);
    } else {
        fn_71003B4C24(2);
    }
}

void TUnk_B60928::fn_71003B4D3C() {
    fn_71003B4C24(0);
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        fn_71003B4C24(1);
    }
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        fn_71003B4C24(2);
    }
}

void TUnk_B60928::fn_71003B4D80() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        unsigned int handle = fn_71003B4B7C(acc.m_handle, 0, false);
        if (handle != 0) {
            ui::EventData event;
        event.m_type = 0x100;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void TUnk_B60928::fn_71003B4E18() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x87));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        unsigned int handle = fn_71003B4B7C(acc.m_handle, 0, false);
        if (handle != 0) {
            ui::EventData event;
        event.m_type = 0x101;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

bool TUnk_B60928::fn_71003B52DC() {
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
    m_seq.addJob(&TUnk_B60928::fn_71003B5E54);
    m_seq.addJob(&TUnk_B60928::fn_71003B5E70);
    return true;
}

bool TUnk_B60928::fn_71003B5B28() {
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
    m_seq2.addJob(&TUnk_B60928::fn_71003B6170);
    return true;
}

bool TUnk_B60928::fn_71003B5E54() {
    GfMenuObjUtil::playSE(0x22);
    return true;
}

bool TUnk_B60928::fn_71003B5E70() {
    ui::UIObjectAcc eff(m_handle, "IMG_time_new_record_eff");
    if (eff.isPlayingAnimation()) {
        return false;
    }
    m_seq.addJob(&TUnk_B60928::fn_71003B5F20);
    return true;
}

bool TUnk_B60928::fn_71003B5F20() {
    ui::UIObjectAcc record(m_handle, "LAY_time_new_record");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_out_r";
    param.m_startFlags = 10;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(record.searchChild("TXT_time_new_record"), param, nullptr);
    m_seq.addJob(&TUnk_B60928::fn_71003B6028);
    return true;
}

bool TUnk_B60928::fn_71003B6028() {
    ui::UIObjectAcc text(m_handle, "TXT_time_new_record");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(text.m_handle))) {
        return false;
    }
    m_seq.addJob(&TUnk_B60928::fn_71003B60DC);
    return true;
}

bool TUnk_B60928::fn_71003B60DC() {
    ui::UIObjectAcc record(m_handle, "LAY_time_new_record");
    record.setDisp(false);
    ui::EventData event;
    event.m_type = 0x102;
    GfMenuObject::sendEvent(searchChildOf(m_handle, "LAY_time"), event, 0.0f);
    return true;
}

bool TUnk_B60928::fn_71003B6170() {
    ui::UIObjectAcc get(m_handle, "TXT_ether_box_get");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(get.m_handle))) {
        return false;
    }
    m_seq2.addWait(60);
    m_seq2.addJob(&TUnk_B60928::fn_71003B62C4);
    return true;
}

bool TUnk_B60928::fn_71003B62C4() {
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
