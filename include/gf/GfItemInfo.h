#ifndef GF_GFITEMINFO_H
#define GF_GFITEMINFO_H

#include "gf/GfMenuItemUtil.h"

// (moved from classes/gf/GfItemBox.h unchanged, so that gf/ItemBox.h and SDataGame.h can hold item entries
// without the item box class, which itself refers to SDataGame)
namespace gf {
// a handle to one item box entry (1.0.0's symbols take it by value; 3.0.1's callers pass a copy by address, so it
// is not trivially copyable). The field name is not the original's.
struct GfItemHandle {
    GfItemHandle() : m_handle(0) {}
    GfItemHandle(const GfItemHandle& other) : m_handle(other.m_handle) {}
    unsigned int m_handle;
};

// one item box entry (1.0.0's symbols: GfItemInfo, 12 bytes: its constructor zeroes 8 bytes then 4). The id is the
// index in the type's BDAT range (getItemID adds getItemStartID - 1). Field names are not the original's.
struct GfItemInfo {
    ItemType::Type getType() const { return static_cast<ItemType::Type>(m_type); }
    GfItemHandle getHandle() const;
    unsigned short getItemID() const;
    void setType(ItemType::Type type);
    // the id field (the index in the type's BDAT range, as GfDataItem::getItemType hands it out); inline, as
    // GfDataManager::fn_7100223974's 16-bit compare of it proves. The name is not the original's.
    unsigned short getIndex() const { return m_id; }

    unsigned int m_id : 13;
    unsigned int m_type : 6;
    unsigned int m_count : 10;  // the stack count (GfItemBoxBase::fn_71002F9DD4 sums it)
    unsigned int pad_0_29 : 1;
    unsigned int m_equip : 1;  // setEquipFlag
    unsigned int pad_0_31 : 1;
    unsigned int m_time;  // getItemTime
    unsigned int m_serial;  // the handle's bits 6-31 (getHandle)
};
}  // namespace gf

#endif
