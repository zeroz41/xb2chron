#ifndef CLASSES_GF_PC_FALLINTOCOLIPLUGIN_H
#define CLASSES_GF_PC_FALLINTOCOLIPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_SEARCH_OBJ; }

namespace gf { namespace pc {
// table 0x7100B69888
class FallIntoColiPlugin : public ::gf::Plugin {
public:
    FallIntoColiPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 9 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 25 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FallIntoColiPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FallIntoColiPlugin();  // slot 1
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
    float getHeight(gf::GfComBehaviorPc& behavior) const;

    static mm::mtl::RTTI m_rtti;

    float m_activeTime;  // update's count of the time since onActivate: it looks only past 10 seconds
    float m_stillTime;   // update's count of the time the PC's height has stayed within 1 of m_height
    gf::GF_SEARCH_OBJ* m_searchObj;  // setup's search object, destroyed by cleanup (-1: none)
    float m_height;      // getHeight's, taken when the search starts and whenever the height moves more than 1
};
}}  // namespace gf::pc

#endif
