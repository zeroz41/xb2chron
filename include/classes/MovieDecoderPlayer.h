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

    // The members below are inlined (no symbols); their names and forms follow Android's MediaClock, whose fields
    // and initial values this clock has (no playback rate). The current time is the system tick in microseconds.
    // VideoRenderer::AVSync's: the first frame's media time anchors at the current real time
    void updateAnchor(long anchorTimeMediaUs, long anchorTimeRealUs, long maxTimeMediaUs) {
        if (anchorTimeMediaUs < 0 || anchorTimeRealUs < 0) {
            return;
        }
        nn::os::LockMutex(&m_mutex);
        long nowUs = nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMicroSeconds();
        long nowMediaUs = anchorTimeMediaUs + (nowUs - anchorTimeRealUs);
        if (nowMediaUs >= 0) {
            m_anchorTimeMediaUs = nowMediaUs;
            m_anchorTimeRealUs = nowUs;
            m_maxTimeMediaUs = maxTimeMediaUs;
        }
        nn::os::UnlockMutex(&m_mutex);
    }
    // AudioOutRenderer::Render's: the media time of the first rendered frame (the argument is read before the lock)
    void setStartingTimeMedia(long startingTimeMediaUs) {
        nn::os::LockMutex(&m_mutex);
        m_anchorTimeUs = startingTimeMediaUs;
        nn::os::UnlockMutex(&m_mutex);
    }
    // the media time at realUs; -1 while no anchor is set
    int getMediaTime_l(long realUs, long* outMediaUs, bool allowPastMaxTime) const {
        if (m_anchorTimeRealUs == -1) {
            return -1;
        }
        long mediaUs = m_anchorTimeMediaUs + (realUs - m_anchorTimeRealUs);
        if (mediaUs > m_maxTimeMediaUs && !allowPastMaxTime) {
            mediaUs = m_maxTimeMediaUs;
        }
        if (mediaUs < m_anchorTimeUs) {
            mediaUs = m_anchorTimeUs;
        }
        if (mediaUs < 0) {
            mediaUs = 0;
        }
        *outMediaUs = mediaUs;
        return 0;
    }
    // VideoRenderer::GetRealTimeUs's: the real time at which targetMediaUs plays (defined below with the inline
    // keyword: GetRealTimeUs inlines it)
    int getRealTimeFor(long targetMediaUs, long* outRealUs);

    nn::os::MutexType m_mutex;
    // -1, -1, INT64_MAX, -1: the initial values of Android's MediaClock (anchor media/real time, max media time,
    // starting media time), which the names follow
    long m_anchorTimeMediaUs;
    long m_anchorTimeRealUs;
    long m_maxTimeMediaUs;
    long m_anchorTimeUs;  // OnOutputAvailable sets it under the lock from the first output's time
};

inline int MediaClock::getRealTimeFor(long targetMediaUs, long* outRealUs) {
    nn::os::LockMutex(&m_mutex);
    long nowUs = nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMicroSeconds();
    long nowMediaUs;
    int status = getMediaTime_l(nowUs, &nowMediaUs, true);
    if (status != 0) {
        nn::os::UnlockMutex(&m_mutex);
        return status;
    }
    *outRealUs = (targetMediaUs - nowMediaUs) + nowUs;
    nn::os::UnlockMutex(&m_mutex);
    return 0;
}

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
    // inlined (no symbol; name inferred): StopAudioVideoRenderer's return of the queued outputs to the decoder
    void Flush() {
        nn::os::LockMutex(&m_outputMutex);
        int count = m_outputBuffers.size();
        for (int i = 0; i < count; i++) {
            if (m_decoder != nullptr) {
                audioData& data = m_outputBuffers.front();
                m_decoder->ReleaseOutputBufferIndex(data.m_index);
            }
            m_outputBuffers.erase(m_outputBuffers.begin());
        }
        nn::os::UnlockMutex(&m_outputMutex);
    }

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

    // inlined (no symbols; names inferred, Close and Finalize after AudioOutRenderer's): StopAudioVideoRenderer
    // returns the queued outputs to the decoder, stops the render thread and frees its stack
    void Flush() {
        nn::os::LockMutex(&m_outputMutex);
        int count = m_outputBuffers.size();
        for (int i = 0; i < count; i++) {
            m_decoder->ReleaseOutputBufferIndex(m_outputBuffers.begin()->m_index);
            m_outputBuffers.erase(m_outputBuffers.begin());
        }
        nn::os::UnlockMutex(&m_outputMutex);
    }
    void Close() {
        m_exit = true;
        if (m_threadCreated) {
            if (m_threadStarted) {
                nn::os::WaitThread(&m_thread);
                m_threadStarted = false;
            }
            nn::os::DestroyThread(&m_thread);
            m_threadCreated = false;
        }
    }
    void Finalize() {
        if (m_threadStack != nullptr) {
            MultimediaFree(m_threadStack, nullptr);
            m_threadStack = nullptr;
        }
        nn::os::FinalizeMutex(&m_outputMutex);
    }

    int Render();
    bool AVSync(long presentationTimeUs);
    long GetRealTimeUs(long mediaTimeUs, long nowUs);

    movie::Decoder* m_decoder;  // Render takes the outputs from it
    bool m_threadStarted;  // the render thread runs (Close waits for it)
    bool m_exit;  // the render thread runs until it is set
    bool m_threadCreated;  // the render thread exists (Close destroys it)
    unsigned char pad_b[0x5];
    long m_presentationTimeUs;  // AVSync's: the time of the frame it checks
    unsigned char pad_18[0x10];
    void* m_threadStack;  // StopAudioVideoRenderer frees it with the render thread at 0x30
    nn::os::ThreadType m_thread;
    unsigned char pad_1f0[0x20];
    std::vector<VideoData> m_outputBuffers;  // the decoder's outputs not yet shown, under m_outputMutex
    unsigned char pad_228[0x8];
    nn::os::MutexType m_outputMutex;
    unsigned long m_frameSize;  // Render's capacity and range of the frame buffer
    void* m_frame;  // Render copies the first shown output into it
    unsigned char pad_260[0x8];
    bool m_started;  // isstandby's: the first frame is shown
    bool m_eos;  // isplaying's: the video has played out
    unsigned char pad_26a[0x6];
    MediaClock* m_mediaClock;
    long m_sleepUs;  // the render thread's wait before the next frame (AVSync's; kept within 2000..300000)
    long m_startRealTimeUs;  // AVSync's: the real time of the first frame
    int m_droppedFrames;  // AVSync's count of frames shown more than 40 ms late
    bool m_firstFrame;  // AVSync anchors the clock at the next frame while it is set
    long m_lastPresentationTimeUs;  // AVSync's; GetRealTimeUs's base while the clock has no anchor
};

class MovieDecoderPlayer {
public:
    int Initialize(unsigned long coreMask);
    void Finalize();
    void StopAudioVideoRenderer();
    void DestroypAudioVideoRenderer();
    int CreateExtractor(const char* path, movie::ContainerType type, movie::Extractor** extractor,
                        movie::ClientStreamReader** reader);
    int VideoInputBufferAvailableEvent();
    int CreateDecoders(movie::Extractor* extractor);
    int ReadInputDataFromExtractorSendTodecoder(int index, movie::Decoder* decoder);
    int SendEosToDecoder();
    int CheckForInputBuffersAndReadVideoInputData();
    int CheckForInputBuffersAndReadAudioInputData();
    int VideoOutputBufferAvailableEvent();
    int VideoFormatChangedEvent();
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
    // inlined helpers (no symbols; names inferred): CMovie::stop tells an input thread to stop and waits for it
    void StopVideoInputReadThread() {
        if (m_videoInputThreadCreated) {
            m_videoInputThreadDone = true;
            nn::os::SendMessageQueue(&m_videoInputQueue, 2);
            nn::os::WaitThread(&m_videoInputThread);
            nn::os::DestroyThread(&m_videoInputThread);
            m_videoInputThreadCreated = false;
        }
    }
    void StopAudioInputReadThread() {
        if (m_audioInputThreadCreated) {
            m_audioInputThreadDone = true;
            nn::os::SendMessageQueue(&m_audioInputQueue, 4);
            nn::os::WaitThread(&m_audioInputThread);
            nn::os::DestroyThread(&m_audioInputThread);
            m_audioInputThreadCreated = false;
        }
    }
    // inlined helpers (no symbols; names inferred): the oldest free input buffer's index leaves the list (-1 when it
    // is empty), and the list's size, each under its lock
    int GetBufferFromVideoIndexList() {
        int bufferIndex = -1;
        nn::os::LockMutex(&m_videoInputMutex);
        if (static_cast<int>(m_videoInputBuffers.size()) > 0) {
            bufferIndex = m_videoInputBuffers.front();
            m_videoInputBuffers.erase(m_videoInputBuffers.begin());
        }
        nn::os::UnlockMutex(&m_videoInputMutex);
        return bufferIndex;
    }
    int GetBufferFromAudioIndexList() {
        int bufferIndex = -1;
        nn::os::LockMutex(&m_audioInputMutex);
        if (static_cast<int>(m_audioInputBuffers.size()) > 0) {
            bufferIndex = m_audioInputBuffers.front();
            m_audioInputBuffers.erase(m_audioInputBuffers.begin());
        }
        nn::os::UnlockMutex(&m_audioInputMutex);
        return bufferIndex;
    }
    int GetVideoIndexListSize() {
        nn::os::LockMutex(&m_videoInputMutex);
        int size = m_videoInputBuffers.size();
        nn::os::UnlockMutex(&m_videoInputMutex);
        return size;
    }
    int GetAudioIndexListSize() {
        nn::os::LockMutex(&m_audioInputMutex);
        int size = m_audioInputBuffers.size();
        nn::os::UnlockMutex(&m_audioInputMutex);
        return size;
    }

    movie::Extractor* m_extractor;  // ReadInputDataFromExtractorSendTodecoder's reads
    movie::Decoder* m_audioDecoder;
    movie::Decoder* m_videoDecoder;
    // AudioVideoWorkerThreadFunction waits on all the holders below. A decoder's four events come in the order its
    // handlers tell (input buffer available, output buffer available, format changed, error). The three nested
    // types' names are inferred: CreateDecoders registers the pointer sets (0xB0, 0xD0) with the decoders, and
    // Initialize/Finalize reach each event and holder set through its start address.
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
    movie::DecoderEvents m_audioDecoderEvents;
    movie::DecoderEvents m_videoDecoderEvents;
    DecoderEventTypes m_audioDecoderEventTypes;
    DecoderEventTypes m_videoDecoderEventTypes;
    DecoderMultiWaitHolders m_audioDecoderHolders;
    DecoderMultiWaitHolders m_videoDecoderHolders;
    AudioOutRenderer* m_audioOutRenderer;
    VideoRenderer* m_videoRenderer;
    int m_trackCount;  // CreateExtractor's: the extractor's track count
    int m_width;  // VideoFormatChangedEvent's "width"
    int m_height;  // VideoFormatChangedEvent's "height"
    unsigned char pad_44c[0xC];
    double m_frameRate;  // CreateDecoders': the video track's "frame-rate", 60 when it has none
    unsigned char pad_460[0x8];
    int m_audioTrackIndex;  // the extractor's track the audio decoder reads
    int m_videoTrackIndex;  // the extractor's track the video decoder reads
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
    int m_audioDecoderType;  // CreateDecoders': 4 for "audio/mp4a-latm", 5 for "audio/vorbis" (0 without a decoder)
    // CreateDecoders': the video decoder's type, 1..3 for "video/avc", "video/x-vnd.on2.vp8", "video/x-vnd.on2.vp9";
    // CheckForInputBuffersAndReadAudioInputData tests 1..3 when there is no extractor
    int m_mode;
    bool m_audioDecoderCreated;  // CreateDecoders sets it with the audio decoder
    bool m_running;  // CreateDecoders sets it with the video decoder; CMovie::stop tears the player down while set
    bool m_loop;  // at the stream's end the extractor seeks back to the start while it is set
    unsigned char pad_b0b[0x1];
    int m_loopCount;  // ReadInputDataFromExtractorSendTodecoder counts each rewind to the start at the stream's end
    // two formats (destroyed with the player as an array, no other user in the unit; name inferred) and the
    // extractor's reader
    movie::MediaData m_formats[2];
    movie::ClientStreamReader* m_streamReader;
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
