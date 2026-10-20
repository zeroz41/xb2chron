#ifndef CLASSES_FW_CAMERA_H
#define CLASSES_FW_CAMERA_H

namespace fw { class UpdateInfo; }

namespace fw {
// table none (its derived classes')
class Camera {
public:
    virtual ~Camera();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void getName() const;  // slot 3
    virtual void onPush();  // slot 4
    virtual void onPop();  // slot 5
    virtual void onActivate();  // slot 6
    virtual void onDeactivate();  // slot 7
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void updateViewMatrix();  // slot 9
};
}  // namespace fw

#endif
