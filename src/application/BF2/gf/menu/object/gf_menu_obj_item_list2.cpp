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
