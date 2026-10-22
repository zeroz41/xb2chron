#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"
#include "classes/fw/Framework.h"
#include "classes/gf/SubViewCamera.h"
#include "classes/mm/mtl/IAllocator.h"

namespace gf {

// where a new sub view camera looks from and at, until something moves it
static mm::Vec3 s_defaultEye(0.0f, 2.0f, 10.0f);
static mm::Vec3 s_defaultTarget(0.0f, 0.5f, 0.0f);

mm::mtl::RTTI SubViewCamera::m_rtti("SubViewCamera", &fw::Camera::m_rtti, nullptr);

inline SubViewCamera::SubViewCamera()
    : Camera(::fw::CAMERA_PRIO(55)), m_eye(s_defaultEye), m_target(s_defaultTarget) {}

SubViewCamera::~SubViewCamera() {}

mm::mtl::IntrusivePtr<SubViewCamera> SubViewCamera::create(VIEWCAM viewCam) {
#line 44
    SubViewCamera* camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) SubViewCamera();
    camera->m_viewCam = viewCam;
    return camera;
}

void SubViewCamera::onActivate() {}

void SubViewCamera::update(fw::UpdateInfo const&) { setLookAt(m_eye, m_target, 0.0f); }

const char* SubViewCamera::getName() const { return "SubViewCamera"; }

}  // namespace gf
