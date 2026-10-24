#ifndef CLASSES_GF_GFCOMBEHAVIORENEMY_H
#define CLASSES_GF_GFCOMBEHAVIORENEMY_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "fw/Transform.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }
namespace gmk { class AGmkBase; }
namespace fw { class ReferenceFrame; }

namespace gf {
// a base of gf::GfComBehaviorEnemy no evidence names yet
class TUnk_B65E98 {
public:
    virtual const fw::Transform& getTransform() const = 0;
    virtual const fw::Transform& getTransformToSearchPlayer() const = 0;
    virtual void getBdatId_CHR_EnArrange() const = 0;
    virtual void getGmkBattleLockInfo(int&, int&) const = 0;
};
// table 0x7100B65E30; base at 0x98 unknown (TUnk_B65E98)
class GfComBehaviorEnemy : public ::gf::GfComBehavior, public TUnk_B65E98 {
public:
    class Listener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorEnemy();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    // where it searches for the player from: pad_138's world transform when it has that frame, else getTransform's
    virtual const fw::Transform& getTransformToSearchPlayer() const;  // slot 7
    // its object's world transform (the transform component's frame)
    virtual const fw::Transform& getTransform() const;  // slot 8
    virtual void getBdatId_CHR_EnArrange() const;  // slot 9
    virtual void getGmkBattleLockInfo(int&, int&) const;  // slot 10
    // the gimmick its object is bound to, none when it is bound to none
    gmk::AGmkBase* getBindedGmkInst() const;
    // whether its CHR_EnArrange row's act type (SDataEnemy::m_actType) is 3 (flying) / 1 (in water)
    bool isFly() const;
    bool isWater() const;
    // (re)makes its state machine: the enemy's 16 states (battle, field idle/spawn/walk/home/squad/blade)
    void createFsm();
    static mm::mtl::RTTI m_rtti;
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_129[0xF];
    fw::ReferenceFrame* pad_138;  // getTransformToSearchPlayer's frame when set
    unsigned char pad_140[0x53A8];
    void* pad_54e8;  // its Listener clears it on a standby logout
};
}  // namespace gf

#endif
