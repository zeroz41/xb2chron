#ifndef CLASSES_GF_GFMENUREFERENCENUMBER_H
#define CLASSES_GF_GFMENUREFERENCENUMBER_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf {
// table 0x7100B5FB90; a counted number with its range a menu object shares with GfMenuReferenceAdapter
class GfMenuReferenceNumber : public ::mm::mtl::ReferenceObject {
public:
    virtual ~GfMenuReferenceNumber();  // slot 0
    // GfMenuReferenceAdapter shows it (plus its offset) and its range; the names are not the original's
    int m_value;
    int m_min;  // the number plugin's setMin
    int m_max;  // the number plugin's setMax
};
}  // namespace gf

#endif
