#ifndef CLASSES_GF_GFGAMEENV_H
#define CLASSES_GF_GFGAMEENV_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { class Vec3; }

namespace gf { class GfGameEnv; }

namespace gf {
// table 0x7100B54838
class GfGameEnv : public ::mm::mtl::PtrSingleton< ::gf::GfGameEnv> {
public:
    virtual ~GfGameEnv();  // slot 0
    static void sendPlayerPositionToRender(const mm::Vec3& pos);
};
}  // namespace gf

#endif
