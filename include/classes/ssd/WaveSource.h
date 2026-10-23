#ifndef CLASSES_SSD_WAVESOURCE_H
#define CLASSES_SSD_WAVESOURCE_H

#include "classes/ssd/AudioFileBase.h"
#include "classes/ssd/String.h"
#include "ssd/AudioContents.h"
#include "classes/ssd/Object.h"
#include "ssd/Debug.h"

namespace ssd { class IoStreamBase; }
namespace ssd { class TextRef; }

namespace ssd {

// an ADPCM channel's header, 0x80 bytes after the contents header for each channel (the name is not the
// original's)
struct AdpcmHeader {
    unsigned char pad_0[0x80];
};

// table 0x7100B82100: audio data in memory (Init) or named by a file (InitWithFile) and its format. The field
// names are not the original's.
class WaveSource : public ::ssd::Object {
public:
    WaveSource();
    virtual ~WaveSource();  // slot 0

    Result Quit();
    Result Init(void* data, unsigned long size);
    Result InitWithFile(const TextRef& path);
    unsigned long TimeToSample(float time) const;
    unsigned long SampleToPosition(unsigned int sample) const;
    Result PreLoad(IoStreamBase* stream, bool headerOnly);
    const AdpcmHeader* GetAdpcmHeader(int channel) const;
    const unsigned char* GetDataAddress(int channel) const;
    unsigned int GetDataSize() const;

    // PreLoad has read the format; the source is a file (InitWithFile) rather than memory (Init)
    bool loaded_ = false;
    bool fromFile_ = false;
    unsigned char formatType_ = 0;
    AudioFormat format_;
    AudioFormatExtra extra_;
    unsigned int pad_6c = 0;
    // the memory Init was given, the audio data in it (or in buffer_, when it is not 64-byte aligned), the
    // ADPCM headers (format 3) and the copy PreLoad allocates
    AudioContents* contents_ = nullptr;
    unsigned long contentsSize_ = 0;
    unsigned char* data_ = nullptr;
    unsigned long dataSize_ = 0;
    AdpcmHeader* adpcmHeaders_ = nullptr;
    unsigned char* buffer_ = nullptr;
    // the file InitWithFile names
    String path_;
};
}  // namespace ssd

#endif
