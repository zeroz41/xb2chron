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
};

}}  // namespace gf::pc

#endif
