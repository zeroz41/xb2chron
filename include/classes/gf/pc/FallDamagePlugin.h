#ifndef CLASSES_GF_PC_FALLDAMAGEPLUGIN_H
#define CLASSES_GF_PC_FALLDAMAGEPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"

namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }
namespace gf { class MsgPcFieldGetFallMaxHeight; }
namespace gf { class MsgPcFieldSetFallMaxHeight; }

namespace gf { namespace pc {
// table 0x7100B69758
class FallDamagePlugin : public ::gf::Plugin {
public:
    FallDamagePlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 7 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 27 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FallDamagePlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FallDamagePlugin();  // slot 1
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
    void cacheMaxHeight(bool reset);
    gf::GF_OBJ_HANDLE* getAttachObj() const;
    void procMsgPcFieldGetFallMaxHeight(fw::MessageObject* sender, gf::MsgPcFieldGetFallMaxHeight& msg);
    void procMsgPcFieldSetFallMaxHeight(fw::MessageObject* sender, gf::MsgPcFieldSetFallMaxHeight& msg);

    static mm::mtl::RTTI m_rtti;

    gf::GfComPropertyPc* m_property;  // the PC's property component, found by setup
    float m_maxHeight;                // cacheMaxHeight's: the highest the PC reaches while active
    bool m_damageDisable;             // StateUtil::setFallDamageDisable's: landing deals no damage while set
    gf::GF_OBJ_HANDLE* m_attachObj;   // getAttachObj's, cached each update (-1: none)
};
}}  // namespace gf::pc

#endif
