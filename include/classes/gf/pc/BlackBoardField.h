#ifndef CLASSES_GF_PC_BLACKBOARDFIELD_H
#define CLASSES_GF_PC_BLACKBOARDFIELD_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BlackBoard.h"
#include "mm/Vec3.h"
#include "mm/Plane.h"

namespace gf { class GfComPropertyPc; }
namespace navi { class NvmshAcObj; }
namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B67908
class BlackBoardField : public ::ai::BlackBoard {
public:
    BlackBoardField();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~BlackBoardField();  // slot 1
    static mm::mtl::RTTI m_rtti;

    // a word of flag bits (inline: the class's and its members' names are not the original's). Its setter is a
    // member of its own: TaskFieldSensor::update's flag stores are word accesses of a 4-aligned object (not of the
    // 16-aligned blackboard, whose word clang would widen into the following timer's load) and select as one
    class Flags {
    public:
        // sets (on) or clears the bits of mask
        void set(unsigned int mask, bool on) {
            if (on) {
                m_value |= mask;
            } else {
                m_value &= ~mask;
            }
        }
        operator unsigned int() const { return m_value; }
        Flags& operator|=(unsigned int mask) {
            m_value |= mask;
            return *this;
        }
        Flags& operator&=(unsigned int mask) {
            m_value &= mask;
            return *this;
        }

        unsigned int m_value;
    };

    gf::GfComPropertyPc* m_property;  // the PC's property (TaskFieldIdle::update sets its idle input)
    navi::NvmshAcObj* m_nvmshAcObj;   // the PC's navigation mesh path (TaskFieldRetreat::update routes it)
    // the frame's update (AIAgentField::update sets it; the name is not the original's)
    const fw::UpdateInfo* m_updateInfo;
    // the following fields are the field AI's, set by TaskFieldSensor::update and TaskFieldFollowTarget::update
    // (the names are not the original's)
    mm::Vec3 m_targetPos;    // where the formation sends the PC
    float m_targetDist;      // the PC's distance from m_targetPos across the ground (x and z)
    mm::Vec3 m_followPos;    // the position of the formation's transform the PC follows
    float m_followDist;      // the PC's distance from m_followPos across the ground
    unsigned char pad_54[0xC];
    // the wall the PC climbs: a point on it and its plane (the wall states hand both to
    // StateUtilField::calcWallPreparePosition; the names are not the original's)
    mm::Vec3 m_wallPos;
    mm::Plane m_wallPlane;
    // where the PC climbs off a wall (TaskFieldWallFollow::update hands it to AgentUtilField::setFollowWallEndInput;
    // the name is not the original's)
    mm::Vec3 m_wallEndPos;
    unsigned char pad_a0[0x140];
    void* pad_1e0[2];  // two words the constructor clears
    mm::Vec3 m_retreatPos;            // TaskFieldRetreat routes the PC to it while farther than 1 from it
    // bits 0-2: TaskFieldSensor::update (0 the PC is stuck, 1 an obstacle is in its way, 2 it can jump onto it);
    // bit 3: set by TaskFieldRetreat::update and the follow tasks' update, cleared by TaskFieldIdle::update;
    // bit 4: TaskFieldRetreat::testCondition requires it; bits 6, 7 and 9: AIAgentField's high jump, water warp
    // and buddy water warp notices, which TaskFieldSensor::update asks the PC for until m_noticeTimer runs out;
    // bit 8: a wall jump notice, which lasts while the PC's field status has bit 4; bit 10: AIAgentField::update,
    // the player the PC follows is moving
    Flags m_flags;
    // the time left before TaskFieldSensor::update asks the PC to act on a notice (AIAgentField sets it; the name
    // is not the original's)
    float m_noticeTimer;
};
}}  // namespace gf::pc

#endif
