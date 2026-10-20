#ifndef CLASSES_SSD_AUDIOFILEWAVE_H
#define CLASSES_SSD_AUDIOFILEWAVE_H

namespace ssd { class IoStreamBase; }

namespace ssd {
// table 0x7100B82310
class AudioFileWave {
public:
    virtual void Open(ssd::IoStreamBase*);  // slot 0
    virtual void Close();  // slot 1
    virtual void PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual void PreSave();  // slot 4
    virtual void SaveAudioData(short const*, int);  // slot 5
    virtual ~AudioFileWave();  // slot 6
};
}  // namespace ssd

#endif
