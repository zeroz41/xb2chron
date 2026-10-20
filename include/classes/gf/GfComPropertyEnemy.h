#ifndef CLASSES_GF_GFCOMPROPERTYENEMY_H
#define CLASSES_GF_GFCOMPROPERTYENEMY_H

#include "classes/gf/GfComProperty.h"

namespace gf {
// table 0x7100B660D0
class GfComPropertyEnemy : public ::gf::GfComProperty {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComPropertyEnemy();  // slot 1
};
}  // namespace gf

#endif
