#ifndef CLASSES_GF_GFMENUREWRITENUMBER_H
#define CLASSES_GF_GFMENUREWRITENUMBER_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf {
// table 0x7100B640F8; counted (GfMenuAdapter references the one it is given)
class GfMenuRewriteNumber : public ::mm::mtl::ReferenceObject {
public:
    virtual ~GfMenuRewriteNumber();  // slot 0
    // what GfMenuAdapter::setNumber shows while m_enabled is set (the names are not the original's)
    int m_number;
    bool m_enabled;
};
}  // namespace gf

#endif
