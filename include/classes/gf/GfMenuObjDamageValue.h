#ifndef CLASSES_GF_GFMENUOBJDAMAGEVALUE_H
#define CLASSES_GF_GFMENUOBJDAMAGEVALUE_H

#include "classes/gf/GfMenuObject.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedQueue.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B61808: the damage, heal, miss, evade and level up numbers over a character, on copies of
// LAY_damage_root; open objects are GfMenuManyObjects' kind 0
class GfMenuObjDamageValue : public ::gf::GfMenuObject {
public:
    class DamageInfo;
    class ListListener;
    // what open shows (1.0.0's open(OpenParam const&) names the type; the field names are not the original's)
    struct OpenParam {
        int m_type;  // 0 damage, 1 heal, 2 miss, 3 spike damage, 4 damage over time, 5 evade, 6 level up
        int m_value;  // the number shown
        int m_target;  // whose: damage 2 the player's, 1 the party's, else an enemy's; heal 0 an enemy's
        int m_level;  // 0-3: how much larger the number shows (its event flags' bits 3-4)
        bool m_large;  // the number at its larger scale (event flag bit 0)
        bool m_flag1;  // event flag bit 1: a longer move when it opens (the name is not the original's)
        bool m_special;  // event flag bit 2: shows IMG_spbg (the name is not the original's)
        mm::Vec3 m_pos;  // where it shows, for its GfMenuFieldPosAdapter
    };
    GfMenuObjDamageValue(unsigned int handle);
    virtual ~GfMenuObjDamageValue();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // a LAY_damage_root copy of that param at its position, its object queued (the oldest closes past 32): the copy's
    // handle, or 0 when none opens (1.0.0's open, 0x7100445578: the same code but for the check of a free text index)
    static unsigned int open(const OpenParam& param);
    // shows the type's text on a LAY_damage_root copy (the parameter names are not the original's): the registered
    // text's id, whose (OpenParam::m_target) and the open event's flags
    static void setupScreen(unsigned int handle, int type, int text, int target, int flags);
    // the screen off kind 0's queue and terminated (1.0.0 symbol; inline here, the original's calls are inlined)
    static void removeObject(ui::UIObjectAcc screen);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it fills this class's
    // queue of opens that update hands to open, and 1.0.0's callers of open (btl::BattleCharacter's
    // AttackTimingRactProc and NotifyDamage, GfComProperty's procMsgObjectDamage and procMsgObjectHealHp) call it in
    // 3.0.1. What it does: pushes a copy of the param on that queue of 32, dropping the oldest when it is full;
    // answers 0 (no screen yet, where open answers the copy's handle).
    static unsigned int fn_71003E7394(const OpenParam& param);
    static void close(unsigned int handle);  // fades that copy out (event 0x22)
    static void closeAll();  // GfMenuManager::gevSalvageStateChange(6) calls it (1.0.0 symbol)
    // the opens fn_71003E7394 queues for update to hand to open, each update (a global: its code loads it through
    // the GOT; 2.0.0's symbols name it)
    static mm::mtl::FixedQueue<OpenParam, 32> s_queue;
};
}  // namespace gf

#endif
