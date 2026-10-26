#ifndef CLASSES_GF_GFCOMBEHAVIORMOB_H
#define CLASSES_GF_GFCOMBEHAVIORMOB_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "mm/Quat.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gmk { class AGmkBase; }

namespace gf {
// table 0x7100B66500
class GfComBehaviorMob : public ::gf::GfComBehavior {
public:
    class Listener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorMob();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void getPos() const;  // slot 7
    virtual void getRot() const;  // slot 8
    // the gimmick its object is bound to, none when it is bound to none
    gmk::AGmkBase* getBindedGmkInst() const;
    // (re)makes its state machine: the mob's 7 states, one level deep
    void createFsm();
    // (re)starts its movement; the states pass true on entering, the approach state false
    void init(bool);
    bool isSquadMember() const;
    void execTurnCmdToPos(const mm::Vec3& pos);
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_98[0xc];
    float pad_a4;  // mob::StateApproachPc's fn_71004D7468 compares it with pad_53d0
    unsigned char pad_a8[0x10];
    void* pad_b8;  // mob::StateMove::isCondMatch: the state may run while it is set
    unsigned char pad_c0[0x60];
    // StateReaction<GfComBehaviorMob>::onLeave hands its saved rotation back to it (the name is not the original's)
    mm::Quat m_reactionRot;
    unsigned char pad_130[0x51F8];
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_53b1[0x7];
    void* pad_53b8;  // its Listener clears it on a standby logout
    unsigned char pad_53c0[0x10];
    float pad_53d0;
    float pad_53d4;  // mob::StateApproachPc's fn_71004D7468 needs it at most 4
    unsigned char pad_53d8;
    bool pad_53d9;  // mob::StateApproachPc sets it on entering
};
}  // namespace gf

#endif
