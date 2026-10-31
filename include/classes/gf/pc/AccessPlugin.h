#ifndef CLASSES_GF_PC_ACCESSPLUGIN_H
#define CLASSES_GF_PC_ACCESSPLUGIN_H

#include "classes/fw/ParamList.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }
namespace gf { struct AccessParam; }

namespace gf { namespace pc {
// table 0x7100B69550
class AccessPlugin : public ::gf::Plugin {
public:
    AccessPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 4 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 31 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_access_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) AccessPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~AccessPlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual bool onSetup(gf::GfComBehavior& behavior) {  // slot 5
        return setup(static_cast<gf::GfComBehaviorPc&>(behavior));
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
    void drawDebug(gf::GfComBehaviorPc& behavior, unsigned int index);

    static mm::mtl::RTTI m_rtti;

    gf::GF_OBJ_HANDLE* m_target;  // the object the PC can access (-1: none); SCOM_ACCESS_TARGET passes changes on
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // setup's: the param manager's list 5, its entries the reaches
    gf::GfComBehaviorPc* m_behavior;                   // the behavior setup was given
    // the PC state's access kinds: StateFieldOnGround::enter sets 0x2E, StateFieldOnWall's 8, StateFieldWaterNormal's
    // 0x10, their leave 0; update keeps no target while it is 0 (the name is not the original's)
    int m_accessKinds;
};

// whether the object behind handle can be accessed within param's reach of the PC
bool isActiveRange(gf::GfComPropertyPc& property, const gf::AccessParam& param, gf::GF_OBJ_HANDLE* handle);
}}  // namespace gf::pc

#endif
