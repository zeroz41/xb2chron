#ifndef CLASSES_GF_GFMENUOBJLVUPSELECT_H
#define CLASSES_GF_GFMENUOBJLVUPSELECT_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;
// table 0x7100B62EF8: the driver level select of the level-up menu. Field names are not the original's.
class GfMenuObjLvupSelect : public ::gf::GfMenuObject {
public:
    class DrImgListener;
    class MainListener;
    class SelectListener;
    GfMenuObjLvupSelect(unsigned int handle);
    virtual ~GfMenuObjLvupSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // opens the level select for a driver row (GfMenuObjLvupMain's MainListener passes its context and the selection)
    static void openLevelSelect(GfMenuCallContext* context, unsigned int driver);
    // m_bonusExp: the reference driver's experience left at the virtual level (1.0.0's name)
    void updateBonusExp();
    // m_seq's jobs (1.0.0's names: SelectListener queues seqConfirmLevelUp at the same place in both versions, and
    // it queues seqExecLevelUp)
    bool seqConfirmLevelUp();
    // 2.0.0's symbols name it. What it does: a second confirmation (common window 0x102), queued instead of
    // seqExecLevelUp after the game is cleared when the bonus experience overflows (m_bonusOver); once answered with 0
    // it queues seqExecLevelUp, otherwise enables input 4.
    bool seqConfirmLostExp();
    bool seqExecLevelUp();

    GfMenuSequence<GfMenuObjLvupSelect, 8> m_seq;  // 0x28
    bool m_confirmOpen;  // 0x2B8: the running job has started (its window opened, its effect started)
    unsigned char pad_2B9[7];
    unsigned int m_level;  // 0x2C0: the level chosen (SelectListener's case 8)
    bool m_levelDown;  // 0x2C4: m_level is below the driver's level (execLevelDown instead of execLevelUp)
    bool m_bonusOver;  // 0x2C5: updateBonusExp's experience is over 999999999
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_levelNumber;  // 0x2C8: "TXT_lvslc_lvnum@%02d"'s number
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_bonusExp;  // 0x2D0: "TXT_bonus_exp_num"'s number
    GfMenuCallContext* m_callContext;  // 0x2D8: the constructor creates it, the destructor releases it
};
}  // namespace gf

#endif
