#include "classes/gf/GfMenuObject.h"
#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjComboRoute.h"
#include "classes/gf/GfMenuObjComboRoute/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuElementComboAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/TUnk_B61408.h"

namespace gf {

namespace {
// the routes' cursors, by the route a display condition event (0xD) names (the name is not the original's)
const char* s_routeCursors[] = {
    "IMG_root_cursor@0101", "IMG_root_cursor@0201", "IMG_root_cursor@0202", "IMG_root_cursor@0301",
    "IMG_root_cursor@0302", "IMG_root_cursor@0303", "IMG_root_cursor@0304",
};
}  // namespace

GfMenuObjComboRoute::GfMenuObjComboRoute(unsigned int handle) : GfMenuObject(handle), m_openCtrl(-1) {
    for (int i = 0; i < 7; i++) {
        m_cursorCtrls[i] = -1;
    }
}

GfMenuObjComboRoute::~GfMenuObjComboRoute() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjComboRoute::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 82
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x5E, main);
    GfMenuObject::initialize();
}

void GfMenuObjComboRoute::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjComboRoute::update() {
    GfMenuObject::update();
}

void GfMenuObjComboRoute::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupComboRoute(acc);
        acc.setDisp(true);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0xD:
        if (event.m_param1 == 1) {
            unsigned int route = event.m_param2;
            int type = event.m_param0;
            ui::UIObjectAcc cursor(acc.searchChild(s_routeCursors[route]));
            if (type == 5) {
                GfMenuObjUtil::CtrlParam param;
                cursor.setDisp(true);
                cursor.setAlpha(1.0f);
                param.m_methods = 0x40004;
                param.m_time = 0.5f;
                param.m_alpha = 0.5f;
                param.m_scale = 0.3f;
                param.m_reserve = true;
                param.m_startFlags = 8;
                param.m_curve = 3;
                int ctrl = GfMenuObjUtil::startCtrl(cursor.m_handle, param, nullptr);
                if (m_owner->m_cursorCtrls[route] == -1) {
                    m_owner->m_cursorCtrls[route] = ctrl;
                }
            } else if (type == 6) {
                if (m_owner->m_cursorCtrls[route] != -1) {
                    GfMenuObjUtil::stopCtrl(m_owner->m_cursorCtrls[route]);
                    m_owner->m_cursorCtrls[route] = -1;
                }
                cursor.setDisp(false);
            }
        }
        break;
    case 0x21:
        if (m_open == 0) {
            ui::UIObjectAcc root(handle, "LAY_root");
            GfMenuObjUtil::setChildDisp(handle, "LAY_root@01", true);
            GfMenuObjUtil::setChildDisp(handle, "LAY_root_base", true);
            root.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x401;
            param.m_curve = 1;
            param.m_time = 0.3f;
            param.m_setDefault = true;
            param.m_startFlags = 4;
            param.m_slot = m_owner->m_openCtrl;
            m_owner->m_openCtrl = GfMenuObjUtil::startCtrl(root.m_handle, param, nullptr);
            m_open = 1;
        }
        break;
    case 0x22: {
        ui::UIObjectAcc root(handle, "LAY_root");
        if (m_open == 1) {
            int ctrl = m_owner->m_openCtrl;
            if (ctrl != -1) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x4002;
                param.m_time = 0.3f;
                param.m_curve = 1;
                param.m_startFlags = 4;
                param.m_slot = ctrl;
                GfMenuObjUtil::startCtrl(root.m_handle, param, nullptr);
            }
            m_open = 0;
        }
        break;
    }
    }
}

void GfMenuObjComboRoute::setupComboRoute(ui::UIObjectAcc& acc) {
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0101"), 5, 0, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0201"), 5, 1, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0202"), 5, 2, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0301"), 5, 3, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0302"), 5, 4, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0303"), 5, 5, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("LAY_root@0304"), 5, 6, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0101"), 1, 0, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0201"), 1, 1, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0202"), 1, 2, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0301"), 1, 3, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0302"), 1, 4, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0303"), 1, 5, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("IMG_root_icon@0304"), 1, 6, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("TXT_eff_name@0301"), 2, 3, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("TXT_eff_name@0302"), 2, 4, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("TXT_eff_name@0303"), 2, 5, true);
    GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild("TXT_eff_name@0304"), 2, 6, true);
    for (unsigned int i = 0; i < 7; i++) {
        GfMenuElementComboAdapter::createReferenceRoute(acc.searchChild(s_routeCursors[i]), 6, i, true);
        GfMenuObject::addDispEventCondition(acc.m_handle, s_routeCursors[i], 1, i, false);
    }
}

void GfMenuObjComboRoute::open() {
    if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuReference::fn_7100368418(5)) {
        TUnk_B61408::fn_71003DC3AC();
        return;
    }
    unsigned int handle = GfMenuObject::getAttachedObject(0x5E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjComboRoute::close() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        TUnk_B61408::fn_71003DC440();
    }
    unsigned int handle = GfMenuObject::getAttachedObject(0x5E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjComboRoute::disp(bool disp) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        TUnk_B61408::fn_71003DC4D4(disp);
    }
    unsigned int handle = GfMenuObject::getAttachedObject(0x5E);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc(handle).setDisp(disp);
        }
    }
}

}  // namespace gf
