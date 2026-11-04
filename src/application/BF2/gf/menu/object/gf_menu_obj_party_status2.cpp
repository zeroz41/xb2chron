#include "classes/gf/GfMenuObjPartyStatus2.h"
#include "classes/gf/GfMenuObjPartyStatus2/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuRewriteNumber.h"
#include "classes/gf/GfGameParty.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfObjAcc.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjPartyStatus2::GfMenuObjPartyStatus2(unsigned int handle) : GfMenuObject(handle) {
    m_open = false;
    m_rewriteNumber = nullptr;
    m_frameCtrl[0] = -1;
    m_frameCtrl[1] = -1;
    m_frameCtrl[2] = -1;
}

GfMenuObjPartyStatus2::~GfMenuObjPartyStatus2() {
    if (m_rewriteNumber != nullptr) {
        m_rewriteNumber->release();
        m_rewriteNumber = nullptr;
    }
}

void GfMenuObjPartyStatus2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 110
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x5D, main);
    {
        ui::UIObjectAcc icon(acc.m_handle, "IMG_buff_icon");
        ui::UIObjectAcc gauge(acc.m_handle, "IMG_buff_gauge");
        GfMenuBattleAdapter::create(icon.m_handle, 0x16)->m_index = 0;
        icon.setExtType(4);
        GfMenuBattleAdapter::create(gauge.m_handle, 0x16)->m_index = 0;
        gauge.setExtType(4);
    }
    GfMenuObject::initialize();
}

void GfMenuObjPartyStatus2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPartyStatus2::update() {
    GfMenuObject::update();
}

void GfMenuObjPartyStatus2::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_owner->m_rewriteNumber = GfMenuRewriteNumber::create();
        setupPartyStatus(acc, m_owner->m_rewriteNumber);
        GfMenuObjUtil::setChildDisp(handle, "LAY_dr_list", true);
        acc.setDisp(false);
        break;
    case 3: {
        unsigned int id = event.m_param0;
        switch (id) {
        case 1:
            movePartyFrameIn(acc, 0, m_owner->m_frameCtrl[0]);
            movePartyFrameIn(acc, 1, m_owner->m_frameCtrl[1]);
            movePartyFrameIn(acc, 2, m_owner->m_frameCtrl[2]);
            break;
        case 4:
            movePartyFrameOut(acc, 0, m_owner->m_frameCtrl[0]);
            movePartyFrameOut(acc, 1, m_owner->m_frameCtrl[1]);
            movePartyFrameOut(acc, 2, m_owner->m_frameCtrl[2]);
            break;
        case 7:
        case 8:
        case 9:
            movePartyFrameInEnd(acc, id - 7);
            m_owner->m_frameCtrl[id - 7] = -1;
            break;
        case 10:
        case 11:
        case 12:
            m_owner->m_frameCtrl[id - 10] = -1;
            break;
        }
        break;
    }
    case 0xD:
        if (event.m_param1 == 0) {
            int no = event.m_param2;
            int state = event.m_param0;
            mm::mtl::FixStr<32> name;
            name.format("IMG_dr_dmg_eff@%02d", no);
            ui::UIObjectAcc eff(acc.searchChild(name.m_str));
            if (state == 1 || state == 2) {
                eff.setDisp(true);
                eff.startAnimation("pinch", false);
            } else {
                eff.setDisp(false);
            }
        }
        break;
    case 0x21:
        if (!m_owner->m_open) {
            for (int i = 0; i < 3; i++) {
                if (m_owner->m_frameCtrl[i] != -1) {
                    GfMenuObjUtil::stopCtrl(m_owner->m_frameCtrl[i]);
                    m_owner->m_frameCtrl[i] = -1;
                }
            }
            acc.setDisp(true);
            mm::mtl::FixStr<32> name;
            for (int i = 1; i < 4; i++) {
                name.format("LAY_dr@%02d", i);
                ui::UIObjectAcc frame(handle, name.m_str);
                frame.setAlpha(0.0f);
                name.format("dr_position%02d", i);
                mm::Rect<short> rect;
                frame.getLayoutRect(name.m_str, rect);
                mm::Pnt<short> pos;
                frame.getPos(pos);
                pos.x = rect.x;
                frame.setPos(pos);
                name.format("TXT_dr_name@%02d", i);
                ui::UIObjectAcc text(handle, name.m_str);
                text.setAlpha(0.0f);
                name.format("TXT_dr_hp_num@%02d", i);
                ui::UIObjectAcc hp(handle, name.m_str);
                hp.setAlpha(0.0f);
            }
            if (m_owner->m_rewriteNumber != nullptr) {
                m_owner->m_rewriteNumber->m_enabled = false;
            }
            m_owner->m_open = true;
            if (handle != 0) {
                ui::EventData start;
                start.m_type = 3;
                start.m_param0 = 1;
                ui::UIManager::get()->requestObjectEvent(handle, start, 0.0f);
            }
        }
        break;
    case 0x22:
        if (m_owner->m_open) {
            m_owner->m_open = false;
            for (int i = 0; i < 3; i++) {
                if (m_owner->m_frameCtrl[i] != -1) {
                    GfMenuObjUtil::stopCtrl(m_owner->m_frameCtrl[i]);
                    m_owner->m_frameCtrl[i] = -1;
                }
            }
            if (handle != 0) {
                ui::EventData out;
                out.m_type = 3;
                out.m_param0 = 4;
                ui::UIManager::get()->requestObjectEvent(handle, out, 0.0f);
            }
        }
        break;
    case 0x101:
        if (!GfMenuObjUtil::isValidExpansion(3) || !GfMenuManager::isOpenFullScreen()) {
            int index = event.m_param0 + 1;
            mm::mtl::FixStr<32> name;
            name.format("IMG_dr_exp_eff@%02d", index);
            ui::UIObjectAcc eff(acc.searchChild(name.m_str));
            eff.startAnimation("label", false);
            name.format("TXT_dr_levelup@%02d", index);
            ui::UIObjectAcc text(acc.searchChild(name.m_str));
            if (text.m_object != nullptr) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "mnu034_levelup_move";
                param.m_motion = "level_up";
                param.m_setDefault = true;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
            }
            name.format("TXT_dr_levelup2@%02d", index);
            ui::UIObjectAcc text2(acc.searchChild(name.m_str));
            if (text2.m_object != nullptr) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "mnu034_levelup_scale";
                param.m_motion = "level_up";
                param.m_setDefault = true;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(text2.m_handle, param, nullptr);
            }
            GfMenuObjUtil::playJingle(5);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjPartyStatus2::setupPartyStatus(ui::UIObjectAcc& acc, GfMenuRewriteNumber* rewrite) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
        int no = i + 1;
        name.format("TXT_dr_name@%02d", no);
        GfMenuCharDataAdapter* adapter =
            GfMenuCharDataAdapter::createFromPartyDriver(acc.searchChild(name.m_str), 2, i, true);
        name.format("LAY_dr@%02d", no);
        adapter->m_rowHandle = acc.searchChild(name.m_str);
        name.format("TXT_dr_lv_num@%02d", no);
        GfMenuCharDataAdapter::createFromPartyDriver(acc.searchChild(name.m_str), 1, i, true);
        name.format("TXT_dr_hp_num@%02d", no);
        GfMenuGfObjAdapter* number = GfMenuGfObjAdapter::createFromPartyDriver(acc.searchChild(name.m_str), 0, i, true);
        if (number != nullptr) {
            number->setNumberInterpolateMode(0.2f);
            number->setRewriteNumber(rewrite);
        }
        name.format("LAY_dr_hp@%02d", no);
        ui::UIObjectAcc hp(acc.m_handle, name.m_str);
        name.format("IMG_dr_hp_bar@%02d", no);
        unsigned int barHandle = acc.searchChild(name.m_str);
        ui::UIObjectAcc bar(barHandle);
        GfMenuGfObjAdapter* gauge = GfMenuGfObjAdapter::createFromPartyDriver(barHandle, 0, i, true);
        if (gauge != nullptr) {
            gauge->setNumberInterpolateMode(0.2f);
            gauge->setRewriteNumber(rewrite);
        }
        bar.setExtType(1);
        bar.setAddColor("dr_hp_normal");
        GfMenuObject::addNumberEventCondition(acc.m_handle, name.m_str, 0, no, 0.2f);
        unsigned int backHandle = hp.duplicateChild(name.m_str);
        ui::UIObjectAcc back(backHandle);
        if (back.m_object != nullptr) {
            if (!GfMenuObjUtil::isValidExpansion(3)) {
                GfMenuGfObjAdapter* damage = GfMenuGfObjAdapter::createFromPartyDriver(backHandle, 0, i, true);
                if (damage != nullptr) {
                    damage->setNumberInterpolateMode(0.6f);
                    damage->setRewriteNumber(rewrite);
                }
                back.setExtType(1);
                back.setAddColor("red");
                back.setAlpha(0.5f);
            } else {
                GfMenuGfObjAdapter* pinch = GfMenuGfObjAdapter::createFromPartyDriver(backHandle, 0x2C, i, true);
                if (pinch != nullptr) {
                    pinch->setNumberInterpolateMode(0.2f);
                }
                back.setExtType(1);
                back.setAddColor("dr_hp_pinch");
                back.setMulColor("black");
            }
            back.setDispPriority(bar.getDispPriority() - 1);
        }
        name.format("IMG_dr_exp_bar@%02d", no);
        unsigned int expHandle = acc.searchChild(name.m_str);
        ui::UIObjectAcc exp(expHandle);
        GfMenuCharDataAdapter* expAdapter = GfMenuCharDataAdapter::createFromPartyDriver(expHandle, 0x16, i, true);
        if (expAdapter != nullptr) {
            expAdapter->setNumberInterpolateMode(0.2f);
            expAdapter->setRewriteNumber(rewrite);
        }
        exp.setExtType(1);
    }
}

void GfMenuObjPartyStatus2::movePartyFrameIn(ui::UIObjectAcc& acc, unsigned int index, int& ctrl) {
    mm::mtl::FixStr<32> name;
    GfObjAcc driver(GfGameParty::getHandleDriver(index, static_cast<PTPOS>(0)));
    driver.getBdatId();
    name.format("LAY_dr@%02d", index + 1);
    ui::UIObjectAcc frame(acc.searchChild(name.m_str));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x201;
    param.m_curve = 1;
    param.m_setDefault = true;
    param.m_eventId = index + 7;
    param.m_time = 0.3f;
    param.m_delay = index * 0.1f;
    ctrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
    GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
}

void GfMenuObjPartyStatus2::movePartyFrameOut(ui::UIObjectAcc& acc, unsigned int index, int& ctrl) {
    mm::mtl::FixStr<32> name;
    GfObjAcc driver(GfGameParty::getHandleDriver(index, static_cast<PTPOS>(0)));
    int id = driver.getBdatId();
    name.format("LAY_dr@%02d", index + 1);
    ui::UIObjectAcc frame(acc.searchChild(name.m_str));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x2002;
    param.m_curve = 1;
    param.m_eventId = index + 10;
    param.m_time = id == 0 ? 0.0f : 0.3f;
    param.m_delay = id == 0 ? 0.0f : index * 0.1f;
    ctrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
    GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
}

void GfMenuObjPartyStatus2::movePartyFrameInEnd(ui::UIObjectAcc& acc, unsigned int index) {
    mm::mtl::FixStr<32> name;
    GfMenuObjUtil::CtrlParam param;
    name.format("TXT_dr_name@%02d", index + 1);
    {
        ui::UIObjectAcc text(acc.m_handle, name.m_str);
        param.m_methods = 1;
        param.m_time = 0.2f;
        GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
    }
    name.format("TXT_dr_hp_num@%02d", index + 1);
    {
        ui::UIObjectAcc text(acc.m_handle, name.m_str);
        param.m_methods = 1;
        param.m_time = 0.2f;
        GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
    }
}

void GfMenuObjPartyStatus2::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5D);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyStatus2::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5D);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyStatus2::disp(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5D);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc(handle).setDisp(disp);
        }
    }
}

void GfMenuObjPartyStatus2::levelup(unsigned int party) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5D);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            event.m_param0 = party;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyStatus2::clearDying(unsigned int value) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5D);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0xD;
            event.m_param0 = 3;
            event.m_param2 = value;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

}  // namespace gf
