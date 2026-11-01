#ifndef CLASSES_SSD_SOUNDEFFECTER_H
#define CLASSES_SSD_SOUNDEFFECTER_H

namespace ssd {

// An effect SystemCore's AddSoundEffecter puts on an effect bus. The class names come from
// SystemCorePlatform's symbols (InitDelayEffect(unsigned char, SoundDelayEffecter*), ...); no table or constructor
// of them is in the module, so the bytes before 0x18 are unknown. The field names are not the original's.
class SoundEffecter {
public:
    unsigned char pad_0[0x18];
    unsigned char type_;    // 0x18: 0 SoundDelayEffecter, 1 SoundI3dl2ReverbEffecter (InitEffect's dispatch)
    bool attached_;         // 0x19: set by InitDelayEffect/InitI3dl2ReverbEffect, cleared by QuitEffect
    unsigned char bus_;     // 0x1A: the effect bus Init*Effect put it on
    float volume_;          // 0x1C: the bus's buffer mixer volume
};

// the parameters, named after the nn::audio setters Init*Effect passes them to
class SoundDelayEffecter : public SoundEffecter {
public:
    float delayTime_;     // 0x20 (seconds)
    float delayTimeMax_;  // 0x24 (seconds)
    float inGain_;
    float feedbackGain_;
    float dryGain_;
    float channelSpread_;
    float lowPassAmount_;
};

class SoundI3dl2ReverbEffecter : public SoundEffecter {
public:
    bool flag_20;  // 0x20: InitI3dl2ReverbEffect clears it (meaning not known)
    float roomGain_;
    float roomHfGain_;
    float lateReverbDecayTime_;     // seconds
    float lateReverbHfDecayRatio_;
    float reflectionsGain_;
    float reflectionDelayTime_;     // seconds
    float reverbGain_;
    float lateReverbDelayTime_;     // seconds
    float lateReverbDiffusion_;
    float lateReverbDensity_;
    float hfReference_;
    float dryGain_;
};

}  // namespace ssd

#endif
