#ifndef CLASSES_ML_DRENVCOLIOBJ_H
#define CLASSES_ML_DRENVCOLIOBJ_H

#include "classes/mm/mtl/IAllocator.h"

namespace mm { class Vec3; }

namespace ml {
// table none (its derived classes')
class DrEnvColiObj : public ::mm::mtl::IAllocator {
public:
    virtual ~DrEnvColiObj();  // slot 0
    virtual void envcoli_box(unsigned char const*, mm::Vec3 const&, float, mm::Vec3 const*);  // slot 5
};
}  // namespace ml

#endif
