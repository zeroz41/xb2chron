#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/MainListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/PartsListListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/ItemListListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/NumSelectListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/MainListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/PartsListListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/ItemListListener.h"
#include "classes/gf/GfMenuObjHanaPartsCrystal/NumSelectListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuHanaAdapter.h"
#include "classes/gf/GfMenuHanaPartsAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuObjHanaCustom.h"
#include "classes/gf/GfMenuObjHanaSubmenu.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/ui/UICtrlCursorColor.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfGameUtilHana.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjHanaPartsCrystal::GfMenuObjHanaPartsCrystal(unsigned int handle)
    : GfMenuObject(handle), m_partsList(nullptr), m_partsSelect(nullptr), m_partsCursor(nullptr), m_itemList(nullptr),
      m_itemSelect(nullptr), m_itemCursor(nullptr), m_context(nullptr), m_count(), m_price() {}

GfMenuObjHanaPartsCrystal::~GfMenuObjHanaPartsCrystal() {
    if (m_partsList != nullptr) {
        m_partsList->release();
        m_partsList = nullptr;
    }
    if (m_partsSelect != nullptr) {
        m_partsSelect->release();
        m_partsSelect = nullptr;
    }
    if (m_partsCursor != nullptr) {
        m_partsCursor->release();
        m_partsCursor = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_itemSelect != nullptr) {
        m_itemSelect->release();
        m_itemSelect = nullptr;
    }
    if (m_itemCursor != nullptr) {
        m_itemCursor->release();
        m_itemCursor = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    m_count = nullptr;
    m_price = nullptr;
}

void GfMenuObjHanaPartsCrystal::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 128
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x74, handle);
    handle = acc.searchChild("LAY_partsmake_window");
    {
#line 134
        PartsListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PartsListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_recry_window");
    {
#line 138
        ItemListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_recrys_diarog");
    {
#line 142
        NumSelectListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) NumSelectListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_itemList = GfMenuItemList::create();
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_itemSelect = ui::UISelectObjList::create(create);
    m_partsList = GfMenuIDList::create();
    ui::UIListInfoBase::SetupParam setup;
    setup.m_pageRowSize = 5;
    m_partsList->setup(getAllocator(ALLOCATOR(0)), setup);
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_partsSelect = ui::UISelectObjList::create(create);
    m_context = GfMenuCallContext::create();
    m_count = GfMenuReferenceNumber::create();
    m_count->m_value = 0;
    m_count->m_max = 99;
    m_price = GfMenuReferenceNumber::create();
    m_price->m_value = 0;
    m_price->m_max = 999999999;
    GfMenuObject::initialize();
}

void GfMenuObjHanaPartsCrystal::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjHanaPartsCrystal::update() {
    GfMenuObject::update();
}

void GfMenuObjHanaPartsCrystal::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        GfMenuObjOperationInfo::setGuideText(0x1A, 0);
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        break;
    case 3:
        if (event.m_param0 == 2) {
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjHanaSubmenu::returnHanaSubMenu();
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaPartsCrystal::PartsListListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    GfMenuReference::getReferenceBladeID(0);
    switch (event.m_type) {
    case 1: {
        setupPartsList(acc, m_owner->m_partsList, m_owner->m_partsSelect);
        ui::UICtrlCursorColor::CursorSetting setting;
        setting.m_normalColor = "txt_normal2";
        setting.m_selectColor = "txt_normal2";
        setting.m_dispName = "IMG_mplist_sltag@%02d";
        setting.m_colorName = "TXT_partsname@%02d";
        m_owner->m_partsCursor = ui::UICtrlCursorColor::create(handle, setting, m_owner->m_partsSelect);
        m_owner->m_partsCursor->open(0);
        updatePartsList(acc, m_owner->m_partsList, m_owner->m_partsSelect);
        GfMenuObject::setupInputSelection(handle, 0, m_owner->m_partsList->getSize());
        GfMenuObject::enableInput(handle);
        break;
    }
    case 6: {
        unsigned int index = event.m_param0;
        m_owner->m_partsList->getIndex(true);
        m_owner->m_partsList->setIndex(index);
        unsigned int selected = m_owner->m_partsList->getIndex(true);
        if (m_owner->m_partsCursor->inputChange(selected)) {
            makeCategoryItemList(m_owner->m_partsList, m_owner->m_itemList);
            m_owner->m_itemCursor->setDisp(false);
            GfMenuIDList* list = m_owner->m_partsList;
            unsigned int category = list->getContents(list->getIndex(false)).m_id;
            GfMenuObjHanaCustom::refreshItemInfo(ownerAcc, m_owner->m_itemList, category, 1);
        }
        break;
    }
    case 8:
        switch (event.m_param1) {
        case 1:
            if (m_owner->m_itemList->getSize() != 0) {
                {
                    ui::EventData close;
                    close.m_type = 0x102;
                    ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
                }
                sendEvent(ownerAcc.searchChild("LAY_recry_window"), 0x101, 0);
            }
            break;
        case 2:
            {
                ui::EventData close;
                close.m_type = 0x102;
                ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
            }
            sendEvent(ownerAcc.searchChild("LAY_main"), 0x22, 0);
            break;
        }
        break;
    case 0x101:
        GfMenuObject::enableInput(handle);
        break;
    case 0x102:
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaPartsCrystal::ItemListListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    GfMenuReference::getReferenceBladeID(0);
    switch (event.m_type) {
    case 1: {
        m_owner->m_itemSelect->clear();
        m_owner->m_itemSelect->pickupObject(acc.m_handle, "LAY_reclist_tag@%02d", 1);
        setupItemList(acc, m_owner->m_itemList, m_owner->m_itemSelect);
        ui::UICtrlCursorColor::CursorSetting setting;
        setting.m_normalColor = "txt_normal2";
        setting.m_selectColor = "txt_normal2";
        setting.m_dispName = "IMG_reclist_sltag@%02d";
        setting.m_colorName = "TXT_recpartsname@%02d";
        m_owner->m_itemCursor = ui::UICtrlCursorColor::create(handle, setting, m_owner->m_itemSelect);
        m_owner->m_itemCursor->setDisp(false);
        GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_melist_scr_point"), m_owner->m_itemList,
                                              "IMG_melist_scr_line", false);
        makeCategoryItemList(m_owner->m_partsList, m_owner->m_itemList);
        GfMenuIDList* list = m_owner->m_partsList;
        unsigned int category = list->getContents(list->getIndex(false)).m_id;
        GfMenuObjHanaCustom::refreshItemInfo(acc, m_owner->m_itemList, category, 1);
        GfMenuObject::disableInput(handle);
        break;
    }
    case 6: {
        unsigned int index = event.m_param0;
        m_owner->m_itemList->setIndex(index);
        unsigned int selected = m_owner->m_itemList->getIndex(true);
        if (m_owner->m_itemCursor->inputChange(selected)) {
            GfMenuIDList* list = m_owner->m_partsList;
            unsigned int category = list->getContents(list->getIndex(false)).m_id;
            GfMenuObjHanaCustom::refreshItemInfo(acc, m_owner->m_itemList, category, 1);
        }
        break;
    }
    case 8:
        switch (event.m_param1) {
        case 1:
            {
                ui::EventData close;
                close.m_type = 0x102;
                ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
            }
            sendEvent(ownerAcc.searchChild("LAY_recrys_diarog"), 0x101, 0);
            break;
        case 2:
            {
                ui::EventData close;
                close.m_type = 0x102;
                ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
            }
            sendEvent(ownerAcc.searchChild("LAY_partsmake_window"), 0x101, 0);
            break;
        }
        break;
    case 0x101: {
        makeCategoryItemList(m_owner->m_partsList, m_owner->m_itemList);
        GfMenuIDList* list = m_owner->m_partsList;
        unsigned int category = list->getContents(list->getIndex(false)).m_id;
        GfMenuObjHanaCustom::refreshItemInfo(acc, m_owner->m_itemList, category, 1);
        GfMenuObject::setupInputSelection(handle, m_owner->m_itemList->getIndex(false), m_owner->m_itemList->getSize());
        GfMenuObject::enableInput(handle);
        break;
    }
    case 0x102: {
        m_owner->m_itemCursor->setDisp(false);
        GfMenuIDList* list = m_owner->m_partsList;
        refreshItemList(m_owner->m_itemList, m_owner->m_itemSelect, list->getContents(list->getIndex(false)).m_id);
        GfMenuObject::disableInput(handle);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaPartsCrystal::NumSelectListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    GfMenuReference::getReferenceBladeID(0);
    switch (event.m_type) {
    case 1:
        setupNumSelect(acc, m_owner->m_count, m_owner->m_price);
        acc.setDisp(false);
        break;
    case 6: {
        int count = event.m_param0;
        m_owner->m_count->m_value = count;
        GfMenuItemList* items = m_owner->m_itemList;
        unsigned int item = items->getContents(items->getIndex(false)).m_id;
        ItemProperty property;
        GfItemUtil::getProperty(property, item, 0);
        m_owner->m_price->m_value = property.m_dustEther * count;
        break;
    }
    case 8:
        switch (event.m_param1) {
        case 1: {
            GfMenuIDList* parts = m_owner->m_partsList;
            unsigned int category = parts->getContents(parts->getIndex(false)).m_id;
            GfMenuItemList* items = m_owner->m_itemList;
            unsigned int item = items->getContents(items->getIndex(false)).m_id;
            unsigned int count = m_owner->m_count->m_value;
            for (unsigned int i = 0; i < count; i++) {
                switch (category) {
                case 1:
                case 2:
                case 3:
                case 9:
                case 6:
                    GfGameUtilHana::execConvertToEther(item);
                    break;
                }
            }
        }
        case 2:
            {
                ui::EventData close;
                close.m_type = 0x102;
                ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
            }
            sendEvent(ownerAcc.searchChild("LAY_recry_window"), 0x101, 0);
            break;
        }
        break;
    case 0x101: {
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        GfMenuItemList* items = m_owner->m_itemList;
        unsigned int item = items->getContents(items->getIndex(false)).m_id;
        GfMenuObject::setupInputSelection(handle, 0, GfItemUtil::getItemBoxCount(item) + 1);
        GfMenuObject::enableInput(handle);
        break;
    }
    case 0x102:
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaPartsCrystal::setupPartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select) {
    mm::mtl::FixStr<32> name;
    select->clear();
    select->pickupObject(acc.m_handle, "LAY_mplist_tag@%02d", 1);
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        name.format("TXT_partsname@%02d", i + 1);
        GfMenuHanaPartsAdapter* adapter = GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, false);
        if (adapter != nullptr) {
            name.format("LAY_mplist_tag@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_partsicon@%02d", i + 1);
        GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.m_str), 1, list, i, false);
    }
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_mplist_etnum"), 0, 0, true);
    ui::UIObjectAcc(acc.searchChild("IMG_mplist_pic")).startAnimation("loop", false);
}

void GfMenuObjHanaPartsCrystal::makeCategoryItemList(GfMenuIDList* parts, GfMenuItemList* items) {
    // the category's item type (the table's name is not the original's)
    static const struct {
        unsigned int m_category;
        unsigned int m_type;
    } s_categoryTypes[] = {{1, 0x10}, {2, 0x11}, {3, 0x13}, {9, 0x12}, {6, 0x14}};
    unsigned int category = parts->getContents(parts->getIndex(false)).m_id;
    for (int i = 0; i < 5; i++) {
        if (s_categoryTypes[i].m_category == category) {
            unsigned int type = s_categoryTypes[i].m_type;
            items->clear();
            GfMenuItemList::ItemBoxSetup setup;
            setup.m_setup.m_pageRowSize = 10;
            setup.m_type = type;
            setup.pad_28 = 0;
            setup.pad_29 = 0;
            items->setupFromBox(setup);
            return;
        }
    }
}

void GfMenuObjHanaPartsCrystal::setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        name.format("TXT_recpartsname@%02d", i + 1);
        GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, false);
        if (adapter != nullptr) {
            name.format("LAY_reclist_tag@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_recpartslicon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, list, i, false);
        name.format("TXT_reclist_ptnum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 3, list, i, false);
        name.format("TXT_reclist_stcnum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x11, list, i, false);
    }
    GfMenuObjHanaCustom::setupItemInfo(acc, list);
}

void GfMenuObjHanaPartsCrystal::setupNumSelect(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> count,
                                               mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price) {
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), count, true);
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), price, true);
}

}  // namespace gf
