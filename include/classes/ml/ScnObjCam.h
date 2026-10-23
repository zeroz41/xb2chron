#ifndef CLASSES_ML_SCNOBJCAM_H
#define CLASSES_ML_SCNOBJCAM_H

#include "classes/ml/ScnObj.h"
#include "classes/ml/threadval.h"
#include "ml/AttrTransform.h"  // tree: ml/AttrTransform.h (new)

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77D38
class ScnObjCam : public ::ml::ScnObj {
public:
    // what a camera keeps per thread (0x380 bytes: threadval's tvSwap copies that much)
    struct RENDER_INFO {
        AttrTransform m_transform;  // setLookAt updates it (the name is not the original's)
    };
    virtual ~ScnObjCam();  // slot 0
    virtual void update();  // slot 2
    virtual void renderDebug(ml::DebDraw*);  // slot 3
    virtual void apply();  // slot 4
    virtual void getName() const;  // slot 6

    unsigned char pad_14[0x5C];
    threadval<RENDER_INFO> m_info;  // apply and setLookAt read its banks (the name is not the original's)
};
}  // namespace ml

#endif
