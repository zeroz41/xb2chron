#ifndef CLASSES_FW_COLIMOVEOBJECT_H
#define CLASSES_FW_COLIMOVEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ColiObject.h"

namespace mm { class Vec3; }

namespace fw {
// table 0x7100B41140
class ColiMoveObject : public ::fw::ColiObject {
public:
    virtual ~ColiMoveObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void postUpdate();  // slot 4
    virtual void setDir(mm::Vec3 const&);  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
