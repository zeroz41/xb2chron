#ifndef CLASSES_SSD_AUDIOFILEAIFF_H
#define CLASSES_SSD_AUDIOFILEAIFF_H

#include "classes/ssd/AudioFileBase.h"

namespace ssd { class IoStreamBase; }

namespace ssd {
// table 0x7100B82400
class AudioFileAiff : public ::ssd::AudioFileBase {
public:
    virtual Result Open(IoStreamBase* stream);  // slot 0
    virtual Result Close();  // slot 1
    virtual Result PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual ~AudioFileAiff() {}  // slot 6

    unsigned char pad_98[0x50];
};
}  // namespace ssd

#endif
