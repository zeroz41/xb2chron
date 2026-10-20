#ifndef CLASSES_GF_GFGAMECAMERA_H
#define CLASSES_GF_GFGAMECAMERA_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameCamera; }

namespace gf {
// table 0x7100B546D8
class GfGameCamera : public ::mm::mtl::PtrSingleton< ::gf::GfGameCamera> {
public:
    virtual ~GfGameCamera();  // slot 0
};
}  // namespace gf

#endif
