#ifndef CLASSES_GF_GFGAMESTATE_H
#define CLASSES_GF_GFGAMESTATE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameState; }

namespace gf {
// table 0x7100B55FF0
class GfGameState : public ::mm::mtl::PtrSingleton< ::gf::GfGameState> {
public:
    virtual ~GfGameState();  // slot 0
};
}  // namespace gf

#endif
