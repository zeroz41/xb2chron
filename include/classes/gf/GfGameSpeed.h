#ifndef CLASSES_GF_GFGAMESPEED_H
#define CLASSES_GF_GFGAMESPEED_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameSpeed; }

namespace gf {
// table 0x7100B54818
class GfGameSpeed : public ::mm::mtl::PtrSingleton< ::gf::GfGameSpeed> {
public:
    virtual ~GfGameSpeed();  // slot 0
    static float getPlaySpeed();  // 0 without the singleton
};
}  // namespace gf

#endif
