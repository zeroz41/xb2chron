#ifndef CLASSES_GF_GFAPPENDWIRE_H
#define CLASSES_GF_GFAPPENDWIRE_H

#include "gf/GfObjAcc.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {

// a driver's wire (GfAppendWire.cpp): the wire object hangs from its owner's mount bone and reaches out to a target
// object (GfGameScene::getAppendControl hands it out; GfGameUtil's wire helpers start and end it). Field names are
// not the original's.
class GfAppendWire {
public:
    // the wire's states (the names are not the original's)
    enum State {
        STATE_NONE = 0,     // no target; the wire is hidden
        STATE_EXTEND = 1,   // reaching the target over m_time
        STATE_HOLD = 2,     // on the target for m_holdTime
        STATE_RETRACT = 3,  // pulling back (m_timer counts down)
    };

    GfAppendWire(GF_OBJ_HANDLE* owner, GF_OBJ_HANDLE* wire);
    ~GfAppendWire();
    void startWire(GF_OBJ_HANDLE* target, float time);
    void startWireWithClose(GF_OBJ_HANDLE* target, float time, float holdTime, float closeTime);
    void endWire(float time);
    void checkAndSetupSalvagePoint();
    void calcTargetPosotion();
    void updateState(const fw::UpdateInfo& info);
    void updateWire(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);

private:
    // drops the target and hides the wire (inline: the constructor, endWire, startWireWithClose and the updates
    // each repeat it; the name is not the original's)
    void resetWire() {
        m_time = 0.0f;
        m_timer = 0.0f;
        m_state = STATE_NONE;
        m_target = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        GfObjAcc(m_wire).setAlphaNormal(0.0f);
    }

public:
    GF_OBJ_HANDLE* m_owner;
    GF_OBJ_HANDLE* m_wire;
    unsigned short m_ownerMountBone;  // the owner skeleton's index of "MT_wire" (Skeleton::m_mountNames)
    unsigned short m_wireBoneA;       // the wire model's "EX_wireA" bone (ml::ScnObjAccResNode)
    unsigned short m_wireBoneB;       // the wire model's "EX_wireB" bone (ml::ScnObjAccResNode)
    unsigned short m_wireAccBoneA;    // the wire object's "EX_wireA" bone (GfObjAcc::getBoneIdx)
    GF_OBJ_HANDLE* m_target;          // (GF_OBJ_HANDLE*)-1 for none
    mm::Vec3 m_targetPos;
    short m_targetBone;  // the target's "JD_hip" (else "JD_hipA") bone, negative for none
    int m_state;         // State
    float m_timer;
    float m_time;
    float m_holdTime;
    float m_closeTime;
    bool m_salvagePoint;  // checkAndSetupSalvagePoint placed m_targetPos on the ground below a salvage gimmick
};

}  // namespace gf

#endif
