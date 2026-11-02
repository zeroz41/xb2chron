#ifndef CLASSES_EVENT_VOLUMESEAMLESS_H
#define CLASSES_EVENT_VOLUMESEAMLESS_H

#include "mm/mtl/FixedArray.h"

namespace event {
// table 0x7100B3D910; VolumeManager's member at 0x50 (its constructor stores this table there)
class VolumeSeamless {
public:
    // inline: 3.0.1 has no copy (1.0.0's VolumeSeamless() at 0x71000FFA88)
    VolumeSeamless() : m_flags(0), pad_c(0), pad_10(0) {
        m_volumes.assign(1.0f);
        pad_48 = 0;
    }
    virtual ~VolumeSeamless() {}  // slot 0
    void start(float);  // out of line (0x7100111A18); SeqManager::start_fadeout passes SeqManager's pad_2794
    void update();  // 1.0.0's VolumeSeamless::update (0x71000FFAEC); inlined into VolumeManager's
    // bits 1 and 2: update counts m_timer down; bit 2 is cleared once it runs out (the name is not the original's)
    unsigned int m_flags;  // 0x8
    unsigned int pad_c;
    unsigned int pad_10;
    // the ctor stores 1.0 to each (as VolumeSkip's m_volumes); the name is not the original's
    mm::mtl::FixedArray<float, 13> m_volumes;  // 0x14
    unsigned int pad_48;
    float m_timer;  // 0x4c frames left, update subtracts 1 each frame (the name is not the original's)
};
}  // namespace event

#endif
