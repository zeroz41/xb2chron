#ifndef GF_PC_MOVEUTILFIELD_H
#define GF_PC_MOVEUTILFIELD_H

namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {

// the PC's field movement helpers (functions, by their symbols)
class MoveUtilField {
public:
    static void enterMoveRun(gf::GfComPropertyPc& property, bool flag);
    static void updateMoveRun(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveTurn(const fw::UpdateInfo& info, gf::GfComPropertyPc& property, const mm::Vec3& dir);
    static void updateMoveWalkTurn(const fw::UpdateInfo& info, gf::GfComPropertyPc& property, const mm::Vec3& dir);
    static void updateFallDown(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateBrake(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static float getSpeedEffect(gf::GfComPropertyPc& property);
    static void updateMoveJump(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveJumpBack(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateLandBrake(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    // the water states'
    static void enterMoveSwim(gf::GfComPropertyPc& property);
    static void updateMoveSwim(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterSink(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterRise(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterHoleRise(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterTurn(const fw::UpdateInfo& info, gf::GfComPropertyPc& property, const mm::Vec3& dir);
};

}}  // namespace gf::pc

#endif
