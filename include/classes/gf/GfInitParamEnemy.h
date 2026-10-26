#ifndef CLASSES_GF_GFINITPARAMENEMY_H
#define CLASSES_GF_GFINITPARAMENEMY_H

#include "classes/gf/GfInitParam.h"
#include "classes/gf/SubViewCamera.h"

namespace gf {
// table 0x7100B3FB98
class GfInitParamEnemy : public ::gf::GfInitParam {
public:
    virtual unsigned int getBladeID() const;  // slot 1
    virtual unsigned int getEnArrangeID() const;  // slot 2
    void setupForEvent(unsigned int arrangeId);
    void setupBlade(const GfInitParamEnemy& param);
    void setupForUi(unsigned int arrangeId, VIEWCAM camera);
    unsigned char pad_90[0x98 - 0x90];
    // the enemy's CHR_EnParam row: setupForEvent and setupForUi read it from its CHR_EnArrange row (the name is not
    // the original's)
    unsigned int m_paramId;
    // the enemy's CHR_EnArrange row (setupForEvent, setupForUi; the name is not the original's)
    unsigned int m_arrangeId;
    // what getBladeID returns: setupBlade reads it from the CHR_EnArrange row (the name is not the original's)
    unsigned int m_bladeId;
    // setupForEvent: the CHR_EnParam row's resource id again
    unsigned int pad_a4;
    // setupBlade sets it to 1; createSetupParam copies it to the setup's m_actMoveId when set
    unsigned int pad_a8;
    // createSetupParam passes it to SDataEnemy's constructor
    unsigned short pad_ac;
};
}  // namespace gf

#endif
