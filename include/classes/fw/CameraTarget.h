#ifndef CLASSES_FW_CAMERATARGET_H
#define CLASSES_FW_CAMERATARGET_H

namespace fw {
// table 0x7100B45DB0
class CameraTarget {
public:
    virtual ~CameraTarget();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void requestResetCamera();  // slot 4
};
}  // namespace fw

#endif
