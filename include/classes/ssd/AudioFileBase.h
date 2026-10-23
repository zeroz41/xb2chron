#ifndef CLASSES_SSD_AUDIOFILEBASE_H
#define CLASSES_SSD_AUDIOFILEBASE_H

#include "ssd/Debug.h"

namespace ssd { class IoStreamBase; }

namespace ssd {

// the kind of media file MediaContentsHeader::CheckFileType finds; AudioFileBase::CreateFileBase makes the
// reader for it
enum MediaFileType : unsigned char {};

class MediaContentsHeader {
public:
    // reads the stream's header and stores the kind of file it is in type
    static Result CheckFileType(IoStreamBase* stream, MediaFileType* type);
};

// an audio file's format, as the readers' PreLoad fill it and WaveSource::PreLoad copies it, in three parts
// WaveSource::PreLoad copies one by one (the types' and the field names are not the original's:
// AudioFileSadf::PreLoad writes 16 bits per sample, the bytes per sample and per block from them, and the loop
// flag from the loop start and end; format 3 is ADPCM, whose samples TimeToSample and SampleToPosition count 14
// to 8 bytes)
struct AudioFormat {
    struct Data {
        unsigned int pad_0 = 0;
        unsigned int dataOffset = 0;
        unsigned int dataSize = 0;
        // WaveSource::PreLoad refuses in-memory data where it is not 0
        unsigned int reserved = 0;
        float sampleRate = 48000.0f;
        unsigned int pad_14 = 0;
    };
    struct Sample {
        unsigned char format = 0;
        unsigned char channelCount = 0;
        unsigned char pad_2[2];
        unsigned int bitsPerSample = 0;
        unsigned int bytesPerSample = 0;
        unsigned int blockAlign = 0;
    };
    // its copy is 0xE bytes, two short of a 4-aligned size: packed to 2
#pragma pack(push, 2)
    struct Loop {
        unsigned int loopStart = 0;
        unsigned int loopEnd = 0;
        unsigned short pad_8 = 0;
        unsigned short pad_a = 0;
        bool loop = false;
        unsigned char pad_d;
    };
#pragma pack(pop)

    Data data;
    Sample sample;
    Loop loop;
};

// what follows the format in a reader and a WaveSource, copied with it (the type's name is not the
// original's; AudioFileSadf::PreLoad fills its words from the file's header)
struct AudioFormatExtra {
    unsigned int pad_0[6];
};

// table 0x7100B82210
class AudioFileBase {
public:
    virtual void Open(ssd::IoStreamBase*);  // slot 0
    virtual void Close();  // slot 1
    virtual void PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual void PreSave();  // slot 4
    virtual void SaveAudioData(short const*, int);  // slot 5
    virtual ~AudioFileBase();  // slot 6

    // the reader for type, constructed in buffer, or null
    static AudioFileBase* CreateFileBase(MediaFileType type, unsigned char* buffer);
    // destroys the reader file points to
    static void CloseFileBase(AudioFileBase** file);

    unsigned char pad_8[0x14];
    AudioFormat format_;
    AudioFormatExtra extra_;
};

}  // namespace ssd

#endif
