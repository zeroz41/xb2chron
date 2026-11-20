#include "classes/gf/GfMenuObjItemList2.h"
#include "classes/gf/GfMenuObjItemList2/MainListener.h"
#include "classes/gf/GfMenuObjItemList2/ItemListListener.h"
#include "classes/gf/GfMenuObjItemList2/FilterListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "ui/UIStr.h"
#include "gf/GfDataItem.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C1E1C). The item type each filter lists
// (filter 0: every type, filled from the other entries).
static const unsigned int s_filterItemTypes[] = {0, 0xC, 7, 0xB, 0xA, 0xE, 9, 3, 2, 1, 6, 5, 8};
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C1E50). The sort menu (GfMenuObjSort's
// table) of each filter.
static const unsigned int s_filterSortMenus[] = {0xB, 3, 4, 5, 6, 7, 8, 9, 2, 0xA, 0xB, 0xC, 0xD};

GfMenuObjItemList2::GfMenuObjItemList2(unsigned int handle)
    : GfMenuObject(handle), m_itemList(nullptr), m_itemSelect(nullptr), m_filters(), m_filterIndex(0), pad_9C(0),
      m_fadeOnClose(true) {}

GfMenuObjItemList2::~GfMenuObjItemList2() {
    if (m_itemSelect != nullptr) {
        m_itemSelect->release();
        m_itemSelect = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
}

void GfMenuObjItemList2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjItemList2::update() {
    GfMenuObject::update();
}

void GfMenuObjItemList2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 164
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x6F, handle);
    handle = acc.searchChild("LAY_mainwindow");
    {
#line 170
        ItemListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_filter");
    {
#line 174
        FilterListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FilterListener(this);
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
    {
        ui::UIObjectAcc filter(acc.m_handle, "LAY_filter");
        mm::mtl::FixStr<32> name;
        m_filters.clear();
        for (unsigned long i = 0; i < 13; i++) {
            unsigned int type = s_filterItemTypes[i];
            if (i == 0 || GfMenuFlag::get1(type + 0x3A) == 1) {
                unsigned int icon = 0;
                name.format("IMG_ficon@%02d", m_filters.size() + 1);
                ui::UIObjectAcc image(filter.m_handle, name.m_str);
                m_filters.push_back(i);
                if (i == 0) {
                    icon = 0xE;
                } else {
                    GfMenuItemUtil::getIconNumber(static_cast<ItemType::Type>(type), 0, icon, true);
                }
                image.setImageIndex(icon);
                image.setDisp(true);
            }
        }
        unsigned int count = filter.countChild("LAY_icon@%02d", 1);
        for (unsigned int i = m_filters.size(); i < count;) {
            i++;
            name.format("IMG_ficon@%02d", i);
            ui::UIObjectAcc image(filter.m_handle, name.m_str);
            image.setDisp(false);
        }
        mm::Rect<short> all;
        mm::Rect<short> range;
        filter.getLayoutRect("all_item", all);
        filter.getLayoutRect("all_item_range", range);
        GfMenuObjUtil::placeObjectH(filter.m_handle, "LAY_icon@%02d", m_filters.size(),
                                    mm::Pnt<short>(all.x + all.w / 2, all.y + all.h / 2), range.x - all.x);
    }
    GfMenuAdapterManager::beginAddAfter();
    {
        ui::UIObjectAcc stock(acc.m_handle, "LAY_stock");
        GfMenuGameAdapter::create(stock.searchChild("IMG_stock_icon"), 0x12, true);
        GfMenuGameAdapter::create(stock.searchChild("TXT_stock_num"), 0x13, true);
        GfMenuGameAdapter::create(stock.searchChild("TXT_stock_max"), 0x14, true);
        GfMenuReference::setReferenceItemType(static_cast<ItemType::Type>(0));
    }
    GfMenuAdapterManager::endAddAfter();
    GfMenuObject::initialize();
}

void GfMenuObjItemList2::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::setGuideText(3, 0);
        setFadeIn(handle);
        break;
    case 2:
        sendEvent(handle, 0x22, 0, 0);
        break;
    case 3:
        if (event.m_param0 == 1) {
            sendEvent(acc.searchChild("LAY_mainwindow"), 0x101, 0, 0);
            sendEvent(acc.searchChild("LAY_filter"), 0x101, 0, 0);
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
            GfMenuObjOperationInfo::add(acc.searchChild("LAY_mainwindow"), 0, 0, 0);
        } else if (event.m_param0 == 2) {
            GfMenuObjOperationInfo::remove(acc.searchChild("LAY_mainwindow"), 0, 0, 0);
            acc.setDisp(false);
            acc.setTerm();
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        if (!m_owner->m_fadeOnClose) {
            sendEvent(handle, 3, 2, 0);
        } else {
            setFadeOut(handle);
        }
        break;
    case 0x24:
        GfMenuObject::disableInput(acc.searchChild("LAY_mainwindow"));
        setFadeOutSub(handle);
        m_owner->m_fadeOnClose = false;
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjItemList2::ItemListListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc main(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_owner->m_filterIndex = 0;
        m_owner->m_itemSelect->clear();
        m_owner->m_itemSelect->pickupObject(acc.m_handle, "LAY_listtag@%02d", 1);
        setupItemList(acc, m_owner->m_itemList, m_owner->m_itemSelect);
        GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_scroll_point"), m_owner->m_itemList,
                                              "IMG_scroll_line", true);
        updateItemList(m_owner->m_itemList, m_owner->m_itemSelect, m_owner->m_filterIndex, 0);
        refreshItemList(acc, m_owner->m_itemList, m_owner->m_itemSelect, m_owner->m_filterIndex);
        setupFilter(acc, 0);
        GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(0xB, 0), acc.searchChild("TXT_sort_label"));
        sendEvent(handle, 0x101, 0, 0);
        m_sort = 0;
        return;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_itemList->setIndex(index);
            unsigned int type = GfDataItem::getItemType(m_owner->m_itemList->getContents(index).m_id);
            acc.setDispChild(type != 10, "LAY_iteminfo_normal");
            acc.setDispChild(type == 10, "LAY_iteminfo_pouch");
            refreshItemList(acc, m_owner->m_itemList, m_owner->m_itemSelect, m_owner->m_filterIndex);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        return;
    }
    case 8:
        if (event.m_param1 == 2) {
            sendEvent(handle, 0x102, 0, 0);
            sendEvent(main.searchChild("LAY_main"), 0x22, 0, 0);
        } else if (event.m_param1 == 9) {
            unsigned int filter = m_owner->m_filters[m_owner->m_filterIndex];
            GfMenuObjSort::open(acc.m_handle, acc.searchChild("TXT_sort_label"), s_filterSortMenus[filter], m_sort);
            GfMenuObject::disableInput(handle);
            GfMenuObjOperationInfo::remove(main.searchChild("LAY_mainwindow"), 0, 0, 0);
            sendEvent(main.searchChild("LAY_filter"), 0x102, 0, 0);
        }
        return;
    case 0x101:
        GfMenuObject::setupInputSelectionFromList(handle, *m_owner->m_itemList);
        GfMenuObject::enableInput(handle);
        return;
    case 0x102:
        GfMenuObject::disableInput(handle);
        return;
    case 0x103: {
        unsigned int filter = m_owner->m_filters[m_owner->m_filterIndex];
        bool pouch = filter == 4;
        {
            ui::UIStr text;
            getFilterText(filter, text);
            ui::UIObjectAcc label(acc.searchChild("TXT_filterlabel"));
            label.setText(text);
        }
        GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(s_filterSortMenus[filter], 0),
                                        acc.searchChild("TXT_sort_label"));
        m_sort = 0;
        updateItemList(m_owner->m_itemList, m_owner->m_itemSelect, filter, 0);
        m_owner->m_itemList->setIndex(0);
        m_owner->m_itemList->getSize();
        acc.setDispChild(!pouch, "LAY_iteminfo_normal");
        acc.setDispChild(pouch, "LAY_iteminfo_pouch");
        refreshItemList(acc, m_owner->m_itemList, m_owner->m_itemSelect, m_owner->m_filterIndex);
        return;
    }
    case 0x104:
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelectionFromList(handle, *m_owner->m_itemList);
        return;
    case 0x148: {
        GfMenuObject::enableInput(handle);
        GfMenuObjOperationInfo::add(main.searchChild("LAY_mainwindow"), 0, 0, 0);
        sendEvent(main.searchChild("LAY_filter"), 0x101, 0, 0);
        if (m_sort == event.m_param0) {
            return;
        }
        unsigned int filter = m_owner->m_filters[m_owner->m_filterIndex];
        unsigned short sortId = GfMenuObjSort::getSortID(s_filterSortMenus[filter], event.m_param0);
        m_owner->m_itemList->sort(sortId, false);
        m_sort = event.m_param0;
        GfMenuItemList* list = m_owner->m_itemList;
        bool pouch = GfDataItem::getItemType(list->getContents(list->getIndex(false)).m_id) == 10;
        acc.setDispChild(!pouch, "LAY_iteminfo_normal");
        acc.setDispChild(pouch, "LAY_iteminfo_pouch");
        refreshItemList(acc, m_owner->m_itemList, m_owner->m_itemSelect, m_owner->m_filterIndex);
        return;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        return;
    }
}

void GfMenuObjItemList2::setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        name.format("IMG_itemicon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, list, i, false);
        name.format("TXT_itemname@%02d", i + 1);
        GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, false);
        name.format("LAY_listtag@%02d", i + 1);
        adapter->m_rowHandle = acc.searchChild(name.m_str);
        name.format("IMG_reaicon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 7, list, i, false);
        name.format("TXT_pricenum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 6, list, i, false);
        name.format("TXT_stc_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 3, list, i, false);
        name.format("TXT_stc_maxnum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 4, list, i, false);
    }
    GfMenuAdapterManager::beginAddAfter();
    GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild("TXT_infotxt"), 9, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_rowHandle = acc.searchChild("LAY_info_text");
    }
    name.format("TXT_getarea@%02d", 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xB, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_rowHandle = acc.searchChild("LAY_getinfo");
    }
    adapter->m_subIndex = 0;
    name.format("TXT_getarea@%02d", 2);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xB, list, -1, false);
    adapter->m_subIndex = 1;
    for (unsigned int i = 0; i < 3; i++) {
        name.format("TXT_iteminfo_pouch_eff@%02d", i + 1);
        adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xE, list, -1, false);
        if (adapter != nullptr) {
            adapter->m_subIndex = i;
        }
    }
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_iteminfo_pouch_time"), 0xD, list, -1, false);
    GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjItemList2::updateItemList(GfMenuItemList* list, ui::UISelectObjList* select, unsigned int filter,
                                        unsigned int) {
    GfMenuItemList::ItemBoxSetup setup;
    setup.m_setup.m_pageRowSize = select->getSize();
    setup.m_setup.m_pageScroll = true;
    setup.pad_28 = 0;
    setup.pad_29 = 0;
    if (filter != 0) {
        unsigned int type = s_filterItemTypes[filter];
        setup.m_type = type;
        list->setupFromBox(setup);
        GfMenuReference::setReferenceItemType(static_cast<ItemType::Type>(type));
    } else {
        list->setup(getAllocator(ALLOCATOR(0)), setup.m_setup);
        for (int i = 1; i < 13; ++i) {
            setup.m_type = s_filterItemTypes[i];
            list->addListFromBox(setup);
        }
        GfMenuReference::setReferenceItemType(static_cast<ItemType::Type>(0));
    }
    list->sort(1, false);
    list->setIndex(0);
}

void GfMenuObjItemList2::refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select,
                                         unsigned int filter) {
    if (list != nullptr && select != nullptr) {
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
            const MenuItemInfo& item = list->getContents(list->getPageIndex(i));
            name.format("IMG_tagsellect@%02d", i + 1);
            GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, list->getIndex(true) == i);
            name.format("LAY_stock@%02d", i + 1);
            GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, GfMenuItemUtil::canCountStack(item.m_type));
        }
        if (filter == 0) {
            unsigned int type = 0;
            if (list->getSize() != 0) {
                type = list->getContents(list->getIndex(false)).m_type;
            }
            GfMenuReference::setReferenceItemType(static_cast<ItemType::Type>(type));
        }
        unsigned int type = GfMenuReference::getReferenceItemType();
        acc.setDispChild(type == 2 || type == 3, "LAY_stock");
    }
}

void GfMenuObjItemList2::setupFilter(ui::UIObjectAcc& acc, unsigned int filter) {
    ui::UIStr text;
    getFilterText(filter, text);
    {
        ui::UIObjectAcc label(acc.searchChild("TXT_filterlabel"));
        label.setText(text);
    }
}

void GfMenuObjItemList2::FilterListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc main(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (m_owner->m_filterIndex != index) {
            m_owner->m_filterIndex = index;
            m_owner->refreshFilterIcon();
            sendEvent(acc.getParentHandle(), 0x103, 0, 0);
            sendEvent(acc.getParentHandle(), 0x104, 0, 1);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonTab();
        }
        break;
    }
    case 0x101:
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelection(handle, m_owner->m_filterIndex, m_owner->m_filters.size());
        GfMenuObject::enableInput(handle);
        m_owner->refreshFilterIcon();
        break;
    case 0x102:
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjItemList2::refreshFilterIcon() {
    ui::UIObjectAcc filter(m_handle, "LAY_filter");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_filters.size(); ++i) {
        bool select = i == m_filterIndex;
        name.format("IMG_ficon@%02d", i + 1);
        ui::UIObjectAcc icon(filter.searchChild(name.m_str));
        if (select) {
            icon.setMulColor("sys_select");
        } else {
            icon.loadDefColor();
        }
    }
}

}  // namespace gf
