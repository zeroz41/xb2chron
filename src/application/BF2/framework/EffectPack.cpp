#include "classes/fw/EffectPack.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectData.h"
#include "classes/fw/EffectManager.h"
#include "ml/PathUtil.h"
#include "mtl/MemManager.h"

namespace fw {

EffectPack* EffectPack::createFromMemory(void* data, unsigned int size, const char* name, bool flag) {
    mm::mtl::FixStr<256> packName;
    packName.format("%s+%p", name, data);
    EffectPack* pack = EffectManager::get()->findPack(packName.m_str);
    if (pack != nullptr) {
        pack->addRef();
        return pack;
    }
    if (data != nullptr && static_cast<EffectResHeader*>(data)->m_version == 0) {
        EffectManager* manager = EffectManager::get();
        if (manager != nullptr) {
            pack = new (manager->m_sysHandle, nullptr, 0, 4, false)
                EffectPack(manager->m_sysHandle, data, size, packName.m_str, flag);
            if (pack != nullptr) {
                return pack;
            }
        }
    }
    return nullptr;
}

EffectPack::EffectPack(mtl::ALLOC_HANDLE handle, void* data, unsigned int size, const char* name, bool flag)
    : m_data(data), m_datas(DataMap::allocator_type(handle)), m_size(size), m_flag(flag), m_name(name) {
    if (m_data != nullptr && static_cast<ResEntry*>(data)->m_magic == 'a') {
        unsigned int count = 0;
        ResEntry* entry = static_cast<ResEntry*>(data);
        while ((entry = entry->next()) != nullptr) {
            count++;
        }
        if (count != 0) {
            m_datas.reserve(count);
            ResEntry* head = static_cast<ResEntry*>(m_data);
            if (head->m_magic == 'a') {
                for (ResEntry* entry = head->next(); entry != nullptr; entry = entry->next()) {
                    EffectData* effectData = EffectData::createFromMemory(entry, 1, entry->m_name, true);
                    if (effectData != nullptr) {
                        m_datas[std::string(entry->m_name)] = effectData;
                    }
                }
            }
            effect::SystemManager::getPtr()->es_pack_regist(data, size);
        }
    }
    EffectManager::get()->addPack(this);
    addRef();
}

EffectPack::~EffectPack() {
    for (DataMap::iterator it = m_datas.begin(); it != m_datas.end(); ++it) {
        it->second->release();
    }
    m_datas.clear();
    if (m_data != nullptr) {
        effect::SystemManager::getPtr()->es_pack_free(reinterpret_cast<unsigned long>(m_data));
        m_data = nullptr;
    }
    EffectManager::get()->removePack(this);
}

void* EffectPack::searchEfb(const char* name) const {
    if (m_data != nullptr) {
        mm::mtl::FixStr<128> path;
        ml::PathUtil::getFsaPath(path, name);
        DataMap::const_iterator it = m_datas.find(std::string(path.m_str));
        if (it != m_datas.end()) {
            EffectData* data = it->second;
            if (data == nullptr) {
                return nullptr;
            }
            return data->getHandle();
        }
    }
    return nullptr;
}

}  // namespace fw
