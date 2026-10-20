#ifndef CLASSES_SSD_SOUNDENTRY_H
#define CLASSES_SSD_SOUNDENTRY_H

namespace ssd {
// a base of ssd::SoundEntry no evidence names yet
class TUnk_B81A60 {
public:
    virtual ~TUnk_B81A60();
    unsigned char pad_8[0x10];  // fields: size from where the next base starts
};
// a base of ssd::SoundEntry no evidence names yet
class TUnk_B81A80 {
public:
    virtual ~TUnk_B81A80();
};
// table 0x7100B81A60; base at 0x0 unknown (TUnk_B81A60), base at 0x18 unknown (TUnk_B81A80)
class SoundEntry : public TUnk_B81A60, public TUnk_B81A80 {
public:
    virtual ~SoundEntry();  // slot 0
};
}  // namespace ssd

#endif
