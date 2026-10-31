#ifndef CLASSES_FW_CAMERALAYER_H
#define CLASSES_FW_CAMERALAYER_H

#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace fw { class Camera; }
namespace fw { class CameraPlugin; }
namespace fw { class UpdateInfo; }
namespace ml { class Scn; }
namespace ml { class ScnObjCam; }

namespace fw {
// table 0x7100B41038
class CameraLayer {
public:
    CameraLayer();
    ~CameraLayer();
    virtual void update(fw::UpdateInfo const&);  // slot 0
    // fw::CameraManager's constructor sets each of its layers up on its scene, with the layer's index
    void setup(ml::Scn* scn, unsigned int index);
    // where the layer's camera is (GfGameVisible::updateImpl asks the first layer)
    mm::Vec3 getCameraPosition() const;
    void push(mm::mtl::IntrusivePtr<Camera>& camera, float time);
    void pop(mm::mtl::IntrusivePtr<Camera>& camera, float time);
    void cleanup();
    void pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin>& plugin);
    void popPlugin(mm::mtl::IntrusivePtr<CameraPlugin>& plugin);
    // the inverse of the layer's view: the camera's world matrix
    void getMtx(mm::Mat44& mtx) const;

    // 0xd0 bytes: fw::CameraManager's layers are that far apart. The names are not the original's.
    // the pushed cameras by their order (push keeps it sorted by m_prio), the first one the active one
    mm::mtl::IntrusiveList<Camera> m_cameras;
    // what runs on the camera, the last pushed first
    mm::mtl::IntrusiveList<CameraPlugin> m_plugins;
    ml::ScnObjCam* m_pScnCam;  // setup's: the scene's camera of the layer's index; push hands it to each camera
    mm::Mat44 m_viewMtx;  // getMtx returns its inverse, getCameraPosition that inverse's translation
    // the view a change of camera blends from: push and pop copy the active camera's view here
    mm::Mat44 m_blendMtx;
    float m_blendTime;      // 0 when a blend starts
    float m_blendDuration;  // push's and pop's time (1 from the constructor)
    bool m_blending;        // set when push or pop starts a blend
};
}  // namespace fw

#endif
