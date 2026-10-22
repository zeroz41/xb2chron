#include "mm/Mat44.h"
#include "mm/Obb.h"

namespace mm {

void Obb::setMat(const Mat44& mat, const Vec3& size) {
    m_mat = mat;
    m_size = size;
}

}  // namespace mm
