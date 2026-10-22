#include "mm/mtl/FixedVector.h"
#include "ml/PathUtil.h"
#include "classes/fw/SoundReferenceObject.h"
#include "classes/fw/SoundSsdSource.h"
#include "classes/fw/SoundSsdBank.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundPack.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Hash.h"
#include <string.h>

namespace fw {

SoundPack* SoundPack::createFromStream(mm::mtl::IAllocator* allocator, const SetupInfo& info) {
    SoundPack* pack = mm::mtl::PtrSingleton<SoundManager>::get()->findPack(info.name.m_str, allocator);
    if (pack != nullptr) {
        pack->addRef();
        return pack;
    }
#line 171
    pack = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__)
        SoundPack(info.category, allocator, info.name.m_str, info.priority);
    pack->addRef();
    mm::mtl::FixStr<256> bankName;
    bankName.format("%s_%p", info.name.m_str, allocator);
    pack->m_bank = SoundSsdBank::create(bankName.m_str, info.category, info.maxSound);
    pack->m_bank->setMaxSound(info.maxSound);
    pack->registSource(info.data, info.size);
    mm::mtl::PtrSingleton<SoundManager>::get()->registPack(pack);
    return pack;
}

SoundPack* SoundPack::create(const SetupInfo& info) {
    SoundPack* pack = mm::mtl::PtrSingleton<SoundManager>::get()->findPack(info.name.m_str, nullptr);
    if (pack != nullptr) {
        pack->addRef();
        return pack;
    }
#line 210
    pack = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__)
        SoundPack(info.category, nullptr, info.name.m_str, info.priority);
    pack->addRef();
    mm::mtl::FixStr<256> bankName;
    bankName.format("%s_%p", info.name.m_str, nullptr);
    pack->m_bank = SoundSsdBank::create(bankName.m_str, info.category, info.maxSound);
    pack->m_bank->setMaxSound(info.maxSound);
    pack->registSource(info.data, info.size);
    mm::mtl::PtrSingleton<SoundManager>::get()->registPack(pack);
    return pack;
}

SoundPack::SoundPack(SoundCategory category, mm::mtl::IAllocator* allocator, const char* name, SoundPriority priority)
    : m_category(category), m_allocator(allocator), m_priority(priority) {
    m_name = name;
    m_nameHash = mm::mtl::hashStrCrc(name);
    m_fileName = ml::PathUtil::getNoPathExtName(name);
}

SoundPack::~SoundPack() {
    if (m_bank != nullptr) {
        m_bank->stopAll();
    }
    m_sources.clear();
    m_sourceIds.clear();
    if (m_bank != nullptr) {
        m_bank->release();
        m_bank = nullptr;
    }
    mm::mtl::PtrSingleton<SoundManager>::get()->removePack(this);
}

}  // namespace fw
