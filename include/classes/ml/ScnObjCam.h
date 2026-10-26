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
        unsigned char pad_140[0x180];
        mm::Plane m_planeGbl[6];  // 0x2C0 getPlaneGbl's (the name is not the original's)
    };
    // one of the six planes of the calculation thread's (true) or the render thread's (false) information
    const mm::Plane& getPlaneGbl(unsigned int index, bool cpu) const;
    void setCopydataCam(bool);
    virtual ~ScnObjCam();  // slot 0
    virtual void update();  // slot 2
    virtual void renderDebug(ml::DebDraw*);  // slot 3
    virtual void apply();  // slot 4
    virtual const char* getName() const;  // slot 6

    unsigned char pad_14[0x4];
    mm::mtl::FixStr<64> m_name;  // 0x18 getName's (the name is not the original's)
    unsigned char pad_5C[0x14];
    threadval<RENDER_INFO> m_info;  // apply and setLookAt read its banks (the name is not the original's)
};
}  // namespace ml

#endif
