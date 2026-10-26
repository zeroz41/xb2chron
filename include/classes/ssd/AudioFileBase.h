#ifndef CLASSES_SSD_AUDIOFILEBASE_H
#define CLASSES_SSD_AUDIOFILEBASE_H

#include "classes/ssd/AudioMarkerList.h"
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

// table 0x7100B82210: a reader (or writer) of one kind of audio file, over a stream. The field names other than
// format_'s are not the original's.
class AudioFileBase {
public:
    AudioFileBase()
        : stream_(nullptr), readBuffer_(nullptr), ownsReadBuffer_(false), heap_(false), ownsStream_(false),
          writing_(false) {}

    virtual Result Open(IoStreamBase* stream);  // slot 0
    virtual Result Close();  // slot 1
    virtual Result PreLoad();  // slot 2
    virtual void SetPositionBySample(unsigned long);  // slot 3
    virtual Result PreSave();  // slot 4
    virtual Result SaveAudioData(const short* data, int count);  // slot 5
    virtual ~AudioFileBase();  // slot 6

    // the reader for type, constructed in buffer (or allocated when buffer is null), or null
    static AudioFileBase* CreateFileBase(MediaFileType type, unsigned char* buffer);
    // closes and destroys the reader file points to
    static Result CloseFileBase(AudioFileBase** file);

    // frees the read buffer if this reader allocated it
    void DeleteReadBuffer();
    // allocates a read buffer of size bytes unless there is one
    void NewReadBuffer(unsigned long size);
    // writes count blocks from data to the stream
    int WriteBySamples(const short* data, int count);

    IoStreamBase* stream_;
    void* readBuffer_;
    // DeleteReadBuffer frees readBuffer_ only while it is set (NewReadBuffer sets it)
    bool ownsReadBuffer_;
    // CreateFileBase allocated the reader: CloseFileBase deletes it rather than only destroying it
    bool heap_;
    // CloseFileBase closes the stream while it is set
    bool ownsStream_;
    // AudioFileWave::Close writes the RIFF header while it is set
    bool writing_;
    AudioFormat format_;
    AudioFormatExtra extra_;
    AudioMarkerList markers_;
};

}  // namespace ssd

#endif
