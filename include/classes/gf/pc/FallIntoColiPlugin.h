#ifndef CLASSES_GF_PC_FALLINTOCOLIPLUGIN_H
#define CLASSES_GF_PC_FALLINTOCOLIPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_SEARCH_OBJ; }

namespace gf { namespace pc {
// table 0x7100B69888
class FallIntoColiPlugin : public ::gf::Plugin {
public:
    FallIntoColiPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FallIntoColiPlugin();  // slot 1
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
    float getHeight(gf::GfComBehaviorPc& behavior) const;

    static mm::mtl::RTTI m_rtti;

    unsigned char pad_9[0xF];        // +0xC, +0x10: two times update counts (not named yet)
    gf::GF_SEARCH_OBJ* m_searchObj;  // setup's search object, destroyed by cleanup (-1: none)
};
}}  // namespace gf::pc

#endif
