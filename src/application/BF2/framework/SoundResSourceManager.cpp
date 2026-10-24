#include "mm/mtl/Map.h"
#include "anm/StringPtr.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundResSourceManager.h"

#include <string.h>

#include "bin/BinaryResolver.h"
#include "fw/Allocator.h"

namespace fw {

const ResSoundSource* SoundResSourceImporter::importBinary(void* binary) {
    const ResSoundRoot* root = static_cast<const ResSoundRoot*>(bin::BinaryResolver::resolve(binary));
    if (root == nullptr) {
        return nullptr;
    }
    if (memcmp(root->m_magic, "SDSB", 4) != 0) {
        return nullptr;
    }
    if (root->m_version != 2) {
        return nullptr;
    }
    return static_cast<const ResSoundSource*>(root->m_resource);
}

SoundResSourceManager::SoundResSourceManager() : pad_48(false) {}

SoundResSourceManager::~SoundResSourceManager() {
    clearAll();
}

void SoundResSourceManager::clearAll() {
    SoundResSourceManager* self = get();
    if (self == nullptr) {
        return;
    }
    self->m_sources.clear();
    self->m_sources.setAllocator(nullptr);
    self->m_resources.clear();
    self->m_resources.setAllocator(nullptr);
}

void SoundResSourceManager::beginPush(unsigned int count, mm::mtl::IAllocator* allocator) {
    SoundResSourceManager* self = get();
    if (self == nullptr) {
        return;
    }
    self->m_sources.setAllocator(allocator);
    self->m_resources.setAllocator(allocator);
    self->m_resources.reserve(count);
}

void SoundResSourceManager::endPush() {
    SoundResSourceManager* self = get();
    if (self == nullptr) {
        return;
    }
    for (const ResSoundSource* resource : self->m_resources) {
        for (const ResSimpleSoundSource& source : resource->m_simples) {
            mm::mtl::MapPair<anm::StringPtr, const ResSoundSourceBase*> pair(source.m_name, &source);
            self->m_sources.insert(pair);
        }
        for (const ResComplexSoundSource& source : resource->m_complexes) {
            mm::mtl::MapPair<anm::StringPtr, const ResSoundSourceBase*> pair(source.m_name, &source);
            self->m_sources.insert(pair);
        }
    }
}

void SoundResSourceManager::pushResource(const ResSoundSource* resource) {
    if (resource == nullptr) {
        return;
    }
    SoundResSourceManager* self = get();
    if (self == nullptr) {
        return;
    }
    self->m_resources.push_back(resource);
}

unsigned int findComplexIndex(const SoundVariableTable& table, const ResComplexSoundSource* source) {
    int values[8];
    unsigned int count = 0;
    for (const char* name : source->m_variables) {
        if (!table.getVariable(name, &values[count])) {
            return -1;
        }
        ++count;
    }
    for (unsigned int i = 0; i < source->m_entries.size(); ++i) {
        bool match = true;
        for (unsigned int j = 0; j < source->m_entries[i].m_values.size(); ++j) {
            if (source->m_entries[i].m_values[j] >= 0 && source->m_entries[i].m_values[j] != values[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;
}

unsigned int SoundResSourceManager::playSe(const char* name, float volume, const SoundVariableTable& variables,
                                           SoundCategory category,
                                           const mm::mtl::Delegate<void(const ResSoundData&, CustomInfo*)>& callback) {
    SoundResSourceManager* self = get();
    SoundManager* sound = mm::mtl::PtrSingleton<SoundManager>::get();
    if (self == nullptr || sound == nullptr) {
        return 0;
    }
    mm::mtl::Map<anm::StringPtr, const ResSoundSourceBase*>::node* node = self->m_sources.find(anm::StringPtr(name));
    if (node == nullptr) {
        return 0;
    }
    const ResSoundSourceBase* source = node->value.second;
    if (source->m_type == 0) {
        const ResSimpleSoundSource* simple = static_cast<const ResSimpleSoundSource*>(source);
        SoundPack* pack = sound->findPack(simple->m_data.m_packName, nullptr);
        if (pack == nullptr) {
            return 0;
        }
        if (callback.isValid()) {
            CustomInfo info;
            callback(simple->m_data, &info);
            volume = info.m_volume * volume;
        }
        return sound->playSe(simple->m_data.m_id, pack, volume, category);
    } else if (source->m_type == 1) {
        const ResComplexSoundSource* complex = static_cast<const ResComplexSoundSource*>(source);
        unsigned int index = findComplexIndex(variables, complex);
        if (index == static_cast<unsigned int>(-1)) {
            return 0;
        }
        const ResSoundData& data = complex->m_entries[index].m_data;
        SoundPack* pack = sound->findPack(data.m_packName, nullptr);
        if (pack == nullptr) {
            return 0;
        }
        if (callback.isValid()) {
            CustomInfo info;
            callback(data, &info);
            volume = info.m_volume * volume;
        }
        return sound->playSe(data.m_id, pack, volume, category);
    }
    return 0;
}

void SoundResSourceManager::stopSe(unsigned int handle, float fade) {
    if (SoundManager* sound = mm::mtl::PtrSingleton<SoundManager>::get()) {
        sound->stopSe(handle, fade);
    }
}

}  // namespace fw
