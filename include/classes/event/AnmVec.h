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
    AnmVec() { clear(); }
    virtual ~AnmVec() {}  // slot 0
    mm::mtl::FixedVector<mm::Vec3, 16> m_values;  // @0x80, count @0x180 (one value per key, append's Vec3)
    mm::mtl::FixedVector<CV_TYPE, 16> m_types;  // @0x190, count @0x1D0 (one curve type per key)
    mm::Vec3 calcEvalute(unsigned long index, float blend) const;
    void append(float time, mm::Vec3 const& value, CV_TYPE type);
    // 1.0.0's AnmVec::clear (0x7100092744); inline in 3.0.1 (the linear commands' updates)
    void clear() {
        AnmBase::clear();
        m_values.clear();
        m_types.clear();
        m_value.x = 0.0f;
        m_value.y = 0.0f;
        m_value.z = 0.0f;
    }
    // 1.0.0's AnmVec::update(float) (0x7100092790): the curve advanced, then m_value evaluated again at the current
    // time while bit 1 of pad_8 is set; inline in 3.0.1
    void update(float step);
    unsigned int pad_1d8;
    mm::Vec3 m_value;  // @0x1E0 (CamObj's constructor clears it; the name is not the original's)
};
}  // namespace event

#endif
