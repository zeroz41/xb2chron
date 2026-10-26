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
    unsigned char pad_90[0x98 - 0x90];
    // the enemy's CHR_EnParam row: setupForEvent and setupForUi read it from its CHR_EnArrange row (the name is not
    // the original's)
    unsigned int m_paramId;
    // the enemy's CHR_EnArrange row (setupForEvent, setupForUi; the name is not the original's)
    unsigned int m_arrangeId;
    unsigned char pad_a0[0xa4 - 0xa0];
    // setupForEvent: the CHR_EnParam row's resource id again
    unsigned int pad_a4;
};
}  // namespace gf

#endif
