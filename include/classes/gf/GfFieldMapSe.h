#ifndef CLASSES_GF_GFFIELDMAPSE_H
#define CLASSES_GF_GFFIELDMAPSE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldMapSe; }

namespace gf {
// table 0x7100B521E8
class GfFieldMapSe : public ::mm::mtl::PtrSingleton< ::gf::GfFieldMapSe> {
public:
    class SEOBJ;
    virtual ~GfFieldMapSe();  // slot 0
};
}  // namespace gf

#endif
