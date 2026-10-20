#ifndef CLASSES_GF_PLUGIN_H
#define CLASSES_GF_PLUGIN_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B65938
class Plugin {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~Plugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior&) = 0;  // slot 5
    virtual void onCleanup(gf::GfComBehavior&) = 0;  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&) = 0;  // slot 7
};
}  // namespace gf

#endif
