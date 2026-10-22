#ifndef CLASSES_GF_GFPAUSE_H
#define CLASSES_GF_GFPAUSE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfPause; }

namespace gf {
// table 0x7100B59510
class GfPause : public ::mm::mtl::PtrSingleton< ::gf::GfPause> {
public:
    virtual ~GfPause();  // slot 0
    static bool isPause(unsigned int kind);
};
}  // namespace gf

#endif
