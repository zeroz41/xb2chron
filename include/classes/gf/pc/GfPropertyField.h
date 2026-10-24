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

    // the wall jump the PC prepares (the name is not the original's)
    struct WallJumpInfo {
        unsigned char pad_0[0x10];
        mm::Vec3 m_pos;  // where it lands (TaskFieldWallJumpWait::update waits while another player is near it)
    };
    const WallJumpInfo* getWallJumpInfo() const;
    // keeps a wall jump notice (StateFieldWallPrepareJump::procMsgPcFieldNotifyWallJump hands it on); null clears
    // the jump's status bit
    void setWallJump(const MsgPcFieldNotifyWallJump* msg);
    // keeps the warp a MsgPcFieldNotifyWarp tells of (StateFieldWaterPrepareWarp hands it on)
    void setWarpInfo(const gf::MsgPcFieldNotifyWarp* msg);

    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // the PC's field parameters (FadePlugin::setup takes entry 18)
    // resetStatus and flush set its bits; bit 2: TaskFieldIdle::update clears the field AI blackboard's bit 3
    // while it is set, TaskFieldIdleTurn::testCondition requires it
    unsigned int m_statusFlags;
    unsigned char pad_14[0x40];
    // setup reads it from the asm's "uniqueIdleSpace" appendix: the room StateFieldIdle::checkSpace tests for a unique
    // idle motion, the length of its capsule (0: no test; the name is not the original's)
    float m_uniqueIdleSpace;
    unsigned char pad_58[0x20];
    // the object that sent the last wall jump or warp notice (StateFieldWallPrepareJump::procMsgPcFieldNotifyWallJump
    // and StateFieldWaterPrepareWarp store it; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_noticeSender;
    unsigned char pad_80[0xE0];  // size: GfComPropertyPc's GfPropertyBattle follows at 0x160
};
}}  // namespace gf::pc

#endif
