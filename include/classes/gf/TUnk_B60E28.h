#ifndef CLASSES_GF_TUNK_B60E28_H
#define CLASSES_GF_TUNK_B60E28_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GfMenuArtsList; }

namespace gf {
// table 0x7100B60E28: the menu object of gf_menu_obj_char_change.cpp (new in 3.0.1, no RTTI; nothing names the class
// yet). GfMenuManager::reciveEvent makes it; its static functions drive the object attached under 0x3C (the one
// GfMenuObjBladeChange's static functions drive too) and work only while GfMenuObjUtil::fn_710048FD30(3) holds
class TUnk_B60E28 : public ::gf::GfMenuObject {
public:
    TUnk_B60E28(unsigned int handle);
    virtual ~TUnk_B60E28();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they act on the object
    // attached under 0x3C, as this unit's code does. Each sends an event to that object while it is there (and,
    // except fn_71003C3550 and fn_71003C35C8, not terminated), only while GfMenuObjUtil::fn_710048FD30(3) holds:
    // fn_71003C32F8: event 0x108; fn_71003C3368: event 0x109 (both from GfMenuManager::gevPlayerControl);
    // fn_71003C3470: event 0x10A; fn_71003C34E0: event 0x10B (both from GfMenuManager::gevChangeParty and
    // fn_7100367D6C); fn_71003C3550: event 0x106 with the flag as its first parameter (from fn_710036810C);
    // fn_71003C35C8: event 0x107 with the value as its first parameter, to the object's child "LAY_cmd" (from
    // GfMenuReference::postUpdate and fn_71003C56C0).
    static void fn_71003C32F8();
    static void fn_71003C3368();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it acts on the object
    // attached under 0x3C. What it does: shows or hides that object while it is there and not terminated (no
    // fn_710048FD30 test). Caller: fn_7100359144.
    static void fn_71003C33D8(bool disp);
    static void fn_71003C3470();
    static void fn_71003C34E0();
    static void fn_71003C3550(bool flag);
    static void fn_71003C35C8(unsigned int value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member of this class (not
    // GfMenuObjBladeChange's): its code sits in this unit (gf_menu_obj_char_change.cpp's assertions), among this
    // class's other static functions of the same shape. What it does: sends event 0x10F with the flag as its first
    // parameter to the object attached under 0x3C while it is there and not terminated. Caller:
    // GfMenuObjBladeChange::dispInfo (when GfMenuObjUtil::fn_710048FD30(3) holds).
    static void fn_71003C3648(bool disp);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. What it does: shows or hides LAY_main's
    // LAY_info and its four LAY_char2_*_elem_root@0N children, and LAY_chain's LAY_chain_info. Caller: fn_71003C56C0.
    void fn_71003C55E0(bool disp);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. What it does: for chain member index (when
    // LAY_chain has that many LAY_chain@NN), hides IMG_chain_recast@NN and colours IMG_chain_face@NN white when
    // m_chainFlags[index] has bit 2, else shows the recast and colours the face gray. Caller: fn_71003C6EBC.
    void fn_71003C5164(unsigned int index);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. fn_71003C4450 refreshes LAY_char2 for
    // a bool mode (false from fn_71003C5278, true from fn_71003C5408). fn_71003C4DFC: for character index (0 or 1,
    // LAY_main's IMG_char2_recast@NN there), shows the recast and colours the faces by m_charFlags[index] (caller:
    // fn_71003C56C0). fn_71003C5278: refreshes with false and, unless pad_1C0, slides LAY_char2@01/@02 apart by the
    // distance between LAY_char2's active_up and active_down rectangles. fn_71003C5408: refreshes with true and
    // moves LAY_char2_active@NN/LAY_char2_reserve@NN of each blade-owning driver 0/1 (callers: fn_71003C56C0).
    void fn_71003C4450(bool mode);
    void fn_71003C4DFC(unsigned int index);
    void fn_71003C5278();
    void fn_71003C5408();

    unsigned int pad_24;  // -1 from the constructor
    bool pad_28;
    bool pad_29;
    bool pad_2A;          // true from the constructor
    unsigned char pad_2B[5];
    GfMenuSequence<TUnk_B60E28, 4> m_seq;  // 0x30
    // the two characters' flags (LAY_char2 @01/@02): fn_71003C4DFC shows character N's recast with bit 1 clear and
    // plays its "select" animation once with bit 2 (then clears bit 2); the name is not the original's
    unsigned int m_charFlags[3];
    // the chain's members' flags: fn_71003C5164 shows member N's recast lit with bit 2 (value-initialized with
    // m_charFlags: the constructor zeroes 0x190-0x1AF; the name is not the original's)
    unsigned int m_chainFlags[3];
    unsigned int pad_1A8;
    unsigned int pad_1AC;
    unsigned int pad_1B0;  // fn_71003C5408 moves the active/reserve rows only while it is not 0
    // what update last gave GfMenuReference::fn_7100368380 for bits 0 and 1 (the party's second and third
    // characters shown while pad_1B8 is -1)
    bool pad_1B4;
    bool pad_1B5;
    unsigned char pad_1B6[2];
    unsigned int pad_1B8;  // -1 from the constructor; update sets it back to -1 once GfReqManager::isValid fails
    bool pad_1BC;  // update: GfGameManager::isBattle() as last sent (event 0x10E to LAY_main)
    bool pad_1BD;  // update: GfMenuManager::isBattleState(0) as last sent (event 0x110 to LAY_main), outside battle
    bool pad_1BE;
    bool pad_1BF;
    bool pad_1C0;
    GfMenuArtsList* m_artsList;  // 0x1C8: made by the constructor (two rows, one column), released by the destructor
};
}  // namespace gf

#endif
