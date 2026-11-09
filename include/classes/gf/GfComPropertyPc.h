#ifndef CLASSES_GF_GFCOMPROPERTYPC_H
#define CLASSES_GF_GFCOMPROPERTYPC_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/GfComProperty.h"
#include "mm/Vec2.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Bitflag.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/pc/GfPropertyBattle.h"

namespace fw { class Message; }
namespace mm { class Mat44; }
namespace fw { class MessageObject; }
namespace gf { class EnviromentSensor; }
namespace anm { class QsTransform; }
namespace gf { class MsgObjectFlushProperty; }
namespace gf { class MsgObjectGetVelocity; }
namespace gf { class MsgPcFieldNotifyChangePlayerID; }
namespace gf { class MsgDebugActivateComponentWindow; }

namespace gf { namespace pc {
// GfComPropertyPc's m_paramList entry 4 (gf::pc::SlideParam by setMoveSlidePacket's symbol; the field names are
// not the original's)
struct SlideParam {
    unsigned char pad_0[0x14];
    float m_stopSpeed;  // StateUtilField::isSlideStop: the slide stops once m_moveSpeed is no more than it
    // StateUtilField::isStartSlidePosuture: on slide ground the PC starts sliding while pad_f0 is at least
    // m_startSlideValue or its speed along pad_d0 at least m_startSlideSpeed (the names are not the original's)
    float m_startSlideValue;
    float m_startSlideSpeed;
    // and StateUtilField::isEndSlipPosuture: off a slide slope the slip ends once that speed is no more than it
    float m_landSpeed;  // StateUtilField::onLandSliding: the most speed a landing keeps
    // StateUtilField::isFallFromSlideState: the PC falls once this far above the ground under it
    float m_fallHeight;
};
}}  // namespace gf::pc

namespace gf {
// table 0x7100B69448
class GfComPropertyPc : public ::gf::GfComProperty {
public:
    GfComPropertyPc();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    // inline (its deleting destructor inlines the body), so recieveMessage is the key function
    virtual inline ~GfComPropertyPc();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    const gf::EnviromentSensor* getEnvSensor() const;
    // sets (on) or clears (off) the given bits of its GfComEnvSensor's sensor's m_checkFlags
    void setEnvSensorCheckFlags(unsigned int flags, bool on);
    void setInputDirPow(const mm::Vec3& dir, float pow);
    bool existInputXY() const;  // (by its symbol)
    void setLocomotion(const anm::QsTransform& locomotion);
    // what setLocomotion keeps (m_locomotion, its translation and rotation) while m_stateFlags bit 2 is set, else a static
    // zero translation and identity rotation (by its symbol; the struct's names are not the original's)
    struct Locomotion {
        mm::Vec3 m_translation;
        mm::Quat m_rotation;
    };
    const Locomotion* getLocomotion() const;
    // the gravity it falls with: minus the parameters' entry 1 while m_stateFlags bit 3 is set, else none
    float getGravity() const;
    // m_stateFlags bit 10 set (on) or cleared, then the parameters re-picked and m_field's status reset
    void setPadControl(bool on);
    // m_paramList from ParamManager's list 13, m_field's from list 14 while m_stateFlags bit 10 is set, else 15
    void resetParams();
    void cleanup();
    // m_pos and m_rot written to the transform's frame (its local transform synced under a parent, its child
    // frame's world transform), then m_lastPos and m_lastRot kept as m_prevPos and m_prevRot
    void writeBack();
    void procMsgObjectFlushProperty(fw::MessageObject* sender, gf::MsgObjectFlushProperty& msg);
    // 1.0.0's message handlers (3.0.1 inlines them into recieveMessage)
    void procMsgActivateComponentDebugWindow(fw::MessageObject* sender, gf::MsgDebugActivateComponentWindow& msg);
    void procMsgPcFieldNotifyChangePlayerID(fw::MessageObject* sender, gf::MsgPcFieldNotifyChangePlayerID& msg);
    void procMsgObjectGetVelocity(fw::MessageObject* sender, gf::MsgObjectGetVelocity& msg);
    // m_paramList's entry index, read without a bounds check (inline: the name is not the original's)
    template <typename T>
    const T* getParam(unsigned int index) const {
        return static_cast<const T*>(m_paramList->m_entries[index].m_data);
    }
    // m_paramList's entry index, none past its end (inline: the name is not the original's; StateUtilField's
    // isBigSplashFallSpeed keeps its component's null check only behind a member call)
    fw::ParamAdapter getParamAdapter(unsigned int index) const { return m_paramList->getAdapter(index); }
    // m_paramList's entry 1 (the names are not the original's)
    struct GravityParam {
        float m_gravity;  // getGravity: the PC falls with minus it
        // StateUtil::reflectionAdsorption: the collision's adsorption on flat ground and in the air, the one it
        // blends to as the ground's slope reaches m_slopeAngle (degrees)
        float m_adsorption;
        float m_slopeAdsorption;
        float m_slopeAngle;
        unsigned char pad_10[0x8];
        // StateUtilField::isBigLandDistance: a fall from at least this high (FallDistancePlugin::calcDistance, plus
        // 0.01) lands big (the name is not the original's)
        float m_bigLandDistance;
        // StateUtilField::isBigSplashFallSpeed: a fall at least this fast makes the big splash (the name is not the
        // original's)
        float m_bigSplashFallSpeed;
    };
    // m_paramList's entry 4 (gf::pc's, by setMoveSlidePacket's symbol)
    typedef pc::SlideParam SlideParam;
    // by its symbol (GfComBehaviorPc's warps call it)
    void flush();
    // by its symbol: the camera's directions from the inverse of the view matrix (flush passes CameraManager's)
    void setViewMtx(const mm::Mat44& viewMtx);
    // by its symbol: the world directions the stick moves the PC along (up, the camera's front and right flattened)
    void updateWorldDirs();
    // by its symbol: the water states call it after turning m_rot
    void syncDirection();

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

    // StateFieldOnGround::update: at 1 a battle start hands m_battle MsgPcBattleStart(0) and goes to state 0x3F,
    // otherwise it asks StateUtilField::requestBattleStart (the name is not the original's)
    int m_battleStartKind;
    // the height GfComBehaviorPc::resetHeadColPosition hands calcHeadColiPos, which it skips while this is not above
    // FLT_EPSILON (the name is not the original's)
    float m_headColiHeight;
    unsigned char pad_44[0xC];
    mm::Vec3 m_headColiPos;  // resetHeadColPosition's: what calcHeadColiPos computes (the name is not the original's)
    InputDir m_inputDir;
    // the actions asked for this frame, by gf::pc::InputID: the pad's action handlers set them (0 to 4 from
    // PadField's, PadBattle's up to 32 for "spskill"), TaskFieldJump::update 2; PadAgent::update clears them each
    // frame. A Bitflag<40>: BattleCharacter::IsInputButtonDirect's operator[] asserts index < Size against 0x28
    // (the name is not the original's)
    mm::mtl::Bitflag<40> m_inputFlags;
    InputDir m_prevInputDir;                // PadAgent::update's copy of last frame's m_inputDir
    mm::mtl::Bitflag<40> m_prevInputFlags;  // and of m_inputFlags
    mm::Vec3 m_velocity;        // TaskFieldJump::update keeps its speed, turned along m_moveDir
    // two more of its motions: 1.0.0's procMsgObjectFlushProperty counts the PC as moving while either (or the
    // velocity or the locomotion) is not zero; isFollowBuddyPc keeps following while m_moveVec2.y is not, the
    // follow tests while m_moveSpeed is above 0 (the names are not the original's)
    mm::Vec2 m_moveVec2;
    Locomotion m_locomotion;  // setLocomotion's translation and rotation
    float m_moveSpeed;
    // StateUtilField::isBigSplashFallSpeed adds m_moveSpeed times its y to the fall speed (meaning not known)
    mm::Vec3 pad_d0;
    mm::Vec3 pad_e0;
    float pad_f0;
    mm::Vec3 m_colVel;          // ColVelCalculatorPlugin::update's: the ground's movement it carries the PC with
    // bit 4: ColVelCalculatorPlugin::update takes the ground's movement; bit 10: DeadColCheckPlugin::testDead asks
    // the first collision object instead of the dead plane
    unsigned int m_stateFlags;
    // flush's: how deep in water the PC is, 0 out of it up to 3 (the water surface at least its chest height above
    // the ground under it); the field AI takes its swimming parameters at 3 (the name is not the original's)
    int m_waterLevel;
    // StateUtilField::isInterruptionWater: the PC is out of the water once m_pos.y is 0.2 above it less m_chestHeight
    float pad_118;
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
    mm::Quat m_prevRot;         // writeBack's: m_lastRot, kept with m_prevPos (the name is not the original's)
    // what writeBack hands on to m_prevPos and m_prevRot after writing m_pos and m_rot to the transform (the names
    // are not the original's)
    mm::Vec3 m_lastPos;
    mm::Quat m_lastRot;
    mm::Vec3 m_frontDir;        // StateFieldIdle::checkSpace starts its capsule 0.6 along it from m_pos
                                // (the name is not the original's)
    mm::Vec3 m_frontDirInv;     // syncDirection's -m_frontDir (the name is not the original's)
    mm::Vec3 m_moveDir;         // TaskFieldJump::update sets m_velocity along it
    // syncDirection stores -m_moveDir here; the turn states turn to it when the stick gives no direction
    // (the name is not the original's)
    mm::Vec3 m_moveDirInv;
    // AgentUtilField::setFollowWallEndInput sets the stick's x by the target's side along it, as its y by m_frontDir
    // (the name is not the original's)
    mm::Vec3 m_sideDir;
    // syncDirection's -m_sideDir: m_frontDir, m_moveDir and m_sideDir are m_rot's y, z and -x axes, each kept with
    // its negation (the name is not the original's)
    mm::Vec3 m_sideDirInv;
    // setViewMtx's, from the inverse of the view matrix: its translation row (the camera's position) and its rows
    // 1, 2 and 0 each with its negation, -row 2 (the camera's front) first (the names are not the original's)
    mm::Vec3 m_viewPos;
    mm::Vec3 m_viewUp;
    mm::Vec3 m_viewDown;
    mm::Vec3 m_viewFront;
    mm::Vec3 m_viewBack;
    mm::Vec3 m_viewRight;
    mm::Vec3 m_viewLeft;
    // two of updateWorldDirs' world directions: the ones the stick's y and x move the PC along
    // (TaskFieldWallEscape::update picks the stick's signs by them; the names are not the original's)
    mm::Vec3 m_stickFrontDir;
    mm::Vec3 m_stickFrontDirInv;  // updateWorldDirs': -m_stickFrontDir (the name is not the original's)
    // updateWorldDirs': the front direction at +0x250 flattened against m_stickFrontDir and normalized; the turn
    // states move the stick's y along it with m_stickSideDir for its x (the name is not the original's)
    mm::Vec3 m_groundFrontDir;
    mm::Vec3 m_groundFrontDirInv;  // updateWorldDirs': -m_groundFrontDir (the name is not the original's)
    // updateWorldDirs': m_viewRight flattened the same way (else m_sideDir), and its negation (the names are not
    // the original's)
    mm::Vec3 m_stickSideDir;
    mm::Vec3 m_stickSideDirInv;
    float m_chestHeight;        // setup's: the character data's chest height in metres (the name is not the original's)
    // flush's: water at least this deep (above the ground under the PC) puts it at m_waterLevel 2 (the name is
    // not the original's)
    float m_waistHeight;
    // StateFieldWater::update takes the PC out of water once m_waterDepth is no more than it (the name is not the
    // original's)
    float m_waterLeaveDepth;
    unsigned char pad_2fc[0x4];
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // the PC's parameters
    unsigned char pad_308[0x8];
    pc::GfPropertyField m_field;  // setup, cleanup and flush pass it this property
    pc::GfPropertyBattle m_battle;  // StateField::recieveMessage hands it the battle start (0x470)
};
}  // namespace gf

#endif
