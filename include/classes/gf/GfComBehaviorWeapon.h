#ifndef CLASSES_GF_GFCOMBEHAVIORWEAPON_H
#define CLASSES_GF_GFCOMBEHAVIORWEAPON_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class MsgObjectForceWeaponMount; }
namespace gf { class MsgObjectNotifyAsmCallback; }

namespace gf {
// table 0x7100B69DC0
class GfComBehaviorWeapon : public ::gf::GfComBehavior {
public:
    GfComBehaviorWeapon();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorWeapon();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    void procMsgObjectNotifyAsmCallback(fw::MessageObject* sender, MsgObjectNotifyAsmCallback& msg);
    void procMsgObjectOnChangeWeapon(fw::MessageObject* sender, MsgObjectForceWeaponMount& msg);
    static mm::mtl::RTTI m_rtti;

    // the "weaponTrans" annotations' commands, executed on the asm component by the next update (the name is
    // not the original's)
    mm::mtl::Vector<const char*> m_commands;
};
}  // namespace gf

#endif
