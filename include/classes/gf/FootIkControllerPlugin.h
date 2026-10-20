#ifndef CLASSES_GF_FOOTIKCONTROLLERPLUGIN_H
#define CLASSES_GF_FOOTIKCONTROLLERPLUGIN_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B656B0
class FootIkControllerPlugin {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~FootIkControllerPlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior&);  // slot 5
    virtual void onCleanup(gf::GfComBehavior&);  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7
    virtual void setup(gf::GfComBehavior&);  // slot 8
    virtual void cleanup(gf::GfComBehavior&);  // slot 9
    virtual void update(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 10
};
}  // namespace gf

#endif
