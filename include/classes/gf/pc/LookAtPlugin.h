#ifndef CLASSES_GF_PC_LOOKATPLUGIN_H
#define CLASSES_GF_PC_LOOKATPLUGIN_H

#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"
#include "classes/gf/GfBdatLookAt.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Map.h"

namespace fw { class LookIkSolver; }
namespace fw { class ParamList; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_SEARCH_OBJ; }
namespace gf { class GfComBehavior; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B698F0; turns the PC's look solver toward objects its search finds around it, one at a time, by the
// look parameters GfBdatLookAt gives for the pair (the field names below are not the original's)
class LookAtPlugin : public ::gf::Plugin {
public:
    // an object the search holds (the map's value, keyed by its handle; the field names are not the original's)
    struct TargetInfo {
        gf::GF_OBJ_HANDLE* m_handle;
        const void* m_searchNode;                    // updateHoldHandles: the search list's entry (null: lost)
        const gf::GfBdatLookAt::LookInfo* m_lookInfo;  // GfBdatLookAt::getLookInfo's for the PC and the object
        unsigned short m_charaType;                  // GfBdatLookAt::getCharaType's for the object
        bool m_looked;                               // updateHoldHandles inserts it cleared
    };

    LookAtPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 5 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 39 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_lookat_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LookAtPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~LookAtPlugin();  // slot 1
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

    void updateHoldHandles(gf::GfComBehaviorPc& behavior);
    bool changeTarget();
    void onReloadBdat();
    void drawDebug();

    static mm::mtl::RTTI m_rtti;

    mm::mtl::IntrusivePtr<fw::LookIkSolver> m_solver;  // setup's: the PC's look solver (its IK component's 3rd)
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // setup's: the param manager's list 5 (entry 4: gf::LookParam)
    gf::GF_SEARCH_OBJ* m_searchObj;                    // setup's search around the PC; -1: none
    mm::mtl::Map<gf::GF_OBJ_HANDLE*, TargetInfo> m_targets;  // updateHoldHandles': what the search holds
    TargetInfo* m_current;      // changeTarget's: the target looked at (m_currentInfo), null: none
    TargetInfo m_currentInfo;
    int m_lookState;            // update clears it without a target
    float m_changeWait;         // update counts it down, then changeTarget (reset to the target's look time)
    float m_typeWaits[5];       // per chara type: update counts each down; changeTarget skips a type still waiting
};
}}  // namespace gf::pc

#endif
