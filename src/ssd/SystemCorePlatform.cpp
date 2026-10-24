#include "nn/os.h"
#include "nn/diag.h"
#include "nn/mem.h"
#include "nn/audio.h"
#include "nn/util.h"
#include "ssd/Debug.h"
#include "ssd/MemoryBlock.h"
#include "ssd/Hash.h"
#include "ssd/Text.h"
#include "ssd/Thread.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"

#include <string.h>

namespace ssd {

void SystemCorePlatform::InitPlatform(const SoundCore::InitParam& param) {
    tickFrequency_ = nn::os::GetSystemTickFrequency();
}

int SystemCorePlatform::fn_710089E218() {
    return 0x400;
}

void SystemCorePlatform::QuitAudioDevice() {
    nn::audio::StopAudioRenderer(handle_);
    nn::audio::CloseAudioRenderer(handle_);
    nn::os::DestroySystemEvent(systemEvent_.GetBase());
    audioDataAllocator_.Finalize();
    audioDataBlock_.Free();
    effectAllocator_.Finalize();
    effectBlock_.Free();
    workAllocator_.Finalize();
    workBlock_.Free();
    set_result(Result(0));
}

void SystemCorePlatform::UpdateDevice() {
    NN_ABORT_UNLESS_RESULT_SUCCESS(nn::audio::RequestUpdateAudioRenderer(handle_, &config_));
}

double SystemCorePlatform::GetSystemTime() {
    return nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetNanoSeconds() / 1000000000.0;
}

void* SystemCorePlatform::GetPlatformDataImpl(const char* name) {
    if (strcmp(name, "AudioRendererConfig") == 0) {
        return &config_;
    }
    return nullptr;
}

void* SystemCorePlatform::AllocAudioDataBuffer(unsigned long size) {
    return audioDataAllocator_.Allocate(size, 0x40);
}

void SystemCorePlatform::FreeAudioDataBuffer(void* buffer) {
    audioDataAllocator_.Free(buffer);
}

SystemCorePlatform::~SystemCorePlatform() {}

}  // namespace ssd
