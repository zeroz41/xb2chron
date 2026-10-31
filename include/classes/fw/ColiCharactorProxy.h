#ifndef CLASSES_FW_COLICHARACTORPROXY_H
#define CLASSES_FW_COLICHARACTORPROXY_H

#include "mm/Vec3.h"

namespace fw { class ColiObject; }

namespace fw {
// moves a character's collision object as far as the collision allows (GfComBehaviorPc builds one on the stack);
// the field names are not the original's
class ColiCharactorProxy {
public:
    ColiCharactorProxy();
    // moves the object from `position` by `move`; `result` gets how far it went
    void integrate(mm::Vec3 const& position, mm::Vec3 const& move, mm::Vec3* result);

    ColiObject* m_object;  // whose IDColiObj is moved
    float m_floor;         // handed to IDColiMove::setFloor (0.4 by default)
};
}  // namespace fw

#endif
