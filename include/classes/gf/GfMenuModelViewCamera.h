#ifndef CLASSES_GF_GFMENUMODELVIEWCAMERA_H
#define CLASSES_GF_GFMENUMODELVIEWCAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace gf {
// table 0x7100B5F918
class GfMenuModelViewCamera : public ::fw::Camera {
public:
    virtual ~GfMenuModelViewCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void getName() const;  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
