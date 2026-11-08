#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "gf/GfDataUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjMainSubmenu.h"
#include "classes/gf/GfMenuObjMainSubmenu/ListListener.h"
#include "classes/gf/GfMenuObjMainSubmenu/MainListener.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"

#include <string.h>

namespace gf {

namespace {
// a submenu item: the menu layer it opens, the menu condition that shows it and its info text (an index into
// message list 0x164; 0 for none) (the names are not the original's)
struct SubmenuItem {
    unsigned int m_layer;
    unsigned int m_condition;
    unsigned short m_text;
};
// mnu094_submenu_book's items
const SubmenuItem s_bookItems[] = {
    {0x45, 0x15, 0xD},
    {0x42, 0x16, 0xE},
};
// mnu094_submenu_crystal's items
const SubmenuItem s_crystalItems[] = {
    {0x41, 0x18, 0xC},
    {0x14, 0x17, 0xB},
    {0x45, 0x15, 0xD},
};
// mnu094_submenu_system's items on menu layer 3 (GfMenuObjUtil::isValidExpansion(3)): four, and item 5 replaces the
// first when GfMenuObjUtil::isIraSinMaskOff holds
const SubmenuItem s_systemItemsLayer3[] = {
    {0x44, 0x2D, 0xF},
    {0x36, 0x2C, 0x10},
    {0x1A, 0x2E, 0x11},
    {0x12E, 0x38, 0x16},
    {0x44, 0x2D, 0xF},
};
// mnu094_submenu_system's items otherwise
const SubmenuItem s_systemItems[] = {
    {0x44, 0x21, 0xF},
    {0x36, 0x20, 0x10},
    {0x1A, 0x22, 0x11},
};
}  // namespace


GfMenuObjMainSubmenu::GfMenuObjMainSubmenu(unsigned int handle)
    : GfMenuObject(handle), m_kind(0), m_guideText(0), m_subIndexText(0), m_list(nullptr), m_items(),
      m_fadeOnClose(true), m_context(nullptr) {
    for (int i = 0; i < 5; i++) {
        m_growCtrl[i] = -1;
    }
}

GfMenuObjMainSubmenu::~GfMenuObjMainSubmenu() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfMenuObjMainSubmenu::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 134
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
#line 135
    ListListener* listListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
    listListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_item_list"), listListener);
    if (listListener != nullptr) {
        listListener->release();
    }
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_list = ui::UISelectObjList::create(create);
    }
    {
        ui::UIObjectAcc self(m_handle);
        unsigned int count = 0;
        const SubmenuItem* items = nullptr;
        if (strcmp(self.getName(), "mnu094_submenu_book") == 0) {
            m_kind = 1;
            m_guideText = 5;
            m_subIndexText = 0xE;
            count = 2;
            items = s_bookItems;
        } else if (strcmp(self.getName(), "mnu094_submenu_crystal") == 0) {
            m_kind = 2;
            m_guideText = 6;
            m_subIndexText = 0xF;
            count = 3;
            items = s_crystalItems;
        } else if (strcmp(self.getName(), "mnu094_submenu_system") == 0) {
            m_kind = 3;
            m_guideText = 8;
            m_subIndexText = 0x11;
            count = 3;
            items = s_systemItems;
            if (GfMenuObjUtil::isValidExpansion(3)) {
                items = s_systemItemsLayer3;
                count = 4;
            }
        }
        m_items.clear();
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < count; i++) {
            name.format("LAY_item@%02d", i + 1);
            if (GfMenuObjUtil::getMenuCondition(items[i].m_condition)) {
                if (GfMenuObjUtil::isValidExpansion(3) && i == 0 && GfMenuObjUtil::isIraSinMaskOff()) {
                    GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
                    name.format("LAY_item@%02d", 5);
                    m_list->addContents(acc.searchChild(name.m_str));
                    m_items.push_back(4);
                } else {
                    m_list->addContents(acc.searchChild(name.m_str));
                    m_items.push_back(i);
                }
                GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, true);
            } else {
                GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
            }
        }
    }
    m_context = GfMenuCallContext::create();
    GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
    GfMenuObject::initialize();
}

void GfMenuObjMainSubmenu::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMainSubmenu::update() {
    GfMenuObject::update();
}

void GfMenuObjMainSubmenu::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::sendEvent(acc.m_handle, ui::EventData(0x21), 0.0f);
        break;
    case 2: {
        ui::EventData open(0x22);
        open.m_param0 = 1;
        GfMenuObject::sendEvent(acc.m_handle, open, 0.0f);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
            GfMenuObjOperationInfo::add(acc.searchChild("LAY_item_list"), 0, 0, 0);
        } else if (event.m_param0 == 2) {
            acc.setTerm();
        }
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x22: {
        if (m_owner->m_fadeOnClose) {
            bool keep = event.m_param0 == 1;
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_out = 1;
            param.m_preset = 6;
            param.m_eventId = 2;
            param.m_startFlag1 = keep;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        } else {
            ui::EventData term(3);
            term.m_param0 = 2;
            ui::UIManager::get()->requestObjectEvent(handle, term, 0.0f);
        }
        ui::EventData close;
        close.m_type = 0x22;
        GfMenuObject::sendEvent(acc.searchChild("LAY_item_list"), close, 0.0f);
        break;
    }
    case 0x24: {
        GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->m_fadeOnClose = false;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
