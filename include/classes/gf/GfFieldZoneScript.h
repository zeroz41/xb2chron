#ifndef CLASSES_GF_GFFIELDZONESCRIPT_H
#define CLASSES_GF_GFFIELDZONESCRIPT_H

#include "classes/gf/IEventZone.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfFieldZone.h"

namespace gf { class GfFieldZoneScript; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B527F0: the field zone's script (0x18 bytes, build's new): it joins GfFieldZone's events as
// GfFieldZoneSe does
class GfFieldZoneScript : public ::mm::mtl::PtrSingleton< ::gf::GfFieldZoneScript>, public ::gf::IEventZone {
public:
    GfFieldZoneScript(const GfSetupParam& param) {
        initialize(param);
    }
    virtual ~GfFieldZoneScript();  // slot 0
    void initialize(const GfSetupParam& param) {
        m_initialized = true;
        GfFieldZone::addEvent(this);
    }
    static void build(const GfSetupParam& param);
    static void destroy();
    // the original's finalize hands itself to GfFieldZone::addEvent again (destroy's code), not removeEvent
    void finalize() {
        GfFieldZone::addEvent(this);
        m_initialized = false;
    }
    // runs the named script, else the jump map's fld_<resource name>; false when there is neither
    static bool execScript(const char* name);
    static void destroyScript();
    static bool isExecScriptBusy();
    static bool isDestroyScriptBusy();

    bool m_initialized;  // set as it joins GfFieldZone's events, cleared by finalize
};
}  // namespace gf

#endif
