#include "classes/gf/GfMenuManyObjects.h"
#include "classes/gf/GfMenuObjPartyStatus2.h"
#include "classes/gf/GfMenuObjExpGet.h"
#include "classes/gf/GfMenuObjExpGet/ExpGetInfo.h"
#include "classes/gf/GfMenuObjExpGet/ListListener.h"
#include "classes/gf/GfMenuObjExpGet.h"
#include "classes/gf/GfMenuObjExpGet/ExpGetInfo.h"
#include "classes/gf/GfMenuObjExpGet/ListListener.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "classes/gf/GfMenuObjPartyStatus2.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/MenuOffset.h"
#include "gf/GfDataParty.h"
#include "gf/GfObjAcc.h"
#include "plugin/Bdat.h"
#include "mm/mtl/FixedQueue.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

namespace {
// per screen type with a plugin: the layer that moves and the background fitted over it, and its margin (the names
// are not the original's)
struct PluginInfo {
    const char* m_layer;
    const char* m_bg;
    int m_margin;
};
PluginInfo s_plugins[] = {
    {"LAY_exp_move", "IMG_exp_bg", 0x1e},
    {"LAY_sp_move", "IMG_sp_bg", 0x1e},
    {"LAY_wp_move", "IMG_wp_bg", 0x1e},
};

// the open object at that place of a kind's queue, none while the kind's opens are held (the name is not the
// original's)
GfMenuObjExpGet::ExpGetInfo* getOpenInfo(unsigned int kind, unsigned int position) {
    GfMenuManyObjects* objects = GfMenuManyObjects::get();
    mm::mtl::Queue<GfMenuObjExpGet::ExpGetInfo>* queue = GfMenuManyObjects::getQueue<GfMenuObjExpGet::ExpGetInfo>(kind);
    if (!objects->m_hold[kind] && queue != nullptr && !queue->empty()) {
        return &(*queue)[position];
    }
    return nullptr;
}
}  // namespace

// 2.0.0's symbols name it
mm::mtl::FixedQueue<GfMenuObjExpGet::OpenParam, 64> GfMenuObjExpGet::s_queue;

GfMenuObjExpGet::GfMenuObjExpGet(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjExpGet::~GfMenuObjExpGet() {
    GfMenuManyObjects::destroy<ExpGetInfo>(4);
    GfMenuManyObjects::destroy<ExpGetInfo>(5);
}

void GfMenuObjExpGet::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int list = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(list).m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x2e, list);
#line 101
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    ui::UIObjectAcc(m_handle).setTerm();
    GfMenuObject::initialize();
    GfMenuManyObjects::createQueue<ExpGetInfo>(4, 64);
    GfMenuManyObjects::createQueue<ExpGetInfo>(5, 64);
    s_queue.clear();
}

void GfMenuObjExpGet::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjExpGet::update() {
    const mm::mtl::FixedQueue<OpenParam, 64>& requests = s_queue;
    for (mm::mtl::FixedQueue<OpenParam, 64>::const_iterator it = requests.begin(); it != requests.end(); ++it) {
        myOpen(*it);
    }
    s_queue.clear();
    GfMenuObject::update();
}

// myOpen (GfMenuObjExpGet::myOpen) is not identical yet


inline void GfMenuObjExpGet::removeObject2(ui::UIObjectAcc screen) {
    GfMenuManyObjects::remove<ExpGetInfo>(5, screen.m_handle);
    screen.setDisp(false);
    screen.setTerm();
}

inline void GfMenuObjExpGet::removeObject(ui::UIObjectAcc screen) {
    GfMenuManyObjects::remove<ExpGetInfo>(4, screen.m_handle);
    screen.setDisp(false);
    screen.setTerm();
}

inline void GfMenuObjExpGet::sendOpen(unsigned int root, const ExpGetInfo& info) {
    ui::EventData event;
    event.m_type = 0x21;
    event.m_param0 = info.m_param.m_type;
    event.m_param1 = info.m_param.m_value;
    event.m_paramShort[4] = ui::UIObjectAcc(info.m_handle).getDuplicateIndex();
    event.m_paramShort[5] = info.m_param.m_extra;
    event.m_param3 = info.m_param.m_bonus;
    GfMenuObject::sendEvent(root, event, 0.0f);
}

void GfMenuObjExpGet::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_main_root", event.m_paramShort[4]));
        if (screen.m_object != nullptr) {
            int type = event.m_param0;
            ui::UIObjectAcc target(screen.m_handle);
            GfMenuObjUtil::CtrlParam param;
            switch (type) {
            case 0:
                param.m_methods = 1;
                param.m_time = 1.0f;
                break;
            case 1:
            case 2:
                param.m_motionLib = "cmn_fade_btresult";
                param.m_methods = 0x10000000;
                param.m_motion = "fadein";
                break;
            case 3:
                param.m_motionLib = "cmn_zoomin_a";
                param.m_methods = 0x10000000;
                param.m_motion = "fadein";
                break;
            }
            param.m_eventId = (type << 24) | (event.m_paramShort[4] << 8) | 1;
            int ctrl = GfMenuObjUtil::startCtrl(target.m_handle, param, nullptr);
            if (ctrl == -1) {
                if (type == 1) {
                    removeObject2(screen);
                } else {
                    removeObject(screen);
                }
            } else {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
        }
        break;
    }
    case 0x22: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_main_root", event.m_paramShort[0]));
        if (screen.m_object != nullptr) {
            if (event.m_paramShort[1] == 0) {
                removeObject(screen);
                if (!GfMenuManyObjects::get()->m_hold[4]) {
                    mm::mtl::Queue<ExpGetInfo>* queue = GfMenuManyObjects::getQueue<ExpGetInfo>(4);
                    if (queue != nullptr && !queue->empty()) {
                        ExpGetInfo info = queue->front();
                        sendOpen(handle, info);
                    }
                }
            } else {
                removeObject2(screen);
                if (!GfMenuManyObjects::get()->m_hold[5]) {
                    mm::mtl::Queue<ExpGetInfo>* queue = GfMenuManyObjects::getQueue<ExpGetInfo>(5);
                    if (queue != nullptr && !queue->empty()) {
                        ExpGetInfo info = queue->front();
                        sendOpen(handle, info);
                    }
                }
            }
        }
        break;
    }
    case 3: {
        // the control's end: the type << 24, the screen's index << 8, then 1 opened, 2 shown, 3 closed
        unsigned int id = event.m_param0;
        if (id == 0) {
            break;
        }
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_main_root", id >> 8));
        if (screen.m_object == nullptr) {
            break;
        }
        unsigned int type = id >> 24;
        switch (id & 0xff) {
        case 1: {
            GfMenuObjUtil::CtrlParam param;
            if (type == 3) {
                ui::UIObjectAcc anim(screen.searchChild("IMG_lvup_anim"));
                anim.startAnimation("start", false);
                param.m_time = 2.0f;
            } else if (type == 0) {
                param.m_time = 2.0f;
            } else {
                param.m_time = 0.01f;
            }
            param.m_eventId = (type << 24) | (id & 0xffff00) | 2;
            param.m_methods = 0;
            int ctrl = GfMenuObjUtil::startCtrl(screen.m_handle, param, nullptr);
            if (ctrl == -1) {
                removeExpGet(acc, screen, type);
            } else {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
            break;
        }
        case 2: {
            GfMenuObjUtil::CtrlParam param;
            switch (type) {
            case 3:
                param.m_motionLib = "cmn_zoomin_a";
                param.m_methods = 0x10000000;
                param.m_motion = "fadeout";
                break;
            case 0:
                param.m_methods = 2;
                param.m_time = 1.0f;
                break;
            default:
                param.m_methods = 0;
                param.m_time = 0.01f;
                break;
            }
            param.m_eventId = (type << 24) | (id & 0xffff00) | 3;
            int ctrl = GfMenuObjUtil::startCtrl(screen.m_handle, param, nullptr);
            if (ctrl == -1) {
                removeExpGet(acc, screen, type);
            } else {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
            break;
        }
        case 3:
            removeExpGet(acc, screen, type);
            break;
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}


// removeExpGet is not identical yet


void GfMenuObjExpGet::close2(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x2e));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc screen(handle);
        if (screen.m_object != nullptr && screen.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_paramShort[0] = ui::UIObjectAcc(handle).getDuplicateIndex();
            event.m_paramShort[1] = 1;
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

const char* GfMenuObjExpGet::setupScreen(unsigned int handle, int type, int value, int unused, int bonus) {
    ui::UIObjectAcc acc(handle);
    const char* layer;
    switch (type) {
    case 0:
        GfMenuObjUtil::createNumberPlugin(ui::UIObjectAcc(handle, "TXT_exp_num").m_handle, value);
        GfMenuObjUtil::setChildDisp(handle, "IMG_exp_bonus", bonus != 0);
        layer = "LAY_exp";
        GfMenuObjUtil::setChildDisp(handle, "LAY_exp", true);
        GfMenuObjUtil::setChildDisp(handle, "LAY_sp", false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_wp", false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", false);
        break;
    case 1:
        GfMenuObjUtil::createNumberPlugin(ui::UIObjectAcc(handle, "TXT_sp_num").m_handle, value);
        GfMenuObjUtil::setChildDisp(handle, "IMG_sp_bonus", bonus != 0);
        GfMenuObjUtil::setChildDisp(handle, "LAY_exp", false);
        layer = "LAY_sp";
        GfMenuObjUtil::setChildDisp(handle, "LAY_sp", true);
        GfMenuObjUtil::setChildDisp(handle, "LAY_wp", false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", false);
        break;
    case 2:
        GfMenuObjUtil::createNumberPlugin(ui::UIObjectAcc(handle, "TXT_wp_num").m_handle, value);
        GfMenuObjUtil::setChildDisp(handle, "IMG_wp_bonus", bonus != 0);
        GfMenuObjUtil::setChildDisp(handle, "LAY_exp", false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_sp", false);
        layer = "LAY_wp";
        GfMenuObjUtil::setChildDisp(handle, "LAY_wp", true);
        GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", false);
        break;
    case 3: {
        ui::UIObjectAcc number(handle, "TXT_lvup_num");
        number.setDisp(false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_exp", false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_sp", false);
        GfMenuObjUtil::setChildDisp(handle, "LAY_wp", false);
        layer = "LAY_lvup";
        GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", true);
        break;
    }
    default:
        layer = nullptr;
        break;
    }
    return layer;
}

void GfMenuObjExpGet::setupPlugin(unsigned int handle, unsigned int type) {
    if (type < 3) {
        unsigned int layer = ui::UIUtil::searchChild(handle, s_plugins[type].m_layer);
        if (ui::UIUtil::isValid(layer)) {
            unsigned int bg = ui::UIUtil::searchChild(handle, s_plugins[type].m_bg);
            if (ui::UIUtil::isValid(bg)) {
                GfMenuObjUtil::FitOption option;
                option.m_offsetWidth = 0;
                GfMenuObjUtil::createFitPlugin(bg, layer, s_plugins[type].m_margin, 0, option);
            }
        }
    }
}

unsigned int GfMenuObjExpGet::open(const OpenParam& param) {
    if (s_queue.full()) {
        s_queue.pop();
    }
    s_queue.push_back(param);
    return 0;
}

void GfMenuObjExpGet::close(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x2e));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc screen(handle);
        if (screen.m_object != nullptr && screen.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_paramShort[0] = ui::UIObjectAcc(handle).getDuplicateIndex();
            event.m_paramShort[1] = 0;
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjExpGet::closeAll() {
    GfMenuManyObjects::closeAll<ExpGetInfo>(4, &close);
    GfMenuManyObjects::closeAll<ExpGetInfo>(5, &close2);
    s_queue.clear();
}

}  // namespace gf

// the info queue's operations (their callers, myOpen and the list listener's, are not written yet)
template void mm::mtl::Queue<gf::GfMenuObjExpGet::ExpGetInfo>::push_back(const gf::GfMenuObjExpGet::ExpGetInfo&);
template void gf::GfMenuManyObjects::remove<gf::GfMenuObjExpGet::ExpGetInfo>(unsigned int, unsigned int);
