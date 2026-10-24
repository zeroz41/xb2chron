#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "mm/Quat.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gmk { class AGmkBase; }

namespace gf {
// table 0x7100B66840
class GfComBehaviorNpc : public ::gf::GfComBehavior {
public:
    class Listener;
    class LocalSteerIsTargetNotPlayer;
    // the npc's row of its BDAT sheets (BdatInfo::create reads it); only what this unit's code shows is declared
    class BdatInfo {
    public:
        // how far above or below an npc a target may be (2): static or not, the symbol cannot tell
        static float getDistYThreshold();
    };
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorNpc();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    // its object's asm component (slot 2), none when the slot holds another kind
    virtual GfComAsm* getComAsm() const;  // slot 7
    // the gimmick its object is bound to, none when it is bound to none
    gmk::AGmkBase* getBindedGmkInst() const;
    // (re)makes its state machine: the npc's 7 states, one level deep
    void createFsm();
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_98[0x38];
    // StateReaction<GfComBehaviorNpc>::onLeave hands its saved rotation back to it (the name is not the original's)
    mm::Quat m_reactionRot;
    unsigned char pad_e0[0x28];
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_191[0x7];
    void* pad_198;  // its Listener clears it on a standby logout
};
}  // namespace gf

#endif
