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
class TUnk_B638F8 : public ::gf::GfMenuObject {
public:
    TUnk_B638F8(unsigned int handle);
    virtual ~TUnk_B638F8();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in this
    // class's unit and it fills m_list. What it does: clears m_list, then adds each row of the named enemy table
    // (0x2A, 0x2B when GfGameManager::fn_71002A9E68) whose enemy has a resource, is named, has the difficulty's
    // record flag (fn_71002ED5B0), no blade and lies in the selected zone (all for zone 0); the entry's second id is
    // the zone (8 shown as 6). Sorts the list with fn_7100446BA4 and selects its first entry.
    void fn_7100445F58();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member (this unused: its callers leave
    // x0 undefined) for the same reasons. What it does: the index of zone in the filter's zone table; with
    // GfMenuObjUtil::fn_710048FD30(3), 0 for zone 0, 1 for 0x35, 11 for 0x34; -1 otherwise. initialize shows it as
    // a filter icon's image index.
    unsigned int fn_7100446240(unsigned int zone);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reasons. What it
    // does: shows m_difficulty's name (message list 0x169) in TXT_difficulty_index and starts its animation on
    // IMG_difficulty_base (TUnk_B606F0::fn_71003AE838's twin).
    void fn_7100446374();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reasons. What it
    // does: colours the filter icon of m_zoneIndex "sys_select" and the others their default colour.
    void fn_7100446AC8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because fn_7100445F58
    // hands it to the sort (GfMenuIDList::fn_710037212C) and it sits in this class's unit. What it does: orders
    // by the enemies' level (GfBdatChrEnArrange::getChrEnArrangeLv) ascending, then by row ascending.
    static bool fn_7100446BA4(const MenuID& a, const MenuID& b);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because its address lies
    // in this class's unit (no this). What it does: fn_71002ED5B0 of the row's "EnemyID" in the named enemy table
    // with GfGameManager::fn_71002AC57C(); false without the table. TUnk_B638A8::reciveEvent calls it.
    static bool fn_7100446C54(unsigned int row);

    unsigned char pad_24[4];
    GfMenuIDList* m_list;                // 0x28 the named enemies listed (the name is not the original's)
    ui::UISelectObjList* m_select;       // 0x30 initialize creates it (the name is not the original's)
    ui::UICtrlCursorSelect* m_cursor;    // 0x38 initialize creates it on m_select (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 12> m_zones;  // 0x40 the filter's zones, 0 first (the name is not the original's)
    unsigned int m_zoneIndex;            // 0x78 the selected filter zone's index (the name is not the original's)
    unsigned int pad_7C;
    int m_difficulty;                    // 0x80 as TUnk_B606F0's (the name is not the original's)
    int m_difficultyCount;               // 0x84 GfMenuObjOption::fn_7100452B84 (the name is not the original's)
};

// table 0x7100B63940: TUnk_B638F8's list listener (nothing names the class yet)
class TUnk_B63940 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table, as other menus' listeners do
    TUnk_B63940(TUnk_B638F8* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B63940() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    TUnk_B638F8* m_owner;  // what initialize makes it for
};

// table 0x7100B63968: TUnk_B638F8's zone filter listener (nothing names the class yet)
class TUnk_B63968 : public ::ui::UIObjectListener {
public:
    TUnk_B63968(TUnk_B638F8* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B63968() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    TUnk_B638F8* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
