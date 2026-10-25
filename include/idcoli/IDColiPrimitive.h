#ifndef IDCOLI_IDCOLIPRIMITIVE_H
#define IDCOLI_IDCOLIPRIMITIVE_H

#include "classes/idcoli/IDColiObjBase.h"

namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace idcoli {
// builds an object's base shape (into IDColiObjBase::m_base) from a matrix and a size, and its bounding box
class IDColiPrimitive {
public:
    static void createBaseSphere(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    static void createBaseBox(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    static void createBaseCapsule(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    static void createBaseCharacter(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    static void createBasePoli(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    static void createBaseInBox(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    static void createBaseInCapsule(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size);
    // the bool: IDColiObjData::primset_subbase passes whether the object's flag 0x800 is clear
    static void createSubBaseCharacter(void* base, IDColiBaseType& type, const mm::Mat44& matrix,
                                       const mm::Vec3& size, bool flag);
};
}  // namespace idcoli

#endif
