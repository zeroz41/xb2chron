#ifndef CLASSES_GF_TUNK_B60E28_H
#define CLASSES_GF_TUNK_B60E28_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GfMenuArtsList; }

namespace gf {
// table 0x7100B60E28: the menu object of gf_menu_obj_char_change.cpp (new in 3.0.1, no RTTI; nothing names the class
// yet). GfMenuManager::reciveEvent makes it; its static functions drive the object attached under 0x3C (the one
// GfMenuObjBladeChange's static functions drive too) and work only while GfMenuObjUtil::isValidExpansion(3) holds
class GfMenuObjCharChange : public ::gf::GfMenuObject {
public:
    GfMenuObjCharChange(unsigned int handle);
    virtual ~GfMenuObjCharChange();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name them. Each sends an event to that object while it is there (and, except reverse and
    // updateOperation, not terminated), only while GfMenuObjUtil::isValidExpansion(3) holds: open: event 0x108; close:
    // event 0x109 (both from GfMenuManager::gevPlayerControl); changeFormation: event 0x10A; changeBlade: event 0x10B
    // (both from GfMenuManager::gevChangeParty and fn_7100367D6C); reverse: event 0x106 with the flag as its first
    // parameter (from setIraOperationDisp); updateOperation: event 0x107 with the value as its first parameter, to the
    // object's child "LAY_cmd" (from GfMenuReference::postUpdate and MainListener::reciveEvent).
    static void open();
    static void close();
    // 2.0.0's symbols name it. What it does: shows or hides that object while it is there and not terminated (no
    // isValidExpansion test). Caller: GfMenuManager::updateHudState.
    static void disp(bool disp);
    static void changeFormation();
    static void changeBlade();
    static void reverse(bool flag);
    static void updateOperation(GfMenuReference::IRA_OPERATION_BTN value);
    // 2.0.0's symbols name it. What it does: sends event 0x10F with the flag as its first parameter to the object
    // attached under 0x3C while it is there and not terminated. Caller: GfMenuObjBladeChange::dispInfo (when
    // GfMenuObjUtil::isValidExpansion(3) holds).
    static void dispInfo(bool disp);
    // 2.0.0's symbols name it. What it does: shows or hides LAY_main's LAY_info and its four LAY_char2_*_elem_root@0N
    // children, and LAY_chain's LAY_chain_info. Caller: MainListener::reciveEvent (0x71003C56C0).
    void dispInfoLocal(bool disp);
    // 2.0.0's symbols name it (the bool is unused). What it does: for chain member index (when LAY_chain has that many
    // LAY_chain@NN), hides IMG_chain_recast@NN and colours IMG_chain_face@NN white when m_chainFlags[index] has bit 2,
    // else shows the recast and colours the face gray. Caller: ChainListener::reciveEvent (0x71003C6EBC).
    void updateChainRecast(unsigned int index, bool);
    // 2.0.0's symbols name them. updateFace refreshes LAY_char2 for a bool mode (false from startFormationChange, true
    // from startBladeChange). updateRecast: for character index (0 or 1, LAY_main's IMG_char2_recast@NN there), shows
    // the recast and colours the faces by m_charFlags[index] (caller: MainListener::reciveEvent). startFormationChange:
    // refreshes with false and, unless pad_1C0, slides LAY_char2@01/@02 apart by the distance between LAY_char2's
    // active_up and active_down rectangles. startBladeChange: refreshes with true and moves
    // LAY_char2_active@NN/LAY_char2_reserve@NN of each blade-owning driver 0/1 (callers: MainListener::reciveEvent).
    void updateFace(bool mode);
    void updateRecast(unsigned int index);
    void startFormationChange();
    void startBladeChange();

    unsigned int pad_24;  // -1 from the constructor
    bool pad_28;
    bool pad_29;
    bool pad_2A;          // true from the constructor
    unsigned char pad_2B[5];
    GfMenuSequence<GfMenuObjCharChange, 4> m_seq;  // 0x30
    // the two characters' flags (LAY_char2 @01/@02): updateRecast shows character N's recast with bit 1 clear and
    // plays its "select" animation once with bit 2 (then clears bit 2); the name is not the original's
    unsigned int m_charFlags[3];
    // the chain's members' flags: updateChainRecast shows member N's recast lit with bit 2 (value-initialized with
    // m_charFlags: the constructor zeroes 0x190-0x1AF; the name is not the original's)
    unsigned int m_chainFlags[3];
    unsigned int pad_1A8;
    unsigned int pad_1AC;
    unsigned int pad_1B0;  // startBladeChange moves the active/reserve rows only while it is not 0
    // what update last gave GfMenuReference::setIraFlag for bits 0 and 1 (the party's second and third
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
