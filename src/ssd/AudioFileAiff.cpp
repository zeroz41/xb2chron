#include "classes/ssd/AudioFileAiff.h"
#include "mm/Vec3.h"

namespace ssd {

// Three mm::Vec3 constants at file scope that only this unit's static initializer touches (no code reads them):
// copies of mm::Vec3::zero and mm::Vec3::unitY, then (0, -1, 0). No symbol names them in either version.
static const mm::Vec3 s_unkVec3A = mm::Vec3::zero;
static const mm::Vec3 s_unkVec3B = mm::Vec3::unitY;
static const mm::Vec3 s_unkVec3C(0.0f, -1.0f, 0.0f);

void AudioFileAiff::SetPositionBySample(unsigned long) {}

}  // namespace ssd
