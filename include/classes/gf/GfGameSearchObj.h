#ifndef CLASSES_GF_GFGAMESEARCHOBJ_H
#define CLASSES_GF_GFGAMESEARCHOBJ_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameSearchObj; }

namespace gf {
// table 0x7100B55F30
class GfGameSearchObj : public ::mm::mtl::PtrSingleton< ::gf::GfGameSearchObj> {
public:
    class GFSEARCH_INFO;
    virtual ~GfGameSearchObj();  // slot 0
};
}  // namespace gf

#endif
