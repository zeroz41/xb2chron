#ifndef CLASSES_ML_SCNDEBUGMANIPUOBJ_H
#define CLASSES_ML_SCNDEBUGMANIPUOBJ_H

#include "classes/ml/threadval.h"
#include "ml/AttrTransform.h"

namespace ml { class DebDraw; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B78270
class ScnDebugManipuObj {
public:
    // what a manipulator keeps per thread (0x140 bytes: threadval's tvSwap copies that much): its transform (the
    // constructor clears it; ScnDebugManipu::getTrans returns a bank's)
    struct RENDER_INFO {
        AttrTransform m_trans;  // (the name is not the original's)
    };
    virtual ~ScnDebugManipuObj();  // slot 0
    // the slots ScnDebugManipuRot and ScnDebugManipuTrans fill (their names)
    virtual void checkMouseButtonDown(ml::EventView*) = 0;  // slot 2
    virtual bool checkMouseButtonUp(ml::EventView*) = 0;  // slot 3
    virtual void checkMouseMove(ml::EventView*) = 0;  // slot 4
    virtual void setRadius(float) = 0;  // slot 5
    virtual void update() = 0;  // slot 6
    virtual void render(ml::DebDraw*) = 0;  // slot 7

    unsigned char pad_8[0x8];
    int m_type;  // 0x10 the SCNMANIPU it was made as: 1.0.0's ScnDebugManipu::getType returns it (the name is not the original's)
    unsigned char pad_14[0x4];
    int m_pick;  // 0x18 non-zero while picked: 1.0.0's ScnDebugManipu::isPick tests it (the name is not the original's)
    unsigned char pad_1C[0x4];
    bool m_disp;  // 0x20 1.0.0's ScnDebugManipu::setDisp writes it (the name is not the original's)
    unsigned char pad_21[0x8F];
    threadval<RENDER_INFO> m_info;  // its destructor's (the name is not the original's)
};
}  // namespace ml

#endif
