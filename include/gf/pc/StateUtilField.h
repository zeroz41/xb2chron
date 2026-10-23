#ifndef GF_PC_STATEUTILFIELD_H
#define GF_PC_STATEUTILFIELD_H

#include "mm/Vec3.h"

namespace gf { class GfComPropertyPc; }
namespace gf { class GfComBehaviorPc; }
namespace mm { class Plane; }

namespace gf { namespace pc {

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
};

}}  // namespace gf::pc

#endif
