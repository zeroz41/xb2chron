#ifndef GF_PC_MOVEUTILFIELD_H
#define GF_PC_MOVEUTILFIELD_H

#include "classes/gf/GfMoveJumpControler.h"
#include "classes/gf/GfMoveRunControler.h"
#include "classes/gf/GfMoveSlideControler.h"

namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace gf { class GfComPropertyPc; }
namespace gf { namespace pc { struct SlideParam; } }

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
    static void updateMoveSlide(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);  // (by its symbol)
    // the PC's climb velocity on its wall by m_field's wall move mode (by its symbol; StateFieldWallMove::update)
    static void updateMoveWall(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    // the water states'
    static void enterMoveSwim(gf::GfComPropertyPc& property);
    static void updateMoveSwim(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterSink(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterRise(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterHoleRise(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    static void updateMoveWaterTurn(const fw::UpdateInfo& info, gf::GfComPropertyPc& property, const mm::Vec3& dir);
};

// the run controler's packet from the property and its param list (on the ground / in water)
void setMoveRunPacket(gf::GfComPropertyPc& property, gf::GfMoveRunControler::Packet* packet);
void setMoveSwimPacket(gf::GfComPropertyPc& property, gf::GfMoveRunControler::Packet* packet);
// the jump controler's packet from the property (its velocity, turning speed and param list entry)
void setMoveJumpPacket(gf::GfComPropertyPc& property, gf::GfMoveJumpControler::Packet* packet);
// the slide controler's packet from the property and its slide parameters (by its symbol)
void setMoveSlidePacket(gf::GfComPropertyPc& property, const SlideParam& param, gf::GfMoveSlideControler::Packet* packet);

}}  // namespace gf::pc

#endif
