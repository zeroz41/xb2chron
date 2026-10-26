#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjArtsPalette/MainListener.h"
#include "classes/gf/GfMenuObjArtsPalette/ReverseListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Col3.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjArtsPalette::GfMenuObjArtsPalette(unsigned int handle)
    : GfMenuObject(handle), m_slotSeq0(this), m_slotSeq1(this), m_slotSeq2(this), m_elemSeq(this) {
    for (int i = 0; i < 3; i++) {
        m_ctrlIds[i] = -1;
    }
    m_slotSeqs[0] = &m_slotSeq0;
    m_slotSeqs[1] = &m_slotSeq1;
    m_slotSeqs[2] = &m_slotSeq2;
    for (int i = 0; i < 3; i++) {
        m_slotFlags[i] = 0;
    }
}

GfMenuObjArtsPalette::~GfMenuObjArtsPalette() {}

void GfMenuObjArtsPalette::push(unsigned int slot) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10A;
        event.m_param0 = slot;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjArtsPalette::startChainAttack() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10B;
        event.m_param0 = 1;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjArtsPalette::exitChainAttack() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10B;
        event.m_param0 = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjArtsPalette::reverse(bool reverse) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10C;
        event.m_param0 = reverse;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjArtsPalette::pushReverseBtn(unsigned int slot) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10D;
        event.m_param0 = slot;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjArtsPalette::initialize() {
    ui::UIObjectAcc acc(m_handle);
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc main(acc.m_handle, "LAY_main");
        if (main.m_object != nullptr) {
#line 190
            MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
            // the original stores the count after the listener's own fields, not with its base
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuObject::attachExternalCall(0x27, main.m_handle);
            mm::mtl::FixStr<32> name;
            if (GfMenuObjUtil::fn_710048FD30(3)) {
                GfMenuCharDataAdapter* icon =
                    GfMenuCharDataAdapter::createFromPartyDriver(main.searchChild("IMG_elem_icon"), 0x2A, 0, true);
                if (icon != nullptr) {
                    icon->m_rowHandle = main.searchChild("IMG_elem_eff");
                }
                GfMenuCharDataAdapter::createFromPartyDriver(main.searchChild("IMG_elem_range_icon"), 0x2A, 0, true);
                GfMenuBattleAdapter::create(main.searchChild("LAY_elem_range_icon"), 0x17);
                GfMenuObject::addDispEventCondition(main.m_handle, "LAY_elem_range_icon", 2, 0, false);
                GfMenuCharDataAdapter* eff =
                    GfMenuCharDataAdapter::createFromPartyDriver(main.searchChild("IMG_elem_eff"), 0x3A, 0, true);
                if (eff != nullptr) {
                    eff->setColorMode(0);
                    eff->m_rowHandle = main.searchChild("LAY_elem_range");
                }
                GfMenuCharDataAdapter* range =
                    GfMenuCharDataAdapter::createFromPartyDriver(main.searchChild("IMG_elem_range"), 0x3A, 0, true);
                if (range != nullptr) {
                    range->setColorMode(1);
                }
            } else {
                GfMenuCharDataAdapter* icon = GfMenuCharDataAdapter::createFromPartyBlade(
                    main.searchChild("IMG_elem_icon"), 0x2A, 0, -1, true, false, false);
                if (icon != nullptr) {
                    icon->m_rowHandle = main.searchChild("IMG_elem_eff");
                }
                GfMenuCharDataAdapter::createFromPartyBlade(main.searchChild("IMG_elem_range_icon"), 0x2A, 0, -1, true,
                                                            false, false);
                GfMenuBattleAdapter::create(main.searchChild("LAY_elem_range_icon"), 0x17);
                GfMenuObject::addDispEventCondition(main.m_handle, "LAY_elem_range_icon", 2, 0, false);
                GfMenuCharDataAdapter* eff = GfMenuCharDataAdapter::createFromPartyBlade(
                    main.searchChild("IMG_elem_eff"), 0x3A, 0, -1, true, false, false);
                if (eff != nullptr) {
                    eff->setColorMode(0);
                    eff->m_rowHandle = main.searchChild("LAY_elem_range");
                }
                GfMenuCharDataAdapter* range = GfMenuCharDataAdapter::createFromPartyBlade(
                    main.searchChild("IMG_elem_range"), 0x3A, 0, -1, true, false, false);
                if (range != nullptr) {
                    range->setColorMode(1);
                }
            }
            {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x80000;
                param.m_scale = 0.8f;
                param.m_time = 1.5f;
                param.m_reserve = true;
                param.m_curve = 3;
                GfMenuObjUtil::startCtrl(main.m_handle, param, "IMG_elem_eff");
            }
            for (int i = 0; i < 3; i++) {
                name.format("IMG_recast@%02d", i + 1);
                ui::UIObjectAcc recast(main.m_handle, name.m_str);
                if (recast.m_object != nullptr) {
                    GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(recast.m_handle, 0);
                    adapter->m_index = i;
                    adapter->setNumberInterpolateMode(0.25f);
                    recast.startAnimation("start", true);
                }
                GfMenuObject::addNumberEventCondition(main.m_handle, name.m_str, 0, i, 1.0f);
                name.format("IMG_icon_type@%02d", i + 1);
                GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 3);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
                name.format("IMG_icon_enhance@%02d", i + 1);
                adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 4);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
                name.format("IMG_icon_react@%02d", i + 1);
                adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 5);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
                name.format("IMG_icon_range@%02d", i + 1);
                adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 6);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
                name.format("IMG_icon_disable@%02d", i + 1);
                adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 10);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                    adapter->setDispReverseMode(true);
                    ui::UIObjectAcc(main.searchChild(name.m_str)).setAlpha(0.0f);
                    GfMenuObject::addDispEventCondition(main.m_handle, name.m_str, 1, i, false);
                }
                name.format("LAY_arts_info@%02d", i + 1);
                ui::UIObjectAcc info(main.m_handle, name.m_str);
                name.format("TXT_arts_name@%02d", i + 1);
                adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 7);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                    adapter->m_rowHandle = info.m_handle;
                }
                name.format("TXT_arts_info@%02d", i + 1);
                adapter = GfMenuBattleAdapter::create(main.searchChild(name.m_str), 8);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
                name.format("LAY_arts_info_text@%02d", i + 1);
                ui::UIObjectAcc text(info.m_handle, name.m_str);
                GfMenuObjUtil::FitOption option;
                option.m_keepScaleY = true;
                name.format("IMG_arts_info_bg@%02d", i + 1);
                GfMenuObjUtil::createFitPlugin(main.searchChild(name.m_str), text.m_handle, 0x30, 0, option);
            }
            main.setDispChild(false, "LAY_spsign");
#line 354
            ReverseListener* reverse = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReverseListener(this);
            reverse->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_reverse"), reverse);
            if (reverse != nullptr) {
                reverse->release();
            }
            GfMenuObject::initialize();
        }
    }
}

void GfMenuObjArtsPalette::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjArtsPalette::update() {
    m_slotSeqs[0]->update();
    m_slotSeqs[1]->update();
    m_slotSeqs[2]->update();
    m_elemSeq.update();
    GfMenuObject::update();
}

void GfMenuObjArtsPalette::ReverseListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(false);
        int count;
        {
            mm::mtl::FixStr<32> name;
            count = acc.countChild("LAY_reverse_icon@%02d", 1);
            for (int i = 0; i != count; i++) {
                name.format("LAY_reverse_icon@%02d", i + 1);
                ui::UIObjectAcc icon(acc.m_handle, name.m_str);
                GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(icon.m_handle, 0x18);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
                icon.setScale(mm::Vec2(0.0f, 1.0f));
            }
        }
        m_count = count;
        ui::UIObjectAcc frame(acc.m_handle, "IMG_reverse_frame");
        frame.setMulColor(mm::Col3(0.78f, 1.0f, 0.78f));
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            acc.setDispChild(true, "IMG_reverse_frame");
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
        }
        break;
    case 0x21: {
        mm::mtl::FixStr<32> name;
        acc.setDisp(true);
        if (m_count > 0) {
            int ctrl;
            int i = 0;
            do {
                i++;
                name.format("LAY_reverse_icon@%02d", i);
                ui::UIObjectAcc icon(acc.m_handle, name.m_str);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x100000;
                param.m_scaleY = 1.0f;
                param.m_scale = 1.0f;
                param.m_setDefault = true;
                param.m_time = 0.1f;
                param.m_eventId = 1;
                ctrl = GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
            } while (i < m_count);
            if (ctrl != -1) {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
        }
        break;
    }
    case 0x22: {
        mm::mtl::FixStr<32> name;
        if (m_count > 0) {
            int ctrl;
            int i = 0;
            do {
                i++;
                name.format("LAY_reverse_icon@%02d", i);
                ui::UIObjectAcc icon(acc.m_handle, name.m_str);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x100000;
                param.m_scaleY = 1.0f;
                param.m_scale = 0.0f;
                param.m_time = 0.1f;
                param.m_eventId = 2;
                ctrl = GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
            } while (i < m_count);
            if (ctrl != -1) {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
        }
        acc.setDispChild(false, "IMG_reverse_frame");
        break;
    }
    case 0x10D: {
        unsigned int slot = event.m_param0;
        if (GfMenuReference::isReversePaletteBtnState(slot, 1)) {
            mm::mtl::FixStr<32> name;
            name.format("IMG_reverse_icon@%02d", slot + 1);
            ui::UIObjectAcc icon(acc.m_handle, name.m_str);
            icon.setAddColor("black");
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x40040000;
            param.m_bright = 1.0f;
            param.m_time = 0.15f;
            param.m_scale = 0.1f;
            param.m_setDefault = true;
            param.m_curve = 4;
            GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

int GfMenuObjArtsPalette::ctrlPalletteDisp(bool reverse, unsigned int mode) {
    ui::UIObjectAcc palette(m_handle, "LAY_palette");
    mm::mtl::FixStr<32> name;
    float time;
    if (mode == 1) {
        time = 0.1f;
    } else if (mode == 0) {
        time = GfMenuObjUtil::getParamMenu()->m_chainAttackWait;
    } else {
        time = 0.0f;
    }
    ui::UIObjectAcc info(palette.m_handle, "LAY_arts_info");
    int ctrl;
    if (!reverse) {
        for (int i = 1; i < 4; i++) {
            name.format("LAY_arts_icon@%02d", i);
            ui::UIObjectAcc icon(palette.m_handle, name.m_str);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x100000;
            param.m_scaleY = 1.0f;
            param.m_eventId = 9;
            param.m_scale = 1.0f;
            param.m_time = time;
            ctrl = GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
            name.format("LAY_arts_st@%02d", i);
            palette.setDispChild(true, name.m_str);
            name.format("LAY_arts_info@%02d", i);
            GfMenuObjUtil::CtrlParam fade;
            fade.m_methods = 1;
            fade.m_time = time;
            GfMenuObjUtil::startCtrl(info.m_handle, fade, name.m_str);
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = time;
        GfMenuObjUtil::startCtrl(palette.m_handle, param, "LAY_elem_eff");
        GfMenuObjUtil::startCtrl(palette.m_handle, param, "IMG_elem_icon");
        GfMenuObjUtil::startCtrl(palette.m_handle, param, "LAY_elem_range");
    } else {
        for (int i = 1; i < 4; i++) {
            name.format("LAY_arts_icon@%02d", i);
            ui::UIObjectAcc icon(palette.m_handle, name.m_str);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x100000;
            param.m_scaleY = 1.0f;
            param.m_eventId = 8;
            param.m_scale = 0.0f;
            param.m_time = time;
            ctrl = GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
            name.format("LAY_arts_st@%02d", i);
            palette.setDispChild(false, name.m_str);
            name.format("LAY_arts_info@%02d", i);
            GfMenuObjUtil::CtrlParam fade;
            fade.m_methods = 2;
            fade.m_time = time;
            GfMenuObjUtil::startCtrl(palette.m_handle, fade, name.m_str);
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = time;
        GfMenuObjUtil::startCtrl(palette.m_handle, param, "LAY_elem_eff");
        GfMenuObjUtil::startCtrl(palette.m_handle, param, "IMG_elem_icon");
        GfMenuObjUtil::startCtrl(palette.m_handle, param, "LAY_elem_range");
    }
    return ctrl;
}


void GfMenuObjArtsPalette::open() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x100;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjArtsPalette::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x27));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x101;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

}  // namespace gf
