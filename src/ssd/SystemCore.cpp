#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/BehaviorInstance.h"
#include "classes/ssd/XorShift128Random.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SystemCore.h"

namespace ssd {

void SystemCore::SetMasterVolume(float volume, float fadeTime) {
    masterVolume_.Start(this, &SystemCore::MasterVolumeBehavior, volume, fadeTime);
}

void SystemCore::MasterVolumeBehavior(float frameTime) {}

void SystemCore::SetMasterPitch(float pitch, float fadeTime) {
    masterPitch_.Start(this, &SystemCore::MasterPitchBehavior, pitch, fadeTime);
}

void SystemCore::MasterPitchBehavior(float frameTime) {}

OutputMode::Type SystemCore::GetOutputMode() const {
    return outputMode_;
}

void SystemCore::SetOutputMode(OutputMode::Type mode) {
    outputMode_ = mode;
}

float SystemCore::GetMasterVolume() const {
    return masterVolume_.value_;
}

float SystemCore::GetMasterPitch() const {
    return masterPitch_.value_;
}

int SystemCore::GetNumPlaySound() const {
    return playVoices_.count_;
}

float SystemCore::GetSpeedOfSound() const {
    return speedOfSound_;
}

void SystemCore::SetSpeedOfSound(float speed) {
    speedOfSound_ = speed;
}

double SystemCore::GetAudioCpuLoad() const {
    const CpuLoad& load = cpuLoad_[1 - cpuLoadIndex_];
    if (load.frameTime != 0.0) {
        return load.processTime / load.frameTime;
    }
    return 0.0;
}

void SystemCore::LockAudio() const {
    audioLock_.Lock();
}

void SystemCore::UnlockAudio() const {
    audioLock_.Unlock();
}

const SoundCore::DebugInfo* SystemCore::GetDebugInfo() const {
    return &debugInfo_;
}

SoundCore::DebugInfo SystemCore::debugInfo_;

}  // namespace ssd
