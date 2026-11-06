#ifndef CLASSES_EVENT_CHARAWEIGHTITEM_H
#define CLASSES_EVENT_CHARAWEIGHTITEM_H

#include "classes/event/AnmF32.h"

namespace event {
// table 0x7100B3FC08
class CharaWeightItem {
public:
    virtual ~CharaWeightItem();  // slot 0
    unsigned char pad_8[0x8];
    // the name CharaWeightPlayer's eases look the item up by (the field names here are not the original's)
    const char* m_name;  // 0x10
    // the curves the destructor tears down (last first), one per WeightLayer (easeOut indexes them)
    AnmF32 m_anm[2];  // 0x18
    float m_weight;  // 0x238: easeOut's start value
};
}  // namespace event

#endif
