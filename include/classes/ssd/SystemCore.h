#ifndef CLASSES_SSD_SYSTEMCORE_H
#define CLASSES_SSD_SYSTEMCORE_H

#include "classes/ssd/BehaviorInstance.h"
#include "classes/ssd/List.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/XorShift128Random.h"
#include "classes/ssd/Array.h"
#include "classes/ssd/SoundCategory.h"
#include "classes/ssd/SoundGroup.h"
#include "ssd/Mutex.h"
#include "ssd/Thread.h"

namespace ssd { class SoundActor; }
namespace ssd { class SoundBank; }
namespace ssd { class SoundEffecter; }
namespace ssd { class SoundHandle; }
namespace ssd { class SoundListener; }
namespace ssd { class VoiceHandle; }
namespace ssd { class StreamController; }
namespace ssd { namespace Delegate { class Handle; }}
namespace ssd { namespace OutputMode { enum Type : int; }}  // the values are not known yet

namespace ssd {
// table 0x7100B81D10
class SystemCore : public ::ssd::SystemCorePlatform {
public:
    // builds every member; Init sets them up
    SystemCore();
    virtual OutputMode::Type GetOutputMode() const;  // slot 0
    virtual void SetOutputMode(OutputMode::Type);  // slot 1
    virtual float GetMasterVolume() const;  // slot 2
    virtual void SetMasterVolume(float, float);  // slot 3
    virtual float GetMasterPitch() const;  // slot 4
    virtual void SetMasterPitch(float, float);  // slot 5
    virtual void AddSoundListener(ssd::SoundListener*);  // slot 6
    virtual void RemoveSoundListener(ssd::SoundListener*);  // slot 7
    virtual Result GetSoundEffectList(int, ssd::SoundEffecter**, int*);  // slot 8
    virtual Result AddSoundEffecter(unsigned char, ssd::SoundEffecter*);  // slot 9
    virtual Result RemoveSoundEffecter(ssd::SoundEffecter*);  // slot 10
    virtual bool IsActiveEffect(unsigned char);  // slot 11
    virtual int GetNumPlaySound() const;  // slot 12
    virtual float GetSpeedOfSound() const;  // slot 13
    virtual void SetSpeedOfSound(float);  // slot 14
    virtual double GetAudioCpuLoad() const;  // slot 15
    virtual void LockAudio() const;  // slot 16
    virtual void UnlockAudio() const;  // slot 17
    virtual ~SystemCore();  // slot 19
    virtual const DebugInfo* GetDebugInfo() const;  // slot 21

    Result Init(const SoundCore::InitParam& param);
    Result Quit();
    Result SetCategory(const SoundCategory& category);
    Result ResetCategory(int categoryId);
    // copies the category with the id into *category (-42 when no category has it)
    Result GetCategory(int id, SoundCategory* category) const;
    // the actors SoundActor::Init connects and Quit disconnects (ConnectActor links the actor into the list at
    // 0x448 under audioLock_); Stop and Pause reach every sound an actor plays
    void StopActor(SoundActor* actor, float fadeTime);
    void PauseActor(SoundActor* actor, bool pause, float fadeTime);
    // fills handles with the sounds actor plays and returns how many
    int GetPlaySoundHandleFromActor(const SoundActor* actor, Array<SoundHandle*>* handles) const;
    void ConnectActor(SoundActor* actor);
    // the banks SoundBank::Init adds and Quit removes; StopBank stops every sound of the bank's entries
    void AddBank(SoundBank* bank);
    void RemoveBank(SoundBank* bank);
    void StopBank(SoundBank* bank, float fadeTime);
    void DisconnectActor(SoundActor* actor);
    void UpdateGameFrame(float frameTime);
    void StopSound(float fadeTime);

    // the category with the id (SoundHandle::Start and SetCategoryId copy it)
    SoundCategory* GetCategory(int id) const;
    // a free voice in *voice (SoundHandle::Prepare passes 0 for kind, whose meaning is unknown, and checks only
    // *voice)
    Result AllocVoiceHandle(int kind, VoiceHandle** voice);
    VoiceHandle* GetVoiceHandle(unsigned int id) const;  // 0 when no voice has the id
    // gives a voice back (VoiceHandle::FreeVoice)
    void FreeVoiceHandle(VoiceHandle* voice);
    void MasterVolumeBehavior(float frameTime);
    void MasterPitchBehavior(float frameTime);
    // the stream thread links the stream controllers in and out under audioLock_
    void AddStreamController(StreamController* controller);
    void RemoveStreamController(StreamController* controller);
    // the two threads' functions: the stream thread runs StreamThreadImpl, the audio thread processes one audio
    // frame each time the platform's system event is signalled, until the thread is closed
    static void StreamThreadEntry(SystemCore* core, void* userData);
    static void AudioThreadEntry(SystemCore* core, void* userData);
    void StreamThreadImpl();
    void AudioFrameProcess();

    static DebugInfo debugInfo_;

    // one audio frame's processing time and the frame's length (the names are not the original's)
    struct CpuLoad {
        double processTime;
        double frameTime;
    };

    // SoundCore::NewInstance allocates 0xA28 bytes for the instance; SystemCorePlatform's fields end at 0x270.
    // The field names are not the original's.
    unsigned char pad_270[0x8];
    unsigned long audioFrameCount_;  // 0x278: AudioThreadEntry counts the frames it processes
    double audioTime_;  // 0x280: audioFrameCount_ / audioFrameRate_, before each frame
    unsigned char pad_288[0x8];
    double audioFrameRate_;  // 0x290
    unsigned char pad_298[0x8];
    double appliedFrameRate_;  // 0x2A0: AudioThreadEntry copies audioFrameRate_ to it before each frame
    double startTime_;  // 0x2A8: the system time the audio thread starts at
    unsigned char pad_2b0[0x38];
    void* pad_2e8[2];  // the constructor zeroes both
    unsigned char pad_2f8[0x8];
    OutputMode::Type outputMode_;
    unsigned char pad_304[0x4];
    BehaviorInstance<SystemCore> masterVolume_;  // 0x308
    BehaviorInstance<SystemCore> masterPitch_;  // 0x350
    unsigned char pad_398[0x4];
    int voiceSerial_;  // 0x39C: AllocVoiceHandle builds a voice's id from it (1..0xFFFFF)
    List<VoiceHandle> playVoices_;  // 0x3A0: GetNumPlaySound counts it
    List<VoiceHandle> freeVoices_;  // 0x3C8: FreeVoiceHandle links a voice back in
    VoiceHandle* voices_;  // 0x3F0: Init allocates them
    unsigned char pad_3f8[0x18];
    int pad_410;  // VoiceHandle::UpdateAudioInternal takes a released channel's pad_b4 off it
    unsigned char pad_414[0x4];
    List<SoundBank> banks_;  // 0x418: AddBank / RemoveBank
    List<SoundActor> actors_;  // 0x440: ConnectActor / DisconnectActor
    Array<SoundCategory> categories_;  // 0x468: GetCategory (the first one is the default)
    SoundGroup group_;  // 0x480: the constructor builds it with the defaults (id 0, 256 sounds)
    void* pad_4a0;  // the constructor zeroes it
    unsigned char pad_4a8[0x8];
    Array<SoundListener*> listeners_;  // 0x4B0
    Array<SoundEffecter*> effecters_;  // 0x4C8
    float speedOfSound_;  // 0x4E0
    unsigned char pad_4e4[0x4];
    Thread audioThread_;  // 0x4E8: runs AudioThreadEntry
    mutable Mutex audioLock_;  // 0x708: LockAudio / UnlockAudio
    Thread streamThread_;  // 0x730: runs StreamThreadEntry
    List<StreamController> streams_;  // 0x950: AddStreamController / RemoveStreamController
    List<BehaviorControl> behaviors_;  // 0x978: the running BehaviorInstances (master volume and pitch)
    XorShift128Random random_;  // 0x9A0
    Mutex delegateLock_;  // 0x9B8
    Array<Delegate::Handle*> delegates_;  // 0x9E0
    CpuLoad cpuLoad_[2];  // 0x9F8: GetAudioCpuLoad reads the one cpuLoadIndex_ does not select
    double frameStartTime_;  // 0xA18: AudioThreadEntry sets it with startTime_
    int cpuLoadIndex_;
    unsigned char pad_a24[0x4];
};
}  // namespace ssd

#endif
