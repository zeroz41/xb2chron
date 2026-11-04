#ifndef GF_ITEMCOUNTLOWLEVEL_H
#define GF_ITEMCOUNTLOWLEVEL_H

namespace gf { struct ItemBox; struct ItemBoxEx; }

namespace gf {

// counts an item over the item box's entries (functions; 2.0.0's symbols name the class)
class ItemCountLowLevel {
public:
    // 2.0.0's symbols name it. What it does: GfDataItem::getItemType of item, then by the type (1..0x14, jump table
    // 0x71009B9BCC) getLowLevelCount on the matching parts of the item box (SDataGame::m_itemBox, an ItemBox)
    // and the second entry area (SDataGame::m_itemBoxExtend); 0 for an unknown item. GfGameUtil::isAdvancedGameOption /
    // isAdvancedDifficulity pass items 25495 / 25496 and test it against 0.
    static unsigned int getCount(const ItemBox& box, const ItemBoxEx& boxEx, unsigned int item);
};

// 2.0.0's symbols name it (one instance per item type, those of types 6, 14 and 7 inline in
// ItemCountLowLevel::getCount, its only caller). What it does: the sum of the stack counts of the entries of both
// lists whose id is id.
template <typename List, typename Box>
unsigned int getLowLevelCount(List& list, Box& box, unsigned short id);

}  // namespace gf

#endif
