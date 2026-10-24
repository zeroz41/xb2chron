#ifndef CLASSES_GF_GFFIELDGMKTUTORIAL_H
#define CLASSES_GF_GFFIELDGMKTUTORIAL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldGmkTutorial; }

namespace gf {
// table 0x7100B524E8
class GfFieldGmkTutorial : public ::mm::mtl::PtrSingleton< ::gf::GfFieldGmkTutorial> {
public:
    virtual ~GfFieldGmkTutorial();  // slot 0

    unsigned char pad_8[0x4C];
    // GfPlayComWaitPlayerToStartGmkTuto sets it once the player has waited 3 seconds without the mover being ready
    // and clears it when the mover is (the name is not the original's)
    bool m_waitMover;
};
}  // namespace gf

#endif
