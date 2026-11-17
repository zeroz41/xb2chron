#include "classes/gf/GfMenuObjDropItem.h"
#include "classes/gf/GfMenuObjDropItem/DropItemInfo.h"
#include "classes/gf/GfMenuObjDropItem/ListListener.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfDataItem.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

namespace {
// a closed screen off the queue and terminated (the name is not the original's)
void termScreen(ui::UIObjectAcc screen) {
    GfMenuManyObjects::remove<GfMenuObjDropItem::DropItemInfo>(3, screen.m_handle);
    screen.setDisp(false);
    screen.setTerm();
}

// per screen type with a plugin: its text, the background fitted over it and the background's margin (the names
// are not the original's)
struct PluginInfo {
    const char* m_text;
    const char* m_bg;
    int m_margin;
};
PluginInfo s_plugins[] = {
    {"TXT_item_gold", "IMG_item_gold_bg", 0x28},
    {"TXT_item_heal", "IMG_item_heal_bg", 0x10},
    {"TXT_item_get", "IMG_item_get_bg", 0x20},
    {"TXT_item_sell", "IMG_item_sell_bg", 0x10},
};
}  // namespace

GfMenuObjDropItem::GfMenuObjDropItem(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjDropItem::~GfMenuObjDropItem() {
    GfMenuManyObjects::destroy<DropItemInfo>(3);
}

void GfMenuObjDropItem::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int list = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(list).m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x2b, list);
#line 99
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
    GfMenuManyObjects::createQueue<DropItemInfo>(3, 64);
}

void GfMenuObjDropItem::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjDropItem::update() {
    GfMenuObject::update();
}

void GfMenuObjDropItem::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_item_root", event.m_paramShort[6]));
        if (screen.m_object != nullptr) {
            screen.setDisp(true);
            screen.setDispChild(true, "LAY_item");
            setupScreen(screen.m_handle, event.m_param0, event.m_param1, event.m_param2);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "getitem";
            param.m_motion = "fadein";
            param.m_eventId = (screen.getDuplicateIndex() << 16) | 0x200;
            int ctrl = GfMenuObjUtil::startCtrl(screen.m_handle, param, nullptr);
            if (ctrl == -1) {
                termScreen(screen);
            } else {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
        }
        break;
    }
    case 0x22: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_item_root", event.m_param0Short));
        if (screen.m_object != nullptr) {
            termScreen(screen);
        }
        break;
    }
    case 3: {
        // the control's end: the screen's index << 16, 2 << 8 for its fade
        unsigned int id = event.m_param0;
        if (id == 0) {
            break;
        }
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_item_root", id >> 16));
        if ((id & 0xff00) == 0x200 && screen.m_object != nullptr) {
            termScreen(screen);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjDropItem::setupScreen(unsigned int handle, int type, int value, int item) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_gold", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_heal", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_get", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_sell", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_ether", false);
    switch (type) {
    case 0: {
        GfMenuObjUtil::setChildDisp(handle, "LAY_item_gold", true);
        unsigned int number = ui::UIUtil::searchChild(handle, "TXT_item_gold");
        if (ui::UIUtil::isValid(number)) {
            GfMenuObjUtil::createNumberPlugin(number, value);
        }
        break;
    }
    case 1: {
        GfMenuObjUtil::setChildDisp(handle, "LAY_item_heal", true);
        unsigned int number = ui::UIUtil::searchChild(handle, "TXT_item_heal");
        if (ui::UIUtil::isValid(number)) {
            GfMenuObjUtil::createNumberPlugin(number, value);
        }
        break;
    }
    case 2: {
        GfMenuObjUtil::setChildDisp(handle, "LAY_item_get", true);
        GfMenuObjUtil::setChildText(handle, "TXT_item_get", value);
        MenuItemInfo info;
        info.m_type = GfDataItem::getItemType(item);
        info.m_id = item;
        GfMenuItemAdapter::create(ui::UIObjectAcc(handle).searchChild("IMG_item_get_icon"), 2, info, false);
        break;
    }
    case 3: {
        GfMenuObjUtil::setChildDisp(handle, "LAY_item_sell", true);
        GfMenuObjUtil::setChildText(handle, "TXT_item_sell_name", value);
        unsigned int price = ui::UIUtil::searchChild(handle, "TXT_item_sell_price");
        if (ui::UIUtil::isValid(price)) {
            GfMenuObjUtil::createNumberPlugin(price, item);
        }
        break;
    }
    case 4: {
        GfMenuObjUtil::setChildDisp(handle, "LAY_item_ether", true);
        unsigned int number = ui::UIUtil::searchChild(handle, "TXT_item_ether_num");
        if (ui::UIUtil::isValid(number)) {
            GfMenuObjUtil::createNumberPlugin(number, value);
        }
        unsigned int shadow = ui::UIUtil::searchChild(handle, "TXT_item_ether_num_shadow");
        if (ui::UIUtil::isValid(shadow)) {
            GfMenuObjUtil::createNumberPlugin(shadow, value);
        }
        break;
    }
    }
}

void GfMenuObjDropItem::setupPlugin(unsigned int handle, unsigned int type) {
    if (type < 4) {
        unsigned int text = ui::UIUtil::searchChild(handle, s_plugins[type].m_text);
        if (ui::UIUtil::isValid(text)) {
            unsigned int bg = ui::UIUtil::searchChild(handle, s_plugins[type].m_bg);
            if (ui::UIUtil::isValid(bg)) {
                GfMenuObjUtil::FitOption option;
                option.m_offsetWidth = -20;
                GfMenuObjUtil::createFitPlugin(bg, text, s_plugins[type].m_margin, 0, option);
            }
        }
    }
}

// open (0x71003E8654) is not here yet

void GfMenuObjDropItem::close(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x2b));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc screen(handle);
        if (screen.m_object != nullptr && screen.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0Short = screen.getDuplicateIndex();
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjDropItem::closeAll() {
    unsigned int root = GfMenuObject::getAttachedObject(0x2b);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return;
    }
    if (ui::UIObjectAcc(root).isTerm()) {
        return;
    }
    GfMenuManyObjects::closeAll<DropItemInfo>(3, &close);
}

}  // namespace gf

// the info queue's push_back (its caller, open, is not written yet)
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::push_back(const gf::GfMenuObjDropItem::DropItemInfo&);
