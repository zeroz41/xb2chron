#include <string.h>

#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfItemBox.h"
#include "gf/GfDataItem.h"
#include "gf/GfItemUtil.h"

namespace gf {

item_iterator item_iterator::operator++() {
    GfItemInfo** end = m_box->getItemTypeInfo(m_type).m_end;
    if (m_cur != end) {
        do {
            ++m_cur;
            if (m_cur == end) {
                break;
            }
        } while ((*m_cur)->m_id != 0 && (*m_cur)->getType() != m_type);
    }
    return *this;
}

item_iterator GfItemBoxBase::end(ItemType::Type type) {
    ItemTypeInfo& info = getItemTypeInfo(type);
    return item_iterator(this, info.m_end, info.m_step, info.m_multi, type);
}

GfItemBoxBase::GfItemBoxBase() : m_favoriteItemType(nullptr), m_itemBox(nullptr) {}

GfItemBoxBase::~GfItemBoxBase() {}

template <ItemType::Type Type, size_t N, size_t M>
void GfItemBoxBase::fn_71002F42F4(ItemBox* box, unsigned int index, ItemTypeInfo* infos,
                                  ::mm::mtl::Array<GfItemInfo*>* lists, GfItemInfo (&items)[N],
                                  GfItemInfo (&extra)[M], unsigned short maxStack, bool multi) {
    ::mm::mtl::Array<GfItemInfo*>& list = lists[index];
    size_t count = multi ? N + M : N;
    list.setAllocator(getAllocator(ALLOCATOR(1)));
    list.reserve(count);
    size_t i = 0;
    for (GfItemInfo& item : items) {
        list[i++] = &item;
    }
    if (multi) {
        for (GfItemInfo& item : extra) {
            list[i++] = &item;
        }
    }
    ItemTypeInfo& info = infos[index];
    info.m_begin = list.begin();
    info.m_end = list.end();
    info.m_maxSlot = count;
    info.m_step = sizeof(GfItemInfo);
    info.m_maxStack = maxStack;
    info.m_multi = multi;
    info.m_serial = &box->m_serials[index];
}

void GfItemBoxBase::fn_71002F3F98(ItemBox* box, SDataGame::ItemBoxEx* extra) {
    m_favoriteItemType = box;
    m_itemBox = extra;
    memset(box, 0, sizeof(ItemBox));
    memset(m_itemBox, 0, sizeof(SDataGame::ItemBoxEx));
    fn_71002F42F4<ItemType::Type(1)>(box, 1, m_info, m_lists, box->m_type1, extra->m_type1, 99, true);
    fn_71002F42F4<ItemType::Type(2)>(box, 2, m_info, m_lists, box->m_type2, extra->m_type2, 1, false);
    fn_71002F42F4<ItemType::Type(3)>(box, 3, m_info, m_lists, box->m_type3, extra->m_type3, 1, false);
    fn_71002F42F4<ItemType::Type(5)>(box, 4, m_info, m_lists, box->m_type5, extra->m_type5, 99, true);
    fn_71002F42F4<ItemType::Type(6)>(box, 5, m_info, m_lists, box->m_type6, extra->m_type6, 99, true);
    fn_71002F42F4<ItemType::Type(7)>(box, 8, m_info, m_lists, box->m_type7, extra->m_type7, 999, true);
    fn_71002F42F4<ItemType::Type(8)>(box, 9, m_info, m_lists, box->m_type8, extra->m_type8, 99, true);
    fn_71002F42F4<ItemType::Type(9)>(box, 10, m_info, m_lists, box->m_type9, extra->m_type9, 99, true);
    fn_71002F42F4<ItemType::Type(10)>(box, 11, m_info, m_lists, box->m_type10, extra->m_type10, 99, true);
    fn_71002F42F4<ItemType::Type(11)>(box, 12, m_info, m_lists, box->m_type11, extra->m_type11, 99, true);
    fn_71002F42F4<ItemType::Type(12)>(box, 13, m_info, m_lists, box->m_type12, extra->m_type12, 99, true);
    fn_71002F42F4<ItemType::Type(14)>(box, 6, m_info, m_lists, box->m_type14, extra->m_type14, 1, true);
    fn_71002F42F4<ItemType::Type(15)>(box, 7, m_info, m_lists, box->m_type15, extra->m_type15, 1, true);
    fn_71002F42F4<ItemType::Type(16)>(box, 14, m_info, m_lists, box->m_type16, extra->m_type16, 1, false);
    fn_71002F42F4<ItemType::Type(17)>(box, 15, m_info, m_lists, box->m_type17, extra->m_type17, 1, false);
    fn_71002F42F4<ItemType::Type(18)>(box, 16, m_info, m_lists, box->m_type18, extra->m_type18, 1, false);
    fn_71002F42F4<ItemType::Type(19)>(box, 17, m_info, m_lists, box->m_type19, extra->m_type19, 1, false);
    fn_71002F42F4<ItemType::Type(20)>(box, 18, m_info, m_lists, box->m_type20, extra->m_type20, 1, false);
}

item_iterator GfItemBoxBase::begin(ItemType::Type type) {
    if (type >= 64) {
        return item_iterator(nullptr, nullptr, 0, false, type);
    }
    ItemTypeInfo& info = getItemTypeInfo(type);
    item_iterator it(this, info.m_begin, info.m_step, info.m_multi, type);
    item_iterator last = end(type);
    for (; it.m_cur != last.m_cur; ++it) {
        GfItemInfo* item = *it.m_cur;
        if (item->m_id == 0 || item->getType() == type) {
            return it;
        }
    }
    return last;
}

bool GfItemBoxBase::isMulti(ItemType::Type type) {
    return getItemTypeInfo(type).m_multi;
}

void GfItemBoxBase::setEquipFlag(unsigned int item, GfItemHandle handle, bool equip) {
    if (item != 0) {
        GfItemInfo* info = findItemHandle(item, handle);
        if (info != nullptr) {
            info->m_equip = equip;
        }
    }
}

GfItemInfo* GfItemBoxBase::findItemHandle(unsigned int item, GfItemHandle handle) {
    ItemType::Type type;
    unsigned int index;
    GfDataItem::getItemType(type, index, item);
    item_iterator it = begin(type);
    item_iterator last = end(type);
    for (; it.m_cur != last.m_cur; ++it) {
        GfItemInfo* info = *it.m_cur;
        if (info->getType() == type && info->m_id == index && info->getHandle().m_handle == handle.m_handle) {
            return info;
        }
    }
    return nullptr;
}

GfItemHandle GfItemInfo::getHandle() const {
    GfItemHandle handle;
    handle.m_handle = m_type;
    handle.m_handle |= m_serial << 6;
    return handle;
}

unsigned int GfItemBoxBase::updateSerialLocal(ItemType::Type type) {
    unsigned int* serial = getItemTypeInfo(type).m_serial;
    unsigned int next = (*serial + 1) & 0x3ffffff;
    next += next == 0;
    *serial = next;
    return next;
}

bool GfItemBoxBase::fn_71002F87F8(ItemType::Type type, unsigned int serial) {
    item_iterator it = begin(type);
    item_iterator last = end(type);
    for (; it.m_cur != last.m_cur; ++it) {
        GfItemInfo* info = *it.m_cur;
        if (info->getIndex() != 0 && (info->getHandle().m_handle >> 6) == serial) {
            return true;
        }
    }
    return false;
}

GfItemInfo* GfItemBoxBase::findItem(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    GfDataItem::getItemType(type, index, item);
    item_iterator it = begin(type);
    item_iterator last = end(type);
    for (; it.m_cur != last.m_cur; ++it) {
        GfItemInfo* info = *it.m_cur;
        if (info->getType() == type && info->m_id == index) {
            return info;
        }
    }
    return nullptr;
}

void GfItemInfo::setType(ItemType::Type type) {
    m_type = type;
}

int GfItemBoxBase::countItem(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    GfDataItem::getItemType(type, index, item);
    item_iterator it = begin(type);
    item_iterator last = end(type);
    int count = 0;
    if (item != 0) {
        for (; it.m_cur != last.m_cur; ++it) {
            GfItemInfo* info = *it.m_cur;
            if (info->m_id != 0 && info->m_id == index && info->getType() == type) {
                count += info->m_count;
            }
        }
    }
    return count;
}

int GfItemBoxBase::fn_71002F9DD4(ItemType::Type type) {
    item_iterator it = begin(type);
    item_iterator last = end(type);
    int count = 0;
    for (; it.m_cur != last.m_cur; ++it) {
        GfItemInfo* item = *it.m_cur;
        if (item->m_id != 0) {
            count += item->m_count;
        }
    }
    return count;
}

int GfItemBoxBase::fn_71002F9F6C(ItemType::Type type) {
    item_iterator it = begin(type);
    return getItemTypeInfo(type).m_end - it.m_cur;
}

unsigned int GfItemBoxBase::getItemTime(unsigned int item) {
    if (item != 0) {
        GfItemInfo* info = findItem(item);
        if (info != nullptr) {
            return info->m_time;
        }
    }
    return 0;
}

unsigned int GfItemBoxBase::getItemTime(unsigned int item, GfItemHandle handle) {
    if (item != 0) {
        GfItemInfo* info = findItemHandle(item, handle);
        if (info != nullptr) {
            return info->m_time;
        }
    }
    return 0;
}

unsigned short GfItemInfo::getItemID() const {
    return GfDataItem::getItemStartID(getType()) + m_id - 1;
}

bool GfItemBox::addItem(unsigned int item, unsigned int count) {
    int have = get()->countItem(item);
    if (GfItemUtil::getEnableStock(item) - have < count) {
        return false;
    }
    GfItemBox* box = get();
    for (unsigned int i = 0; i < count; i++) {
        GfItemHandle handle;
        if (!box->canAddItem(item) || !box->GfItemBoxBase::addItem(item, handle)) {
            return false;
        }
    }
    return true;
}

void GfItemBox::fn_71002FA0F4() {
    get()->fn_71002F3F98(GfDataItem::getFavoriteItemType(), GfDataItem::getItemBox());
}

void GfItemBox::fn_71002FA134() {
    GfItemBox* box = get();
    for (int i = 0; i < 19; i++) {
        box->m_lists[i].clear();
    }
    box->m_itemBox = nullptr;
    box->m_favoriteItemType = nullptr;
}

bool GfItemBox::decItem(unsigned int item, unsigned int count) {
    if (count == 0) {
        return false;
    }
    return get()->GfItemBoxBase::decItem(item, count);
}

bool GfItemBox::decItemForNewGame(unsigned int item, unsigned int count) {
    if (count == 0) {
        return false;
    }
    return get()->GfItemBoxBase::decItem(item, count);
}

}  // namespace gf

namespace gf {
bool GfItemBox::fn_71002FA2B0(unsigned int item, GfItemHandle handle) {
    return get()->fn_71002F9634(item, handle);
}
}  // namespace gf
