#ifndef CLASSES_GF_GFCOMPROPERTYPC_H
#define CLASSES_GF_GFCOMPROPERTYPC_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/GfComProperty.h"
#include "mm/Vec2.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/pc/GfPropertyBattle.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class EnviromentSensor; }
namespace anm { class QsTransform; }

namespace gf {
// table 0x7100B69448
class GfComPropertyPc : public ::gf::GfComProperty {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPropertyPc();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    const gf::EnviromentSensor* getEnvSensor() const;
    // sets (on) or clears (off) the given bits of its GfComEnvSensor's sensor's m_checkFlags
    void setEnvSensorCheckFlags(unsigned int flags, bool on);
    void setInputDirPow(const mm::Vec3& dir, float pow);
    void setLocomotion(const anm::QsTransform& locomotion);

    static mm::mtl::RTTI m_rtti;

    // setup copies it from its SetupInfo's first word (0 and nonzero pick different state flags); the constructor
    // and cleanup set -1, and AIAgent runs its field AI only while it is not -1. It is the PC's player index:
    // 1.0.0's procMsgPcFieldNotifyChangePlayerID sets it, GfGamePlayerFormation's tables are indexed by it, and the
    // field AI's isFollowMainPc follows always at 0 (the main PC)
    unsigned int m_setupKind;
    // the stick: the pad's axes write x and y, setInputDirPow the direction it is given times its power
    struct InputDir {
        float x;
        float y;
    };
    // the actions asked for this frame: the pad's action handlers set bits in m_actions (bit 0, 3 and 4 from
    // PadField's), TaskFieldJump::update bit 2; PadAgent::update clears the whole word pair each frame
    struct InputFlags {
        unsigned int m_actions;
        unsigned char pad_4[0x4];
    };

    unsigned char pad_3c[0x24];
    InputDir m_inputDir;
    InputFlags m_inputFlags;
    InputDir m_prevInputDir;      // PadAgent::update's copy of last frame's m_inputDir
    InputFlags m_prevInputFlags;  // and of m_inputFlags
    mm::Vec3 m_velocity;        // TaskFieldJump::update keeps its speed, turned along m_moveDir
    // two more of its motions: 1.0.0's procMsgObjectFlushProperty counts the PC as moving while either (or the
    // velocity or the locomotion) is not zero; isFollowBuddyPc keeps following while m_moveVec2.y is not, the
    // follow tests while m_moveSpeed is above 0 (the names are not the original's)
    mm::Vec2 m_moveVec2;
    unsigned char pad_a0[0x20];  // setLocomotion's translation and rotation
    float m_moveSpeed;
    unsigned char pad_c4[0x3C];
    mm::Vec3 m_colVel;          // ColVelCalculatorPlugin::update's: the ground's movement it carries the PC with
    // bit 4: ColVelCalculatorPlugin::update takes the ground's movement; bit 10: DeadColCheckPlugin::testDead asks
    // the first collision object instead of the dead plane
    unsigned int m_stateFlags;
    // flush's: how deep in water the PC is, 0 out of it up to 3 (the water surface at least its chest height above
    // the ground under it); the field AI takes its swimming parameters at 3 (the name is not the original's)
    int m_waterLevel;
    unsigned char pad_118[0x4];
    float m_waterDepth;         // flush's: the water surface's height above the ground under the PC (the name is not
                                // the original's)
    int m_wallJumpState;        // StateFieldWallJump::enter sets 0, leave 2 (the name is not the original's)
    unsigned char pad_124[0xC];
    // a warp the field AI's warp tasks ask for (setting m_stateFlags bit 26, which 1.0.0's procMsgPcFieldWarpCancel
    // clears): where to, facing which way, and how (0 to the formation, 1 to the wall follow transform, 3 1.0.0's
    // TaskFieldCheckWarpFallDead's). The names are not the original's.
    mm::Vec3 m_warpPos;
    mm::Quat m_warpRot;
    int m_warpType;
    unsigned char pad_154[0xC];
    mm::Vec3 m_pos;             // TaskFieldRetreat::update routes the PC from it
    mm::Quat m_rot;             // the PC's facing: isActiveRange and isActiveRangeLure turn their reach's offset by it
                                // (the name is not the original's)
    mm::Vec3 m_prevPos;         // DeadColCheckPlugin::testDead: falling from above a dead plane's height to it
    unsigned char pad_190[0x30];
    mm::Vec3 m_frontDir;        // StateFieldIdle::checkSpace starts its capsule 0.6 along it from m_pos
                                // (the name is not the original's)
    unsigned char pad_1d0[0x10];
    mm::Vec3 m_moveDir;         // TaskFieldJump::update sets m_velocity along it
    unsigned char pad_1f0[0xA0];
    // two of updateWorldDirs' world directions: the ones the stick's y and x move the PC along
    // (TaskFieldWallEscape::update picks the stick's signs by them; the names are not the original's)
    mm::Vec3 m_stickFrontDir;
    unsigned char pad_2a0[0x30];
    mm::Vec3 m_stickSideDir;
    unsigned char pad_2e0[0x10];
    float m_chestHeight;        // setup's: the character data's chest height in metres (the name is not the original's)
    unsigned char pad_2f4[0xC];
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // the PC's parameters
    unsigned char pad_308[0x8];
    pc::GfPropertyField m_field;  // setup, cleanup and flush pass it this property
    pc::GfPropertyBattle m_battle;  // StateField::recieveMessage hands it the battle start (0x470)
};
}  // namespace gf

#endif
