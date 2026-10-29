#ifndef CLASSES_GF_GFCOMBEHAVIORPC_H
#define CLASSES_GF_GFCOMBEHAVIORPC_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/UniquePtr.h"
#include "mm/mtl/IntrusivePtr.h"
#include "ai/Hfsm.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/fw/SoundResSourceManager.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace fw { class Transform; }
namespace mm { class Vec3; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }
namespace gf { class GfComPropertyPc; }
namespace gf { class MsgPcFieldSetFallMaxHeight; }
namespace gf { class MsgPcFieldReqFallDeadMotion; }
namespace gf { class MsgUnk_100001C; }
namespace gf { namespace pc { class Agent; } }

namespace gf {
// table 0x7100B693E8
class GfComBehaviorPc : public ::gf::GfComBehavior {
public:
    // table 0x7100B69430: what the WK standby logout calls back (classes/gf/GfComBehaviorPc/Listener.h names it)
    class Listener {
    public:
        explicit Listener(GfComBehaviorPc* owner) : m_owner(owner) {}
        virtual void onWkStandbyLogout();  // slot 0: inline (emitted with the unit's inline functions)
        GfComBehaviorPc* m_owner;  // the behavior it listens for (the name is not the original's)
    };

    // what setup takes (the field names are not the original's)
    struct SetupInfo {
        unsigned int m_state;  // the Hfsm state the PC starts in
        bool m_eyeBlink;       // whether the eye blink plugin is made
    };

    GfComBehaviorPc();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorPc();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    // the asm and sound callbacks, the pad or AI agent, the plugins, the field and battle states and the head frame
    void setup(const SetupInfo& info);
    // the field's animation callback: does nothing (defined in PadField's unit, as 1.0.0's)
    void callbackField(gf::GfComAsm* asmCom, const gf::CallBackCache& cache);
    // the battle's animation callback: does nothing (defined in PadBattle's unit)
    void callbackBattle(gf::GfComAsm* asmCom, const gf::CallBackCache& cache);
    // what the sound resources call back with: a footstep or movement pack (isAttenuationPack) of a PC whose
    // m_setupKind is 1 to 5 gets that kind's volume from param list 18's table
    void callbackSound(const fw::ResSoundData& data, fw::SoundResSourceManager::CustomInfo* info);
    // the property's m_headColiPos recomputed for transform (none while its m_headColiHeight is zero)
    void resetHeadColPosition(const fw::Transform& transform);
    // the move of the property's integrate mode (its m_wallJumpState: 0 normal, 1 child height, 2 wall), none
    // while its m_stateFlags bit 16 is set
    void integrateMove(const fw::UpdateInfo& info);
    void integrateMoveNormal(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    void integrateMoveChildHeight(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    void integrateMoveWall(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    // the fall damage plugin activated and handed the message
    void procMsgPcFieldSetFallMaxHeight(fw::MessageObject* sender, gf::MsgPcFieldSetFallMaxHeight& msg);
    // the asm put in "S_fall" (unless it is there) and "C_falldead" run
    void procMsgPcFieldReqFallDeadMotion(fw::MessageObject* sender, gf::MsgPcFieldReqFallDeadMotion& msg);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because recieveMessage hands it
    // the behavior's own message 0x100001C (new in 3.0.1). What it does: like procMsgPcFieldChangeControlMode, the
    // property's m_stateFlags bit 26 cleared, the Hfsm cleared (bit 0), the agent cleaned up and dropped, the pad
    // plugins (Access, FallIntoColi, FallDamage, Fade, Lure, TerrainDamage, DeadColCheck, FallDistanceAchiev)
    // destroyed and pad control off for a pad PC (bit 10); then mode 1 makes an AIAgent, mode 0 a PadAgent with pad
    // control and those plugins made again (TerrainDamage and DeadColCheck activated); with bit 0 the Hfsm goes to
    // state 3 and the asm to "S_idle".
    void fn_710050EF90(fw::MessageObject* sender, gf::MsgUnk_100001C& msg);
    void calcHeadColiPos(float height, const fw::Transform& transform, mm::Vec3* pos);
    // switch the PC's agent's field and battle AI (StateUtil hands them on)
    void setEnableAgentField(bool enable);
    void setEnableAgentBattle(bool enable);
    static mm::mtl::RTTI m_rtti;

    mm::mtl::UniquePtr<pc::Agent> m_agent;  // the PC's pad or AI agent (the name is not the original's)
    ai::Hfsm m_hfsm;                        // the PC's field and battle states
    // the "JU_neck" (else "JU_spA") bone frame cleanup releases (the name is not the original's)
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_headFrame;
    void* pad_130;  // its Listener clears it on a standby logout
    Listener m_listener;
};
inline void GfComBehaviorPc::Listener::onWkStandbyLogout() {
    m_owner->pad_130 = nullptr;
}

// whether a sound pack is one of the PC movement packs callbackSound attenuates
bool isAttenuationPack(const char* packName);
}  // namespace gf

#endif
