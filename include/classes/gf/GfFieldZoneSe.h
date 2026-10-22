#ifndef CLASSES_GF_GFFIELDZONESE_H
#define CLASSES_GF_GFFIELDZONESE_H

#include "classes/gf/IEventZone.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldZoneSe; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B52870
class GfFieldZoneSe : public ::mm::mtl::PtrSingleton< ::gf::GfFieldZoneSe>, public ::gf::IEventZone {
public:
    GfFieldZoneSe(const GfSetupParam& param) {
        initialize(param);
    }
    virtual ~GfFieldZoneSe();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();

    bool m_initialized;  // set as it joins GfFieldZone's events, cleared as it leaves them
};
}  // namespace gf

#endif
