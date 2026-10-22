#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuOrderMgr.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuObjLocationTelop.h"
#include "classes/gf/GfMenuObjLocationTelop/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjLocationTelop::GfMenuObjLocationTelop(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjLocationTelop::~GfMenuObjLocationTelop() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjLocationTelop::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
#line 62
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x25, acc.m_handle);
        GfMenuObject::attachExternalCall(0x26, acc.m_handle);
        GfMenuObject::initialize();
    }
}

void GfMenuObjLocationTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjLocationTelop::update() {
    GfMenuObject::update();
}

void GfMenuObjLocationTelop::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
        m_time = Time();
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            GfMenuOrderMgr::finishOrder(2);
        }
        break;
    case 0xC: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 1.0f;
        param.m_eventId = 2;
        if (GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr) == -1) {
            acc.setDisp(false);
            GfMenuOrderMgr::finishOrder(2);
        }
        break;
    }
    case 0x100: {
        acc.setDisp(true);
        const char* textName = event.m_param2 == 2 ? "TXT_name_area" : "TXT_name_other";
        ui::UIObjectAcc text(acc.m_handle, textName);
        GfMenuObject::setText(text.m_handle, event.m_param0);
        const char* anim = nullptr;
        unsigned int jingle = 0;
        if (event.m_param2 == 0) {
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_landmark", true);
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_secret", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_area", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_name_other", true);
            GfMenuObjUtil::setChildDisp(handle, "TXT_name_area", false);
            jingle = 1;
            anim = "landmark";
        } else if (event.m_param2 == 1) {
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_landmark", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_secret", true);
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_area", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_name_other", true);
            GfMenuObjUtil::setChildDisp(handle, "TXT_name_area", false);
            jingle = 3;
            anim = "secret";
        } else if (event.m_param2 == 2) {
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_landmark", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_secret", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_index_area", true);
            GfMenuObjUtil::setChildDisp(handle, "TXT_name_other", false);
            GfMenuObjUtil::setChildDisp(handle, "TXT_name_area", true);
            jingle = 2;
            anim = "area";
        }
        ui::UIObjectAcc bg(acc.m_handle, "IMG_bg");
        bg.startAnimation(anim, false);
        GfMenuObject::hookAnimationEvent(handle, bg.m_handle, 0);
        ui::UIObjectAcc index(acc.searchChild("LAY_index"));
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(index.m_handle, param, nullptr);
        ui::UIObjectAcc name(acc.searchChild("LAY_name"));
        param.m_eventId = 1;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(name.m_handle, param, nullptr);
        ui::UIObjectAcc self(handle);
        self.setAlpha(1.0f);
        if (jingle != 0) {
            GfMenuObjUtil::playJingle(jingle);
        }
        m_state = 1;
        m_time.m_time = event.m_param1;
        break;
    }
    case 0x101:
        if (m_state != 0 && m_state != 3) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.25f;
            param.m_eventId = 2;
            if (GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr) == -1) {
                acc.setDisp(false);
                GfMenuOrderMgr::finishOrder(2);
            }
            {
                ui::UIObjectAcc bg(acc.m_handle, "IMG_bg");
                if (bg.m_object != nullptr && bg.isPlayingAnimation()) {
                    bg.stopAnimation();
                }
            }
            m_time.m_count = 0;
            m_state = 3;
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjLocationTelop::open(const OpenParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x25));
    if (acc.m_object != nullptr && !acc.isTerm() && param.m_disp) {
        unsigned short text = GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_name));
        ui::EventData event;
        event.m_type = 0x100;
        event.m_param0 = text;
        event.m_param1 = 200;
        event.m_param2 = param.m_type;
        event.m_param3 = param.m_disp;
        GfMenuOrderMgr::setOrder(2, acc.m_handle, event);
    }
}

void GfMenuObjLocationTelop::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x25));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x101;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjLocationTelop::cancel() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x25));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        GfMenuOrderMgr::cancelOrder(2);
    }
}

}  // namespace gf
