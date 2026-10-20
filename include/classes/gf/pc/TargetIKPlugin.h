#ifndef CLASSES_GF_PC_TARGETIKPLUGIN_H
#define CLASSES_GF_PC_TARGETIKPLUGIN_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B69A90
class TargetIKPlugin {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~TargetIKPlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior&);  // slot 5
    virtual void onCleanup(gf::GfComBehavior&);  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7
    virtual void setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9
    virtual void update(gf::GfComBehaviorPc&, fw::UpdateInfo const&);  // slot 10
};
}}  // namespace gf::pc

#endif
