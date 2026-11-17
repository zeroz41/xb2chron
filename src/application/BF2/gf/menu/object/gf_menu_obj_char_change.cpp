#include "classes/gf/GfMenuObjCharChange.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuArtsList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/Rect.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfDataDriver.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjCharChange::GfMenuObjCharChange(unsigned int handle)
    : GfMenuObject(handle), pad_24(-1), pad_28(false), pad_29(false), pad_2A(true), m_seq(this), m_charFlags(),
      m_chainFlags(), m_cmdFlags(), pad_1AC(), pad_1B0(), pad_1B8(-1), m_artsList(nullptr) {
    pad_1C0 = false;
    pad_1BC = false;
    pad_1BD = false;
    pad_1BE = false;
    pad_1BF = false;
    m_artsList = GfMenuArtsList::create();
    ui::UIListInfoBase::SetupParam param;
    param.m_pageRowSize = 2;
    m_artsList->setup(getAllocator(ALLOCATOR(0)), param);
}

GfMenuObjCharChange::~GfMenuObjCharChange() {
    if (m_artsList != nullptr) {
        m_artsList->release();
        m_artsList = nullptr;
    }
}


void GfMenuObjCharChange::open() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x108;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharChange::close() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x109;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharChange::disp(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x3C);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc(handle).setDisp(disp);
        }
    }
}


void GfMenuObjCharChange::changeFormation() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x10A;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharChange::changeBlade() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x10B;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharChange::reverse(bool flag) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x106;
            event.m_param0 = flag;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharChange::updateOperation(GfMenuReference::IRA_OPERATION_BTN value) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x107;
            event.m_param0 = value;
            GfMenuObject::sendEvent(acc.searchChild("LAY_cmd"), event, 0.0f);
        }
    }
}

void GfMenuObjCharChange::dispInfo(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x10F;
        event.m_param0 = disp;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjCharChange::updateRecast(unsigned int index) {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    name.format("IMG_char2_recast@%02d", index + 1);
    ui::UIObjectAcc recast(main.m_handle, name.m_str);
    if (recast.m_object != nullptr) {
        name.format("IMG_char2_recast_eff@%02d", index + 1);
        ui::UIObjectAcc eff(main.m_handle, name.m_str);
        name.format("LAY_recast_body@%02d", index + 1);
        ui::UIObjectAcc body(main.m_handle, name.m_str);
        unsigned int flags = m_charFlags[index];
        if (!(flags & 2)) {
            if (index == 0) {
                ui::UIObjectAcc active(main.m_handle, "IMG_char2_active_recast@02");
                active.setAlpha(1.0f);
                if (pad_28 && GfGameManager::isBattle() && (flags & 4)) {
                    ui::UIObjectAcc activeEff(main.m_handle, "IMG_char2_active_recast_eff@02");
                    activeEff.startAnimation("select", false);
                    active.setAlpha(0.0f);
                    GfMenuObjUtil::playSE(0x2E);
                }
                ui::UIObjectAcc face(main.m_handle, "IMG_char2_active_face@02");
                face.setMulColor("gray");
            } else {
                recast.setAlpha(1.0f);
                if (pad_28 && GfGameManager::isBattle() && (flags & 4)) {
                    eff.startAnimation("select", false);
                    GfMenuObjUtil::playSE(0x2E);
                }
                body.setMulColor("gray");
                ui::UIObjectAcc face1(main.m_handle, "IMG_char2_reserve_face@01");
                face1.setMulColor("gray");
                ui::UIObjectAcc face2(main.m_handle, "IMG_char2_reserve_face@02");
                face2.setMulColor("gray");
            }
            m_charFlags[index] &= ~4u;
        } else {
            if (index == 0) {
                ui::UIObjectAcc active(main.m_handle, "IMG_char2_active_recast@02");
                active.setAlpha(0.0f);
                if (pad_28 && GfGameManager::isBattle()) {
                    ui::UIObjectAcc activeEff(main.m_handle, "IMG_char2_active_recast_eff@02");
                    activeEff.startAnimation("standbye", false);
                }
                ui::UIObjectAcc face(main.m_handle, "IMG_char2_active_face@02");
                face.setMulColor("white");
            } else {
                recast.setAlpha(0.0f);
                if (pad_28 && GfGameManager::isBattle()) {
                    eff.startAnimation("standbye", false);
                }
                body.setMulColor("white");
                ui::UIObjectAcc face1(main.m_handle, "IMG_char2_reserve_face@01");
                face1.setMulColor("white");
                ui::UIObjectAcc face2(main.m_handle, "IMG_char2_reserve_face@02");
                face2.setMulColor("white");
            }
        }
    }
}

void GfMenuObjCharChange::updateChainRecast(unsigned int index, bool) {
    ui::UIObjectAcc chain(m_handle, "LAY_chain");
    unsigned int count = chain.countChild("LAY_chain@%02d", 1);
    mm::mtl::FixStr<32> name;
    if (index < count) {
        name.format("IMG_chain_recast@%02d", index + 1);
        ui::UIObjectAcc recast(chain.m_handle, name.m_str);
        if (recast.m_object != nullptr) {
            name.format("IMG_chain_face@%02d", index + 1);
            ui::UIObjectAcc face(chain.m_handle, name.m_str);
            const char* color;
            if (m_chainFlags[index] & 2) {
                recast.setAlpha(0.0f);
                color = "white";
            } else {
                recast.setAlpha(1.0f);
                color = "gray";
            }
            face.setMulColor(color);
        }
    }
}

void GfMenuObjCharChange::startFormationChange() {
    ui::UIObjectAcc char2(m_handle, "LAY_char2");
    int distance;
    {
        mm::Rect<short> up;
        char2.getLayoutRect("active_up", up);
        mm::Rect<short> down;
        char2.getLayoutRect("active_down", down);
        distance = down.y - up.y;
    }
    updateFace(false);
    if (!pad_1C0) {
        {
            ui::UIObjectAcc first(char2.m_handle, "LAY_char2@01");
            GfMenuObjUtil::addPos(first.m_handle, 0, distance);
            GfMenuObjUtil::CtrlParam param;
            param.m_distance = distance;
            param.m_methods = 0x20;
            param.m_time = 0.3f;
            param.m_setDefault = true;
            param.m_curve = 1;
            GfMenuObjUtil::startCtrl(char2.m_handle, param, "LAY_char2@01");
        }
        {
            ui::UIObjectAcc second(char2.m_handle, "LAY_char2@02");
            GfMenuObjUtil::addPos(second.m_handle, 0, -distance);
            GfMenuObjUtil::CtrlParam param;
            param.m_distance = distance;
            param.m_methods = 0x40;
            param.m_time = 0.3f;
            param.m_setDefault = true;
            param.m_curve = 1;
            GfMenuObjUtil::startCtrl(char2.m_handle, param, "LAY_char2@02");
        }
    }
}

void GfMenuObjCharChange::startBladeChange() {
    ui::UIObjectAcc char2(m_handle, "LAY_char2");
    updateFace(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10;
    param.m_curve = 1;
    param.m_distance = 0x20;
    param.m_time = 0.25f;
    for (unsigned int i = 0; i < 2; i++) {
        const GfMenuReference::IraCharInfo* owner = GfMenuReference::getIraCharInfoFromFromID(i);
        if (owner != nullptr && !GfDataDriver::isIraFront(owner->m_driver) && pad_1B0 != 0) {
            mm::mtl::FixStr<32> name;
            name.format("LAY_char2_active@%02d", i + 1);
            {
                ui::UIObjectAcc active(char2.m_handle, name.m_str);
                GfMenuObjUtil::startCtrl(active.m_handle, param, nullptr);
            }
            param.m_methods = 8;
            name.format("LAY_char2_reserve@%02d", i + 1);
            ui::UIObjectAcc reserve(char2.m_handle, name.m_str);
            GfMenuObjUtil::startCtrl(reserve.m_handle, param, nullptr);
        }
    }
}

void GfMenuObjCharChange::dispInfoLocal(bool disp) {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    acc.setDispChild(disp, "LAY_info");
    acc.setDispChild(disp, "LAY_char2_reserve_elem_root@01");
    acc.setDispChild(disp, "LAY_char2_active_elem_root@01");
    acc.setDispChild(disp, "LAY_char2_reserve_elem_root@02");
    acc.setDispChild(disp, "LAY_char2_active_elem_root@02");
    ui::UIObjectAcc chain(acc.searchSibiling("LAY_chain"));
    chain.setDispChild(disp, "LAY_chain_info");
}

void GfMenuObjCharChange::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCharChange::CommandListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_count = acc.countChild("LAY_cmd@%02d", 1);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
        }
        break;
    case 0x21: {
        mm::mtl::FixStr<32> name;
        acc.setDisp(true);
        int ctrl = -1;
        for (int i = 0; i < m_count; i++) {
            name.format("LAY_cmd@%02d", i + 1);
            ui::UIObjectAcc cmd(acc.m_handle, name.m_str);
            if (GfMenuReference::isIraOperationBtnState(
                    static_cast<GfMenuReference::IRA_OPERATION_BTN>(i), static_cast<GfMenuReference::BTN_STATUS>(0))) {
                cmd.setScale(mm::Vec2(0.0f, 1.0f));
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x100000;
                param.m_scaleY = 1.0f;
                param.m_scale = 1.0f;
                param.m_setDefault = true;
                param.m_time = 0.1f;
                param.m_eventId = 1;
                ctrl = GfMenuObjUtil::startCtrl(cmd.m_handle, param, nullptr);
            } else {
                cmd.setDisp(false);
            }
        }
        if (ctrl != -1) {
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        break;
    }
    case 0x22: {
        mm::mtl::FixStr<32> name;
        int ctrl = -1;
        for (int i = 0; i < m_count; i++) {
            name.format("LAY_cmd@%02d", i + 1);
            ui::UIObjectAcc cmd(acc.m_handle, name.m_str);
            if (cmd.isDisp()) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x100000;
                param.m_scaleY = 1.0f;
                param.m_scale = 0.0f;
                param.m_time = 0.1f;
                param.m_eventId = 2;
                ctrl = GfMenuObjUtil::startCtrl(cmd.m_handle, param, nullptr);
            }
        }
        if (ctrl != -1) {
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        break;
    }
    case 0x107: {
        unsigned int index = event.m_param0;
        mm::mtl::FixStr<32> name;
        name.format("LAY_cmd@%02d", index + 1);
        ui::UIObjectAcc cmd(acc.m_handle, name.m_str);
        name.format("IMG_cmd_icon@%02d", index + 1);
        ui::UIObjectAcc icon(acc.m_handle, name.m_str);
        if (GfMenuReference::isIraOperationBtnState(
                static_cast<GfMenuReference::IRA_OPERATION_BTN>(index), static_cast<GfMenuReference::BTN_STATUS>(0))) {
            bool enabled = GfMenuReference::isIraOperationBtnState(
                    static_cast<GfMenuReference::IRA_OPERATION_BTN>(index), static_cast<GfMenuReference::BTN_STATUS>(1));
            bool selected = GfMenuReference::isIraOperationBtnState(
                    static_cast<GfMenuReference::IRA_OPERATION_BTN>(index), static_cast<GfMenuReference::BTN_STATUS>(3));
            cmd.setMulColor(enabled ? "white" : "gray");
            icon.setImageIndex(selected | GfMenuReference::getIraOperationBtnCommand(index) << 1);
            name.format("IMG_cmd_base@%02d", index + 1);
            {
                ui::UIObjectAcc base(acc.m_handle, name.m_str);
                bool shown = m_owner->m_cmdFlags.test(index);
                if (selected) {
                    if (!shown) {
                        base.startAnimation("select_keep", false);
                        if (m_owner->pad_1BF) {
                            GfMenuObjUtil::playSE(0x2D);
                        }
                    }
                } else {
                    if (shown && m_owner->pad_1BF) {
                        GfMenuObjUtil::playSE(0x2D);
                    }
                    base.startAnimation("wait", false);
                }
            }
            m_owner->m_cmdFlags.set(index, selected);
            if (!selected && enabled && GfMenuReference::isIraOperationBtnState(
                    static_cast<GfMenuReference::IRA_OPERATION_BTN>(index), static_cast<GfMenuReference::BTN_STATUS>(2))) {
                name.format("IMG_cmd_base@%02d", index + 1);
                ui::UIObjectAcc base(acc.m_handle, name.m_str);
                base.startAnimation("select", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
                if (m_owner->pad_1BF) {
                    GfMenuObjUtil::playSE(0x2D);
                }
            }
        }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCharChange::ChainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_ctrl = -1;
        break;
    case 3:
        if (event.m_param0 - 1U <= 2) {
            GfMenuObject::termCallContext(acc.searchSibiling("LAY_main"));
            m_owner->updateChainRecast(0, false);
            m_owner->updateChainRecast(1, false);
            m_owner->updateChainRecast(2, false);
        }
        break;
    case 0xD: {
        unsigned int index = event.m_param2;
        if (event.m_param1 == 0) {
            if (event.m_param0 == 1) {
                if (m_owner->pad_28 && GfGameManager::isBattle()) {
                    GfMenuObjUtil::playSE(0x2C);
                }
                *(m_owner->m_chainFlags + index) |= 2;
            } else {
                *(m_owner->m_chainFlags + index) &= ~2u;
            }
            m_owner->updateChainRecast(index, false);
        }
        break;
    }
    case 0x21:
        if (event.m_param0 == 0) {
            mm::mtl::FixStr<32> name;
            float wait = GfMenuObjUtil::getParamMenu()->m_chainAttackWait;
            if (m_ctrl != -1) {
                GfMenuObjUtil::setCtrlDefault(m_ctrl);
            }
            for (unsigned int i = 0; i < 3; i++) {
                name.format("LAY_chain@%02d", i + 1);
                ui::UIObjectAcc chain(acc.m_handle, name.m_str);
                GfMenuObjUtil::CtrlParam param;
                param.m_eventId = i + 1;
                param.m_methods = 0x10000000;
                param.m_motionLib = "sample";
                param.m_motion = "fadein";
                param.m_time = wait;
                param.m_delay = wait * i;
                int ctrl = GfMenuObjUtil::startCtrl(chain.m_handle, param, nullptr);
                chain.setAlpha(0.0f);
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                m_owner->updateChainRecast(i, false);
                name.format("IMG_chain_recast@%02d", i + 1);
                ui::UIObjectAcc recast(acc.m_handle, name.m_str);
                recast.setAlpha(0.0f);
            }
            GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_chain_info_main"), 0, 0);
        } else {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 0;
            param.m_out = 0;
            param.m_eventId = 0;
            param.m_startFlag4 = true;
            param.m_slot = m_ctrl;
            m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        }
        acc.setDisp(true);
        break;
    case 0x22:
        if (event.m_param0 == 0) {
            acc.setDisp(false);
        } else {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_out = 1;
            param.m_startFlag4 = true;
            param.m_slot = m_ctrl;
            m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf

template void gf::GfMenuSequence<gf::GfMenuObjCharChange, 4>::addAnimJob(unsigned int, const char*);

template bool gf::GfMenuSequence<gf::GfMenuObjCharChange, 4>::wait_anim();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjCharChange, 4>>(const mm::mtl::Delegate<bool()>*);

template void ui::UIListInfo<gf::MenuArtsInfo>::addContents(const gf::MenuArtsInfo&);
