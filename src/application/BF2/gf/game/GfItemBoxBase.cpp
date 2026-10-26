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
