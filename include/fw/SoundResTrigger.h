#ifndef FW_SOUNDRESTRIGGER_H
#define FW_SOUNDRESTRIGGER_H

#include "anm/Array.h"
#include "mm/Vec3.h"

namespace fw {
// one sound trigger of a state: what an annotation of kind 4 carries (1.0.0's gf::checkSoundTriggerPlayer(
// gf::GfComSound*, fw::ResSoundTriggerInfo const&)); 0x40 bytes, the state's name first (the field names are not
// the original's)
struct ResSoundTriggerInfo {
    const char* m_stateName;
    int m_kind;  // GfComSound::callbackAnimImpl: 0 plays the sound, 1 stops it
    unsigned char pad_c[0x4];
    const char* m_seName;  // the sound GfComSound plays or stops
    float m_volume;
    int m_playType;  // GfComSound::callbackAnimImpl: 0 playSe, 1 playSeBone, 2 playSe2D
    const char* m_boneName;  // playSeBone's bone
    unsigned char pad_28[0x8];
    mm::Vec3 m_offset;  // playSe's and playSeBone's offset
};

// a trigger at a frame of its state: 0x50 bytes (the names are not the original's)
struct ResSoundFrameTrigger {
    ResSoundTriggerInfo m_info;
    unsigned int m_frame;
    unsigned char pad_44[0xC];
};

// what fw::SoundResTriggerImporter::importBinary reads from a file: the triggers on entering, on leaving and at a
// frame of their states (the names are not the original's)
struct ResSoundTrigger {
    anm::Array<ResSoundTriggerInfo> m_enterTriggers;
    anm::Array<ResSoundTriggerInfo> m_leaveTriggers;
    anm::Array<ResSoundFrameTrigger> m_frameTriggers;
};
}  // namespace fw

#endif
