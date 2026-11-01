#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuObjCompass.h"
#include "classes/gf/GfMenuObjCompass/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Col3.h"
#include "mm/mtl/FixStr.h"

namespace gf {

GfMenuObjCompass::GfMenuObjCompass(unsigned int handle) : GfMenuObject(handle) {
    m_IconObjList.clear();
}

GfMenuObjCompass::~GfMenuObjCompass() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjCompass::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x42, acc.m_handle);
    GfMenuObject::attachExternalCall(0x43, acc.m_handle);
#line 83
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjCompass::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCompass::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(false);
        m_ctrl = -1;
        State state = {-1, 0};
        m_state = state;
        mm::mtl::FixStr<32> name;
        name.format("TXT_area@%02d", 1);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        ui::UIObjectPlugin* plugin = ui::UIObjectTextPlugin::create(text.m_handle);
        if (plugin != nullptr) {
            plugin->release();
        }
        break;
    }
    case 0x21:
        if (GfMenuFlag::get1(0x1F) == 0 && m_state.m_open == 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 1;
            param.m_time = 0.25f;
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state.m_open = 1;
            m_ctrl = ctrl;
        }
        break;
    case 0x22:
        if (m_state.m_open == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.25f;
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state.m_open = 0;
            m_ctrl = ctrl;
        }
        break;
    case 0x101:
        if (event.m_param0 == 0) {
            if (m_state.m_frameCtrl != -1) {
                GfMenuObjUtil::stopCtrl(m_state.m_frameCtrl);
                m_state.m_frameCtrl = -1;
            }
        } else if (m_state.m_frameCtrl == -1) {
            ui::UIObjectAcc frame(acc.m_handle, "LAY_frame");
            if (frame.m_object != nullptr) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x2000000;
                param.m_color = mm::Col3(0.8f, 0.0f, 0.0f);
                param.m_reserve = true;
                param.m_curve = 3;
                param.m_startFlags = 8;
                param.m_time = 1.0f;
                m_state.m_frameCtrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
            }
        }
        break;
    case 0x102: {
        unsigned short icon = event.m_paramShort[1];
        ui::UIObjectAcc image(acc.searchDuplicatedChild("IMG_icon", event.m_paramShort[0]));
        if (image.m_object != nullptr) {
            image.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
            image.setDisp(true);
        }
        break;
    }
    case 0x103: {
        ui::UIObjectAcc image(acc.searchDuplicatedChild("IMG_icon", event.m_paramShort[0]));
        if (image.m_object != nullptr) {
            image.setTerm();
            GfMenuObject::termCallContext(image.m_handle);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCompass::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x42);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCompass::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x42);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

mm::mtl::FixedVector<GfMenuObjCompass::IconObj, 32> GfMenuObjCompass::m_IconObjList;

}  // namespace gf
