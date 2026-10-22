#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameCamera.h"
#include "classes/gf/SubViewCamera.h"

namespace gf {

GfGameCamera::GfGameCamera(const GfSetupParam& param) : m_initialized(false) {
    m_subViewCameras.assign(mm::mtl::IntrusivePtr<fw::Camera>());
    initialize(param);
}

GfGameCamera::~GfGameCamera() {}

void GfGameCamera::build(const GfSetupParam& param) {
#line 51
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameCamera(param);
}

void GfGameCamera::destroy() {
    GfGameCamera* camera = get();
    camera->finalize();
    delete camera;
}

void GfGameCamera::createSubViewCamera() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (manager == nullptr) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        m_subViewCameras[i] = SubViewCamera::create(VIEWCAM(i + 1));
        manager->m_layers[i + 1].push(m_subViewCameras[i], 0.0f);
    }
}

void GfGameCamera::destroySubViewCamera() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (manager == nullptr) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (fw::Camera* camera = m_subViewCameras[i].get()) {
            SubViewCamera* subView =
                camera->getRTTI()->isKindOf(&SubViewCamera::m_rtti) ? static_cast<SubViewCamera*>(camera) : nullptr;
            manager->m_layers[subView->m_viewCam].pop(m_subViewCameras[i], 0.0f);
            m_subViewCameras[i] = nullptr;
        }
    }
}

void GfGameCamera::clear() {}

void GfGameCamera::setCameraControlType(int type) {
    GfEvent::callCameraControl(type);
}

}  // namespace gf
