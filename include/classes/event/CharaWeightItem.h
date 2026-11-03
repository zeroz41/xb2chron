#ifndef CLASSES_EVENT_CHARAWEIGHTITEM_H
#define CLASSES_EVENT_CHARAWEIGHTITEM_H

#include "classes/event/AnmF32.h"

namespace event {
// table 0x7100B3FC08
class CharaWeightItem {
public:
    virtual ~CharaWeightItem();  // slot 0
    unsigned char pad_8[0x10];
    // the two curves the destructor tears down (last first); the names are not the original's
    AnmF32 m_anm0;  // 0x18
    AnmF32 m_anm1;  // 0x128
};
}  // namespace event

#endif
