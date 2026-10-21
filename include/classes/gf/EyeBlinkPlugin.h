#ifndef CLASSES_GF_EYEBLINKPLUGIN_H
#define CLASSES_GF_EYEBLINKPLUGIN_H

#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B65648
class EyeBlinkPlugin : public ::gf::Plugin {
public:
    virtual const mm::mtl::RTTI* getRTTI() const;  // slot 0
    virtual ~EyeBlinkPlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior&);  // slot 5
    virtual void onCleanup(gf::GfComBehavior&);  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7
    virtual bool setup(gf::GfComBehavior&);  // slot 8
    virtual void cleanup(gf::GfComBehavior&);  // slot 9
    virtual void update(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 10

    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
