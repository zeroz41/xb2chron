#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/Vec3.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B61760: the buff, debuff and combo names over a character (copies of LAY_buff_root) and the unite combo
// names (copies of LAY_unite_root); their open objects are GfMenuManyObjects' kind 1
class GfMenuObjDamageBuff : public ::gf::GfMenuObject {
public:
    class DamageInfo;
    class ListListener;
    // what openUniteCombo is given (btl::UIManager::DispUniteComboUI fills it; the field names are not the
    // original's): the two values go out as the opened object's event parameters, the position to its
    // GfMenuFieldPosAdapter
    struct OpenUniteParam {
        int m_eventParam0;
        int m_eventParam1;
        unsigned char pad_8[0x8];
        mm::Vec3 m_pos;
    };
    // what open shows (1.0.0's open(OpenParam const&) names the type; btl::UIManager::DispBuffUI fills it; the field
    // names are not the original's)
    struct OpenParam {
        int m_type;  // the background's colour: 0 dmg_buff, 1 dmg_debuff, 2 dmg_combo (white past them)
        bool m_resist;  // shows TXT_resist's first text (DispBuffUI passes its flag)
        bool m_resist2;  // shows TXT_resist's second text, before m_resist
        const char* m_text;  // the name as a text, when there is no message table entry
        unsigned char* m_bdat;  // the message table of the name
        int m_nameId;  // the name's id in m_bdat
        int m_icon;  // passed on in the open event's last parameter (DispBuffUI's Icon)
        mm::Vec3 m_pos;  // where the name shows (a GfMenuFieldPosAdapter)
    };
    GfMenuObjDamageBuff(unsigned int handle);
    virtual ~GfMenuObjDamageBuff();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // a name screen of that param on a LAY_buff_root copy, its object queued (1.0.0 symbol; the same callees at nearly
    // the same size in 3.0.1): the copy's handle, or 0 when none opens
    static unsigned int open(const OpenParam& param);
    // the screen off kind 1's queue and terminated (1.0.0 symbol; inline here, the original's calls are inlined)
    static void removeObject(ui::UIObjectAcc screen);
    // shows the name text, the resist text and the background's colour (the parameter names are not the original's;
    // the fifth is unused)
    static void setupScreen(unsigned int handle, int type, int resist, int text, int unused);
    // fits IMG_bg over LAY_buff_item (1.0.0 symbol; inline here: 3.0.1 has no copy, open has its code)
    static void setupPlugin(unsigned int handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's callers of open call it in 3.0.1).
    // A member because it fills this class's file-static queue of opens that update hands to open. What it does:
    // pushes a copy of the param on that queue of 32, dropping the oldest when it is full; answers 0.
    static unsigned int fn_71003E537C(const OpenParam& param);
    static void close(unsigned int handle);  // fades that copy out (event 0x22)
    static unsigned int openUniteCombo(const OpenUniteParam& param);
    static void closeUniteCombo(unsigned int handle);  // fades that unite copy out (event 0x101)
    static void closeAll();  // GfMenuManager::gevSalvageStateChange(6) calls it (1.0.0 symbol)
    // the opens fn_71003E537C queues for update to hand to open, each update (a global: its code loads it through the
    // GOT; 2.0.0's symbols name it)
    static mm::mtl::FixedQueue<OpenParam, 32> s_queue;
};
}  // namespace gf

#endif
