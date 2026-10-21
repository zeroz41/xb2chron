#ifndef CLASSES_GF_PC_FALLDAMAGEPLUGIN_H
#define CLASSES_GF_PC_FALLDAMAGEPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
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
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FallDamagePlugin();  // slot 1
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
