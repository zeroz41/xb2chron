#ifndef GF_PC_STATEUTILFIELD_H
#define GF_PC_STATEUTILFIELD_H

#include "mm/Vec3.h"

namespace gf { class GfComAsm; }
namespace gf { class GfComPropertyPc; }
namespace gf { class GfComBehaviorPc; }
namespace mm { class Plane; }

namespace gf { namespace pc {
// the PC's field asm commands execAsmCmd takes: an index into getASMCmdNameField's TABLE of command names (the type
// is the symbols'; only the values used so far are named, and those names are not the original's: they spell the
// command name the table holds at that index; callers also pass 0x15 from StateFieldOnWall's wall jump and 1 from
// StateFieldIdle::update)
enum ASM_CMD_ID_FIELD : unsigned int {
    ASM_CMD_ID_FIELD_WATERIDLE = 7,      // "C_wateridle"
    ASM_CMD_ID_FIELD_WATERHOLE_00 = 10,  // "C_waterhole_00"
};

// what the PC's field states share (functions, by its symbols)
class StateUtilField {
public:
    // where the PC gets ready to climb a wall: from the wall's point and plane
    static mm::Vec3 calcWallPreparePosition(gf::GfComPropertyPc& property, const mm::Vec3& wallPos,
                                            const mm::Plane& wallPlane);
    static bool isEnableWallAdsorptionStart(gf::GfComPropertyPc& property, const mm::Vec3& wallPos,
                                            const mm::Vec3& preparePos);
    static bool isEnableWallPrepare(gf::GfComPropertyPc& property);
    static bool isWallPreparePosition(gf::GfComPropertyPc& property, const mm::Vec3& preparePos);
    static void setAccessFlag(gf::GfComBehaviorPc& behavior, bool flag);
    static void setSpecialActStatus(gf::GfComBehaviorPc& behavior, bool status);
    static void setEnableLure(gf::GfComBehaviorPc& behavior, bool enable);  // StateFieldLure::leave's (by its symbol)
    // the auto-run: toggled, set, tested and fed to the input (by their symbols)
    static void flipAutoRun(gf::GfComPropertyPc& property);
    static void setAutoRun(gf::GfComPropertyPc& property, bool on);
    static bool testAutoRun(gf::GfComPropertyPc& property);
    static void setAutoRunInput(gf::GfComPropertyPc& property);
    static bool isInputInverseDirAutoRun(gf::GfComPropertyPc& property);
    static void setWaterMode(gf::GfComBehaviorPc& behavior, bool water);
    static void setLookAtFlag(gf::GfComBehaviorPc& behavior, bool flag);
    static void setIdleStatus(gf::GfComPropertyPc& property, bool idle);
    // runs a field animation command on the PC's animation state machine: whether it ran
    static bool execAsmCmd(gf::GfComAsm& comAsm, ASM_CMD_ID_FIELD id);
    // the water states set it entering a dive and clear it leaving one
    static void setWaterDiveMove(gf::GfComPropertyPc& property, bool dive);
    // StateFieldJump::leave's (by its symbol)
    static void notifyJumpEnd(gf::GfComBehaviorPc& behavior);
    // the air states' (StateFieldAir::enter/leave, StateFieldLand::leave; by their symbols)
    static void setAirStatus(gf::GfComBehaviorPc& behavior, bool air);
    static void setEnableWaterIn(gf::GfComBehaviorPc& behavior, bool enable);
    static void setEnableFallIntoColi(gf::GfComBehaviorPc& behavior, bool enable);
    // StateFieldAir::leave's into state 0x36 (by its symbol)
    static void setSlideDirForce(gf::GfComPropertyPc& property);
};

}}  // namespace gf::pc

#endif
