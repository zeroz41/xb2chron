#ifndef CLASSES_EVENT_ANMVEC_H
#define CLASSES_EVENT_ANMVEC_H

#include "classes/event/AnmBase.h"
#include "event/CvType.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3BEF0
// The layout follows CamObj's constructor (it builds CamHands' two AnmVec in place) and CamHands' destructor (each
// FixedVector is cleared); the names are not the original's. Size 0x1F0.
class AnmVec : public AnmBase {
public:
    // inline: D2/D0 sit in CharaObj's tail; the table is weak
    virtual ~AnmVec() {}  // slot 0
    mm::mtl::FixedVector<mm::Vec3, 16> m_values;  // @0x80, count @0x180 (one value per key, append's Vec3)
    mm::mtl::FixedVector<CV_TYPE, 16> m_types;  // @0x190, count @0x1D0 (one curve type per key)
    unsigned int pad_1d8;
    unsigned long pad_1e0;  // CamObj's constructor clears it
    unsigned int pad_1e8;  // CamObj's constructor clears it
};
}  // namespace event

#endif
