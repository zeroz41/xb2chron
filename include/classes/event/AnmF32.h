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
    // UIManager's constructor (0x71001024A0) builds its two curves cleared: the stores are clear()'s
    AnmF32() { clear(); }

    mm::mtl::FixedVector<float, 16> m_values;  // @0x78, count @0xB8 (one value per key, append's float)
    mm::mtl::FixedVector<CV_TYPE, 16> m_types;  // @0xC0, count @0x100 (one curve type per key)
    // 1.0.0's AnmF32::clear; inline in 3.0.1 (CharaFade::update)
    void clear() {
        AnmBase::clear();
        m_values.clear();
        m_types.clear();
        m_value = 0.0f;
    }
    float calcEvalute(unsigned long index, float blend) const;
    void append(float time, float value, CV_TYPE type);
    // 1.0.0's AnmF32::update(float): the curve advanced, then m_value evaluated again while bit 1 of pad_8 is set
    void update(float step);
    float m_value;  // 0x108 the value at the current time (the name is not the original's)
};
}  // namespace event

#endif
