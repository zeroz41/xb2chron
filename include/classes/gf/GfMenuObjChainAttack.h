#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/IUIInputSelectionChecker.h"

namespace gf {
class GfMenuCallContext;

// table 0x7100B60BC0; the chain attack's HUD (attached object 0x54: LAY_start, LAY_status, LAY_result, LAY_full_burst,
// LAY_extend, LAY_ovk_start, LAY_turn_sel). The checker base at 0x28 is ui::IUIInputSelectionChecker (table
// 0x7100B60C10: offset -0x28, its slot 0 the isEnableSelect thunk).
class GfMenuObjChainAttack : public ::gf::GfMenuObject, public ui::IUIInputSelectionChecker {
public:
    class ExtendListener;
    class FullBurstListener;
    class ResultListener;
    class StartListener;
    class StatusListener;

    // what openResult sends LAY_result with its open event (0x21): the byte as the event's 16-bit first parameter,
    // the int as its second (what they hold is not known yet)
    struct ResultParam {
        unsigned char pad_0;
        int pad_4;
    };

    GfMenuObjChainAttack(unsigned int handle);
    virtual ~GfMenuObjChainAttack();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // a selection of LAY_turn_sel can be chosen when its reference number is 0; any other layer's always
    virtual bool isEnableSelect(unsigned int id, int select);  // slot 7

    static void openStart(GfMenuCallContext* context);
    static void openStatus(GfMenuCallContext* context);
    static void closeStatus();
    static void openResult(const ResultParam& param);
    static void closeResult();
    static void openFullBurst(GfMenuCallContext* context);
    static void openRoundExtend();
    static void closeRoundExtend();
    static void changeCharacter(unsigned int character);
    // 2.0.0's symbols name it. What it does: sends LAY_ovk_start the open event (0x21), then, given a context that has
    // not started (GfMenuObjUtil::checkCCStart), starts it on object 0x54 with LAY_ovk_start's handle. No code or data
    // reference to it in the module.
    static void openOverkill(GfMenuCallContext* context);

    // StatusListener's copy of the target's per-element levels (GfObjPropertyEnemy::m_resAttrs[i].m_level, by
    // element 0..8): the open event (0x21) copies them and then sets each to 3; event 0xD's element damage lowers
    // one (the name is not the original's)
    int m_resLevel[9];
    // how many of the status's overkill thresholds (400, 500 .. 900) event 0xD's value has passed; the open event
    // resets it (the name is not the original's)
    int m_ovkStage;
};
}  // namespace gf

#endif
