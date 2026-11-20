#include "classes/gf/FusionComboCamera.h"
#include "classes/fw/Camera.h"
#include "classes/fw/Framework.h"
#include "classes/mm/mtl/IAllocator.h"
#include "math.h"

namespace gf {

FusionComboCamera::~FusionComboCamera() {}

mm::mtl::IntrusivePtr<::fw::Camera> FusionComboCamera::create(GF_OBJ_HANDLE* a, GF_OBJ_HANDLE* b, Mode mode) {
#line 319 "D:/Monolithsoft/BF2/prog/application/BF2/gf/camera/fusion_combo/gf_camera_fusion_combo.cpp"
    return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) FusionComboCamera(a, b, mode);
}

void FusionComboCamera::onActivate() {}

bool FusionComboCamera::isPlayEnd() const {
    return m_frameMax <= m_frame;
}

float FusionComboCamera::getYaw(const mm::Vec3& from, const mm::Vec3& to) {
    mm::Vec3 a(from.x, 0.0f, from.z);
    mm::Vec3 b(to.x, 0.0f, to.z);
    if (a.isZero() || b.isZero()) {
        return 0.0f;
    }
    float length = a.length();
    if (length <= 1e-6f) {
        a = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        a.x = a.x * scale;
        a.y = a.y * scale;
        a.z = a.z * scale;
    }
    length = b.length();
    if (length <= 1e-6f) {
        b = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        b.x = b.x * scale;
        b.y = b.y * scale;
        b.z = b.z * scale;
    }
    float cosine = mm::Vec3(b).dot(mm::Vec3(a));
    if (cosine < -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f) {
        cosine = 1.0f;
    }
    float yaw = mm::acos(cosine);
    if (a.x * b.z - a.z * b.x < 0.0f) {
        yaw = 6.28318548f - yaw;
    }
    return yaw;
}

const char* FusionComboCamera::getName() const {
    return "FusionComboCamera";
}

mm::mtl::RTTI FusionComboCamera::m_rtti("FusionComboCamera", &fw::Camera::m_rtti, nullptr);

}  // namespace gf
