#ifndef CLASSES_GF_PC_TARGETIKPLUGIN_H
#define CLASSES_GF_PC_TARGETIKPLUGIN_H

#include "classes/fw/LookIkSolver.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"
#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComBehavior; }
namespace gf { class GfComPropertyPc; }
namespace gf { class MsgGameChangeTarget; }

namespace gf { namespace pc {
// table 0x7100B69A90; turns the PC's look solver toward its target while the target is in front of it
class TargetIKPlugin : public ::gf::Plugin {
public:
    TargetIKPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 6 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 33 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TargetIKPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~TargetIKPlugin();  // slot 1
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
    // whether pos is within the look parameters' lookAngle of the PC's front
    bool isActiveRange(gf::GfComPropertyPc& property, const mm::Vec3& pos);
    void procMsgGameChangeTarget(fw::MessageObject* sender, gf::MsgGameChangeTarget& msg);

    static mm::mtl::RTTI m_rtti;

    // (the field names are not the original's)
    gf::GF_OBJ_HANDLE* m_target;                    // procMsgGameChangeTarget's; -1: none
    mm::mtl::IntrusivePtr<fw::LookIkSolver> m_solver;  // setup's: the PC's look solver (its IK component's 3rd)
    fw::ParamAdapter m_param;                       // setup's: the param manager's list 5, entry 4 (gf::LookParam)
    mm::Vec3 m_front;                               // the PC's front in its own space (the constructor's: unit Z)
    float m_upRatio;    // the look solver's target up ratio: update moves it toward 0 or 1 by the animation
    float m_downRatio;  // and its down ratio
};
}}  // namespace gf::pc

#endif
