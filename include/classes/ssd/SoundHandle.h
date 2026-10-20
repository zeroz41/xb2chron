#ifndef CLASSES_SSD_SOUNDHANDLE_H
#define CLASSES_SSD_SOUNDHANDLE_H

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
};
}  // namespace ssd

#endif
