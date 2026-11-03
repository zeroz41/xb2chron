#ifndef CLASSES_EVENT_CHARATARPLAYER_H
#define CLASSES_EVENT_CHARATARPLAYER_H

#include "classes/event/AnmF32.h"

namespace event {
// table 0x7100B3CA10
class CharaTarPlayer {
public:
    virtual ~CharaTarPlayer();  // slot 0
    // a 16-byte entry of m_items (update reads the first one's +0x4, +0x8 byte and +0xC float); the name is not the
    // original's
    struct Item {
        unsigned int pad_0[4];
    };
    unsigned char pad_8[0x18];
    // update erases the first entry once its time runs out, setEnable empties it; the name is not the original's
    mm::mtl::FixedVector<Item, 6> m_items;  // 0x20, count at 0x80
    unsigned char pad_88[0x38];
    // the curve the destructor tears down; the name is not the original's
    AnmF32 m_anm;  // 0xc0
};
}  // namespace event

#endif
