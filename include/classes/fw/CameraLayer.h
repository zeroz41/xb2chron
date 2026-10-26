#ifndef CLASSES_FW_CAMERALAYER_H
#define CLASSES_FW_CAMERALAYER_H

#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"

namespace fw { class Camera; }
namespace fw { class CameraPlugin; }
namespace fw { class UpdateInfo; }
namespace ml { class Scn; }

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

    unsigned char pad_8[0xc8];  // 0xd0 bytes: fw::CameraManager's layers are that far apart
};
}  // namespace fw

#endif
