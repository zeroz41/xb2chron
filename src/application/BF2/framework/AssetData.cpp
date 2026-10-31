#include "classes/fw/AssetData.h"
#include "classes/fw/AssetManager.h"
#include "classes/fw/AssetLoader.h"
#include "classes/ml/DevFileTh.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mtl/MemManager.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ASMControl.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/AnimPoseSamper.h"
#include "classes/fw/AnimAsmPoseSampler.h"
#include "classes/fw/AnimEventAsmPoseSampler.h"
#include "fw/IkResolver.h"
#include "anm/Util.h"
#include "classes/fw/AnimationManager.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ASMControl.h"
#include "classes/anm/Skeleton.h"
#include "classes/anm/Control.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Blender.h"
#include "anm/AsmBlender.h"
#include "anm/ExtraBinding.h"
#include "anm/Util.h"
#include "classes/fw/AnimSinglePoseSamper.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/AnimAfterModifierInterface.h"
#include "classes/fw/AnimPoseSamper.h"
#include "classes/fw/AnimAsmPoseSampler.h"
#include "classes/fw/AnimEventMotPoseSamper.h"
#include "classes/fw/AnimEventAsmPoseSampler.h"
#include <algorithm>
#include <string.h>

namespace fw {

const char* AnimAfterModifyJob::_TYPE_NAME = "AnimAfterModifyJob";
const char* AnimIkResolveJob::_TYPE_NAME = "AnimIkResolveJob";
const char* AnimModifyPoseJob::_TYPE_NAME = "AnimModifyPoseJob";
const char* AnimSamplePoseJob::_TYPE_NAME = "AnimSamplePoseJob";

AnimAfterModifyJob::AnimAfterModifyJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(AnimAfterModifyJob), 2), m_count(count) {}

void AnimAfterModifyJob::exec(anm::Job& job) {
    AnimAfterModifyJob& self = static_cast<AnimAfterModifyJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_modifiers[i]->apply();
    }
}

AnimIkResolveJob::AnimIkResolveJob(unsigned int count)
    : anm::Job(_TYPE_NAME, sizeof(AnimIkResolveJob), 3), m_count(count), m_info(nullptr) {}

void AnimIkResolveJob::exec(anm::Job& job) {
    AnimIkResolveJob& self = static_cast<AnimIkResolveJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_resolvers[i]->resolve(*self.m_info);
    }
}

AnimModifyPoseJob::AnimModifyPoseJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(AnimModifyPoseJob), 1), m_count(count) {}

void AnimModifyPoseJob::exec(anm::Job& job) {
    AnimModifyPoseJob& self = static_cast<AnimModifyPoseJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_modifiers[i]->apply();
    }
}

AnimSamplePoseJob::AnimSamplePoseJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(AnimSamplePoseJob), 0), m_count(count) {}

void AnimSamplePoseJob::exec(anm::Job& job) {
    AnimSamplePoseJob& self = static_cast<AnimSamplePoseJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_samplers[i]->samplePose();
    }
}

// Placeholder name: no symbol (a file-local function). A free function: it takes only the path and reads no object.
// What it does: whether path contains ".arc", ".mot", ".pcefb", ".wiefb", ".stp", ".ssp" or "effect", tested in that
// order; CreateFromCache keeps no asset of such a path as the one to clone.
static bool fn_710015DEE0(const char* path) {
    return strstr(path, ".arc") != nullptr || strstr(path, ".mot") != nullptr || strstr(path, ".pcefb") != nullptr ||
           strstr(path, ".wiefb") != nullptr || strstr(path, ".stp") != nullptr || strstr(path, ".ssp") != nullptr ||
           strstr(path, "effect") != nullptr;
}

AssetData* AssetData::CreateFromCache(mtl::ALLOC_HANDLE handle, const char* path) {
    AssetData* asset = AssetManager::sys()->searchAsset(path, nullptr);
    AssetData* source = nullptr;
    while (asset != nullptr) {
        if (asset->m_allocHandle.m_handle == handle.m_handle) {
            asset->addRef();
            return asset;
        }
        if (!fn_710015DEE0(path)) {
            source = asset;
        }
        asset = AssetManager::sys()->searchAsset(path, asset);
    }
    if (source == nullptr) {
        return nullptr;
    }
    return source->Clone(handle);
}

AssetData* AssetData::CreateFromCache(mm::mtl::IAllocator* allocator, const char* path) {
    AssetData* source = nullptr;
    for (AssetData* asset = AssetManager::sys()->searchAsset(path, nullptr); asset != nullptr;
         asset = AssetManager::sys()->searchAsset(path, asset)) {
        if (asset->m_allocator == allocator) {
            asset->addRef();
            return asset;
        }
        if (!fn_710015DEE0(path)) {
            source = asset;
        }
    }
    if (source == nullptr) {
        return nullptr;
    }
    return source->Clone(allocator);
}

AssetData* AssetData::Clone(mm::mtl::IAllocator* allocator) const {
    AssetData* asset = new (AssetManager::getMemSYS(), nullptr, 0, 4, false) AssetData();
    if (asset != nullptr) {
        if (m_data != nullptr && m_size != 0) {
            asset->m_data = allocator->allocate(m_size, 0x1000);
            memcpy(asset->m_data, m_data, m_size);
            asset->m_size = m_size;
            asset->m_timeStamp = m_timeStamp;
        }
        asset->m_allocator = allocator;
        asset->m_name = m_name;
        asset->m_hash = m_hash;
        asset->addRef();
    }
    return asset;
}

AssetData::~AssetData() {
    if (m_data != nullptr) {
        if (m_allocator != nullptr) {
            m_allocator->deallocate(m_data);
        } else {
            mtl::MemManager::deallocate(m_data, 0, false);
        }
        m_data = nullptr;
    }
    AssetManager::sys()->removeAsset(this);
}

AssetLoader* AssetLoader::Create(mtl::ALLOC_HANDLE handle, const char* path, int prio, int arg) {
    AssetLoader* loader = AssetManager::sys()->searchLoader(handle, path);
    if (loader == nullptr) {
        loader = new (AssetManager::getMemSYS(), nullptr, 0, 4, false) AssetLoader();
        if (loader != nullptr) {
            loader->load(handle, path, arg, static_cast<ml::FILE_PRIO>(prio));
            loader->m_allocHandle = handle;
            loader->SetName(path);
            loader->m_hash = AssetManager::getHash(path);
        }
    } else {
        loader->AddRef();
    }
    return loader;
}

AssetLoader* AssetLoader::Create(mm::mtl::IAllocator* allocator, const char* path, int prio, int arg) {
    AssetLoader* loader = AssetManager::sys()->searchLoader(allocator, path);
    if (loader == nullptr) {
        loader = new (AssetManager::getMemSYS(), nullptr, 0, 4, false) AssetLoader();
        if (loader != nullptr) {
            loader->load(allocator, path, arg, static_cast<ml::FILE_PRIO>(prio));
            loader->m_allocator = allocator;
            loader->SetName(path);
            loader->m_hash = AssetManager::getHash(path);
        }
    } else {
        loader->AddRef();
    }
    return loader;
}

AssetLoader::~AssetLoader() { AssetManager::sys()->removeLoader(this); }

}  // namespace fw
