#include "classes/gf/GfMenuObjComboRouteSimple.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjComboRouteSimple::GfMenuObjComboRouteSimple(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjComboRouteSimple::~GfMenuObjComboRouteSimple() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjComboRouteSimple::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x8E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjComboRouteSimple::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x8E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjComboRouteSimple::disp(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x8E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc(handle).setDisp(disp);
        }
    }
}

void GfMenuObjComboRouteSimple::refresh() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x8E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x100;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjComboRouteSimple::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x8E, acc.m_handle);
#line 115
    TUnk_B61450* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B61450(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjComboRouteSimple::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjComboRouteSimple::update() {
    GfMenuObject::update();
}

void TUnk_B61450::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_open = 0;
        m_ctrl = -1;
        acc.setDisp(true);
        break;
    case 0x21:
        if (m_open == 0) {
            ui::UIObjectAcc route(acc.m_handle, "LAY_route");
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x401;
            param.m_time = 0.15f;
            param.m_curve = 1;
            param.m_setDefault = true;
            param.m_startFlags = 4;
            param.m_slot = m_ctrl;
            m_ctrl = GfMenuObjUtil::startCtrl(route.m_handle, param, nullptr);
            m_open = 1;
        }
        break;
    case 0x22:
        if (m_open == 1) {
            ui::UIObjectAcc route(acc.m_handle, "LAY_route");
            if (m_ctrl != -1) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x4002;
                param.m_time = 0.15f;
                param.m_curve = 1;
                param.m_startFlags = 4;
                param.m_slot = m_ctrl;
                m_ctrl = GfMenuObjUtil::startCtrl(route.m_handle, param, nullptr);
            }
            m_open = 0;
        }
        break;
    case 0x100: {
        const GfMenuReference::IraBladeComboInfo* state = GfMenuReference::getIraBladeComboInfo();
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < 3; i++) {
            unsigned short icon = state->m_values[i] + 0x9E;
            bool reached = i < state->m_stateB;
            name.format("IMG_route_elem@%02d", i + 1);
            ui::UIObjectAcc elem(acc.m_handle, name.m_str);
            {
                name.format("IMG_route_eff@%02d", i + 1);
                ui::UIObjectAcc eff(acc.m_handle, name.m_str);
                if (icon > 0x9E && elem.getImageIndex() == 0) {
                    eff.startAnimation("add", false);
                }
            }
            {
                bool success = state->m_stateA != 0;
                name.format("IMG_route_success@%02d", i + 1);
                ui::UIObjectAcc eff(acc.m_handle, name.m_str);
                eff.setAlpha(reached && success ? 1.0f : 0.0f);
                eff.startAnimation("success", false);
            }
            elem.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
            elem.setDisp(reached);
        }
        for (int i = 1; i <= 2; i++) {
            unsigned int stage = state->m_stateB;
            name.format("IMG_route_cursor@%02d", i);
            ui::UIObjectAcc cursor(acc.m_handle, name.m_str);
            int ctrl = GfMenuObjUtil::getCtrlID(cursor.m_handle);
            if (ctrl != -1) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
            cursor.setDisp(stage == i);
            if (stage == i) {
                cursor.setAlpha(1.0f);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x40004;
                param.m_time = 0.5f;
                param.m_alpha = 0.5f;
                param.m_scale = 0.3f;
                param.m_reserve = true;
                param.m_startFlags = 8;
                param.m_curve = 3;
                GfMenuObjUtil::startCtrl(cursor.m_handle, param, nullptr);
            }
        }
        {
            mm::mtl::FixStr<32> anim;
            ui::UIObjectAcc base(acc.m_handle, "IMG_route_base");
            int ctrl = GfMenuObjUtil::getCtrlID(base.m_handle);
            if (ctrl != -1) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
            if (state->m_stateB != 0) {
                anim.format("stage_%d", state->m_stateB);
                base.startAnimation(anim.m_str, false);
                base.setDisp(true);
            }
        }
        if (state->m_stateA != 0 && state->m_stateB == 3) {
            ui::EventData next;
            next.m_type = 0x101;
            GfMenuObject::sendEvent(handle, next, 0.8f);
        }
        break;
    }
    case 0x101: {
        mm::mtl::FixStr<32> name;
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x80002;
        param.m_scale = 3.0f;
        param.m_curve = 2;
        param.m_time = 1.0f;
        param.m_setDefault = true;
        param.m_startFlags = 10;
        for (int i = 1; i <= 3; i++) {
            name.format("IMG_route_elem@%02d", i);
            ui::UIObjectAcc elem(acc.m_handle, name.m_str);
            name.format("IMG_route_elem_eff@%02d", i);
            ui::UIObjectAcc eff(acc.m_handle, name.m_str);
            eff.setImageIndex(elem.getImageIndex());
            GfMenuObjUtil::startCtrl(eff.m_handle, param, nullptr);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
