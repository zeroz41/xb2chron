#ifndef CLASSES_GF_IGFBEHFIELDOWNER_H
#define CLASSES_GF_IGFBEHFIELDOWNER_H

#include "fw/Transform.h"

namespace gf {
// what the field movement asks its owner (GfComBehaviorEnemy's base at 0x98). The name is the original's: the
// symbols spell it in GfFieldEnemySensor::update(GF_OBJ_HANDLE*, const IGfBehFieldOwner&)
class IGfBehFieldOwner {
public:
    virtual const fw::Transform& getTransform() const = 0;
    virtual const fw::Transform& getTransformToSearchPlayer() const = 0;
    virtual unsigned int getBdatId_CHR_EnArrange() const = 0;
    virtual void getGmkBattleLockInfo(int&, int&) const = 0;
};
}  // namespace gf

#endif
