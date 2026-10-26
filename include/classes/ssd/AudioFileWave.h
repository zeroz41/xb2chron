#ifndef CLASSES_SSD_AUDIOFILEWAVE_H
#define CLASSES_SSD_AUDIOFILEWAVE_H

#include "classes/ssd/AudioFileBase.h"

namespace ssd { class IoStreamBase; }

namespace ssd {
// table 0x7100B82310
class AudioFileWave : public ::ssd::AudioFileBase {
public:
    virtual Result Open(IoStreamBase* stream);  // slot 0
    virtual Result Close();  // slot 1
    virtual Result PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual Result PreSave();  // slot 4
    virtual Result SaveAudioData(const short* data, int count);  // slot 5
    virtual ~AudioFileWave() {}  // slot 6
};
}  // namespace ssd

#endif
