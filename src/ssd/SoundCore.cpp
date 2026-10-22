#include "nn/os.h"
#include "ssd/Debug.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/MemoryManager.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/Object.h"

namespace ssd {

const char* SoundCore::audioRendererConfigName_ = "AudioRendererConfig";
SoundCore* SoundCore::instance_;

SoundCore::InitParam::InitParam()
    : voiceNum(0x80), messageMethod(nullptr), timeStampType(LogTimeStamp::Type(1)), memoryPoolSize(0x2000000) {}

SoundCore* SoundCore::NewInstance(Allocator* allocator) {
    if (instance_ == nullptr) {
        MemoryManager::Init(0x800, allocator);
        instance_ = allocator->NewInstance<SystemCore>();
    }
    return instance_;
}

void SoundCore::DeleteInstance() {
    if (instance_ != nullptr) {
        SoundMemory::allocator_->DeleteInstance(static_cast<SystemCore*>(instance_));
        MemoryManager::Quit();
    }
    instance_ = nullptr;
}

SoundCore::SoundCore() : result_(Result(0x80000000)), initialized_(false) {
    Debug::Init();
}

SoundCore::~SoundCore() {}

Result SoundCore::Init(const InitParam& param) {
    Debug::SetMessageMethod(param.messageMethod);
    Debug::SetTimeStampType(param.timeStampType);
    Result result = static_cast<SystemCore*>(this)->Init(param);
    if (result >= 0) {
        int major;
        int minor;
        int revision;
        int build;
        char16_t buildType[16];
        GetVersion(&major, &minor, &revision, &build, buildType);
        log_message(u"Version %d.%d.%d.%d.%s %dbit Initialized", major, minor, revision, build, buildType,
                    (int)sizeof(void*) * 8);
    } else {
        log_message(u"SoundCore::Init() : Failure");
    }
    initialized_ = true;
    return result;
}

Result SoundCore::Quit(bool) {
    if (!initialized_) {
        return Result(-1);
    }
    initialized_ = false;
    return static_cast<SystemCore*>(this)->Quit();
}

Result SoundCore::SetCategory(const SoundCategory& category) {
    return static_cast<SystemCore*>(this)->SetCategory(category);
}

Result SoundCore::ResetCategory(int categoryId) {
    return static_cast<SystemCore*>(this)->ResetCategory(categoryId);
}

void SoundCore::UpdateGameFrame(float frameTime) {
    if (initialized_) {
        static_cast<SystemCore*>(this)->UpdateGameFrame(frameTime);
    }
}

void SoundCore::StopSound(float fadeTime) {
    static_cast<SystemCore*>(this)->StopSound(fadeTime);
}

LogTimeStamp::Type SoundCore::GetLogTimeStampType() const {
    return Debug::log_.timeStampType;
}

Object::Object(ObjectType::Id type) : type_(type), pad_c(0), core_(SoundCore::instance_) {}

}  // namespace ssd
