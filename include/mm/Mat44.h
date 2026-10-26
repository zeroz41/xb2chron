#ifndef MM_MAT44_H
#define MM_MAT44_H

#include <stddef.h>
#include <string.h>
#include "mm/MMStdBase.h"

// mm_lib's mm_math/mm_mat44.h, as the including file's include path named it (see mm/Math.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MAT44_PATH "../../../mcl/mm_lib/source\\mm_math/mm_mat44.h"
#elif defined(MM_LIB_FROM_XBRD)
// xbrd's (ScnObjModelDrSysStandard::apply's matrix copy cites it so)
#define MM_MAT44_PATH "D:/Monolithsoft/BF2/prog/libs/xbrd/proj/windows/../../../mcl/mm_lib/source\\mm_math/mm_mat44.h"
#else
#define MM_MAT44_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_math/mm_mat44.h"
#endif

// the alignment a matrix keeps (its copy asserts it of the source)
#define MM_MAT_ALIGN 16

namespace mm {

// a 4x4 matrix: 0x40 bytes, copied whole (Obb::setMat copies one with a 0x40-byte memcpy). Its rows are
// laid out as Sphere::getOBB builds one on its stack, the translation in the last. A copy made by
// construction first asserts the source's alignment (mm_mat44.h line 195; ColiMoveObject::postUpdate).
class Mat44 {
public:
    Mat44() {}
    Mat44(const Mat44& ma) {
#line 195 MM_MAT44_PATH
        MM_ASSERT((reinterpret_cast<size_t>(&ma) & size_t(MM_MAT_ALIGN - 1)) == 0);
        memcpy(this, &ma, sizeof(Mat44));
    }
    Mat44& operator=(const Mat44& ma) = default;

    float m[4][4];

    static const Mat44 identity;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
