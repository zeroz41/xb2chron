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

Thread::Param::Param()
    : userData(nullptr), priority(0), idealCore(-1), coreMask(nn::os::GetThreadAvailableCoreMask()), pad_18(0),
      stackSize(0), interval(0.0f) {}

Thread::Thread() : created_(false), running_(false), closing_(false), sleeping_(false) {
    stack_.address = nullptr;
    stack_.size = 0;
    ClearFunction();
}

Thread::~Thread() {}

Result Thread::CreateThreadImpl(void* argument, Function function, const Param& param) {
    userData_ = param.userData;
    argument_ = argument;
    function_ = function;
    nn::os::InitializeEvent(&event_, false, nn::os::EventClearMode_AutoClear);
    closing_ = false;
    sleeping_ = false;
    interval_ = param.interval;
    unsigned long stackSize = param.stackSize == 0 ? 0x8000 : param.stackSize;
    unsigned char* stackBuffer = SoundMemory::allocator_->NewBuffer<unsigned char>(stackSize, STACK_ALIGNMENT_SIZE);
#line 113 "D:/ssd/ssd51/ssd/sources/system/thread.nx.cpp"
    SSD_ASSERT(CheckAlign( stackBuffer, STACK_ALIGNMENT_SIZE ));
    stack_.address = stackBuffer;
    stack_.size = stackSize;
    nn::Result result = nn::os::CreateThread(&thread_, ThreadEntryProc, this, stackBuffer, stackSize, 16);
    NN_ASSERT(result.IsSuccess());
    created_ = true;
    running_ = true;
    nn::os::SetThreadCoreMask(&thread_, param.idealCore, param.coreMask);
    nn::os::StartThread(&thread_);
    return Result(0);
}

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

Result Thread::Sleep(float time) {
    sleeping_ = true;
    if (time == 0.0f) {
        nn::os::WaitEvent(&event_);
    } else {
        nn::os::TimedWaitEvent(&event_, nn::TimeSpan::FromMicroSeconds(static_cast<unsigned long>(time * 1000000.0)));
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

void Hash::CalcTextHash(const char* text) {
    CalcDataHash(text, GetTextLength(text));
}

void Hash::CalcTextHash(const char16_t* text) {
    CalcDataHash(text, GetTextLength(text) * sizeof(char16_t));
}

}  // namespace ssd
