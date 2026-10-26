#ifndef CLASSES_GF_GFMENUOBJBLADECHANGE_H
#define CLASSES_GF_GFMENUOBJBLADECHANGE_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuSequence.h"
#include "ui/EventData.h"

namespace gf {
// table 0x7100B5FE78
class GfMenuObjBladeChange : public ::gf::GfMenuObject {
public:
    // a blade's slot of the panel: the owner's constructor value-initializes them (zeroing, then -1 and 0: default
    // member initializers, no user constructor); updateFace reads flag bits 1 and 2 (the names are not the original's)
    struct Slot {
        unsigned int m_handle = -1;
        unsigned int m_flags = 0;
    };

    GfMenuObjBladeChange(unsigned int handle);
    // what GfMenuObjChainAttack::openStatus (with its context) and closeStatus call
    static void startChainAttack(GfMenuCallContext* context);
    static void exitChainAttack();
    // btl::UIManager::NotifyInput passes 0, 1, 3 or its second argument (the parameter name is not the original's)
    static void pushBladeChange(unsigned int index);
    static void open();
    static void close();
    static void dispInfo(bool disp);
    static void enableAwakening(bool enable);
    static void pushGroupUp();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it drives the object
    // attached at 0x3C (the one the class's open/close/push functions drive) and reads the flag
    // fn_710039232C/fn_71003923CC keep. What it does: sends event 0x105 to the attached object's sibling
    // "LAY_dr_solo" while that flag is set, else to the attached object itself. Callers: BladeListener::reciveEvent,
    // TUnk_B5FEE8::reciveEvent, fn_7100367454 and fn_71003C56C0.
    static void fn_7100391CDC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it drives the object
    // attached at 0x3C. What it does: sends event 0x21 (open) to the attached object's sibling "LAY_dr_solo" and
    // sets s_soloOpen. Caller: fn_7100359144.
    static void fn_710039232C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it drives the object
    // attached at 0x3C. What it does: sends event 0x22 (close) to the attached object's sibling "LAY_dr_solo" and
    // clears s_soloOpen. Caller: fn_7100359144.
    static void fn_71003923CC();
    void ctrlAwakening(bool awake);
    void ctrlHomuri(bool on);
    void updateFace(unsigned int index);
    class BladeListener;
    virtual ~GfMenuObjBladeChange();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EA7170). Whether "LAY_dr_solo" is
    // open: fn_710039232C sets it, fn_71003923CC clears it, fn_7100391CDC reads it (through the GOT: not file-static)
    static bool s_soloOpen;

    unsigned int m_ctrlSlot;   // 0x24: ctrlAwakening's control slot
    unsigned int pad_28;       // -1 from the constructor
    bool m_awakeMoved;         // 0x2C: ctrlAwakening moves only without it (the name is not the original's)
    bool pad_2D;
    bool pad_2E;               // updateFace reads it with a slot's flag bit 2
    bool m_seqActive;          // 0x2F: update runs the sequence only with it
    Slot m_slots[3];           // 0x30
    unsigned int pad_48;       // the constructor sets 0x48-0x54 to -1, 0x50-0x54 as one 8-byte store after the
    unsigned int pad_4C;       // sequence (an array its body fills)
    unsigned int pad_50[2];
    GfMenuSequence<GfMenuObjBladeChange, 4> m_seq;  // 0x58
};
}  // namespace gf

#endif
