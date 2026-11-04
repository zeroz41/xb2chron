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
      m_chainFlags(), pad_1A8(), pad_1AC(), pad_1B0(), pad_1B8(-1), m_artsList(nullptr) {
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

}  // namespace gf
