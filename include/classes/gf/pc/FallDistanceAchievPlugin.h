#ifndef CLASSES_GF_PC_FALLDISTANCEACHIEVPLUGIN_H
#define CLASSES_GF_PC_FALLDISTANCEACHIEVPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B697C0
class FallDistanceAchievPlugin : public ::gf::Plugin {
public:
    FallDistanceAchievPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FallDistanceAchievPlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior& behavior) {  // slot 5
        setup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onCleanup(gf::GfComBehavior& behavior) {  // slot 6
        cleanup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7 (inline in the original; its body reads the property)
    virtual bool setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9

    static mm::mtl::RTTI m_rtti;

    gf::GfComPropertyPc* m_property;  // the PC's property component, found by setup
    float m_maxHeight;                // the highest the PC reaches while active; landing below it by 10 counts
};
}}  // namespace gf::pc

#endif
