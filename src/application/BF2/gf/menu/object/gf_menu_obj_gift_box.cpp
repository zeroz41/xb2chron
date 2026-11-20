#include "classes/gf/GfMenuObjGiftBox.h"
#include "classes/gf/GfMenuObjGiftBox/MainListener.h"
#include "classes/gf/GfMenuObjGiftBox/TopListener.h"
#include "classes/gf/GfMenuObjGiftBox/SubListener.h"
#include "classes/gf/GfMenuObjGiftBox/FilterListener.h"
#include "classes/gf/GfMenuObjAnnounce.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/SCOM_ADD_ETHER.h"
#include "classes/gf/SCOM_ADD_ITEM.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataUtil.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "gf/gf_data_aoc.h"
#include "mm/Math.h"
#include <algorithm>
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Delegate.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjGiftBox::GfMenuObjGiftBox(unsigned int handle)
    : GfMenuObject(handle), m_topList(nullptr), m_subList(nullptr), m_numbers(), m_seq(this), pad_378(0),
      m_filterCount(0), m_filterIndex(0), m_filterCursor(0), m_refItem(), m_ids(), m_counts(), m_menuId(0), m_hasMenuId(false), m_noMenuId(false) {
    m_topList = GfMenuMsgList::create();
    m_subList = GfMenuIDList::create();
    m_refItem = GfMenuReferenceItem::create();
    for (int i = 0; i < 22; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
    }
}

GfMenuObjGiftBox::~GfMenuObjGiftBox() {
    m_refItem = nullptr;
    for (int i = 0; i < 22; i++) {
        m_numbers[i] = nullptr;
    }
    if (m_counts.capacity() != 0) {
        m_counts.destroy();
    }
    if (m_subList != nullptr) {
        m_subList->release();
        m_subList = nullptr;
    }
    if (m_topList != nullptr) {
        m_topList->release();
        m_topList = nullptr;
    }
}

bool GfMenuObjGiftBox::hasGetableGift(bool flag) {
    if (!GfMenuObjUtil::isValidExpansion(3) && GfMenuManager::hasGift()) {
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        int number = GfMenuManager::getGiftNumber();
        if (!flag) {
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = Bdat::getIdTop(fp) + i;
                signed char count = Bdat::getVal(fp, "releasecount", row);
                if (count < 0 && GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(5)) < 0) {
                    continue;
                }
                if (number >= count && canGetItem(row, 0)) {
                    return true;
                }
            }
        } else {
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = Bdat::getIdTop(fp) + i;
                signed char count = Bdat::getVal(fp, "releasecount", row);
                if (count < 0 && GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(5)) < 0) {
                    continue;
                }
                if (number >= count &&
                    GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", row))) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GfMenuObjGiftBox::canGetItem(unsigned int row, unsigned int arg) {
    if (GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", row))) == 0 &&
        GfGameCond::isGameCond(static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "condition", row)))) {
        return !isGetItemFull(row, arg);
    }
    return false;
}

bool GfMenuObjGiftBox::hasGetableFreeGift(bool flag) {
    if (!GfMenuObjUtil::isValidExpansion(3) && GfMenuManager::hasGift()) {
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        int number = GfMenuManager::getGiftNumber();
        if (!flag) {
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = Bdat::getIdTop(fp) + i;
                signed char count = Bdat::getVal(fp, "releasecount", row);
                if (count >= 0) {
                    continue;
                }
                if (number >= count && canGetItem(row, 0)) {
                    return true;
                }
            }
        } else {
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = Bdat::getIdTop(fp) + i;
                signed char count = Bdat::getVal(fp, "releasecount", row);
                if (count >= 0) {
                    continue;
                }
                if (number >= count &&
                    GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", row))) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GfMenuObjGiftBox::hasFreeGift() {
    unsigned char* fp = GfDataBdat::getFP(0x10A);
    if (GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(5)) >= 0) {
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            if (Bdat::getVal(fp, "releasecount", Bdat::getIdTop(fp) + i) & 0x80) {
                return true;
            }
        }
    }
    return false;
}

void GfMenuObjGiftBox::setCloseToAnnounce() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(0x46, param);
}

void GfMenuObjGiftBox::setCloseToAnnounceEx() {
    GfMenuTypes::Param param;
    param.m_menuId = 2;
    GfMenuFullScreen::registLayerParam(0x46, param);
}

unsigned int GfMenuObjGiftBox::getAddedItemValue(unsigned int row) {
    unsigned char* fp = GfDataBdat::getFP(0x10A);
    if (fp != nullptr) {
        unsigned char category = Bdat::getVal(fp, "category", row);
        if (category == 1) {
            unsigned short item = Bdat::getVal(fp, "item_id", row);
            unsigned int total = 0;
            for (unsigned int i = 0; i < m_ids.size(); i++) {
                if (m_ids[i].m_id != row && static_cast<unsigned char>(Bdat::getVal(fp, "category", m_ids[i].m_id)) == 1 &&
                    static_cast<unsigned short>(Bdat::getVal(fp, "item_id", m_ids[i].m_id)) == item) {
                    total += static_cast<unsigned short>(Bdat::getVal(fp, "value", m_ids[i].m_id));
                }
            }
            return total;
        } else if (category == 2) {
            unsigned int total = 0;
            for (unsigned int i = 0; i < m_ids.size(); i++) {
                if (m_ids[i].m_id != row && static_cast<unsigned char>(Bdat::getVal(fp, "category", m_ids[i].m_id)) == 2) {
                    total += static_cast<unsigned short>(Bdat::getVal(fp, "value", m_ids[i].m_id));
                }
            }
            return total;
        } else if (category == 3) {
            unsigned int total = 0;
            for (unsigned int i = 0; i < m_ids.size(); i++) {
                if (m_ids[i].m_id != row && static_cast<unsigned char>(Bdat::getVal(fp, "category", m_ids[i].m_id)) == 3) {
                    total += static_cast<unsigned short>(Bdat::getVal(fp, "value", m_ids[i].m_id));
                }
            }
            return total;
        }
    }
    return 0;
}

bool GfMenuObjGiftBox::hasGetableGiftFromFilter(bool flag) {
    if (GfMenuManager::hasGift()) {
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        int number = GfMenuManager::getGiftNumber();
        if (!flag) {
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = Bdat::getIdTop(fp) + i;
                signed char count = Bdat::getVal(fp, "releasecount", row);
                if (count < 0 && !m_hasMenuId) {
                    continue;
                }
                if (number >= count) {
                    if (m_counts[m_filterIndex] != 0 && m_counts[m_filterIndex] != count) {
                        continue;
                    }
                    if (canGetItem(row, 0)) {
                        return true;
                    }
                }
            }
        } else {
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = Bdat::getIdTop(fp) + i;
                signed char count = Bdat::getVal(fp, "releasecount", row);
                if (count < 0 && !m_hasMenuId) {
                    continue;
                }
                if (number >= count) {
                    if (m_counts[m_filterIndex] != 0 && m_counts[m_filterIndex] != count) {
                        continue;
                    }
                    if (GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", row))) == 0) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void GfMenuObjGiftBox::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    {
#line 430
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_menuId = 0;
    {
        GfMenuTypes::Param param;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
            m_menuId = param.m_menuId;
            m_hasMenuId = true;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        }
    }
    if (m_hasMenuId) {
        main.setDispChild(false, "IMG_list_bg");
        main.setDispChild(true, "IMG_list_bg2");
        ui::UIObjectAcc(main.m_handle, "IMG_list_bg2").setAddColor(mm::Col3(0.8823f, 0.9215f, 0.9803f));
        ui::UIObjectAcc(main.m_handle, "IMG_filter_index_base").setAddColor(mm::Col3(0.7843f, 0.9803f, 0.9803f));
        ui::UIObjectAcc(main.m_handle, "TXT_filter_index").setMulColor("win_sub_other_line");
        m_noMenuId = false;
    } else {
        m_noMenuId = true;
    }
    ui::UIObjectAcc top(main.m_handle, "LAY_top_list");
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = top.countChild("LAY_top_list_item@%02d", 1);
        param.m_pageScroll = true;
        m_topList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_topList->setBdat(0, 0x139);
    GfMenuObjUtil::createVScrollBarPlugin(top.searchChild("IMG_top_list_scroll_bar"), m_topList,
                                          "IMG_top_list_scroll_base", true);
    {
#line 482
        TopListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TopListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(top.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::setFSInputObject(0, top.m_handle);
    ui::UIObjectAcc sub(main.m_handle, "LAY_sub_list");
    {
        mm::mtl::FixStr<32> name;
        {
            ui::UIListInfoBase::SetupParam param;
            param.m_pageRowSize = sub.countChild("LAY_sub_list_item@%02d", 1);
            param.m_pageScroll = true;
            m_subList->setup(getAllocator(ALLOCATOR(0)), param);
        }
        for (unsigned int i = 0; i < m_subList->getPageRowSize(); i++) {
            name.format("TXT_sub_list_item_num@%02d", i + 1);
            GfMenuReferenceAdapter::create(sub.searchChild(name.m_str), m_numbers[i], true);
            name.format("TXT_sub_list_item_gold@%02d", i + 1);
            GfMenuReferenceAdapter::create(sub.searchChild(name.m_str), m_numbers[i], true);
        }
        GfMenuAdapterManager::beginAddAfter();
        GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromReference(sub.searchChild("TXT_infotxt"), 9, m_refItem, false);
        if (adapter != nullptr) {
            adapter->m_rowHandle = sub.searchChild("LAY_info_text");
        }
        for (unsigned int i = 0; i < 2; i++) {
            name.format("TXT_getarea@%02d", i + 1);
            adapter = GfMenuItemAdapter::createFromReference(sub.searchChild(name.m_str), 0xB, m_refItem, false);
            if (i == 0 && adapter != nullptr) {
                adapter->m_rowHandle = sub.searchChild("LAY_getinfo");
            }
            adapter->m_subIndex = i;
        }
        for (unsigned int i = 0; i < 3; i++) {
            name.format("TXT_iteminfo_pouch_eff@%02d", i + 1);
            adapter = GfMenuItemAdapter::createFromReference(sub.searchChild(name.m_str), 0xE, m_refItem, false);
            if (adapter != nullptr) {
                adapter->m_subIndex = i;
            }
        }
        GfMenuItemAdapter::createFromReference(sub.searchChild("TXT_iteminfo_pouch_time"), 0xD, m_refItem, true);
        GfMenuAdapterManager::endAddAfter();
    }
    GfMenuObjUtil::createVScrollBarPlugin(sub.searchChild("IMG_sub_list_scroll_bar"), m_subList,
                                          "IMG_sub_list_scroll_base", true);
    {
#line 561
        SubListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SubListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(sub.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::setFSInputObject(1, sub.m_handle);
    ui::UIObjectAcc filter(main.m_handle, "LAY_filter");
    m_filterIndex = 0;
    m_filterCursor = 0;
    {
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        m_counts.setAllocator(getAllocator(ALLOCATOR(0)));
        m_counts.reserve(Bdat::getIdCount(fp) + 1);
        m_counts.push_back(0);
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            int count = static_cast<signed char>(Bdat::getVal(fp, "releasecount", Bdat::getIdTop(fp) + i));
            if (count <= GfMenuManager::getGiftNumber()) {
                if (!(m_hasMenuId ? count >= 0 : count < 0)) {
                    if (std::find(m_counts.begin(), m_counts.end(), count) == m_counts.end()) {
                        m_counts.push_back(count);
                    }
                }
            }
        }
        if (m_counts.size() > 2) {
            m_filterCount = m_counts.size();
        } else {
            if (m_counts.size() == 2) {
                int value = m_counts.at(1);
                m_counts.clear();
                m_counts.push_back(value);
            }
            m_filterCount = 0;
        }
    }
    {
        unsigned int count = filter.countChild("LAY_icon@%02d", 1);
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < count; i++) {
            name.format("TXT_filter_no@%02d", i + 1);
            GfMenuReferenceAdapter::create(filter.searchChild(name.m_str), m_numbers[i + 9], true);
        }
    }
    refreshFilter();
    if (m_filterCount == 0 && !m_hasMenuId) {
        ui::UIObjectAcc(m_handle, "LAY_filter_index").setDisp(false);
    }
    {
#line 668
        FilterListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FilterListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(filter.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    updateTopList();
    refreshTopList(false);
    GfMenuObject::initialize();
}


void GfMenuObjGiftBox::refreshFilter() {
    ui::UIObjectAcc acc(m_handle, "LAY_filter");
    unsigned int count = acc.countChild("LAY_icon@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < count; i++) {
        unsigned int index = m_filterCursor + i;
        name.format("LAY_icon@%02d", i + 1);
        ui::UIObjectAcc icon(acc.m_handle, name.m_str);
        if (icon.m_object != nullptr) {
            if (i < m_filterCount) {
                unsigned char* fp = GfDataBdat::getFP(0x168);
                name.format("IMG_filter_icon@%02d", i + 1);
                ui::UIObjectAcc image(acc.m_handle, name.m_str);
                if (image.m_object != nullptr) {
                    name.format("TXT_filter_no@%02d", i + 1);
                    ui::UIObjectAcc text(acc.m_handle, name.m_str);
                    if (text.m_object != nullptr) {
                        if (index == 0) {
                            image.setImageIndex(1);
                            text.setDisp(false);
                            m_numbers[i + 9]->m_value = -1;
                        } else {
                            image.setImageIndex(0);
                            text.setDisp(true);
                            if (fp != nullptr && Bdat::getMember(fp, "number") != nullptr) {
                                unsigned char number = Bdat::getVal(fp, "number", i + 1);
                                if (number == 0) {
                                    text.setDisp(false);
                                    m_numbers[i + 9]->m_value = -1;
                                } else {
                                    m_numbers[i + 9]->m_value = number;
                                }
                            } else {
                                m_numbers[i + 9]->m_value = index;
                            }
                        }
                        if (index == m_filterIndex) {
                            image.setMulColor("sys_select");
                        } else if (index == 0) {
                            image.setMulColor("win_sub_other_line");
                        } else {
                            image.setMulColor("white");
                        }
                        icon.setDisp(true);
                    }
                }
            } else {
                icon.setDisp(false);
            }
        }
    }
    {
        unsigned int shown = m_filterCount > count ? count : m_filterCount;
        mm::Rect<short> center;
        mm::Rect<short> range;
        acc.getLayoutRect("icon_l_center", center);
        acc.getLayoutRect("icon_l_range", range);
        GfMenuObjUtil::placeObjectH(acc.m_handle, "LAY_icon@%02d", shown,
                                    mm::Pnt<short>(center.x + center.w / 2, center.y + center.h / 2), range.x - center.x);
    }
    bool next;
    if (count < m_filterCount) {
        acc.setDispChild(m_filterCursor != 0, "IMG_filter_prev");
        next = m_filterCursor + count < m_filterCount;
    } else {
        acc.setDispChild(false, "IMG_filter_prev");
        next = false;
    }
    acc.setDispChild(next, "IMG_filter_next");
    unsigned int filter = m_filterIndex;
    unsigned short msg =
        GfMenuObjUtil::getMsgIDFromList(0x168, m_counts[filter] < 0 ? 101 - m_counts[filter] : m_counts[filter] + 1);
    if (msg != 0) {
        ui::UIObjectAcc text(m_handle, "TXT_filter_index");
        text.setText(ui::UIStr(GfDataBdat::getFP(0x139), msg));
    }
    acc.setDispChild(msg != 0, "TXT_filter_index");
}

void GfMenuObjGiftBox::updateTopList() {
    if (m_topList != nullptr) {
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        int number = GfMenuManager::hasGift() ? GfMenuManager::getGiftNumber() : 0;
        m_topList->clear();
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            int row = Bdat::getIdTop(fp) + i;
            signed char count = Bdat::getVal(fp, "releasecount", row);
            if (number < count) {
                continue;
            }
            if (m_hasMenuId) {
                if (count >= 0) {
                    continue;
                }
            } else if (count < 0) {
                continue;
            }
            if (m_filterIndex != 0 && m_filterCount && m_counts[m_filterIndex] != count) {
                continue;
            }
            unsigned int title = static_cast<unsigned short>(Bdat::getVal(fp, "title", row));
            if (m_topList->find(title) == -1) {
                m_topList->addContents(MsgID{title, 0});
            }
        }
        m_topList->setIndex(0);
    }
}

void GfMenuObjGiftBox::refreshTopList(bool flag) {
    if (m_topList != nullptr) {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        mm::mtl::FixStr<32> name;
        ui::UIStr str;
        for (unsigned int i = 0; i < m_topList->getPageRowSize(); i++) {
            bool has = m_topList->getMsg(i, str, true);
            if (has) {
                if (!flag) {
                    name.format("TXT_top_list_item_name@%02d", i + 1);
                    ui::UIObjectAcc(main.m_handle, name.m_str).setText(str);
                    name.format("IMG_top_list_item_base@%02d", i + 1);
                    if (m_topList->getPageIndex(i) == m_topList->getIndex(false)) {
                        ui::UIObjectAcc(main.m_handle, name.m_str).startAnimation("select", false);
                    } else {
                        ui::UIObjectAcc(main.m_handle, name.m_str).startAnimation("normal", false);
                    }
                }
                unsigned char* fp = GfDataBdat::getFP(0x10A);
                name.format("IMG_top_list_item_status@%02d", i + 1);
                ui::UIObjectAcc status(main.m_handle, name.m_str);
                unsigned int image = 2;
                for (int j = 0; j < Bdat::getIdCount(fp); j++) {
                    if (str.getMsgID() == static_cast<unsigned short>(Bdat::getVal(fp, "title", j + 1)) &&
                        GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", j + 1))) == 0) {
                        image = 0;
                        break;
                    }
                }
                status.setImageIndex(image);
            }
            if (!flag) {
                name.format("LAY_top_list_item@%02d", i + 1);
                main.setDispChild(has, name.m_str);
            }
        }
    }
}

void GfMenuObjGiftBox::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjGiftBox::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjGiftBox::updateSubList() {
    if (m_subList != nullptr) {
        unsigned int title = m_topList->getContents(m_topList->getIndex(false)).m_id;
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        m_subList->clear();
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            int row = Bdat::getIdTop(fp) + i;
            if (title == static_cast<unsigned short>(Bdat::getVal(fp, "title", row))) {
                unsigned short value = Bdat::getVal(fp, "value", row);
                MenuID id;
                id.m_id = row;
                id.m_subId = 0;
                unsigned int index = m_subList->getSize();
                m_subList->addContents(id);
                if (i < static_cast<int>(m_subList->getPageRowSize())) {
                    int count = value;
                    m_numbers[index]->m_max = 999999999;
                    m_numbers[index]->m_value = count;
                }
            }
        }
        m_subList->setIndex(0);
    }
}

void GfMenuObjGiftBox::refreshSubList() {
    if (m_subList != nullptr) {
        unsigned char* fp = GfDataBdat::getFP(0x10A);
        ui::UIObjectAcc main(m_handle, "LAY_main");
        mm::mtl::FixStr<32> name;
        ui::UIStr str;
        for (unsigned int i = 0; i < m_subList->getPageRowSize(); i++) {
            bool disp = false;
            if (i < m_subList->getSize() - m_subList->getRowOffset()) {
                unsigned int row = m_subList->getContents(m_subList->getPageIndex(i)).m_id;
                unsigned char category = Bdat::getVal(fp, "category", row);
                if (category != 0) {
                    unsigned short item = Bdat::getVal(fp, "item_id", row);
                    switch (category) {
                    case 1:
                        if (!item) {
                            disp = false;
                            break;
                        }
                        GfMenuItemUtil::getItemName(GfItemUtil::getType(item), item, str);
                        disp = true;
                        break;
                    case 2:
                    case 3: {
                        unsigned short msg = GfMenuObjUtil::getMsgIDFromList(0x167, category - 1);
                        str.setupMstxt(GfDataBdat::getFP(0xF5), msg);
                        disp = true;
                        break;
                    }
                    default:
                        disp = true;
                        break;
                    }
                    if (str.isValid()) {
                        name.format("TXT_sub_list_item_name@%02d", i + 1);
                        ui::UIObjectAcc(main.m_handle, name.m_str).setText(str);
                    } else {
                        disp = false;
                    }
                    if (category == 1 && item != 0) {
                        unsigned char type = GfItemUtil::getType(item);
                        unsigned int key = 0;
                        if (type == 10) {
                            ItemProperty property;
                            GfItemUtil::getProperty(property, item, 0);
                            key = property.m_favoriteKey;
                        } else if (type == 2) {
                            ItemProperty property;
                            GfItemUtil::getProperty(property, item, 0);
                            key = property.m_iconIndex + 1;
                        } else if (type == 7) {
                            ItemProperty property;
                            GfItemUtil::getProperty(property, item, 0);
                            key = property.m_collectionKey;
                        }
                        unsigned int icon;
                        if (GfMenuItemUtil::getIconNumber(static_cast<ItemType::Type>(type), key, icon, false)) {
                            name.format("IMG_sub_list_item_icon_item@%02d", i + 1);
                            ui::UIObjectAcc(main.m_handle, name.m_str).setImageIndex(icon);
                        }
                    }
                    name.format("IMG_sub_list_item_icon_item@%02d", i + 1);
                    main.setDispChild(category == 1, name.m_str);
                    name.format("IMG_sub_list_item_icon_gold@%02d", i + 1);
                    main.setDispChild(category == 2, name.m_str);
                    name.format("IMG_sub_list_item_icon_ether@%02d", i + 1);
                    main.setDispChild(category == 3, name.m_str);
                    unsigned int value = static_cast<unsigned short>(Bdat::getVal(fp, "value", row));
                    m_numbers[i]->m_max = 999999999;
                    m_numbers[i]->m_value = value;
                    name.format("LAY_sub_list_item_num@%02d", i + 1);
                    main.setDispChild(category == 1 || category == 3, name.m_str);
                    name.format("LAY_sub_list_item_gold@%02d", i + 1);
                    main.setDispChild(category == 2, name.m_str);
                    unsigned int status = 0;
                    if (!canGetItem(row, 0)) {
                        status = GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(
                                                             GfDataBdat::getFP(0x10A), "getflag", row))) != 0
                                     ? 2
                                     : 1;
                    }
                    name.format("IMG_sub_list_item_status@%02d", i + 1);
                    ui::UIObjectAcc(main.m_handle, name.m_str).setImageIndex(status);
                    name.format("TXT_sub_list_item_name@%02d", i + 1);
                    {
                        ui::UIObjectAcc text(main.m_handle, name.m_str);
                        if (status != 0) {
                            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_disable");
                        } else {
                            GfMenuObjUtil::setColDefault(text.m_handle);
                        }
                    }
                    bool select = m_subList->getPageIndex(i) == m_subList->getIndex(false);
                    name.format("IMG_sub_list_item_select@%02d", i + 1);
                    main.setDispChild(select, name.m_str);
                    if (select) {
                        MenuItemInfo info;
                        if (Bdat::getMember(fp, "disp_item_info") != nullptr) {
                            unsigned char flag = Bdat::getVal(fp, "disp_item_info", row);
                            if (item != 0 && flag == 1) {
                                info.m_type = GfDataItem::getItemType(item);
                                info.m_count = Bdat::getVal(fp, "value", row);
                                info.m_id = item;
                            }
                        }
                        m_refItem->m_item = info;
                        bool pouch = info.m_type == 10;
                        main.setDispChild(!pouch, "LAY_iteminfo_normal");
                        main.setDispChild(pouch, "LAY_iteminfo_pouch");
                    }
                }
            }
            name.format("LAY_sub_list_item@%02d", i + 1);
            main.setDispChild(disp, name.m_str);
        }
    }
}

bool GfMenuObjGiftBox::isGetItemFull(unsigned int row, unsigned int arg) {
    unsigned char* fp = GfDataBdat::getFP(0x10A);
    unsigned char category = Bdat::getVal(fp, "category", row);
    unsigned short value = Bdat::getVal(fp, "value", row);
    unsigned short count = value + arg;
    if (category == 0) {
        return false;
    }
    switch (category) {
    case 1: {
        unsigned short item = Bdat::getVal(fp, "item_id", row);
        unsigned int type = GfDataItem::getItemType(item);
        if (GfMenuItemUtil::canCountStack(type)) {
            if (static_cast<unsigned int>(GfItemUtil::getItemBoxCount(item) + count) > static_cast<unsigned int>(GfItemUtil::getEnableStock(item))) {
                return true;
            }
        } else {
            if (static_cast<unsigned int>(GfItemUtil::getCountByType(static_cast<ItemType::Type>(type)) + count) > static_cast<unsigned int>(GfItemUtil::getEnableStock(item))) {
                return true;
            }
        }
        break;
    }
    case 2:
        if (GfDataUtil::getMoney() + count > 999999999) {
            return true;
        }
        break;
    case 3:
        if (static_cast<unsigned int>(GfDataHana::getEther() + count) > 999999999) {
            return true;
        }
        break;
    }
    return false;
}

void GfMenuObjGiftBox::execGetItem(unsigned int row) {
    unsigned char* fp = GfDataBdat::getFP(0x10A);
    unsigned char category = Bdat::getVal(fp, "category", row);
    unsigned short value = Bdat::getVal(fp, "value", row);
    switch (category) {
    case 1:
        SCOM_ADD_ITEM::create(static_cast<unsigned short>(Bdat::getVal(fp, "item_id", row)), value);
        break;
    case 2:
        SCOM_ADD_MONEY::create(value);
        break;
    case 3:
        SCOM_ADD_ETHER::create(value);
        break;
    }
    GfGameFlag::setLocal(1, static_cast<unsigned short>(Bdat::getVal(fp, "getflag", row)), 1);
}

int GfMenuObjGiftBox::ctrlTopItem(bool out) {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    unsigned int count = m_topList->getSize() - m_topList->getRowOffset();
    if (count >= m_topList->getPageRowSize()) {
        count = m_topList->getPageRowSize();
    }
    int ctrl = -1;
    if (out) {
        mm::Pnt<short> firstPos;
        mm::Pnt<short> pos;
        name.format("LAY_top_list_item@%02d", 1);
        ui::UIObjectAcc first(main.searchChild(name.m_str));
        first.getPos(firstPos);
        for (unsigned int i = 0; i != count; i++) {
            name.format("LAY_top_list_item@%02d", i + 1);
            ui::UIObjectAcc item(main.m_handle, name.m_str);
            if (i == m_topList->getIndex(true)) {
                if (i != 0) {
                    item.getPos(pos);
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 0x20;
                    param.m_distance = pos.y - firstPos.y;
                    param.m_time = 0.3f;
                    param.m_eventId = 8;
                    param.m_startFlags = 4;
                    param.m_curve = 1;
                    ctrl = GfMenuObjUtil::startCtrl(item.m_handle, param, nullptr);
                    item.setDispPriority(9);
                }
            } else {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_eventId = 8;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_out_l";
                param.m_time = 0.3f;
                param.m_startFlags = 10;
                ctrl = GfMenuObjUtil::startCtrl(item.m_handle, param, nullptr);
                item.setDispPriority(8);
            }
        }
        GfMenuObjUtil::setCommonFadeOut(main.searchChild("LAY_top_list_scroll_bar"), 0, 0);
    } else {
        for (unsigned int i = 0; i != count; i++) {
            name.format("LAY_top_list_item@%02d", i + 1);
            ui::UIObjectAcc item(main.m_handle, name.m_str);
            if (i == m_topList->getIndex(true)) {
                if (i != 0) {
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 0x80000000;
                    param.m_time = 0.3f;
                    param.m_eventId = 9;
                    param.m_slot = GfMenuObjUtil::getCtrlID(item.m_handle);
                    param.m_curve = 1;
                    ctrl = GfMenuObjUtil::startCtrl(item.m_handle, param, nullptr);
                }
            } else {
                item.setDisp(true);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_eventId = 9;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_l";
                param.m_time = 0.3f;
                param.m_startFlags = 8;
                ctrl = GfMenuObjUtil::startCtrl(item.m_handle, param, nullptr);
            }
            item.setDispPriority(8);
        }
        GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_top_list_scroll_bar"), 0, 0);
    }
    return ctrl;
}

int GfMenuObjGiftBox::ctrlSubItem(bool out) {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    main.setDispChild(true, "LAY_sub_list");
    main.setDispChild(true, "LAY_sub_list_item");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = out ? "fade_out_l" : "fade_in_l";
    param.m_time = 0.3f;
    param.m_eventId = out ? 11 : 10;
    param.m_startFlags = 8;
    param.m_setDefault = true;
    if (out) {
        param.m_startFlags = 10;
    }
    int ctrl = GfMenuObjUtil::startCtrl(main.searchChild("LAY_sub_list_item"), param, nullptr);
    if (out) {
        GfMenuObjUtil::setCommonFadeOut(main.searchChild("LAY_sub_list_scroll_bar"), 0, 0);
        GfMenuObjUtil::setCommonFadeOut(main.searchChild("LAY_iteminfo"), 0, 0);
    } else {
        GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_sub_list_scroll_bar"), 0, 0);
        GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_iteminfo"), 0, 0);
    }
    return ctrl;
}

void GfMenuObjGiftBox::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
    } else if (event.m_type == 2) {
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
    } else if (event.m_type == 3) {
        if (event.m_param0 == 1) {
            GfMenuObject::sendOpenEvent(acc.searchChild("LAY_top_list"), 0, 0.0f);
        } else if (event.m_param0 == 2) {
            acc.setTerm();
        }
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

// tells the filter ("LAY_filter", FilterListener) to take (1) or leave (0) the input when the gift box has filters
// (the name is not the original's)
static inline void setFilterInput(GfMenuObjGiftBox* owner, int active) {
    if (owner->m_filterCount != 0) {
        ui::UIObjectAcc filter(owner->m_handle, "LAY_filter");
        ui::EventData event;
        event.m_type = 0x101;
        event.m_param0 = active;
        GfMenuObject::sendEvent(filter.m_handle, event, 0.0f);
    }
}

void GfMenuObjGiftBox::TopListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 8) {
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_sub_list"), 0, 0.0f);
        } else if (event.m_param0 == 9) {
            GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_topList->setIndex(index);
            m_owner->refreshTopList(false);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        switch (event.m_param1) {
        case 1:
            if (m_owner->m_topList->getSize() != 0) {
                int ctrl = m_owner->ctrlTopItem(true);
                if (ctrl != -1) {
                    GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                } else {
                    GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_sub_list"), 0, 0.0f);
                }
                GfMenuObject::disableFSInput();
                GfMenuObjMainMenu2::setSystemKeyEnable(false);
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
                setFilterInput(m_owner, 0);
                GfMenuObjUtil::playSECommonDecide();
            }
            break;
        case 2:
            if (m_owner->m_menuId != 0) {
                if (m_owner->m_menuId == 2) {
                    GfMenuObjAnnounce::setCloseToDlcGift();
                }
                GfMenuObject::changeFSSubLayer(m_owner->m_handle, GfMenuFullScreen::getLayerGroup(m_owner->m_fsLayer), 0x47, false);
                GfMenuObject::disableFSInput();
                GfMenuObjMainMenu2::setSystemKeyEnable(false);
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            }
            break;
        case 9:
            if (m_owner->m_topList->getSize() != 0) {
                if (m_owner->hasGetableGiftFromFilter(false)) {
                    m_owner->m_seq.clear();
                    m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqGetItemAll);
                    m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqWaitCommonDialog);
                    m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqReturnTop);
                    GfMenuObject::disableFSInput();
                    GfMenuObjMainMenu2::setSystemKeyEnable(false);
                    GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
                    setFilterInput(m_owner, 0);
                } else {
                    GfMenuObjUtil::playSECommon(2);
                }
            }
            break;
        case 10:
            GfMenuObjAnnounce::setCloseToDlcGift();
            GfMenuObject::changeFSSubLayer(m_owner->m_handle, GfMenuFullScreen::getLayerGroup(m_owner->m_fsLayer), 0x47, false);
            GfMenuObjMainMenu2::setSystemKeyEnable(false);
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            break;
        }
        break;
    case 0x21:
        m_owner->refreshTopList(false);
        GfMenuObject::enableFSInput(0);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_topList);
        if (m_owner->m_menuId == 0) {
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
        }
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 2, m_owner->m_menuId != 0);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, m_owner->hasGetableGiftFromFilter(false));
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, m_owner->m_noMenuId);
        GfMenuObjOperationInfo::setGuideText(0x46, 0);
        setFilterInput(m_owner, 1);
        break;
    case 0x100:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
            if (m_owner->m_menuId == 0) {
                GfMenuObjMainMenu2::setSystemKeyEnable(true);
            }
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 2, m_owner->m_menuId != 0);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, m_owner->hasGetableGiftFromFilter(false));
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, m_owner->m_noMenuId);
            setFilterInput(m_owner, 1);
        } else {
            int ctrl = m_owner->ctrlTopItem(false);
            if (ctrl != -1) {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            } else {
                GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
            }
        }
        break;
    case 0x102:
        m_owner->updateTopList();
        m_owner->refreshTopList(false);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_topList);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, m_owner->hasGetableGiftFromFilter(false));
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjGiftBox::seqWaitCommonDialog() {
    return !GfMenuManager::isOpenCommonWindow();
}

bool GfMenuObjGiftBox::seqReturnTop() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    event.m_param0 = 1;
    GfMenuObject::sendEvent(acc.searchSibiling("LAY_top_list"), event, 0.0f);
    return true;
}

void GfMenuObjGiftBox::SubListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 10) {
            GfMenuObject::enableFSInput(1);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_subList);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, false);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, m_owner->m_noMenuId);
        } else if (event.m_param0 == 11) {
            ui::EventData open;
            open.m_type = 0x100;
            GfMenuObject::sendEvent(acc.searchSibiling("LAY_top_list"), open, 0.0f);
            acc.setDisp(false);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_subList->setIndex(index);
            m_owner->refreshSubList();
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            unsigned int row = m_owner->m_subList->getContents(m_owner->m_subList->getIndex(false)).m_id;
            if (GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", row))) != 0) {
                GfMenuObjUtil::playSECommon(2);
                break;
            }
            m_owner->m_seq.clear();
            if (canGetItem(row, 0)) {
                m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqGetItem);
                m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqWaitCommonDialog);
                m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqReturnSub);
                GfMenuObject::disableFSInput();
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
                GfMenuObjUtil::playSECommonDecide();
                break;
            }
            if (!GfGameCond::isGameCond(static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "condition", row)))) {
                GfMenuManager::openCommonWindow(0xE7);
                m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqWaitCommonDialog);
            } else if (isGetItemFull(row, 0)) {
                switch (static_cast<unsigned char>(Bdat::getVal(GfDataBdat::getFP(0x10A), "category", row))) {
                case 1:
                    GfMenuManager::openCommonWindow(0xE5);
                    break;
                case 3:
                    GfMenuManager::openCommonWindow(0xE6);
                    break;
                case 2:
                    GfMenuManager::openCommonWindow(0xE4);
                    break;
                }
                m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqWaitCommonDialog);
            } else {
                GfMenuObjUtil::playSECommon(2);
            }
            m_owner->m_seq.addJob(&GfMenuObjGiftBox::seqReturnSub);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        } else if (event.m_param1 == 10) {
            GfMenuObjAnnounce::setCloseToDlcGift();
            GfMenuObject::changeFSSubLayer(m_owner->m_handle, GfMenuFullScreen::getLayerGroup(m_owner->m_fsLayer), 0x47, false);
            GfMenuObjMainMenu2::setSystemKeyEnable(false);
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        } else if (event.m_param1 == 2) {
            int ctrl = m_owner->ctrlSubItem(true);
            if (ctrl != -1) {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    case 0x21: {
        m_owner->updateSubList();
        m_owner->refreshSubList();
        int ctrl = m_owner->ctrlSubItem(false);
        if (ctrl != -1) {
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        break;
    }
    case 0x100:
        GfMenuObject::enableFSInput(1);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, false);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, m_owner->m_noMenuId);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjGiftBox::seqGetItem() {
    execGetItem(m_subList->getContents(m_subList->getIndex(false)).m_id);
    refreshTopList(true);
    refreshSubList();
    GfMenuManager::openCommonWindow(0xE8);
    return true;
}

bool GfMenuObjGiftBox::seqGetItemAll() {
    unsigned char* fp = GfDataBdat::getFP(0x10A);
    if (m_ids.capacity() != 0) {
        m_ids.destroy();
    }
    m_ids.setAllocator(getAllocator(ALLOCATOR(0)));
    m_ids.reserve(8);
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_topList->getSize()); i++) {
        unsigned int title = m_topList->getContents(i).m_id;
        for (int j = 0; j < Bdat::getIdCount(fp); j++) {
            int row = Bdat::getIdTop(fp) + j;
            unsigned int rowTitle = static_cast<unsigned short>(Bdat::getVal(fp, "title", row));
            unsigned int added = getAddedItemValue(row);
            if (rowTitle == title && canGetItem(row, added)) {
                execGetItem(row);
                AddedItem item;
                item.m_id = row;
                m_ids.push_back(item);
            }
        }
    }
    refreshTopList(true);
    refreshSubList();
    if (m_ids.capacity() != 0) {
        m_ids.destroy();
    }
    GfMenuManager::openCommonWindow(0xE8);
    return true;
}

bool GfMenuObjGiftBox::seqReturnSub() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    GfMenuObject::sendEvent(acc.searchSibiling("LAY_sub_list"), event, 0.0f);
    return true;
}

void GfMenuObjGiftBox::FilterListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(m_owner->m_filterCount != 0);
        GfMenuObject::disableInput(acc.m_handle);
        m_iconCount = acc.countChild("LAY_icon@%02d", 1);
        break;
    case 3:
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1 && index != m_owner->m_filterIndex) {
            m_owner->m_filterIndex = index;
            if (prev != -1) {
                int count = m_iconCount;
                int step = index - prev;
                if (index < count) {
                    if (step == -1) {
                        if (index < m_owner->m_filterCursor) {
                            m_owner->m_filterCursor--;
                        }
                    } else if (mm::abs(step) > 1) {
                        m_owner->m_filterCursor = 0;
                    }
                } else if (step == 1 && index == m_owner->m_filterCursor + count) {
                    m_owner->m_filterCursor++;
                } else if (prev == 0) {
                    m_owner->m_filterCursor = m_owner->m_counts.size() - count;
                }
            }
            m_owner->refreshFilter();
            ui::UIObjectAcc top(m_owner->m_handle, "LAY_top_list");
            ui::EventData refresh;
            refresh.m_type = 0x102;
            GfMenuObject::sendEvent(top.m_handle, refresh, 0.0f);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonTab();
        }
        break;
    }
    case 0x21: {
        int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_filter_list"), 1, 0);
        if (ctrl != -1) {
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        break;
    }
    case 0x22: {
        int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_filter_list"), 2, 0);
        if (ctrl != -1) {
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        break;
    }
    case 0x101: {
        int active = event.m_param0;
        if (active == 1) {
            int index = m_owner->m_filterIndex;
            GfMenuObject::setupInputSelection(acc.m_handle, index, m_owner->m_filterCount);
            GfMenuObject::enableInput(acc.m_handle);
        } else {
            GfMenuObject::disableInput(acc.m_handle);
        }
        ui::UIObjectAcc input(acc.m_handle, "LAY_filter_input");
        input.setAlpha(active == 1 ? 1.0f : 0.5f);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
