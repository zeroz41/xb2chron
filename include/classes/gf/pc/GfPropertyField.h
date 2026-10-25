#ifndef CLASSES_GF_PC_GFPROPERTYFIELD_H
#define CLASSES_GF_PC_GFPROPERTYFIELD_H

#include "classes/fw/ParamList.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfComPropertyPc; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MsgPcFieldNotifyWallJump; }
namespace gf { class MsgPcFieldNotifyWarp; }
namespace gf { class MsgPcFieldNotifyBigJump; }

namespace gf { namespace pc {
// table 0x7100B67E78
class GfPropertyField {
public:
    GfPropertyField();
    virtual void setup(gf::GfComPropertyPc const&);  // slot 0
    virtual void cleanup(gf::GfComPropertyPc const&);  // slot 1
    virtual void flush(gf::GfComPropertyPc const&);  // slot 2
    virtual void flushOwner(gf::GfComPropertyPc&);  // slot 3
    virtual void recieveMessage(gf::GfComPropertyPc const&, fw::MessageObject*, fw::Message&);  // slot 4

    // m_paramList's entry 0 (the names are not the original's)
    struct MoveParam {
        unsigned char pad_0[0x24];
        // StateFieldStopBrake::update runs its stop motion (asm command 5) once the PC is this slow; at 0 it has
        // none and goes to C_idle when the PC stands
        float m_brakeStopSpeed;
        float m_brakeSlowSpeed;  // StateFieldWaterBrake::update runs C_swim_01 once the PC is this slow
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

    // the wall jump the PC prepares (the name is not the original's)
    struct WallJumpInfo {
        unsigned char pad_0[0x10];
        mm::Vec3 m_pos;  // where it lands (TaskFieldWallJumpWait::update waits while another player is near it)
        unsigned char pad_20[0xC];
        // StateFieldWallJump::leave hands it to SCOM_QUEST_GIMMICK::createJump (the name is not the original's)
        unsigned int m_gimmickId;
    };
    // the wall the PC is on (StateUtilField::getWallInfoBase returns it while status bit 0x40 is set; the names are
    // not the original's)
    struct WallInfo {
        unsigned char pad_0[0x20];
        float m_blend;         // StateFieldWall::enter copies it to m_wallBlend
        unsigned int m_flags;  // bit 7: StateFieldWall::flushWallType's sound variable 2
        unsigned char pad_28[0x8];
    };
    const WallJumpInfo* getWallJumpInfo() const;
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
    unsigned char pad_14[0x4];
    // StateFieldWall::enter takes it from the wall info (+0x130) when status bit 0x40 is set;
    // StateFieldWallAdsorptionAir::update blends it to m_wallBlendTarget over a parameter's time (the names are not the
    // original's)
    float m_wallBlend;
    unsigned char pad_1c[0x30];
    float m_wallBlendTarget;
    // the warp states set the child frame's height to minus it as the PC comes out of a warp (the name is not the
    // original's)
    float m_warpRiseDepth;
    // setup reads it from the asm's "uniqueIdleSpace" appendix: the room StateFieldIdle::checkSpace tests for a unique
    // idle motion, the length of its capsule (0: no test; the name is not the original's)
    float m_uniqueIdleSpace;
    unsigned char pad_58[0x20];
    // the object that sent the last wall jump or warp notice (StateFieldWallPrepareJump::procMsgPcFieldNotifyWallJump
    // and StateFieldWaterPrepareWarp store it; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_noticeSender;
    unsigned char pad_80[0xB0];
    WallInfo m_wallInfo;  // getWallInfo returns it. Size: GfComPropertyPc's GfPropertyBattle follows at 0x160
};
}}  // namespace gf::pc

#endif
