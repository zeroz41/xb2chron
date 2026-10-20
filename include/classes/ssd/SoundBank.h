// not proven yet: its table differs from the original's (word 4: _ZN3ssd9SoundBank3vf1Ev where the original has =-24)
#ifndef CLASSES_SSD_SOUNDBANK_H
#define CLASSES_SSD_SOUNDBANK_H

namespace ssd {
// a base of ssd::SoundBank no evidence names yet
class TUnk_B81AA0 {
public:
    virtual ~TUnk_B81AA0();
    unsigned char pad_8[0x10];  // fields: size from where the next base starts
};
// a base of ssd::SoundBank no evidence names yet
class TUnk_B81AC0 {
public:
    virtual ~TUnk_B81AC0();
};
// table 0x7100B81AA0; base at 0x0 unknown (TUnk_B81AA0), base at 0x18 unknown (TUnk_B81AC0)
class SoundBank : public TUnk_B81AA0, public TUnk_B81AC0 {
public:
    virtual ~SoundBank();  // slot 0
    virtual void vf1();  // slot 1
};
}  // namespace ssd

#endif
