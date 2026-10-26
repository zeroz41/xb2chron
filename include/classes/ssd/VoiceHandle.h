#ifndef CLASSES_SSD_VOICEHANDLE_H
#define CLASSES_SSD_VOICEHANDLE_H

#include "classes/ssd/List.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/SoundHandle.h"
#include "nn/audio.h"
#include "ssd/Debug.h"

namespace ssd { class SoundEntry; }
namespace ssd { class StreamController; }
namespace ssd { class WaveSource; }

namespace ssd {
// table 0x7100B820C0: one playing voice. SystemCore keeps them in an array at 0x3F0 (Init gives each its index)
// and links the playing ones into its list through the Node base at 0x18. sizeof 0x710. The field names are not
// the original's.
class VoiceHandle : public Object, public List<VoiceHandle>::Node {
public:
    // one channel's renderer voice and its buffers (the type's and the field names are not the original's)
    struct Channel {
        Channel() : voice(), pad_98(nullptr), pad_a0(nullptr), pad_a8(nullptr) {}

        nn::audio::VoiceType voice;
        unsigned char pad_8[0x90];
        void* pad_98;
        void* pad_a0;
        void* pad_a8;
        int pad_b0;
        unsigned char pad_b4[0x4];
    };

    VoiceHandle();
    virtual ~VoiceHandle();  // slot 0

    static void AllocAdpcmSplitBuffer();
    static void FreeAdpcmSplitBuffer();
    void Init(int index);
    void Quit();
    void FreeVoice();
    void* AllocHWVoice();
    Result Prepare(const SoundEntry* entry, SoundHandle* handle, unsigned int* id);
    Result Start(float fadeTime, bool loop);
    Result Stop(float fadeTime);
    Result Pause(bool pause, float fadeTime);
    Result ForceStop();
    Result GetPlayTime(float* time) const;
    Result SetPlayTime(float time);
    Result GetRemainLoopCount(int* count) const;
    Result SetRemainLoopCount(int count);
    void UpdateGameFrame(float frameTime);
    void UpdateAudioFrame(float frameTime);
    void UpdateAudioInternal(float frameTime);
    void UpdateAudioStream(float frameTime);
    void AcquireBuffer();
    void UpdateAudioVoice(float frameTime);
    void UpdateOutputParam(float frameTime);
    void DeleteStream();
    void StreamingBufferProcess();
    void AddStreamingBuffer();
    void NullBufferProcess();

    // AllocAdpcmSplitBuffer's 0x10000 bytes
    static unsigned char* adpcmSplitBuffer_;

    unsigned char pad_30;
    bool pad_31;  // Start sets it
    bool pad_32;  // Pause resumes only while it is set; Stop and ForceStop clear it
    bool pad_33;
    bool paused_;  // 0x34: Pause sets it
    bool pad_35;
    bool stopping_;  // 0x36: Stop and ForceStop set it
    bool pad_37;
    bool pad_38;
    bool loop_;  // 0x39: Start's flag
    bool free_;  // 0x3A: FreeVoice sets it
    bool pad_3b;  // FreeVoice clears it
    bool pad_3c;
    bool pad_3d;  // the constructor and Stop set it
    unsigned char pad_3e[0x2];
    bool endOfStream_;  // 0x40: StreamingBufferProcess sets it once no buffer is queued
    int state_;  // 0x44: SoundHandle::GetState: 8 once ready to start; 5, 6 and 7 while preparing
    int pad_48;
    int channelCount_;  // 0x4C: StreamingBufferProcess's channel count
    int index_;  // 0x50: Init's index, -1 before
    int pad_54;
    SoundHandle* handle_;  // 0x58
    const SoundEntry* entry_;  // 0x60
    WaveSource* source_;  // 0x68: FreeVoice drops its reference
    StreamController* stream_;  // 0x70
    void (VoiceHandle::*bufferProcess_)();  // 0x78: NullBufferProcess until a buffer process is chosen
    int queuedBuffers_;  // 0x88: StreamingBufferProcess counts released buffers off it
    int releasedBuffers_;  // 0x8C: StreamingBufferProcess counts them; AddStreamingBuffer refills them
    Channel channels_[8];  // 0x90
    unsigned char pad_650[0x8];
    void* audioData_;  // 0x658: SystemCorePlatform::AllocAudioDataBuffer's (Quit frees it)
    int pad_660;
    unsigned char pad_664[0x4];
    unsigned char pad_668;
    unsigned char seek_;  // 0x669: SetPlayTime sets 3, Start 1
    unsigned char pad_66a[0x6];
    unsigned long pad_670;  // Init sets 24000
    unsigned long pad_678;  // Init sets 12000
    unsigned long pad_680;
    unsigned long pad_688;
    unsigned long playPosition_;  // 0x690: StreamingBufferProcess adds each released buffer's size
    unsigned long pad_698;
    float seekTime_;  // 0x6A0: SetPlayTime's time
    unsigned char pad_6a4[0x4];
    unsigned long pad_6a8;
    unsigned short pad_6b0;
    unsigned char pad_6b2[0x2];
    float pad_6b4;
    float pad_6b8;
    float pad_6bc;
    float pad_6c0;
    unsigned char pad_6c4[0xc];
    SoundHandle::FadeValue volume_;  // 0x6D0: Start fades it to 1, Stop and Pause to 0
    unsigned char pad_6e8[0x8];
    float pad_6f0;
    unsigned char pad_6f4[0x1c];
};
}  // namespace ssd

#endif
