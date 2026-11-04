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
    // 2.0.0's symbols name it. What it does: sends event 0x105 to the attached object's sibling "LAY_dr_solo" while
    // that flag is set, else to the attached object itself. Callers: BladeListener::reciveEvent,
    // DrSoloListener::reciveEvent, setBattleMode and GfMenuObjCharChange::MainListener::reciveEvent.
    static void refreshBattleMode();
    // 2.0.0's symbols name it. What it does: sends event 0x21 (open) to the attached object's sibling "LAY_dr_solo" and
    // sets s_DrSolo. Caller: GfMenuManager::updateHudState.
    static void openDrSolo();
    // 2.0.0's symbols name it. What it does: sends event 0x22 (close) to the attached object's sibling "LAY_dr_solo"
    // and clears s_DrSolo. Caller: GfMenuManager::updateHudState.
    static void closeDrSolo();
    void ctrlAwakening(bool awake);
    void ctrlHomuri(bool on);
    void updateFace(unsigned int index);
    class BladeListener;
    class DrSoloListener;  // GfMenuObjBladeChange/DrSoloListener.h
    virtual ~GfMenuObjBladeChange();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name it. Whether "LAY_dr_solo" is open: openDrSolo sets it, closeDrSolo clears it,
    // refreshBattleMode reads it (through the GOT: not file-static)
    static bool s_DrSolo;

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
