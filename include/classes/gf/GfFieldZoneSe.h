#ifndef CLASSES_GF_GFFIELDZONESE_H
#define CLASSES_GF_GFFIELDZONESE_H

#include "classes/gf/IEventZone.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldZoneSe; }

namespace gf {
// table 0x7100B52870
class GfFieldZoneSe : public ::mm::mtl::PtrSingleton< ::gf::GfFieldZoneSe>, public ::gf::IEventZone {
public:
    virtual ~GfFieldZoneSe();  // slot 0
};
}  // namespace gf

#endif
