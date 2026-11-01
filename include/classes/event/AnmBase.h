#ifndef CLASSES_EVENT_ANMBASE_H
#define CLASSES_EVENT_ANMBASE_H

#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3BEB0
// The layout follows UIManager's constructor (it builds two AnmF32 in place) and the destructors (each FixedVector
// is cleared); the names are not the original's.
class AnmBase {
public:
    // inline: D2/D0 sit in CharaObj's tail; the table is weak
    virtual ~AnmBase() {}  // slot 0

    unsigned int pad_8;  // UIManager's constructor stores 1
    mm::mtl::FixedVector<float, 16> m_keys;  // @0x10, count @0x50 (the key frames)
    void update(float step);
    // 1.0.0's AnmBase::clear (0x7100091E28); inline in 3.0.1
    void clear() {
        m_keys.clear();
        pad_58 = 1;
        pad_8 = 1;
        pad_5c = 0.0f;
        pad_68 = 0;
        pad_70 = 0.0f;
        pad_60 = 0.0f;
    }
    // the curve has not reached its end yet (the linear commands' updates return 2 while it holds); the name is not
    // the original's
    bool isPlaying() const { return !(pad_60 <= pad_5c); }

    unsigned int pad_58;  // UIManager's constructor stores 1
    float pad_5c;  // compared with pad_60 (the linear commands' updates)
    float pad_60;
    unsigned long pad_68;  // calcEvalute's key index
    float pad_70;  // calcEvalute's blend
};
}  // namespace event

#endif
