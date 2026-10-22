#ifndef CLASSES_GF_GFMENUOBJELEMENTEFF_H
#define CLASSES_GF_GFMENUOBJELEMENTEFF_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B61C60
class GfMenuObjElementEff : public ::gf::GfMenuObject {
public:
    class MainListener;
    // what start is given (btl::UIManager::StartElementalComboDirectionUI passes its int)
    struct StartParam {
        int m_combo;  // the elemental combo to show; the name is not the original's
    };
    GfMenuObjElementEff(unsigned int handle);
    virtual ~GfMenuObjElementEff();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqInit();
    bool seqOpen();
    bool seqComboName();
    bool seqLoop();
    bool seqClose();
    // the elemental combo's call context (attached under 0x17): start it and open the combo, close it
    static void start(GfMenuCallContext* context, const StartParam& param);
    static void cancel(GfMenuCallContext* context);
    GfMenuSequence<GfMenuObjElementEff, 8> m_seq;
    // -1 when nothing is running: seqClose's control (the slot startCtrl returned), seqComboName's countdown
    // started (0); the name is not the original's
    int m_ctrl;
    int m_combo;  // the open event's: the combo shown (the name is not the original's)
    int m_wait;   // seqComboName's frames left before the name fades out (the name is not the original's)
};
}  // namespace gf

#endif
