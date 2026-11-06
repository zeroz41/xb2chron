#ifndef CLASSES_EVENT_VOICEMAKER_H
#define CLASSES_EVENT_VOICEMAKER_H

#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3D868
class VoiceMaker {
public:
    VoiceMaker() : m_flags(0) {}
    virtual ~VoiceMaker() {}  // slot 0
    // clears the path; with use set and a voice name starting "bf", "qst", "fev", "deb" or "kizuna", formats
    // "/stream/<dir>/<voice folder>/<name>/" into m_path and sets bit 0 (the parameter names are not the original's)
    void create(bool use, const char* dir, const char* name);
    // with bit 0 set, m_path with the name appended (in m_voicePath), else null (VoiceManager's playAuto and
    // preloadAuto skip the voice on null)
    const char* makePath(const char* name);

    // bit 0: m_path holds a stream path (the names are not the original's)
    unsigned int m_flags;  // 0x8
    mm::mtl::FixStr<256> m_path;  // 0xc
    // makePath's result: m_path with the voice name appended (the name is not the original's)
    mm::mtl::FixStr<256> m_voicePath;  // 0x110
};
}  // namespace event

#endif
