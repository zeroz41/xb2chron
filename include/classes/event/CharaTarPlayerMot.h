#ifndef CLASSES_EVENT_CHARATARPLAYERMOT_H
#define CLASSES_EVENT_CHARATARPLAYERMOT_H

#include "classes/event/AnmF32.h"

namespace event {
// table 0x7100B3CA30
class CharaTarPlayerMot {
public:
    virtual ~CharaTarPlayerMot();  // slot 0
    unsigned char pad_8[0x58];
    // the two curves the destructor tears down (last first); the names are not the original's
    AnmF32 m_anm0;  // 0x60
    AnmF32 m_anm1;  // 0x170
};
}  // namespace event

#endif
