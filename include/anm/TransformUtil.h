#ifndef ANM_TRANSFORMUTIL_H
#define ANM_TRANSFORMUTIL_H

namespace anm { class QsTransform; }

namespace anm {
// operations on QsTransforms (anm_transform_util.cpp)
class TransformUtil {
public:
    // the transform that undoes `t`
    static void invert(const QsTransform& t, QsTransform* pOut);
    // `a` then `b` as one transform
    static void mul(const QsTransform& a, const QsTransform& b, QsTransform* pOut);
};
}  // namespace anm

#endif
