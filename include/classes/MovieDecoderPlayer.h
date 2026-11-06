#ifndef CLASSES_MOVIEDECODERPLAYER_H
#define CLASSES_MOVIEDECODERPLAYER_H

// NintendoSDK's movie decoder sample player, as CMovieNX::CMovie drives it. Only the fields the matched code
// reaches are written out; the field names are not the original's.
#include <vector>
#include "movie/Decoder.h"
#include "nn/audio.h"
#include "nn/os.h"

// the movie library's allocator hooks (defined in cmovie_nx.cpp; they go through CMovieNX::CMovie's allocator)
void* MultimediaAllocate(unsigned long size, unsigned long alignment, void* userPtr);
void MultimediaFree(void* address, void* userPtr);
void* MultimediaReallocate(void* address, unsigned long size, void* userPtr);

// the player's threads (MovieDecoderPlayer::Initialize starts them with the player as argument)
void VideoInputReadThreadFunction(void* arg);
void AudioInputReadThreadFunction(void* arg);
void AudioVideoWorkerThreadFunction(void* arg);
// AudioOutRenderer::Initialize starts it with the renderer as argument
void AudioOutRendererThreadFunction(void* arg);

// the player's clock (no symbols of its own: its members are all inlined): the time base the audio's first output
// buffer anchors
class MediaClock {
public:
    // inlined (MovieDecoderPlayer::Initialize news it, 0x40 bytes; Finalize deletes it)
    MediaClock() {
        nn::os::InitializeMutex(&m_mutex, false, 0);
        m_anchorTimeMediaUs = -1;
        m_anchorTimeRealUs = -1;
        m_maxTimeMediaUs = 0x7FFFFFFFFFFFFFFF;
        m_anchorTimeUs = -1;
    }
    ~MediaClock() { nn::os::FinalizeMutex(&m_mutex); }

    nn::os::MutexType m_mutex;
    // -1, -1, INT64_MAX, -1: the initial values of Android's MediaClock (anchor media/real time, max media time,
    // starting media time), which the names follow
    long m_anchorTimeMediaUs;
    long m_anchorTimeRealUs;
    long m_maxTimeMediaUs;
    long m_anchorTimeUs;  // OnOutputAvailable sets it under the lock from the first output's time
};

class AudioOutRenderer {
public:
    // an audio decoder output buffer waiting to be played (the arguments OnOutputAvailable gets)
    struct audioData {
        int m_index;
        long m_presentationTimeUs;
        unsigned int m_flags;
    };

    ~AudioOutRenderer();
    int Initialize(MediaClock* mediaClock);
    int Finalize();
    int Start();
    int Render();
    void GenerateFixedSizeAudioFrame();
    void Close();
    void OnOutputAvailable(int index, long presentationTimeUs, unsigned int flags);

    movie::Decoder* m_decoder;  // Close returns the queued outputs to it
    bool m_threadStarted;  // Start's: the render thread runs (Close waits for it)
    bool m_exit;  // the render thread runs until it is set
    bool m_threadCreated;  // Initialize's: the render thread exists (Close destroys it)
    bool m_started;  // the render thread renders while it is set (StartAudioOut succeeded)
    bool m_audioOutOpened;  // Close stops and closes the audio out while it is set
    unsigned char pad_d[0x3];
    int m_sampleRate;  // Render's divisor of the played frames into microseconds
    int m_channelCount;  // Render repeats each sample this often when it exceeds m_decoderChannelCount
    unsigned char pad_18[0x4];
    int m_decoderChannelCount;
    int m_bytesPerSample;  // Initialize's 2
    unsigned char pad_24[0x4];
    long m_presentationTimeUs;  // Render's: the time of the buffer it plays
    unsigned long m_threadStackSize;
    void* m_threadStack;  // MultimediaAllocate's, for m_thread
    nn::os::ThreadType m_thread;  // "thAudioRenderer"
    nn::audio::AudioOut m_audioOut;
    long m_bufferCountMax;  // Initialize's 16 (no reader in the matched code; name inferred)
    void* m_audioOutBufferData[3];  // Start's: MultimediaAllocate'd, one per m_audioOutBuffers entry
    void* m_pcmBuffer;  // Initialize's: the decoded samples' buffers, sliced into m_emptyBuffers
    int m_pcmBufferSize;  // Initialize's allocation for m_pcmBuffer
    unsigned char pad_39c[0x4];
    nn::audio::AudioOutBuffer m_audioOutBuffers[3];
    int m_pcmBufferCount;  // Initialize cuts m_pcmBuffer into this many buffers of m_pcmBufferStride bytes
    int m_pcmBufferStride;
    int m_fixedFrameSize;  // GenerateFixedSizeAudioFrame's frame size
    bool m_fixedSizeFrames;  // GenerateFixedSizeAudioFrame gathers outputs into frames of m_fixedFrameSize
    unsigned char pad_425[0xB];
    std::vector<audioData> m_outputBuffers;  // the decoder's outputs not yet played, under m_outputMutex
    std::vector<movie::Buffer> m_emptyBuffers;  // Initialize's slices of m_pcmBuffer; Render returns played ones
    std::vector<movie::Buffer> m_filledBuffers;  // the frames waiting for Render, oldest first
    movie::Buffer* m_frameBuffer;  // Initialize's 0x4000-byte buffer
    long m_sleepMs;  // the render thread's wait between frames, in milliseconds
    unsigned long m_audioOutBufferSize;  // Start's allocation per m_audioOutBufferData entry
    nn::os::MutexType m_outputMutex;
    bool m_eos;  // isplaying's: the audio has played out
    MediaClock* m_mediaClock;  // Initialize's
    long m_startTimeUs;  // -1 until the first output buffer arrives
    long m_startRealTimeUs;  // Render's: the system time of the first rendered frame, -1 until then
    long m_playedFrames;  // Render's count of the frames handed to the audio out
};

class VideoRenderer {
public:
    // a video decoder output buffer waiting to be shown
    struct VideoData {
        int m_index;
        long m_presentationTimeUs;
        unsigned int m_flags;
    };

    // inlined (no symbol; the name follows AudioOutRenderer's): the output joins the list under its lock
    void OnOutputAvailable(int index, long presentationTimeUs, unsigned int flags) {
        VideoData data;
        data.m_index = index;
        data.m_presentationTimeUs = presentationTimeUs;
        data.m_flags = flags;
        nn::os::LockMutex(&m_outputMutex);
        m_outputBuffers.push_back(data);
        nn::os::UnlockMutex(&m_outputMutex);
    }

    // inlined (DestroypAudioVideoRenderer deletes it): the render thread's stack goes back to the movie allocator
    ~VideoRenderer() {
        if (m_threadStack != nullptr) {
            MultimediaFree(m_threadStack, nullptr);
        }
    }

    unsigned char pad_0[0x28];
    void* m_threadStack;  // StopAudioVideoRenderer frees it with the render thread at 0x30
    unsigned char pad_30[0x1E0];
    std::vector<VideoData> m_outputBuffers;  // the decoder's outputs not yet shown, under m_outputMutex
    unsigned char pad_228[0x8];
    nn::os::MutexType m_outputMutex;
    unsigned char pad_250[0x18];
    bool m_started;  // isstandby's: the first frame is shown
    bool m_eos;  // isplaying's: the video has played out
};

class MovieDecoderPlayer {
public:
    int Initialize(unsigned long coreMask);
    void Finalize();
    void DestroypAudioVideoRenderer();
    int VideoInputBufferAvailableEvent();
    void CheckForInputBuffersAndReadVideoInputData();
    void CheckForInputBuffersAndReadAudioInputData();
    int VideoOutputBufferAvailableEvent();
    int AudioInputBufferAvailableEvent();
    int AudioOutputBufferAvailableEvent();
    // inlined helpers (no symbols; names inferred): a free input buffer's index joins the list under its lock
    void AddBufferToVideoIndexList(int bufferIndex) {
        nn::os::LockMutex(&m_videoInputMutex);
        m_videoInputBuffers.push_back(bufferIndex);
        nn::os::UnlockMutex(&m_videoInputMutex);
    }
    void AddBufferToAudioIndexList(int bufferIndex) {
        nn::os::LockMutex(&m_audioInputMutex);
        m_audioInputBuffers.push_back(bufferIndex);
        nn::os::UnlockMutex(&m_audioInputMutex);
    }

    unsigned char pad_0[0x8];  // the extractor (ReadInputDataFromExtractorSendTodecoder's reads)
    movie::Decoder* m_audioDecoder;
    movie::Decoder* m_videoDecoder;
    // AudioVideoWorkerThreadFunction waits on all the holders below. A decoder's four events come in the order its
    // handlers tell (input buffer available, output buffer available, format changed, error). The three nested
    // types and their names are inferred: CreateDecoders passes the pointer sets (0xB0, 0xD0) on as one argument,
    // and Initialize/Finalize reach each event and holder set through its start address.
    struct DecoderEvents {
        nn::os::EventType* m_inputBufferAvailableEvent;
        nn::os::EventType* m_outputBufferAvailableEvent;
        nn::os::EventType* m_formatChangedEvent;
        nn::os::EventType* m_errorEvent;
    };
    struct DecoderEventTypes {
        nn::os::EventType m_inputBufferAvailableEvent;
        nn::os::EventType m_outputBufferAvailableEvent;
        nn::os::EventType m_formatChangedEvent;
        nn::os::EventType m_errorEvent;  // "Error event received from Video Decoder"
    };
    struct DecoderMultiWaitHolders {
        nn::os::MultiWaitHolderType m_inputBufferAvailableHolder;
        nn::os::MultiWaitHolderType m_outputBufferAvailableHolder;
        nn::os::MultiWaitHolderType m_formatChangedHolder;
        nn::os::MultiWaitHolderType m_errorHolder;
    };

    nn::os::EventType m_workerExitEvent;  // Finalize signals it before it waits for the worker thread
    nn::os::MultiWaitHolderType m_workerExitHolder;
    nn::os::MultiWaitType m_multiWait;
    DecoderEvents m_audioDecoderEvents;
    DecoderEvents m_videoDecoderEvents;
    DecoderEventTypes m_audioDecoderEventTypes;
    DecoderEventTypes m_videoDecoderEventTypes;
    DecoderMultiWaitHolders m_audioDecoderHolders;
    DecoderMultiWaitHolders m_videoDecoderHolders;
    AudioOutRenderer* m_audioOutRenderer;
    VideoRenderer* m_videoRenderer;
    int m_trackCount;  // CreateExtractor's: the extractor's track count
    int m_width;  // VideoFormatChangedEvent's "width"
    int m_height;  // VideoFormatChangedEvent's "height"
    unsigned char pad_44c[0x24];
    unsigned long m_threadStackSize;  // each of the three threads' stack size
    void* m_videoInputThreadStack;
    bool m_videoInputThreadDone;  // VideoInputReadThreadFunction sets it when it stops
    bool m_videoInputThreadCreated;
    nn::os::ThreadType m_videoInputThread;
    void* m_audioInputThreadStack;
    bool m_audioInputThreadDone;  // AudioInputReadThreadFunction sets it when it stops
    bool m_audioInputThreadCreated;
    nn::os::ThreadType m_audioInputThread;
    void* m_workerThreadStack;
    bool m_workerThreadDone;  // Finalize sets it to stop AudioVideoWorkerThreadFunction
    bool m_workerThreadCreated;
    nn::os::ThreadType m_workerThread;
    std::vector<int> m_audioInputBuffers;  // free decoder input buffers, under m_audioInputMutex
    std::vector<int> m_videoInputBuffers;  // free decoder input buffers, under m_videoInputMutex
    nn::os::MutexType m_audioInputMutex;
    nn::os::MutexType m_videoInputMutex;
    unsigned long m_inputQueueSize;  // each input queue's message count (Initialize: 0x80)
    unsigned long* m_videoInputQueueBuffer;
    nn::os::MessageQueueType m_videoInputQueue;  // told of each free video input buffer
    unsigned long* m_audioInputQueueBuffer;
    nn::os::MessageQueueType m_audioInputQueue;  // told of each free audio input buffer
    unsigned char pad_b00[0xC];
    int m_loopCount;  // ReadInputDataFromExtractorSendTodecoder counts each rewind to the start at the stream's end
    unsigned char pad_b10[0x18];
    MediaClock* m_mediaClock;  // Initialize news it whether the threads started or not
    bool m_done;  // isplaying sets it once audio and video have played out
    unsigned char pad_b31[0x7];
    long m_clearedLong0;  // Initialize clears it (no other user in the unit)
    long m_clearedLong1;  // Initialize clears it (no other user in the unit)
    bool m_audioOutputEos;  // set when an audio output carries the end-of-stream flag (4)
    bool m_videoOutputEos;  // set when a video output carries the end-of-stream flag (4)
    bool m_inputEos;  // ReadInputDataFromExtractorSendTodecoder sets it at the stream's end, then sends EOS
    unsigned char pad_b4b[0x1];
    int m_audioOutputCount;  // audio outputs handed to the renderer
    int m_videoOutputCount;  // video outputs handed to the renderer
};

#endif
