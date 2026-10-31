#ifndef ANM_TRANSFORMUTIL_H
#define ANM_TRANSFORMUTIL_H

namespace anm { class QsTransform; }
namespace mm { class Mat44; }

namespace anm {
// operations on QsTransforms (anm_transform_util.cpp)
class TransformUtil {
public:
    // the transform that undoes `t`
    static void invert(const QsTransform& t, QsTransform* pOut);
    // `a` then `b` as one transform
    static void mul(const QsTransform& a, const QsTransform& b, QsTransform* pOut);
    // `t` as a matrix: its scale, then its rotation, then its translation (anm_pose.cpp)
    static void calcMatrix(const QsTransform& t, mm::Mat44* pOut);
};
}  // namespace anm

#endif
