#ifndef MM_OBB_H
#define MM_OBB_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace mm {

// an oriented bounding box (mm_math/mm_obb): its placement as a matrix and its size along the matrix's axes.
// No table: setMat writes the matrix at its start.
class Obb {
public:
    void setMat(const Mat44& mat, const Vec3& size);

    Mat44 m_mat;
    Vec3 m_size;  // Sphere::getOBB passes its own Vec3 at 0x30 for it
};

}  // namespace mm

#endif
