#ifndef CLASSES_ML_SCNDEBUGMANIPUOBJ_H
#define CLASSES_ML_SCNDEBUGMANIPUOBJ_H

#include "classes/ml/threadval.h"

namespace ml {
// table 0x7100B78270
class ScnDebugManipuObj {
public:
    // what a manipulator keeps per thread (0x140 bytes: threadval's tvSwap copies that much)
    struct alignas(16) RENDER_INFO {
        unsigned char pad_0[0x140];
    };
    virtual ~ScnDebugManipuObj();  // slot 0
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
    virtual void vf6() = 0;  // slot 6
    virtual void vf7() = 0;  // slot 7

    unsigned char pad_8[0xA8];
    threadval<RENDER_INFO> m_info;  // its destructor's (the name is not the original's)
};
}  // namespace ml

#endif
