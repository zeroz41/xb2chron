#ifndef CLASSES_IDCOLI_IDCOLIOBJBASE_H
#define CLASSES_IDCOLI_IDCOLIOBJBASE_H

#include "classes/idcoli/IDColiObj.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace idcoli {
// table 0x7100B7F0F0
// the fields IDColiParmsBase and the shape creators of IDColiParmsCharacter/IDColiParmsPhantom reach (0x1D0 bytes:
// IDColiManager::createColiPhantom allocates its IDColiObjPhantomCheck so). The names are not the original's.
class IDColiObjBase : public ::idcoli::IDColiObj {
public:
    virtual ~IDColiObjBase();  // slot 0

    mm::Vec3 m_max;  // 0x50, IDColiParmsBase::getMax
    mm::Vec3 m_min;  // 0x60, IDColiParmsBase::getMin
    mm::Mat44 m_matrix;  // 0x70, IDColiParmsBase::setMatrix
    mm::Vec3 m_size;  // 0xB0, the shape's extents (a sphere's radius in all three)
    int m_shapeType;  // 0xC0, 0 sphere, 1 box, 2 capsule, 3 character, 6/7 the box/capsule with flag 0x400
    unsigned char pad_c4[4];
    unsigned int m_offMaterialBit;  // 0xC8, IDColiParmsBase::setOffMaterialBit
    unsigned char pad_cc[0x100];
    int m_priority;  // 0x1CC, IDColiParmsBase::setPriority
};
}  // namespace idcoli

#endif
