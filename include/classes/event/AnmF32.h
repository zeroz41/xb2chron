#ifndef CLASSES_EVENT_ANMF32_H
#define CLASSES_EVENT_ANMF32_H

#include "classes/event/AnmBase.h"
#include "event/CvType.h"
#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3BED0
// The layout follows UIManager's constructor and the destructors; the names are not the original's.
class AnmF32 : public AnmBase {
public:
    // inline: the D0 sits in CharaObj's tail; the table is weak
    virtual ~AnmF32() {}  // slot 0

    mm::mtl::FixedVector<float, 16> m_values;  // @0x78, count @0xB8 (one value per key, append's float)
    mm::mtl::FixedVector<CV_TYPE, 16> m_types;  // @0xC0, count @0x100 (one curve type per key)
    unsigned int pad_108;
};
}  // namespace event

#endif
