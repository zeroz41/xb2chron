#include "classes/fw/CameraLayer.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraPlugin.h"
#include "classes/fw/CameraTarget.h"
#include "classes/ml/Scn.h"
#include "mm/Mat44.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/RTTI.h"
#include <algorithm>

namespace fw {

CameraLayer::CameraLayer() : m_pScnCam(nullptr), m_blendTime(0.0f), m_blendDuration(1.0f), m_blending(false) {
    m_blendMtx = mm::Mat44::identity;
    m_viewMtx = mm::Mat44::identity;
}

CameraLayer::~CameraLayer() {}

void CameraLayer::setup(ml::Scn* scn, unsigned int index) {
    m_pScnCam = scn->getCam(index);
}

void CameraLayer::cleanup() {
    while (!m_cameras.empty()) {
        Camera* camera = m_cameras.front();
        camera->onPop();
        camera->m_pushed = false;
        m_cameras.pop_front();
        camera->release();
    }
    while (!m_plugins.empty()) {
        CameraPlugin* plugin = m_plugins.pop_front();
        plugin->release();
    }
}

void CameraLayer::push(mm::mtl::IntrusivePtr<Camera>& camera, float time) {
    camera->addRef();
    if (m_cameras.empty()) {
        m_cameras.push_back(camera.get());
        camera->setScnCam(m_pScnCam);
    } else {
        mm::mtl::IntrusiveList<Camera>::iterator it =
            std::lower_bound(m_cameras.begin(), m_cameras.end(), static_cast<int>(camera->m_prio),
                             [](const Camera& c, int prio) { return c.m_prio < prio; });
        bool first = m_cameras.begin() == it;
        if (time > 0.0f && first) {
            m_blendMtx = it->m_view;
            m_blendTime = 0.0f;
            m_blendDuration = time;
            m_blending = true;
        }
        m_cameras.insert_before(it, camera.get());
        camera->setScnCam(m_pScnCam);
    }
    Camera& pushed = *camera;
    pushed.onPush();
    pushed.m_pushed = true;
    Camera* front = m_cameras.front();
    if (camera.get() == front) {
        camera->onActivate();
    }
}

void CameraLayer::pop(mm::mtl::IntrusivePtr<Camera>& camera, float time) {
    Camera* front = m_cameras.front();
    bool active = camera.get() == front;
    if (time > 0.0f && active) {
        m_blendMtx = camera->m_view;
        m_blendTime = 0.0f;
        m_blendDuration = time;
        m_blending = true;
    }
    camera->onDeactivate();
    Camera& popped = *camera;
    popped.onPop();
    popped.m_pushed = false;
    m_cameras.remove(camera.get());
    camera->release();
    if (!m_cameras.empty()) {
        m_cameras.front()->onActivate();
    }
}

void CameraLayer::pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin>& plugin) {
    plugin->addRef();
    m_plugins.push_front(plugin.get());
}

void CameraLayer::popPlugin(mm::mtl::IntrusivePtr<CameraPlugin>& plugin) {
    m_plugins.remove(plugin.get());
    plugin->release();
}

mm::Vec3 CameraLayer::getCameraPosition() const {
    mm::Mat44 mtx(m_viewMtx);
    mtx.inverse();
    return mtx.getTrans();
}

}  // namespace fw

mm::mtl::RTTI fw::CameraTarget::m_rtti("CameraTarget", nullptr, nullptr);
