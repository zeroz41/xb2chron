#ifndef CLASSES_GF_GFMENUMODELVIEWCAMERA_H
#define CLASSES_GF_GFMENUMODELVIEWCAMERA_H

#include "classes/fw/Camera.h"

namespace gf {
// table 0x7100B5F918
class GfMenuModelViewCamera : public ::fw::Camera {
public:
    virtual ~GfMenuModelViewCamera();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void getName() const;  // slot 3
};
}  // namespace gf

#endif
