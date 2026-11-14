#ifndef CLASSES_GF_FUSIONCOMBOCAMERA_H
#define CLASSES_GF_FUSIONCOMBOCAMERA_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
class GF_OBJ_HANDLE;

// table 0x7100B45A88
class FusionComboCamera : public ::fw::Camera {
public:
    // the camera's mode (update branches on the value at 0x12C); the enumerators are not known
    enum Mode {};

    // out of line (0x71001CC4D0): create calls it
    FusionComboCamera(GF_OBJ_HANDLE*, GF_OBJ_HANDLE*, Mode);
    virtual ~FusionComboCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8

    static mm::mtl::IntrusivePtr<FusionComboCamera> create(GF_OBJ_HANDLE*, GF_OBJ_HANDLE*, Mode);
    bool isPlayEnd() const;
    void getAxis(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& axis);
    float getYaw(const mm::Vec3& from, const mm::Vec3& to);

    static mm::mtl::RTTI m_rtti;

    unsigned char pad_a8[0x78];
    // update advances m_frame by dt / (1/30) while m_frame / m_frameMax < 1 and blends by that ratio; isPlayEnd is
    // m_frame reaching m_frameMax (the names are not the original's)
    float m_frameMax;
    float m_frame;
    unsigned char pad_128[0x38];
};
}  // namespace gf

#endif
