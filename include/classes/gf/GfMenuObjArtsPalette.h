#ifndef CLASSES_GF_GFMENUOBJARTSPALETTE_H
#define CLASSES_GF_GFMENUOBJARTSPALETTE_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B5FAF8; the battle's arts palette (three arts slots and the blade's element), attached under 0x27
class GfMenuObjArtsPalette : public ::gf::GfMenuObject {
public:
    GfMenuObjArtsPalette(unsigned int handle);
    static void reverse(bool reverse);
    // 1.0.0 symbol (GfMenuReference::setReversePaletteBtnState calls it with the slot; the parameter name is not
    // the original's)
    static void pushReverseBtn(unsigned int slot);  // 1.0.0 symbol (GfMenuReference::setPaletteModeReverse calls it)
    // btl::UIManager::NotifyInput passes its second argument on (the parameter name is not the original's)
    static void push(unsigned int slot);
    // what GfMenuObjChainAttack::openStatus and closeStatus call when a chain attack's status opens and closes
    static void startChainAttack();
    static void exitChainAttack();
    // its open (0x100) and close (0x101) events
    static void open();
    static void close();
    // the arts icons' controls for the palette's normal (reverse false) or reverse side: mode 0 runs them in the
    // menu parameters' time, 1 in 0.1 seconds, others at once; the last icon's control slot (parameter names
    // are not the original's)
    int ctrlPalletteDisp(bool reverse, unsigned int mode);
    // an arts slot's icon in white once its arts is ready and usable (slot flags 1 and 2), gray otherwise: inline
    // in MainListener::reciveEvent, whose frame has its locals first (the name is not the original's)
    void updateIconColor(unsigned int slot) {
        ::mm::mtl::FixStr<32> name;
        name.format("LAY_arts_icon@%02d", slot + 1);
        ::ui::UIObjectAcc icon(m_handle, name.m_str);
        if ((m_slotFlags[slot] & 3) == 3) {
            icon.setMulColor("white");
        } else {
            icon.setMulColor("gray");
        }
    }
    class MainListener;
    class ReverseListener;
    virtual ~GfMenuObjArtsPalette();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // the names of the fields are not the original's: per arts slot, the control the listener started on it
    // (-1: none; stopped before it starts another) and its state bits (1: ready, 2: usable, 4: play its select
    // animation)
    int m_ctrlIds[3];
    unsigned int m_slotFlags[3];
    unsigned char pad_3C[4];
    GfMenuSequence<GfMenuObjArtsPalette, 8> m_slotSeq0;
    GfMenuSequence<GfMenuObjArtsPalette, 8> m_slotSeq1;
    GfMenuSequence<GfMenuObjArtsPalette, 8> m_slotSeq2;
    GfMenuSequence<GfMenuObjArtsPalette, 8>* m_slotSeqs[3];  // the three above, by slot
    GfMenuSequence<GfMenuObjArtsPalette, 4> m_elemSeq;       // the element range icon's animations
};
}  // namespace gf

#endif
