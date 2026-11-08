#ifndef MOVIE_DECODER_H
#define MOVIE_DECODER_H

// NintendoSDK's movie library (namespace movie, imported from the SDK's module): only what the sample player the
// game carries (MovieDecoderPlayer) reaches.

namespace movie {

// a decoder's data buffer, 0x30 bytes (std::vector<movie::Buffer> steps by 0x30); copied and destroyed by the
// library's own constructor and destructor
class Buffer {
public:
    Buffer();
    explicit Buffer(unsigned long capacity);
    Buffer(void* base, unsigned long capacity);
    Buffer(const Buffer&);
    ~Buffer();
    Buffer& operator=(const Buffer&);

    void* Base() const;
    unsigned long Capacity() const;
    int Offset() const;
    int Size() const;
    void SetRange(int offset, int size);
    void SetDataAndCapacity(void* base, unsigned long capacity);
    unsigned int GetUint32Data() const;
    long GetInt64Data() const;
    void SetUint32Data(unsigned int data);
    void SetInt32Data(int data);
    void SetInt64Data(long data);


    unsigned char pad_0[0x30];
};

// a call's result (movie::StatusToString(movie::Status) is imported; 0 = success)
enum Status {};
// the constructors' argument types (Decoder(DecoderType, DecoderOutputFormat), Extractor(ContainerType))
enum DecoderType {};
enum DecoderOutputFormat {};
enum ContainerType {};

// a key/value set of a track's or a decoder's format (FindInt32("width", ...)); only the imports the game reaches
class MediaData {
public:
    MediaData();
    ~MediaData();
    MediaData& operator=(const MediaData&);
    bool FindInt32(const char* name, int* value) const;
    bool FindString(const char* name, const char** value) const;
    void Clear();

    unsigned char pad_0[0x8];
};

// the events a decoder signals (Decoder::RegisterClientEvents(DecoderEvents*)); its layout is not reached here
struct DecoderEvents;

// the file access an extractor reads through (Extractor::SetDataSource(ClientStreamReader*, const char*)); the game's
// StreamReader implements it. The library has no table of its own for it (an interface), so the slots follow the
// game's StreamReader table.
class ClientStreamReader {
public:
    virtual ~ClientStreamReader() {}
    virtual bool Open(char const* path, void** handle) = 0;
    virtual unsigned long ReadAt(void* handle, long offset, void* buffer, unsigned long size) = 0;
    virtual bool Close(void* handle) = 0;
    virtual void GetSize(void* handle, long* size) = 0;
};

// The two classes' virtual slots follow the library's own tables (_ZTVN5movie9ExtractorE, _ZTVN5movie7DecoderE in
// the game's subsdk0 module); the argument names are inferred.
class Extractor {
public:
    explicit Extractor(ContainerType type);
    virtual ~Extractor();
    virtual Status SetDataSource(const char* path);
    virtual Status SetDataSource(const void* data, int size);
    virtual Status GetTrackCount(int* trackCount);
    virtual Status GetTrackConfiguration(int trackIndex, MediaData* config);
    virtual Status SelectTrack(int trackIndex);
    virtual Status UnselectTrack(int trackIndex);
    virtual Status SeekTo(long timeUs);
    virtual Status GetTrackIndexForAvailableData(unsigned long* trackIndex);
    virtual Status Read(Buffer* buffer);
    virtual Status Advance();
    virtual Status GetSampleTime(long* timeUs);
    virtual Status GetSampleMetaData(MediaData* meta);
    virtual Status GetBufferedRange(long* startUs, long* endUs);
    virtual Status SetDataSource(ClientStreamReader* reader, const char* path);

    unsigned char pad_8[0x8];
};

class Decoder {
public:
    Decoder(DecoderType type, DecoderOutputFormat outputFormat);
    virtual ~Decoder();
    virtual Status Configure(MediaData* config);
    virtual Status RegisterClientEvents(DecoderEvents* events);
    virtual Status GetOutputFormat(MediaData* format);
    virtual Status Start();
    virtual Status Stop();
    virtual Status Reset();
    virtual Status Flush();
    // a free input buffer's index and how many more are free
    virtual Status AcquireInputBufferIndex(int* index, int* count);
    virtual Status GetInputBuffer(int index, Buffer* buffer);
    virtual Status SendInputBufferForDecode(int index, int offset, int size, long presentationTimeUs,
                                            unsigned int flags);
    // a decoded buffer's index, time and flags (4 at the end of the stream) and how many more are ready
    virtual Status AcquireOutputBufferIndex(int* index, long* presentationTimeUs, unsigned int* flags, int* count);
    virtual Status GetOutputBuffer(int index, Buffer* buffer);
    virtual Status GetOutputBufferSize(int* width, int* height);
    virtual Status ReleaseOutputBufferIndex(int index);
    virtual Status GetLastError();
    virtual Status GetOutputBuffer(int index, Buffer* buffer, MediaData* format);
    virtual Status GetOutputBufferFormat(int index, MediaData* format);
};

// the library's allocator hooks (MovieDecoderPlayer::Initialize installs MultimediaAllocate/Free/Reallocate) and the
// cores its threads may run on
void SetAllocator(void* (*allocate)(unsigned long size, unsigned long alignment, void* userPtr),
                  void (*free)(void* address, void* userPtr),
                  void* (*reallocate)(void* address, unsigned long size, void* userPtr), void* userPtr);
void SetCoreMask(unsigned long coreMask);

}  // namespace movie

#endif
