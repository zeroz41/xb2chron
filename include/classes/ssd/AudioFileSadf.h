#ifndef CLASSES_SSD_AUDIOFILESADF_H
#define CLASSES_SSD_AUDIOFILESADF_H

#include "classes/ssd/AudioFileBase.h"

namespace ssd { class IoStreamBase; }

namespace ssd {
// table 0x7100B822C0
class AudioFileSadf : public ::ssd::AudioFileBase {
public:
    virtual Result Open(IoStreamBase* stream);  // slot 0
    virtual Result Close();  // slot 1
    virtual Result PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual ~AudioFileSadf() {}  // slot 6
};
}  // namespace ssd

#endif
