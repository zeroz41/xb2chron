#ifndef CLASSES_FW_CAMERALAYER_H
#define CLASSES_FW_CAMERALAYER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41038
class CameraLayer {
public:
    virtual void update(fw::UpdateInfo const&);  // slot 0
};
}  // namespace fw

#endif
