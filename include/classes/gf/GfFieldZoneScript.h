#ifndef CLASSES_GF_GFFIELDZONESCRIPT_H
#define CLASSES_GF_GFFIELDZONESCRIPT_H

#include "classes/gf/IEventZone.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldZoneScript; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B527F0
class GfFieldZoneScript : public ::mm::mtl::PtrSingleton< ::gf::GfFieldZoneScript>, public ::gf::IEventZone {
public:
    virtual ~GfFieldZoneScript();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static void destroyScript();
};
}  // namespace gf

#endif
