#ifndef CLASSES_SSD_SOUNDACTOR_H
#define CLASSES_SSD_SOUNDACTOR_H

namespace ssd { class SoundEntry; }
namespace ssd { class SoundHandle; }

namespace ssd {
// a base of ssd::SoundActor no evidence names yet
class TUnk_B81960 {
public:
    virtual ~TUnk_B81960();
    virtual void Init() = 0;
    virtual void Quit() = 0;
    virtual void Play(ssd::SoundHandle*, ssd::SoundEntry const*, float, float) = 0;
    virtual void Stop(float) = 0;
    virtual void Pause(bool, float) = 0;
    virtual void UpdateGameFrame(float) = 0;
    unsigned char pad_8[0x10];  // fields: size from where the next base starts
};
// a base of ssd::SoundActor no evidence names yet
class TUnk_B819B0 {
public:
    virtual ~TUnk_B819B0();
};
// table 0x7100B81960; base at 0x0 unknown (TUnk_B81960), base at 0x18 unknown (TUnk_B819B0)
class SoundActor : public TUnk_B81960, public TUnk_B819B0 {
public:
    virtual ~SoundActor();  // slot 0
    virtual void Init();  // slot 2
    virtual void Quit();  // slot 3
    virtual void Play(ssd::SoundHandle*, ssd::SoundEntry const*, float, float);  // slot 4
    virtual void Stop(float);  // slot 5
    virtual void Pause(bool, float);  // slot 6
    virtual void UpdateGameFrame(float);  // slot 7
};
}  // namespace ssd

#endif
