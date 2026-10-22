#ifndef CLASSES_GF_GFMENUITEMLIST_H
#define CLASSES_GF_GFMENUITEMLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// an item as the menus' item lists hold it (GfMenuItemList::setupFromBox fills one per item; the names are not the
// original's)
class MenuItemInfo {
public:
    // the item box entry's third word (setupFromBox copies it); a copy copies it apart from the rest, so its type
    // has a copy constructor of its own (GfMenuObjCylinderSelect's copy of a list item shows it)
    struct EntryValue {
        EntryValue() : m_value(0) {}
        EntryValue(const EntryValue& other) : m_value(other.m_value) {}
        unsigned int m_value;
    };
    MenuItemInfo() : m_type(0), m_id(0), m_count(0) {}
    unsigned int m_type;     // its ItemType::Type
    unsigned int m_id;       // the item's id
    unsigned short m_count;
    unsigned char pad_A[2];
    EntryValue m_entry;
};

// table 0x7100B5F488
class GfMenuItemList : public ::ui::UIListInfo< ::gf::MenuItemInfo> {
public:
    struct FiltertInfo;
    // what setupFromBox lists: the items of one type in the item box (the names are not the original's)
    struct ItemBoxSetup {
        // inline: its stores are its users' (GfMenuObjCylinderSelect's)
        ItemBoxSetup() : m_filter(nullptr), pad_20(), pad_28(1), pad_29(1), pad_2A(0), pad_2B(0), pad_2C(false) {}
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_type;                     // the items' ItemType::Type
        const FiltertInfo* m_filter;             // its first word's bits pick the filters setupFromBox applies
        unsigned char pad_20[8];
        // one word of byte fields (stored as one): setupFromBox reads 0x29, and 0x2A-0x2B as a 16-bit pair
        unsigned int pad_28 : 8;
        unsigned int pad_29 : 8;
        unsigned int pad_2A : 8;
        unsigned int pad_2B : 8;
        bool pad_2C;
    };
    virtual ~GfMenuItemList();  // slot 0
    static GfMenuItemList* create();  // with a reference for the caller
    void setupFromBox(const ItemBoxSetup& setup);
    void decItem(const MenuItemInfo& item, bool);
    void sort(unsigned int order, bool);
};
}  // namespace gf

#endif
