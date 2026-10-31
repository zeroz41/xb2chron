#ifndef CLASSES_ML_SCNOBJCAM_H
#define CLASSES_ML_SCNOBJCAM_H

#include "classes/ml/ScnObj.h"
#include "classes/ml/threadval.h"
#include "mm/mtl/FixStr.h"
#include "mm/Plane.h"
#include "ml/AttrTransform.h"  // tree: ml/AttrTransform.h (new)

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77D38
class ScnObjCam : public ::ml::ScnObj {
public:
    // what a camera keeps per thread (0x380 bytes: threadval's tvSwap copies that much)
    struct RENDER_INFO {
        AttrTransform m_transform;  // setLookAt updates it (the name is not the original's)
        unsigned char pad_140[0x10];
        // 0x150 the near plane's extents updateFovNearFar works out: -near * tan(fov / 2), its negation, and both
        // times the aspect ratio (the name is not the original's)
        float m_nearExtent[4];
        unsigned char pad_160[0x88];
        float m_fov;     // 0x1E8 degrees: 40 by default (setDefault) (the name is not the original's)
        float m_invTan;  // 0x1EC 1 / tan(fov / 2) (updateFovNearFar) (the name is not the original's)
        float m_aspect;  // 0x1F0 the viewport's width / height, else 1 (apply) (the name is not the original's)
        float m_near;    // 0x1F4 0.1 from the constructor (the name is not the original's)
        float m_far;     // 0x1F8 80000 from the constructor (the name is not the original's)
        unsigned char pad_1FC[0xC4];
        mm::Plane m_planeGbl[6];  // 0x2C0 getPlaneGbl's (the name is not the original's)
    };
    // one of the six planes of the calculation thread's (true) or the render thread's (false) information
    const mm::Plane& getPlaneGbl(unsigned int index, bool cpu) const;
    void setCopydataCam(bool);
    // a new camera numbered index ("Camera%d") in the scene's pool; none when the pool is full
    static ScnObjCam* create(Scn* scn, int index);
    ScnObjCam(Scn* scn, const char* name);
    // the default view: looking from (0, 5, 20) at the origin with a 40 degree field of view
    void setDefault();
    void updateViewMatrix(bool);
    void setLookAt(const mm::Vec3& eye, const mm::Vec3& target, float roll);
    // the projection's derived values from the field of view, near distance and aspect ratio
    void updateFovNearFar();
    virtual ~ScnObjCam();  // slot 0
    virtual void update();  // slot 2
    virtual void renderDebug(ml::DebDraw*);  // slot 3
    virtual void apply();  // slot 4
    virtual const char* getName() const;  // slot 6

    int m_index;  // 0x14 create's index: Scn::getCam finds a camera by it (the name is not the original's)
    mm::mtl::FixStr<64> m_name;  // 0x18 getName's (the name is not the original's)
    unsigned char pad_5C[0x14];
    threadval<RENDER_INFO> m_info;  // apply and setLookAt read its banks (the name is not the original's)
};
}  // namespace ml

#endif
