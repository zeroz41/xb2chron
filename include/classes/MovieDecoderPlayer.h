#ifndef CLASSES_MOVIEDECODERPLAYER_H
#define CLASSES_MOVIEDECODERPLAYER_H

// NintendoSDK's movie decoder sample player, as CMovieNX::CMovie drives it. Only the fields the matched code
// reaches are written out; the field names are not the original's.
#include <vector>
#include "movie/Decoder.h"
#include "nn/os.h"

// the player's clock (no symbols of its own: its members are all inlined): the time base the audio's first output
// buffer anchors
class MediaClock {
public:
    nn::os::MutexType m_mutex;
    unsigned char pad_20[0x18];
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

    void Render();
    void GenerateFixedSizeAudioFrame();
    void OnOutputAvailable(int index, long presentationTimeUs, unsigned int flags);

    unsigned char pad_0[0x9];
    bool m_exit;  // the render thread runs until it is set
    unsigned char pad_a[0x1];
    bool m_started;  // the render thread renders while it is set
    unsigned char pad_c[0x424];
    std::vector<audioData> m_outputBuffers;  // the decoder's outputs not yet played, under m_outputMutex
    unsigned char pad_448[0x38];
    long m_sleepMs;  // the render thread's wait between frames, in milliseconds
    unsigned char pad_488[0x8];
    nn::os::MutexType m_outputMutex;
    bool m_eos;  // isplaying's: the audio has played out
    MediaClock* m_mediaClock;  // Initialize's
    long m_startTimeUs;  // -1 until the first output buffer arrives
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

    unsigned char pad_0[0x210];
    std::vector<VideoData> m_outputBuffers;  // the decoder's outputs not yet shown, under m_outputMutex
    unsigned char pad_228[0x8];
    nn::os::MutexType m_outputMutex;
    unsigned char pad_250[0x18];
    bool m_started;  // isstandby's: the first frame is shown
    bool m_eos;  // isplaying's: the video has played out
};

class MovieDecoderPlayer {
public:
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

    unsigned char pad_0[0x8];
    movie::Decoder* m_audioDecoder;
    movie::Decoder* m_videoDecoder;
    unsigned char pad_18[0x418];
    AudioOutRenderer* m_audioOutRenderer;
    VideoRenderer* m_videoRenderer;
    unsigned char pad_440[0x40];
    bool m_videoInputThreadDone;  // VideoInputReadThreadFunction sets it when it stops
    unsigned char pad_481[0x1CF];
    bool m_audioInputThreadDone;  // AudioInputReadThreadFunction sets it when it stops
    unsigned char pad_651[0x397];
    std::vector<int> m_audioInputBuffers;  // free decoder input buffers, under m_audioInputMutex
    std::vector<int> m_videoInputBuffers;  // free decoder input buffers, under m_videoInputMutex
    nn::os::MutexType m_audioInputMutex;
    nn::os::MutexType m_videoInputMutex;
    unsigned char pad_a58[0x10];
    nn::os::MessageQueueType m_videoInputQueue;  // told of each free video input buffer
    nn::os::MessageQueueType m_audioInputQueue;  // told of each free audio input buffer
    unsigned char pad_b08[0x28];
    bool m_done;  // isplaying sets it once audio and video have played out
    unsigned char pad_b31[0x17];
    bool m_audioOutputEos;  // set when an audio output carries the end-of-stream flag (4)
    bool m_videoOutputEos;  // set when a video output carries the end-of-stream flag (4)
    unsigned char pad_b4a[0x2];
    int m_audioOutputCount;  // audio outputs handed to the renderer
    int m_videoOutputCount;  // video outputs handed to the renderer
};

#endif
