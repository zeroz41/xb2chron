#ifndef CLASSES_EVENT_VOICEONESHOTER_H
#define CLASSES_EVENT_VOICEONESHOTER_H

#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3D848
class VoiceOneShoter {
public:
    VoiceOneShoter() : pad_8(0) {}
    virtual ~VoiceOneShoter();  // slot 0
    bool play(const char* name, float volume);
    void update();

    unsigned int pad_8;
    // the handles play starts; update drops the front one once it has stopped (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 4> m_handles;  // 0x10
};
}  // namespace event

#endif
