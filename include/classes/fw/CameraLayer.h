#ifndef CLASSES_FW_CAMERALAYER_H
#define CLASSES_FW_CAMERALAYER_H

#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"

namespace fw { class Camera; }
namespace fw { class CameraPlugin; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41038
class CameraLayer {
public:
    virtual void update(fw::UpdateInfo const&);  // slot 0
    // where the layer's camera is (GfGameVisible::updateImpl asks the first layer)
    mm::Vec3 getCameraPosition() const;
    void push(mm::mtl::IntrusivePtr<Camera>& camera, float time);
    void pop(mm::mtl::IntrusivePtr<Camera>& camera, float time);
    void cleanup();
    void pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin>& plugin);
    void popPlugin(mm::mtl::IntrusivePtr<CameraPlugin>& plugin);

    unsigned char pad_8[0xc8];  // 0xd0 bytes: fw::CameraManager's layers are that far apart
};
}  // namespace fw

#endif
