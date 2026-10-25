#ifndef CLASSES_GF_PC_GFPROPERTYFIELD_H
#define CLASSES_GF_PC_GFPROPERTYFIELD_H

#include "classes/fw/ParamList.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "gf/MsgPcFieldNotifyBigJump.h"
#include "gf/MsgPcFieldNotifyWarp.h"
#include "gf/MsgPcFieldNotifyWallJump.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfComPropertyPc; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf { namespace pc {
// table 0x7100B67E78
class GfPropertyField {
public:
    // how the PC moves on a wall (the type is the symbols'; StateUtilField::getAsmID maps 0-7 to climb commands, 0, 1
    // and 7 move up by StateUtilField::isWallUpMove; no enumerator names known)
    enum WALL_MOVE_MODE {};

    GfPropertyField();
    virtual void setup(gf::GfComPropertyPc const&);  // slot 0
    virtual void cleanup(gf::GfComPropertyPc const&);  // slot 1
    virtual void flush(gf::GfComPropertyPc const&);  // slot 2
    virtual void flushOwner(gf::GfComPropertyPc&);  // slot 3
    // handles message 0x100003E (hands the wall to the target property): whether it did
    virtual bool recieveMessage(gf::GfComPropertyPc const&, fw::MessageObject*, fw::Message&);  // slot 4
    // m_paramList's entry index, read without a bounds check (StateUtilField::isStop, getWallHeightOffset; inline,
    // the name is not the original's)
    template <typename T>
    const T* getParam(unsigned int index) const {
        return static_cast<const T*>(m_paramList->m_entries[index].m_data);
    }
    void resetStatus(const gf::GfComPropertyPc& property);
    void flashWallInfo(const gf::GfComPropertyPc& property);
    float getWallHeightOffset() const;

    // m_paramList's entry 0 (the names are not the original's)
    struct MoveParam {
        unsigned char pad_0[0x4];
        // StateUtilField::isStop: the PC stops once the stick has given nothing for this many frames
        unsigned int m_stopFrames;
        unsigned char pad_8[0x10];
        // StateUtilField::ignoreOnGroundJump: a jump ignores the ground until this time
        float m_groundIgnoreTime;
        unsigned char pad_1c[0x8];
        // StateFieldStopBrake::update runs its stop motion (asm command 5) once the PC is this slow; at 0 it has
        // none and goes to C_idle when the PC stands
        float m_brakeStopSpeed;
        float m_brakeSlowSpeed;  // StateFieldWaterBrake::update runs C_swim_01 once the PC is this slow
    };

    // m_paramList's entry 15 (the name is not the original's)
    struct WallParam {
        unsigned char pad_0[0x38];
        float m_heightRate;  // getWallHeightOffset scales m_upLanding1Height by it (the name is not the original's)
    };

    // the water states' parameters: m_paramList's entry 9 (the names are not the original's)
    struct WaterParam {
        float m_sinkTime;      // StateFieldWaterSink::update: how long the PC sinks before it rises
        float m_sinkDepth;     // and how deep (the child frame's height below the surface) it sinks at most
        unsigned char pad_8[0x4];
        float m_swimSinkTime;  // StateFieldWaterSwimSink::update: how long the PC sinks swimming
        unsigned char pad_10[0x8];
        float m_warpDiveTime;  // StateFieldWaterWarpDive: how long the dive into a warp lasts
        float m_maxSinkSpeed;  // StateFieldWaterDeadSink::enter limits the downward speed to it
    };

    // the wall the PC is on (StateUtilField::getWallInfoBase returns it while status bit 0x40 is set; the names are
    // not the original's)
    struct WallInfo {
        unsigned char pad_0[0x20];
        float m_blend;         // StateFieldWall::enter copies it to m_wallBlend
        unsigned int m_flags;  // bit 7: StateFieldWall::flushWallType's sound variable 2
        unsigned char pad_28[0x8];
    };
    // the kept wall jump notice, none while status bit 14 is clear (by its symbol): StateFieldWallJump::leave hands
    // its m_gmkId to SCOM_QUEST_GIMMICK::createJump, TaskFieldWallJumpWait::update waits while a player is near m_pos
    const gf::MsgPcFieldNotifyWallJump* getWallJumpInfo() const;
    const WallInfo* getWallInfo() const { return (m_statusFlags & 0x40) ? &m_wallInfo : nullptr; }
    // keeps a wall jump notice (StateFieldWallPrepareJump::procMsgPcFieldNotifyWallJump hands it on); null clears
    // the jump's status bit
    void setWallJump(const MsgPcFieldNotifyWallJump* msg);
    // keeps the warp a MsgPcFieldNotifyWarp tells of (StateFieldWaterPrepareWarp hands it on)
    void setWarpInfo(const gf::MsgPcFieldNotifyWarp* msg);
    // the kept warp notice, none while status bit 13 is clear (by its symbol)
    const gf::MsgPcFieldNotifyWarp* getWarpInfo() const;
    // keeps a big jump notice; null clears the big jump's status bit 12 (by its symbol)
    const gf::MsgPcFieldNotifyBigJump* getBigJumpInfo() const;  // (by its symbol)
    void setBigJumpInfo(const gf::MsgPcFieldNotifyBigJump* msg);

    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // the PC's field parameters (FadePlugin::setup takes entry 18)
    // resetStatus and flush set its bits; bit 2: TaskFieldIdle::update clears the field AI blackboard's bit 3
    // while it is set, TaskFieldIdleTurn::testCondition requires it
    unsigned int m_statusFlags;
    int pad_14;  // the constructor sets -1
    // StateFieldWall::enter takes it from the wall info (+0x130) when status bit 0x40 is set;
    // StateFieldWallAdsorptionAir::update blends it to m_wallBlendTarget over a parameter's time (the names are not the
    // original's)
    float m_wallBlend;
    // setup's, from the asm's locomotion: per landing motion ("S_uplanding_00/01", "S_downlanding_00/01") how far it
    // moves across (the length of its x and z) and how high (its y; downlanding_01's plus 0.01); per climb motion
    // ("S_climbup_base", "S_climedown_base", "S_climbright_base") its playback time scaled by entry 16's speed
    // factors; "S_climbjump_base_02"'s height (the names are not the original's)
    float m_upLanding0Dist;
    float m_upLanding0Height;
    float m_upLanding1Dist;
    float m_upLanding1Height;  // getWallHeightOffset scales it
    float m_downLanding0Dist;
    float m_downLanding0Height;
    float m_downLanding1Dist;
    float m_downLanding1Height;
    float m_climbUpTime;
    float m_climbDownTime;
    float m_climbSideTime;
    float m_climbJumpHeight;
    // setup reads it from the asm's "wallOffset" appendix (the name is not the original's)
    float m_wallBlendTarget;
    // the warp states set the child frame's height to minus it as the PC comes out of a warp; setup takes it from
    // "S_waterhole_01"'s locomotion height (the name is not the original's)
    float m_warpRiseDepth;
    // setup reads it from the asm's "uniqueIdleSpace" appendix: the room StateFieldIdle::checkSpace tests for a unique
    // idle motion, the length of its capsule (0: no test; the name is not the original's)
    float m_uniqueIdleSpace;
    unsigned char pad_58[0x8];
    mm::Vec3 pad_60;    // the constructor sets zero
    int pad_70;         // and 0
    unsigned char pad_74[0x4];
    // the object that sent the last wall jump or warp notice (StateFieldWallPrepareJump::procMsgPcFieldNotifyWallJump
    // and StateFieldWaterPrepareWarp store it; the constructor sets none, -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_noticeSender;
    // the notices setBigJumpInfo, setWarpInfo and setWallJump keep (status bits 12, 13, 14; the names are not the
    // original's)
    gf::MsgPcFieldNotifyBigJump m_bigJump;
    gf::MsgPcFieldNotifyWarp m_warp;
    gf::MsgPcFieldNotifyWallJump m_wallJump;
    WallInfo m_wallInfo;  // getWallInfo returns it. Size: GfComPropertyPc's GfPropertyBattle follows at 0x160
};
}}  // namespace gf::pc

#endif
