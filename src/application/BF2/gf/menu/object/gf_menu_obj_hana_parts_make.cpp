#include "classes/gf/GfMenuObjHanaPartsMake.h"
#include "classes/gf/GfMenuObjHanaPartsMake/MainListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake/PartsListListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake/ItemListListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake/NumSelectListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake.h"
#include "classes/gf/GfMenuObjHanaPartsMake/MainListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake/PartsListListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake/ItemListListener.h"
#include "classes/gf/GfMenuObjHanaPartsMake/NumSelectListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuHanaAdapter.h"
#include "classes/gf/GfMenuHanaPartsAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjHanaCustom.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/ui/UICtrlCursorColor.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

bool GfMenuObjHanaPartsMake::s_UpdateItemList;

GfMenuObjHanaPartsMake::GfMenuObjHanaPartsMake(unsigned int handle)
    : GfMenuObject(handle), m_partsList(nullptr), m_partsSelect(nullptr), m_partsCursor(nullptr), m_itemList(nullptr),
      m_itemSelect(nullptr), m_itemCursor(nullptr), m_context(nullptr), m_count(), m_price(), m_listMode(0),
      m_sortIndex(0) {}

GfMenuObjHanaPartsMake::~GfMenuObjHanaPartsMake() {
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

void GfMenuObjHanaPartsMake::updateItemList() {
    s_UpdateItemList = true;
}

void GfMenuObjHanaPartsMake::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 159
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x73, handle);
    handle = acc.searchChild("LAY_partsmake_window");
    {
#line 165
        PartsListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PartsListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_metl_window");
    {
#line 169
        ItemListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_make_diarog");
    {
#line 173
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
    setup.m_pageScroll = true;
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
    GfMenuObject::disableInput(acc.searchChild("LAY_partsmake_window"));
    GfMenuObject::disableInput(acc.searchChild("LAY_metl_window"));
    GfMenuObject::disableInput(acc.searchChild("LAY_make_diarog"));
    s_UpdateItemList = false;
    GfMenuObject::initialize();
}

void GfMenuObjHanaPartsMake::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjHanaPartsMake::update() {
    if (s_UpdateItemList) {
        if (m_listMode == 0) {
            for (unsigned int i = 0; i < m_itemList->getSize(); i++) {
                m_itemList->getContents(i).m_count = GfItemUtil::getItemBoxCount(m_itemList->getContents(i).m_id);
            }
        }
        s_UpdateItemList = false;
    }
    GfMenuObject::update();
}

void GfMenuObjHanaPartsMake::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupMain(acc);
        GfMenuObjOperationInfo::setGuideText(0x19, 0);
        GfMenuObjMainMenu2::setSubIndexText(0x1A);
        GfMenuObjMainMenu2::closeCharChange();
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjCharSelect::returnSubMenu();
            GfMenuObject::returnFSSubLayer(m_owner);
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

void GfMenuObjHanaPartsMake::setupMain(ui::UIObjectAcc& acc) {
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hplist_etnum"), 0, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_num"), 1, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_max"), 2, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_rol"), 3, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hn_elml"), 5, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hana"), 6, 0, false);
    GfMenuAdapterManager::beginAddAfter();
    {
        ui::UIObjectAcc stock(acc.m_handle, "LAY_stock");
        GfMenuGameAdapter::create(stock.searchChild("IMG_stock_icon"), 0x12, true);
        GfMenuGameAdapter::create(stock.searchChild("TXT_stock_num"), 0x13, true);
        GfMenuGameAdapter::create(stock.searchChild("TXT_stock_max"), 0x14, true);
        GfMenuReference::setReferenceItemType(static_cast<ItemType::Type>(0));
        stock.setDisp(false);
    }
    GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjHanaPartsMake::PartsListListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    GfMenuReference::getReferenceBladeID(0);
    switch (event.m_type) {
    case 1: {
        setupPartsList(acc, m_owner->m_partsList, m_owner->m_partsSelect);
        GfMenuObjUtil::CursorParam param;
        param.m_parent = handle;
        param.m_cursor = acc.searchChild("IMG_parts_cursor");
        param.m_pickup = "LAY_parts@%02d01";
        param.m_setting.m_dockType = 0;
        m_owner->m_partsCursor = GfMenuObjUtil::createCursor(param);
        m_owner->m_partsCursor->open(0);
        updatePartsList(acc, m_owner->m_partsList, m_owner->m_partsSelect);
        GfMenuObject::setupInputSelection(handle, 0, 5);
        sendEvent(handle, 0x101, 0);
        break;
    }
    case 6: {
        unsigned int index = event.m_param0;
        int previous = event.m_param1;
        m_owner->m_partsList->getIndex(true);
        m_owner->m_partsList->setIndex(index);
        unsigned int selected = m_owner->m_partsList->getIndex(true);
        if (m_owner->m_partsCursor->inputChange(selected)) {
            m_owner->m_sortIndex = 0;
            makeCategoryItemList(m_owner->m_partsList, m_owner->m_itemList, m_owner->m_listMode, m_owner->m_sortIndex);
            m_owner->m_itemCursor->setDisp(false);
            GfMenuIDList* parts = m_owner->m_partsList;
            unsigned int category = parts->getContents(parts->getIndex(false)).m_id;
            refreshItemList(ownerAcc, m_owner->m_itemList, m_owner->m_itemSelect, category, m_owner->m_listMode);
            GfMenuObjHanaCustom::refreshItemInfo(ownerAcc, m_owner->m_itemList, category, 1);
            if (previous != -1 && index != previous) {
                GfMenuObjUtil::playSECommonCursor();
            }
            GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(getFirstSortTableId(category, m_owner->m_listMode), 0),
                                            ownerAcc.searchChild("TXT_item_sort_label"));
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
                sendEvent(ownerAcc.searchChild("LAY_metl_window"), 0x101, 0);
                GfMenuObjUtil::playSECommonDecide();
            }
            break;
        case 2:
            {
                ui::EventData close;
                close.m_type = 0x102;
                ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
            }
            sendEvent(ownerAcc.searchChild("LAY_main"), 0x22, 0);
            GfMenuObjUtil::playSECommonCancel();
            break;
        case 9: {
            if (m_owner->m_listMode == 0) {
                m_owner->m_listMode = 1;
                GfMenuObjOperationInfo::changeText(handle, 9, true);
                GfMenuObjOperationInfo::setGuideText(0x1A, 0);
                GfMenuObject::disableInput(handle);
                sendEvent(ownerAcc.searchChild("LAY_metl_window"), 0x104, 0);
            } else {
                m_owner->m_listMode = 0;
                GfMenuObjOperationInfo::changeText(handle, 9, false);
                GfMenuObjOperationInfo::setGuideText(0x19, 0);
                GfMenuObject::disableInput(handle);
                sendEvent(ownerAcc.searchChild("LAY_metl_window"), 0x103, 0);
            }
            m_owner->m_sortIndex = 0;
            makeCategoryItemList(m_owner->m_partsList, m_owner->m_itemList, m_owner->m_listMode, m_owner->m_sortIndex);
            GfMenuIDList* parts = m_owner->m_partsList;
            unsigned int category = parts->getContents(parts->getIndex(false)).m_id;
            refreshItemList(ownerAcc, m_owner->m_itemList, m_owner->m_itemSelect, category, m_owner->m_listMode);
            GfMenuObjHanaCustom::refreshItemInfo(ownerAcc, m_owner->m_itemList, category, 1);
            GfMenuObjUtil::playSECommonDecide();
            GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(getFirstSortTableId(category, m_owner->m_listMode), 0),
                                            ownerAcc.searchChild("TXT_item_sort_label"));
            break;
        }
        }
        break;
    case 0x101:
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        GfMenuObjOperationInfo::changeText(handle, 9, m_owner->m_listMode != 0);
        GfMenuObject::enableInput(handle);
        break;
    case 0x102:
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaPartsMake::setupPartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select) {
    mm::mtl::FixStr<32> name;
    select->clear();
    select->pickupObject(acc.m_handle, "LAY_hplist_tag@%02d", 1);
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        name.format("TXT_partsname@%02d", i + 1);
        GfMenuHanaPartsAdapter* adapter = GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, false);
        if (adapter != nullptr) {
            name.format("LAY_mplist_tag@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_partsicon@%02d01", i + 1);
        GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.m_str), 1, list, i, false);
    }
}

void GfMenuObjHanaPartsMake::makeCategoryItemList(GfMenuIDList* parts, GfMenuItemList* items, unsigned int mode,
                                                  unsigned int sortIndex) {
    // the category's item type (the table's name is not the original's)
    static const struct {
        unsigned int m_category;
        unsigned int m_type;
    } s_categoryTypes[] = {{1, 0x10}, {2, 0x11}, {3, 0x13}, {9, 0x12}, {6, 0x14}};
    unsigned int category = parts->getContents(parts->getIndex(false)).m_id;
    for (int i = 0; i < 5; i++) {
        if (s_categoryTypes[i].m_category == category) {
            unsigned int type = s_categoryTypes[i].m_type;
            updateItemList(items, static_cast<ItemType::Type>(type), mode);
            GfMenuReference::setReferenceItemType(static_cast<ItemType::Type>(type));
            items->sort(GfMenuObjSort::getSortID(getFirstSortTableId(category, mode), sortIndex), false);
            return;
        }
    }
}

void GfMenuObjHanaPartsMake::setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        name.format("TXT_sbpartsname@%02d", i + 1);
        GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, false);
        if (adapter != nullptr) {
            name.format("LAY_sbparts_num@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_sbpartsicon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, list, i, false);
        name.format("TXT_sbparts_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 3, list, i, true);
        name.format("TXT_sbparts_etlnum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x10, list, i, false);
        name.format("TXT_reclist_stcnum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x11, list, i, false);
    }
    GfMenuObjHanaCustom::setupItemInfo(acc, list);
}

void GfMenuObjHanaPartsMake::setupNumSelect(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> count,
                                            mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price) {
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), count, true);
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), price, true);
}

}  // namespace gf
