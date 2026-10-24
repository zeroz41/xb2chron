#ifndef CLASSES_GF_GFFIELDLOD_H
#define CLASSES_GF_GFFIELDLOD_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldLod; }

namespace gf {
// table 0x7100B51EB0
class GfFieldLod : public ::mm::mtl::PtrSingleton< ::gf::GfFieldLod> {
public:
    virtual ~GfFieldLod();  // slot 0
    int findBdatIdByLodId(unsigned short lodId) const;
    void setAnimReverse(int bdatId, bool flag0, bool flag1);
};
}  // namespace gf

#endif
