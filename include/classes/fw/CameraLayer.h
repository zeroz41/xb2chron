#ifndef CLASSES_FW_CAMERALAYER_H
#define CLASSES_FW_CAMERALAYER_H

#include "mm/mtl/IntrusivePtr.h"

namespace fw { class Camera; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41038
class CameraLayer {
public:
    virtual void update(fw::UpdateInfo const&);  // slot 0
    void push(mm::mtl::IntrusivePtr<Camera>& camera, float time);
    void pop(mm::mtl::IntrusivePtr<Camera>& camera, float time);
    void cleanup();
};
}  // namespace fw

#endif
