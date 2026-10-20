#ifndef CLASSES_ML_DRIBLCOLIACC_H
#define CLASSES_ML_DRIBLCOLIACC_H

#include "classes/mm/mtl/IAllocator.h"

namespace mm { class Vec3; }

namespace ml {
// table none (its derived classes')
class DrIBLColiAcc : public ::mm::mtl::IAllocator {
public:
    virtual ~DrIBLColiAcc();  // slot 0
    virtual void envcoli_box(unsigned char const*, mm::Vec3 const&, float);  // slot 5
};
}  // namespace ml

#endif
