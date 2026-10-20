#ifndef CLASSES_GF_PC_TIMERPLUGIN_H
#define CLASSES_GF_PC_TIMERPLUGIN_H

#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B69B60
class TimerPlugin : public ::gf::Plugin {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~TimerPlugin();  // slot 1
    virtual void onSetup(gf::GfComBehavior&);  // slot 5
    virtual void onCleanup(gf::GfComBehavior&);  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7
    virtual void setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9
    virtual void update(gf::GfComBehaviorPc&, fw::UpdateInfo const&);  // slot 10
};
}}  // namespace gf::pc

#endif
