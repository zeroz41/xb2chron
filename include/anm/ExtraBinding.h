#ifndef ANM_EXTRABINDING_H
#define ANM_EXTRABINDING_H

#include "anm/Array.h"

namespace anm { class ExtraTruck; }
namespace anm { class SerialiseArg; }

namespace anm {
// an animation's extra track as a binding sees it (Binding keeps them 0x18 apart). The fields' names are not the
// original's
class ExtraBinding {
public:
    // installs the table of the track's kind over the loaded track (anm_uncompress_extra_truck.cpp)
    ExtraBinding(const SerialiseArg& arg);

    ExtraTruck* m_pTruck;
    Array<short> m_indices;  // per output value, its index in a frame of the track; negative: none
};
}  // namespace anm

#endif
