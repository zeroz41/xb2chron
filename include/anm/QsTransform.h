#ifndef ANM_QSTRANSFORM_H
#define ANM_QSTRANSFORM_H

#include "mm/Quat.h"
#include "mm/Vec4.h"

namespace anm {
// a bone's transform as a translation, a rotation and a scale (0x30 bytes: anm::Pose keeps a vector of them,
// 0x30 per bone)
class QsTransform {
public:
    mm::Vec4 m_translation;
    mm::Quat m_rotation;
    mm::Vec4 m_scale;
};
}  // namespace anm

#endif
