#ifndef CLASSES_FW_COLIMOVEOBJECT_H
#define CLASSES_FW_COLIMOVEOBJECT_H

#include "classes/fw/ColiObject.h"

namespace mm { class Vec3; }

namespace fw {
// table 0x7100B41140
class ColiMoveObject : public ::fw::ColiObject {
public:
    virtual ~ColiMoveObject();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void postUpdate();  // slot 4
    virtual void setDir(mm::Vec3 const&);  // slot 5
};
}  // namespace fw

#endif
