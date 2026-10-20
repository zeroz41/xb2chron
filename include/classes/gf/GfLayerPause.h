#ifndef CLASSES_GF_GFLAYERPAUSE_H
#define CLASSES_GF_GFLAYERPAUSE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfLayerPause; }

namespace gf {
// table 0x7100B547F8
class GfLayerPause : public ::mm::mtl::PtrSingleton< ::gf::GfLayerPause> {
public:
    virtual ~GfLayerPause();  // slot 0
};
}  // namespace gf

#endif
