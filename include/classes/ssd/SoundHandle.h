#ifndef CLASSES_SSD_SOUNDHANDLE_H
#define CLASSES_SSD_SOUNDHANDLE_H

namespace ssd { class SoundActor; }
namespace ssd {
// a base of ssd::SoundHandle no evidence names yet
class TUnk_B81C50 {
public:
    virtual ~TUnk_B81C50();
    unsigned char pad_8[0x10];  // fields: size from where the next base starts
};
// a base of ssd::SoundHandle no evidence names yet
class TUnk_B81C70 {
public:
    virtual ~TUnk_B81C70();
};
// table 0x7100B81C50; base at 0x0 unknown (TUnk_B81C50), base at 0x18 unknown (TUnk_B81C70)
class SoundHandle : public TUnk_B81C50, public TUnk_B81C70 {
public:
    class Notify;
    virtual ~SoundHandle();  // slot 0
    bool IsValidHandle() const;
    bool IsPlay() const;
    int GetState() const;  // 8 once ready to start; 5, 6 and 7 while preparing
    long Start(SoundActor* actor, float volume, float pitch);  // negative on failure
    void Stop(float fadeTime);
    void SetCategoryId(int id);
    long GetPlayTime(float* time) const;
    long SetPlayTime(float time);
    long GetDataTime(float* time) const;
    long SetRemainLoopCount(int count);
    long GetRemainLoopCount(int* count) const;
    // set a value now (fadeTime 0) or over fadeTime: 1.0.0's SetPitch, SetVolume and SetPan (0x7100990D48,
    // 0x7100990D74, 0x7100990DA0, in that order) write the same fields as these
    void SetPitch(float pitch, float fadeTime);
    void SetVolume(float volume, float fadeTime);
    void SetPan(float pan, float fadeTime);
    float GetDistanceVolume() const;
    void Pause(bool pause, float fadeTime);

    // a value Set* moves to its target over a fade time (the type's and the field names are not the original's)
    struct FadeValue {
        float current;
        int elapsed;  // Set* resets it
        float fadeTime;
        float delta;  // target - start
        float start;
        float target;
    };
    unsigned char pad_20[0x4c];
    FadeValue pitch_;  // 0x6C
    FadeValue volume_;  // 0x84 (fw::SoundSsdDriver::getVolume type 0 reads its current value)
    FadeValue pan_;  // 0x9C
    unsigned char pad_b4[0x4];
    float volume2_;  // 0xB8: fw::SoundSsdDriver::getVolume type 2 reads it (the name is not the original's)
};
}  // namespace ssd

#endif
