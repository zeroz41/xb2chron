#ifndef CLASSES_SSD_SOUNDHANDLE_H
#define CLASSES_SSD_SOUNDHANDLE_H

#include "classes/ssd/Array.h"
#include "classes/ssd/Delegate/MultiCast.h"
#include "classes/ssd/List.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/SoundCategory.h"
#include "ssd/Debug.h"

namespace ssd { class SoundActor; }
namespace ssd { class SoundEntry; }
namespace ssd { class VoiceHandle; }
namespace ssd {
// table 0x7100B81C50: a sound as the game holds it (SoundActor::Play's handle): the entry it plays, the voice it
// plays on (voiceId_, SystemCore::GetVoiceHandle) and the values the voice reads. sizeof 0x140. The field names
// are not the original's.
class SoundHandle : public Object, public List<SoundHandle>::Node {
public:
    class Notify;
    SoundHandle();
    virtual ~SoundHandle();  // slot 0
    // stops the voice and gives every delegate back
    void Delete();
    // drops the voice and the entry and gives the delegates back; the handle is invalid until Init
    void Quit();
    // resets the values and makes the handle valid (Play and Prepare call it on an invalid handle)
    void Init();
    // gives every delegate back, under the audio lock
    void ClearDelegate();
    Result AddDelegateInternal(Delegate::Handle* handle);
    Result RemoveDelegateInternal(Delegate::Handle* handle);
    // takes a voice for entry (fails with -33 while the handle holds an entry)
    Result Prepare(const SoundEntry* entry);
    bool IsValidHandle() const;
    bool IsPlay() const;
    int GetState() const;  // 8 once ready to start; 5, 6 and 7 while preparing
    Result Play(const SoundEntry* entry, SoundActor* actor, float volume, float fadeTime);  // SoundActor::Play's
    Result Start(SoundActor* actor, float volume, float fadeTime);  // negative on failure
    Result Stop(float fadeTime);
    void SetCategoryId(int id);
    Result GetPlayTime(float* time) const;
    Result SetPlayTime(float time);
    Result GetDataTime(float* time) const;
    Result SetRemainLoopCount(int count);
    Result GetRemainLoopCount(int* count) const;
    // set a value now (fadeTime 0) or over fadeTime: 1.0.0's SetPitch, SetVolume and SetPan (0x7100990D48,
    // 0x7100990D74, 0x7100990DA0, in that order) write the same fields as these
    void SetPitch(float pitch, float fadeTime);
    void SetVolume(float volume, float fadeTime);
    void SetPan(float pan, float fadeTime);
    float GetDistanceVolume() const;
    Result Pause(bool pause, float fadeTime);
    void UpdateAudioFrame(float frameTime);

    // a value Set* moves to its target over a fade time (the type's and the field names are not the original's)
    struct FadeValue {
        // starts a move to target over fadeTime (at once when it is 0)
        void Set(float value, float time) {
            fadeTime = time;
            if (time == 0.0f) {
                target = value;
                start = value;
                current = value;
            } else {
                start = current;
                target = value;
            }
            delta = target - start;
            elapsed = 0.0f;
        }
        // moves on by frameTime
        void Update(float frameTime) {
            if (elapsed < fadeTime) {
                elapsed += frameTime;
                if (elapsed >= fadeTime) {
                    elapsed = fadeTime;
                }
                current = start + elapsed * delta / fadeTime;
            }
        }

        float current;
        float elapsed;  // Set* resets it
        float fadeTime;
        float delta;  // target - start
        float start;
        float target;
    };
    const SoundEntry* entry_;  // 0x30: Prepare's entry
    SoundActor* actor_;  // 0x38: Start's actor (SystemCore::defaultActor_ when none)
    int groupId_;  // 0x40: the entry's group's id (SystemCore::defaultGroup_'s when none)
    SoundCategory category_;  // 0x48: a copy of the entry's category (SetCategoryId)
    bool valid_;  // 0x58: IsValidHandle asks the voice only while it is set
    bool pad_59;
    bool pad_5a;
    double startTime_;  // 0x60: SystemCorePlatform::GetSystemTime when Start ran
    float pad_68;  // Start asks the voice to start with its flag set when this is not 0
    FadeValue pitch_;  // 0x6C
    FadeValue volume_;  // 0x84 (fw::SoundSsdDriver::getVolume type 0 reads its current value)
    FadeValue pan_;  // 0x9C
    float pad_b4;
    float volume2_;  // 0xB8: fw::SoundSsdDriver::getVolume type 2 reads it
    float pad_bc;
    bool pad_c0;
    FadeValue pad_c4;
    bool pad_dc;
    FadeValue pad_e0;
    unsigned int voiceId_;  // 0xF8: SystemCore::GetVoiceHandle's id
    Delegate::MultiCast notify_;  // 0x100: VoiceHandle::FreeVoice notifies it
    Array<Delegate::Handle*> delegates_;  // 0x128: AddDelegateInternal's handles, given back by ClearDelegate
};
}  // namespace ssd

#endif
