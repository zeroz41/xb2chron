#ifndef CLASSES_GF_GFSEQUENTIALPLAY_H
#define CLASSES_GF_GFSEQUENTIALPLAY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSequentialPlay; }

namespace gf {
// table 0x7100B590E8
class GfSequentialPlay : public ::mm::mtl::PtrSingleton< ::gf::GfSequentialPlay> {
public:
    virtual ~GfSequentialPlay();  // slot 0
};
}  // namespace gf

#endif
