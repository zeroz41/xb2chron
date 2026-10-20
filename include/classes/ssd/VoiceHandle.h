#ifndef CLASSES_SSD_VOICEHANDLE_H
#define CLASSES_SSD_VOICEHANDLE_H

namespace ssd {
// a base of ssd::VoiceHandle no evidence names yet
class TUnk_B820C0 {
public:
    virtual ~TUnk_B820C0();
    unsigned char pad_8[0x10];  // fields: size from where the next base starts
};
// a base of ssd::VoiceHandle no evidence names yet
class TUnk_B820E0 {
public:
    virtual ~TUnk_B820E0();
};
// table 0x7100B820C0; base at 0x0 unknown (TUnk_B820C0), base at 0x18 unknown (TUnk_B820E0)
class VoiceHandle : public TUnk_B820C0, public TUnk_B820E0 {
public:
    virtual ~VoiceHandle();  // slot 0
};
}  // namespace ssd

#endif
