#ifndef CLASSES_GF_CAMERAUTILITIES_H
#define CLASSES_GF_CAMERAUTILITIES_H

#include "mm/Vec3.h"

namespace fw { struct ColiCheckConfig; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// no table: the cameras' helpers (gf_camera_gimmick.cpp defines them). The return types are not known (their
// callers ignore them); the parameter names are not the original's.
class CameraUtilities {
public:
    static void getCameraLookBonePosition(GF_OBJ_HANDLE* handle, mm::Vec3& pos);
    // moves eye out of the collision between it and target
    static void updateCollision(const fw::ColiCheckConfig& config, mm::Vec3& eye, const mm::Vec3& target,
                                const float& fov, const float& nearClip);
};
}  // namespace gf

#endif
