#ifndef CLASSES_EVENT_VOLUMESKIP_H
#define CLASSES_EVENT_VOLUMESKIP_H

#include "mm/mtl/FixedArray.h"

namespace event {
// table 0x7100B3D8F0; VolumeManager's member at 0xa0 (its constructor stores this table there)
class VolumeSkip {
public:
    // inline: 3.0.1 has no copy (1.0.0's VolumeSkip() at 0x71000FD960 stores what clear stores)
    VolumeSkip() { clear(); }
    virtual ~VolumeSkip() {}  // slot 0
    // 1.0.0's VolumeSkip::clear (0x71000FD998): zero, every volume 1.0, zero
    void clear() {
        pad_8 = 0;
        m_volumes.assign(1.0f);
        pad_44 = 0;
    }
    unsigned int pad_8;
    // one volume per sound category (1.0.0's set takes a const mm::mtl::FixedArray<float, 14>*); the name is not the original's
    mm::mtl::FixedArray<float, 14> m_volumes;  // 0xc
    unsigned int pad_44;
};
}  // namespace event

#endif
