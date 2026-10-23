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

Thread::Param::Param()
    : userData(nullptr), priority(0), idealCore(-1), coreMask(nn::os::GetThreadAvailableCoreMask()), pad_18(0),
      stackSize(0), interval(0.0f) {}

Thread::~Thread() {}

void Thread::ThreadEntryProc(void* thread) {
    Thread* self = static_cast<Thread*>(thread);
    self->running_ = true;
    self->function_(self->argument_, self->userData_);
    self->running_ = false;
}

Result Thread::CloseThread() {
    closing_ = true;
    nn::os::WaitThread(&thread_);
    created_ = false;
    running_ = false;
    nn::os::DestroyThread(&thread_);
    nn::os::FinalizeEvent(&event_);
    if (stack_.address != nullptr) {
        stack_.Free();
    }
    return Result(0);
}

void Utf8ToUTF16(const char* text, char16_t* buffer, unsigned long size) {
    nn::util::ConvertStringUtf8ToUtf16Native(reinterpret_cast<unsigned short*>(buffer), size, text);
}

void Utf16ToUTF8(const char16_t* text, char* buffer, unsigned long size) {
    nn::util::ConvertStringUtf16NativeToUtf8(buffer, size, reinterpret_cast<const unsigned short*>(text));
}

bool Utf8ToUTF16(const char* text, MemoryBlock* block) {
    int length;
    nn::util::GetLengthOfConvertedStringUtf8ToUtf16Native(&length, text, GetTextLength(text));
    unsigned long count = length + 2;
    unsigned long size = count * sizeof(char16_t);
    if (block->address != nullptr) {
        SoundMemory::allocator_->DeleteBuffer(block->address);
    }
    block->address = SoundMemory::allocator_->NewBuffer<char16_t>(count);
    block->size = size;
    ClearMemory16(block->address, size);
    nn::util::ConvertStringUtf8ToUtf16Native(static_cast<unsigned short*>(block->address), length + 1, text);
    return true;
}

bool Utf16ToUTF8(const char16_t* text, MemoryBlock* block) {
    int length;
    nn::util::GetLengthOfConvertedStringUtf16NativeToUtf8(&length, reinterpret_cast<const unsigned short*>(text),
                                                          GetTextLength(text));
    unsigned long count = length + 2;
    unsigned long size = (count + 1) & ~1UL;
    if (block->address != nullptr) {
        SoundMemory::allocator_->DeleteBuffer(block->address);
    }
    block->address = SoundMemory::allocator_->NewBuffer<char>(count);
    block->size = size;
    ClearMemory16(block->address, size);
    nn::util::ConvertStringUtf16NativeToUtf8(static_cast<char*>(block->address), length + 1,
                                             reinterpret_cast<const unsigned short*>(text));
    return true;
}

}  // namespace ssd
