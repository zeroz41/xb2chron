#ifndef CLASSES_GF_PC_TERRAINDAMAGEPLUGIN_H
#define CLASSES_GF_PC_TERRAINDAMAGEPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69AF8
class TerrainDamagePlugin : public ::gf::Plugin {
public:
    TerrainDamagePlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~TerrainDamagePlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior& behavior) {  // slot 5
        setup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onCleanup(gf::GfComBehavior& behavior) {  // slot 6
        cleanup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onUpdate(gf::GfComBehavior& behavior, fw::UpdateInfo const& info) {  // slot 7
        update(static_cast<gf::GfComBehaviorPc&>(behavior), info);
    }
    virtual bool setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9
    virtual void update(gf::GfComBehaviorPc&, fw::UpdateInfo const&);  // slot 10

    static mm::mtl::RTTI m_rtti;

    float m_damageTime;    // update adds each update's time and deals damage each time it passes the area's interval
    bool m_inDamageArea;   // update sets it as the PC enters a damaging area and clears it as the PC leaves
};
}}  // namespace gf::pc

#endif
