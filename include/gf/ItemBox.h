#ifndef GF_ITEMBOX_H
#define GF_ITEMBOX_H

#include "gf/GfItemInfo.h"
#include "mm/mtl/FixedArray.h"

namespace gf {
// the entries of one item type each (2.0.0's symbols name them: gf::setupItemLists and gf::getLowLevelCount take
// FixedArrays of them). Each is a GfItemInfo: setupItemLists stores its entries' addresses in GfItemInfo* lists
// and getLowLevelCount reads their id and count.
struct ItemChip : GfItemInfo {};  // item type 1
struct ItemEquipAcce : GfItemInfo {};  // item type 2
struct ItemEquipOrb : GfItemInfo {};  // item type 3
struct ItemSalvage : GfItemInfo {};  // item type 5
struct ItemPrecious : GfItemInfo {};  // item type 6
struct ItemInfo : GfItemInfo {};  // item type 14
struct ItemEvent : GfItemInfo {};  // item type 15
struct ItemCollection : GfItemInfo {};  // item type 7
struct ItemTreasure : GfItemInfo {};  // item type 8
struct ItemOrb : GfItemInfo {};  // item type 9
struct ItemFavorite : GfItemInfo {};  // item type 10
struct ItemCrystal : GfItemInfo {};  // item type 11
struct ItemBooster : GfItemInfo {};  // item type 12
struct ItemHanaRole : GfItemInfo {};  // item type 16
struct ItemHanaAtr : GfItemInfo {};  // item type 17
struct ItemHanaArts : GfItemInfo {};  // item type 18
struct ItemHanaNArts : GfItemInfo {};  // item type 19
struct ItemHanaAssist : GfItemInfo {};  // item type 20

// the item box: the entries of each item type (SDataGame 0xE98D8, 0x122EC bytes). The name is 1.0.0's: its
// GfItemBoxBase::setItemBox(ItemBox*, bool) clears 0x122EC bytes of it and its GfDataItem::getItemBox() returns
// SDataGame+0xE98D8. ItemCountLowLevel::getCount's offsets and the counts' bounds give each list's place and size;
// the member names are not the original's (by item type).
struct ItemBox {
    mm::mtl::FixedArray<ItemChip, 200> m_type1;
    mm::mtl::FixedArray<ItemEquipAcce, 900> m_type2;
    mm::mtl::FixedArray<ItemEquipOrb, 500> m_type3;
    mm::mtl::FixedArray<ItemSalvage, 200> m_type5;
    mm::mtl::FixedArray<ItemPrecious, 500> m_type6;
    mm::mtl::FixedArray<ItemInfo, 200> m_type14;
    mm::mtl::FixedArray<ItemEvent, 100> m_type15;
    mm::mtl::FixedArray<ItemCollection, 500> m_type7;
    mm::mtl::FixedArray<ItemTreasure, 200> m_type8;
    mm::mtl::FixedArray<ItemOrb, 500> m_type9;
    mm::mtl::FixedArray<ItemFavorite, 500> m_type10;
    mm::mtl::FixedArray<ItemCrystal, 200> m_type11;
    mm::mtl::FixedArray<ItemBooster, 200> m_type12;
    mm::mtl::FixedArray<ItemHanaRole, 200> m_type16;
    mm::mtl::FixedArray<ItemHanaAtr, 200> m_type17;
    mm::mtl::FixedArray<ItemHanaArts, 200> m_type18;
    mm::mtl::FixedArray<ItemHanaNArts, 200> m_type19;
    mm::mtl::FixedArray<ItemHanaAssist, 700> m_type20;
    // one serial counter per ItemTypeInfo (GfItemBoxBase::setItemBox's set-up points each type's m_serial at
    // its own; the name is not the original's)
    unsigned int m_serials[19];
};

// the second entry area of each item type (0x11D27C, 0x1B04 bytes; 2.0.0's symbols name it, as
// ItemCountLowLevel::getCount's argument; ItemCountLowLevel::getCount sums a type's counts over ItemBox's list and
// this one; places and sizes from its offsets and the counts' bounds). The member names are not the original's (by
// item type).
struct ItemBoxEx {
    mm::mtl::FixedArray<ItemChip, 8> m_type1;
    mm::mtl::FixedArray<ItemEquipAcce, 8> m_type2;
    mm::mtl::FixedArray<ItemEquipOrb, 8> m_type3;
    mm::mtl::FixedArray<ItemSalvage, 8> m_type5;
    mm::mtl::FixedArray<ItemPrecious, 200> m_type6;
    mm::mtl::FixedArray<ItemInfo, 50> m_type14;
    mm::mtl::FixedArray<ItemEvent, 8> m_type15;
    mm::mtl::FixedArray<ItemCollection, 200> m_type7;
    mm::mtl::FixedArray<ItemTreasure, 8> m_type8;
    mm::mtl::FixedArray<ItemOrb, 8> m_type9;
    mm::mtl::FixedArray<ItemFavorite, 8> m_type10;
    mm::mtl::FixedArray<ItemCrystal, 8> m_type11;
    mm::mtl::FixedArray<ItemBooster, 8> m_type12;
    mm::mtl::FixedArray<ItemHanaRole, 8> m_type16;
    mm::mtl::FixedArray<ItemHanaAtr, 8> m_type17;
    mm::mtl::FixedArray<ItemHanaArts, 8> m_type18;
    mm::mtl::FixedArray<ItemHanaNArts, 8> m_type19;
    mm::mtl::FixedArray<ItemHanaAssist, 8> m_type20;
    unsigned char pad_1AB8[0x4C];
};
}  // namespace gf

#endif
