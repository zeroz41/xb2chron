#ifndef CLASSES_SSD_SOUNDPARAM_H
#define CLASSES_SSD_SOUNDPARAM_H

#include "ssd/Hash.h"

namespace ssd { class TextRef; }

namespace ssd {
// how a sound is set up when it is added to a bank (fw::SoundSsdBank::addWave/addStream and
// fw::SoundSsdSource::getSoundParam call Init); the field names are not the original's
class SoundParam {
public:
    // a name: up to 31 UTF-16 characters and the text's hash
    struct Name {
        Name& operator=(const TextRef& text);

        char16_t text_[0x20];
        Hash hash_;
    };

    void Init();

    Name name_;
    unsigned char pad_48[4];
    bool flag4c_;
    bool flag4d_;
    bool flag4e_;
    bool flag4f_;
    float value50_;
    float value54_;
    float value58_;
    float value5c_;
    bool flag60_;
    bool flag61_;
    bool flag62_;
    bool flag63_;
    bool flag64_;
    bool flag65_;
    bool flag66_;
    bool flag67_;
    bool flag68_;
    bool flag69_;
    bool flag6a_;
    bool flag6b_;
    bool flag6c_;
    bool flag6d_;
    bool flag6e_;
    bool flag6f_;
    bool flag70_;
    bool flag71_;
    bool flag72_;
    bool flag73_;
    float value74_;
    float value78_;
    float value7c_;
    float value80_;
    float value84_;
    float value88_;
    unsigned int value8c_;
    float value90_;
};
}  // namespace ssd

#endif
