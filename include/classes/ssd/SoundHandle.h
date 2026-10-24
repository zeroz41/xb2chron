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
};
}  // namespace ssd

#endif
