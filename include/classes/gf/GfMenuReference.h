#ifndef CLASSES_GF_GFMENUREFERENCE_H
#define CLASSES_GF_GFMENUREFERENCE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuReference; }

namespace gf {
// table 0x7100B5EF48
class GfMenuReference : public ::mm::mtl::PtrSingleton< ::gf::GfMenuReference> {
public:
    class REFLIST;
    virtual ~GfMenuReference();  // slot 0
    static unsigned int getReferenceDriverID(unsigned int index);
};
}  // namespace gf

#endif
