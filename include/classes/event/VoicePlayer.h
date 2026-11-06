#ifndef CLASSES_EVENT_VOICEPLAYER_H
#define CLASSES_EVENT_VOICEPLAYER_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"

namespace event { class IVoiceEvent; }

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

    // a voice update starts (0x54 bytes: update stores the handle, copies the name, then 12 bytes it sets up as
    // -1.0f, 0, 0) (the names are not the original's)
    struct Voice {
        unsigned int m_handle;
        mm::mtl::FixStr<64> m_name;
        float pad_48[3];
    };

    VoicePlayer() : pad_8(0), m_nextHandle(0), m_nextTime(0.0f), m_nowHandle(0), m_event(nullptr) {}
    virtual ~VoicePlayer();  // slot 0
    void preload(float time, const char* name);
    bool play(const char* name, float time, IVoiceEvent* event);
    void clear();
    void update();
    void draw();
    // out of line (0x710010E3DC; FrameManager::pause passes whether a voice pause type is set)
    void pause(bool);

    unsigned int pad_8;  // bit 0 drawn as "delay" by VoiceManager's debug draw
    // preload's queue: it drops the oldest while 8 are queued (the name is not the original's)
    mm::mtl::FixedList<Key, 8> m_keys;  // 0xc
    unsigned char pad_2cc[0x4];
    mm::mtl::FixedVector<Voice, 4> m_voices;  // 0x2d0 (the name is not the original's)
    // the voice drawn as "next" and "now" by VoiceManager's debug draw (the names are not the original's)
    mm::mtl::FixStr<64> m_nextName;  // 0x428
    unsigned int m_nextHandle;  // 0x46c
    float m_nextTime;  // 0x470
    mm::mtl::FixStr<64> m_nowName;  // 0x474
    unsigned int m_nowHandle;  // 0x4b8
    unsigned char pad_4bc[0x4];
    IVoiceEvent* m_event;  // 0x4c0 play's listener (the name is not the original's)
};
}  // namespace event

#endif
