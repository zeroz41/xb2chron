#include "classes/gf/GfMenuObjGiftBox.h"
#include "classes/gf/GfMenuObjGiftBox/MainListener.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "classes/gf/GfMenuReferenceNumber.h"
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
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjGiftBox::GfMenuObjGiftBox(unsigned int handle)
    : GfMenuObject(handle), m_topList(nullptr), m_subList(nullptr), m_numbers(), m_seq(this), pad_378(0),
      m_filterOn(false), m_filterIndex(0), m_filterCursor(0), m_refItem(), m_ids(), m_counts(), m_menuId(0), m_hasMenuId(false), m_noMenuId(false) {
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
            if (m_filterIndex != 0 && m_filterOn && m_counts[m_filterIndex] != count) {
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

}  // namespace gf

// the item and count vectors' growth (their users, initialize and seqGetItemAll, are not written yet)
template void mm::mtl::Vector<int>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfMenuObjGiftBox::AddedItem>::expand(size_t, size_t);
