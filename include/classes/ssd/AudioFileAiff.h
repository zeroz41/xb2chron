#ifndef CLASSES_SSD_AUDIOFILEAIFF_H
#define CLASSES_SSD_AUDIOFILEAIFF_H

#include "classes/ssd/AudioFileBase.h"

namespace ssd { class IoStreamBase; }

namespace ssd {
// table 0x7100B82400
class AudioFileAiff : public ::ssd::AudioFileBase {
public:
    virtual void Open(ssd::IoStreamBase*);  // slot 0
    virtual void Close();  // slot 1
    virtual void PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual ~AudioFileAiff();  // slot 6
};
}  // namespace ssd

#endif
