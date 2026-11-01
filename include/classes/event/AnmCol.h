#ifndef CLASSES_EVENT_ANMCOL_H
#define CLASSES_EVENT_ANMCOL_H

#include "classes/event/AnmBase.h"
#include "event/CvType.h"
#include "mm/Col4.h"
#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3BF10
// The layout follows EffectObj's constructor (it builds EffectLinearCol's AnmCol in place) and the destructors (each
// FixedVector is cleared); the names are not the original's. Size 0x1D8.
class AnmCol : public AnmBase {
public:
    // inline: D2/D0 sit in CharaObj's tail; the table is weak
    virtual ~AnmCol() {}  // slot 0
    mm::Col4 calcEvalute(unsigned long index, float blend) const;
    void append(float time, mm::Col4 const& value, CV_TYPE type);

    // 1.0.0's AnmCol::clear (0x7100092EB4); inline in 3.0.1 (EffectLinearCol::update)
    void clear() {
        AnmBase::clear();
        m_values.clear();
        m_types.clear();
        m_value = mm::Col4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    // 1.0.0's AnmCol::update(float) (0x7100092F08): the curve advanced, then m_value evaluated again at the current
    // time while bit 1 of pad_8 is set; inlined everywhere in 3.0.1
    void update(float step);

    mm::mtl::FixedVector<mm::Col4, 16> m_values;  // @0x78, count @0x178 (one value per key, append's Col4)
    mm::mtl::FixedVector<CV_TYPE, 16> m_types;  // @0x180, count @0x1C0 (one curve type per key)
    mm::Col4 m_value;  // @0x1C8 (EffectObj's constructor sets it to 0,0,0,1)
};
}  // namespace event

#endif
