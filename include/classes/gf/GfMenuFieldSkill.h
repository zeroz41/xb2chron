#ifndef CLASSES_GF_GFMENUFIELDSKILL_H
#define CLASSES_GF_GFMENUFIELDSKILL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuFieldSkill; }

namespace gf {
// table 0x7100B5E588
class GfMenuFieldSkill : public ::mm::mtl::PtrSingleton< ::gf::GfMenuFieldSkill> {
public:
    class StateDispInfo;
    class StateDispResult;
    class StateDispTotal;
    class StateIdle;
    class StateQuit;
    class StateSkip;
    class StateStart;
    class StateTotalNext;
    class StateWait;
    virtual ~GfMenuFieldSkill();  // slot 0
    static bool isRunning();  // whether the field skill menu is up
};
}  // namespace gf

#endif
