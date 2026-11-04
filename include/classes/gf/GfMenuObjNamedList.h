#ifndef CLASSES_GF_TUNK_B638F8_H
#define CLASSES_GF_TUNK_B638F8_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuIDList; class MenuID; }
namespace ui { class UICtrlCursorSelect; class UISelectObjList; struct EventData; }

namespace gf {
// table 0x7100B638F8: the menu object of gf_menu_obj_named_list.cpp (new in 3.0.1; nothing names the class yet).
// It lists the named enemies ("EnemyID" of the named enemy table, GfDataEnemy::isNamed) with their name, level, area
// and record time, filtered by zone (the "LAY_list_filter" icons) and by difficulty (TXT_difficulty_index)
class GfMenuObjNamedList : public ::gf::GfMenuObject {
public:
    class ListListener;
    class FilterListener;
    GfMenuObjNamedList(unsigned int handle);
    virtual ~GfMenuObjNamedList();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: clears m_list, then adds each row of the named enemy table (0x2A, 0x2B
    // when GfGameManager::isGameTypeIra) whose enemy has a resource, is named, has the difficulty's record flag
    // (GfGameUtil::isDefeatNamed), no blade and lies in the selected zone (all for zone 0); the entry's second id is the zone (8
    // shown as 6). Sorts the list with sortLevel and selects its first entry.
    void updateNamedIDList();
    // 2.0.0's symbols name it. What it does: the index of zone in the filter's zone table; with
    // GfMenuObjUtil::isValidExpansion(3), 0 for zone 0, 1 for 0x35, 11 for 0x34; -1 otherwise. initialize shows it as a
    // filter icon's image index.
    unsigned int convZoneToFilter(unsigned int zone);
    // 2.0.0's symbols name it. What it does: shows m_difficulty's name (message list 0x169) in TXT_difficulty_index and
    // starts its animation on IMG_difficulty_base (GfMenuObjBtlchOrder::refreshDifficulty's twin).
    void refreshDifficulty();
    // 2.0.0's symbols name it. What it does: colours the filter icon of m_zoneIndex "sys_select" and the others their
    // default colour.
    void refreshFilterIcon();
    // 2.0.0's symbols name it. What it does: orders by the enemies' level (GfBdatChrEnArrange::getChrEnArrangeLv)
    // ascending, then by row ascending.
    static bool sortLevel(const MenuID& a, const MenuID& b);
    // 2.0.0's symbols name it. What it does: GfGameUtil::isDefeatNamed of the row's "EnemyID" in the named enemy table with
    // GfGameManager::getBtlDifficult(); false without the table. TUnk_B638A8::reciveEvent calls it.
    static bool isDefeated(unsigned int row);

    unsigned char pad_24[4];
    GfMenuIDList* m_list;                // 0x28 the named enemies listed (the name is not the original's)
    ui::UISelectObjList* m_select;       // 0x30 initialize creates it (the name is not the original's)
    ui::UICtrlCursorSelect* m_cursor;    // 0x38 initialize creates it on m_select (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 12> m_zones;  // 0x40 the filter's zones, 0 first (the name is not the original's)
    unsigned int m_zoneIndex;            // 0x78 the selected filter zone's index (the name is not the original's)
    unsigned int pad_7C;
    int m_difficulty;                    // 0x80 as GfMenuObjBtlchOrder's (the name is not the original's)
    int m_difficultyCount;               // 0x84 GfMenuObjOption::getDifficultyMax (the name is not the original's)
};

// table 0x7100B63940: GfMenuObjNamedList's list listener (2.0.0's symbols name it)
class GfMenuObjNamedList::ListListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table, as other menus' listeners do
    ListListener(GfMenuObjNamedList* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjNamedList* m_owner;  // what initialize makes it for
};

// table 0x7100B63968: GfMenuObjNamedList's zone filter listener (2.0.0's symbols name it)
class GfMenuObjNamedList::FilterListener : public ::ui::UIObjectListener {
public:
    FilterListener(GfMenuObjNamedList* owner) : pad_0C(), m_owner(owner) {}
    virtual ~FilterListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjNamedList* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
