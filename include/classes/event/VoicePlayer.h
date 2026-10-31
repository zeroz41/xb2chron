#ifndef CLASSES_EVENT_VOICEPLAYER_H
#define CLASSES_EVENT_VOICEPLAYER_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"

namespace event {
// table 0x7100B3D828
class VoicePlayer {
public:
    // a voice preload queues (0x48 bytes: preload stores the float first, then copies the name)
    // (the names are not the original's)
    struct Key {
        Key(float time, const char* name) : m_time(time), m_name(name) {}

        float m_time;
        mm::mtl::FixStr<64> m_name;
    };

    virtual ~VoicePlayer();  // slot 0
    void preload(float time, const char* name);

    unsigned char pad_8[0x4];
    // preload's queue: it drops the oldest while 8 are queued (the name is not the original's); the layout past
    // 0x2cc is not known
    mm::mtl::FixedList<Key, 8> m_keys;  // 0xc
};
}  // namespace event

#endif
