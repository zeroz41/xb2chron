#include "classes/gf/GfMenuObject.h"
#include "ui/EventData.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjCylinderSelect.h"
#include "classes/gf/GfMenuObjCylinderSelect/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/mtl/FixStr.h"

namespace gf {

GfMenuObjCylinderSelect::GfMenuObjCylinderSelect(unsigned int handle)
    : GfMenuObject(handle), m_itemList(nullptr), m_selectList(nullptr), m_cursor(nullptr), m_context(nullptr) {
    m_context = GfMenuCallContext::create();
}

GfMenuObjCylinderSelect::~GfMenuObjCylinderSelect() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
}

void GfMenuObjCylinderSelect::open(GfMenuCallContext* context, unsigned int item) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x46));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = item;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x46, acc.m_handle);
        acc.setSuspend(false);
        GfMenuAdapterManager::addActiveCategory(2);
    }
}

void GfMenuObjCylinderSelect::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    m_itemList = GfMenuItemList::create();
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList = ui::UISelectObjList::create(create);
    }
    m_selectList->pickupObject(acc.m_handle, "LAY_item_base@%02d", 1);
    {
        ui::UICtrlCursorSelect::CursorSetting setting;
        setting.setType(0);
        setting.m_dockType = 0;
        m_cursor = ui::UICtrlCursorSelect::create(acc.searchChild("IMG_item_cursor"), setting, m_selectList);
    }
    GfMenuAdapterManager::beginCategory(2);
    for (unsigned int i = 0; i < m_selectList->getSize(); i++) {
        name.format("LAY_item@%02d", i + 1);
        ui::UIObjectAcc row(acc.m_handle, name.m_str);
        if (row.m_object != nullptr) {
            name.format("TXT_item_name@%02d", i + 1);
            GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(row.searchChild(name.m_str), 0, m_itemList, i, false);
            adapter->m_rowHandle = row.m_handle;
            name.format("IMG_item_rarelity@%02d", i + 1);
            GfMenuItemAdapter::createFromList(row.searchChild(name.m_str), 7, m_itemList, i, false);
            name.format("TXT_item_num@%02d", i + 1);
            GfMenuItemAdapter::createFromList(row.searchChild(name.m_str), 3, m_itemList, i, true);
            name.format("TXT_item_max@%02d", i + 1);
            GfMenuItemAdapter::createFromList(row.searchChild(name.m_str), 4, m_itemList, i, false);
        }
    }
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_item_scroll_point"), m_itemList, "IMG_item_scroll_base", true);
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_info"), 9, m_itemList, -1, false);
    GfMenuAdapterManager::endCategory();
#line 160
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x46, acc.m_handle);
    acc.setSuspend(true);
    GfMenuObject::initialize();
}

void GfMenuObjCylinderSelect::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCylinderSelect::update() {
    GfMenuObject::update();
}

void GfMenuObjCylinderSelect::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_itemList);
            GfMenuObject::enableInput(acc.m_handle);
        } else if (event.m_param0 == 2) {
            GfMenuObject::termCallContext(acc.m_handle);
            acc.setSuspend(true);
        }
        return;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int last = event.m_param1;
            m_owner->m_itemList->setIndex(index);
            m_owner->m_selectList->setIndex(index);
            if (last != -1 && index != last) {
                GfMenuObjUtil::playSECommonCursor();
            }
            m_owner->m_cursor->setDisp(true);
        }
        return;
    }
    case 8:
        if (event.m_param1 == 1) {
            unsigned int self = acc.m_handle;
            GfMenuItemList* list = m_owner->m_itemList;
            const MenuItemInfo& item = list->getContents(list->getIndex(false));
            GfMenuObject::addResultCallContext(self, item.m_id, 0);
            GfMenuObjUtil::playSECommonDecide();
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 1;
            param.m_eventId = 2;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            GfMenuObject::disableInput(acc.m_handle);
        } else if (event.m_param1 == 2) {
            GfMenuObject::addResultCallContext(acc.m_handle, 0, 1);
            GfMenuObjUtil::playSECommonCancel();
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 1;
            param.m_eventId = 2;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            GfMenuObject::disableInput(acc.m_handle);
        }
        return;
    case 0x21: {
        unsigned int cylinder = event.m_param0;
        GfMenuItemList::ItemBoxSetup setup;
        GfDataBdat::getFP(0xA1);
        setup.m_setup.m_pageRowSize = 10;
        setup.m_setup.m_pageScroll = true;
        setup.m_type = 5;
        m_owner->m_itemList->setupFromBox(setup);
        for (unsigned int i = 0; i < m_owner->m_itemList->getSize();) {
            MenuItemInfo item = m_owner->m_itemList->getContents(i);
            ItemProperty property;
            GfItemUtil::getProperty(property, item.m_id, 0);
            if ((property.m_flags & 0x10) != 0 && item.m_id != cylinder) {
                m_owner->m_itemList->decItem(item, false);
            } else {
                i++;
            }
        }
        if (m_owner->m_itemList->getSize() == 0) {
            m_owner->m_context->reset();
            GfMenuObjCommonText::open(m_owner->m_context, 0x47, 0);
            GfMenuObject::setCallContextEventHandler(m_owner->m_context, acc.m_handle);
        } else {
            m_owner->m_itemList->sort(13, true);
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 0;
            param.m_eventId = 1;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        }
        m_owner->m_cursor->setDisp(false);
        break;
    }
    case 0x42:
        GfMenuObject::addResultCallContext(acc.m_handle, 0, 1);
        GfMenuObject::termCallContext(acc.m_handle);
        acc.setSuspend(true);
        return;
    }
    UIObjectListener::reciveEvent(event, handle);
}

}  // namespace gf
