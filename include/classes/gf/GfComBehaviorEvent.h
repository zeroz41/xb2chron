#ifndef CLASSES_GF_GFCOMBEHAVIOREVENT_H
#define CLASSES_GF_GFCOMBEHAVIOREVENT_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/TFieldExecCmdTurn.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }

namespace gf {
// table 0x7100B66158
class GfComBehaviorEvent : public ::gf::GfComBehavior {
public:
    GfComBehaviorEvent();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorEvent();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    void setup();
    void cleanup();
    void setFootIK(bool enable);
    void setTarget(bool, float, bool);
    void setTargetPos(const mm::Vec3& pos);
    void execTurnCmd(float, float, float, float);
    static mm::mtl::RTTI m_rtti;

    // bit 0: update has turned the foot IK on (the name is not the original's)
    unsigned int m_flags;
    TFieldExecCmdTurn<GfComEvtAnim> m_turnCmd;  // update updates it (the name is not the original's)
};
}  // namespace gf

#endif
