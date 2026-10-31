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
    unsigned int pad_58;  // UIManager's constructor stores 1
    unsigned int pad_5c;
    unsigned int pad_60;
    unsigned long pad_68;
    unsigned int pad_70;
};
}  // namespace event

#endif
