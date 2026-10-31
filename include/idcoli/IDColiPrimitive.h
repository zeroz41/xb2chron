#ifndef IDCOLI_IDCOLIPRIMITIVE_H
#define IDCOLI_IDCOLIPRIMITIVE_H

#include "classes/idcoli/IDColiObjBase.h"

namespace idcoli { class CLBoxWork; }
namespace idcoli { class CLCapsuleWork; }
namespace idcoli { class IDCmfPosData; }

namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace idcoli {
// builds an object's base shape (into IDColiObjBase::m_base) from a matrix and a size, and its bounding box
class IDColiPrimitive {
public:
    // fills a position record from a matrix and two corners (the transposed matrix, its inverse, the bounds)
    static void calcPosDataSetup(IDCmfPosData* posData, const mm::Mat44& matrix, const mm::Vec3& corner0,
                                 const mm::Vec3& corner1);
    static void calcBaseBoxSetup(CLBoxWork* box, const mm::Mat44& matrix, const mm::Vec3& size);
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
    // the bounding box of a shape work (min, max)
    static void createAaBbSphere(mm::Vec3& max, mm::Vec3& min, const void* shape);
    static void createAaBbBox(mm::Vec3& max, mm::Vec3& min, const void* shape);
    static void createAaBbCapsule(mm::Vec3& max, mm::Vec3& min, const void* shape);
    static void createAaBbPoli(mm::Vec3& min, mm::Vec3& max, const void* shape);
    // a shape work's position, offset, flag, radius and height; the parameter names are not the original's
    static void createBaPosSphere(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                  const void* shape);
    static void createBaPosBox(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                               const void* shape);
    static void createBaPosCapsule(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                   const void* shape);
    static void createBaPosPoli(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                const void* shape);
};
}  // namespace idcoli

#endif
