#include "mm/mtl/FixStr.h"
#include "ml/PathUtil.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectData.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectData.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/Framework.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

inline EffectData::EffectData(void* data, const char* name, bool unregistered) : m_handle(data), m_name(name) {
    m_unregistered = unregistered;
    if (!m_unregistered) {
        EffectManager::get()->addData(this);
    }
}

EffectData* EffectData::createFromMemory(void* data, unsigned int size, const char* path, bool unregistered) {
    mm::mtl::FixStr<128> name;
    ml::PathUtil::getFsaPath(name, path);
    if (static_cast<EffectResHeader*>(data)->m_version != 0) {
        return nullptr;
    }
    if (!unregistered && effect::SystemManager::getPtr()->es_regist(data, size) == nullptr) {
        return nullptr;
    }
#line 43
    EffectData* effectData = new (Framework::getAllocator(), 16, __FILE__, __LINE__) EffectData(data, name.m_str, unregistered);
    effectData->addRef();
    return effectData;
}

void* EffectData::getHandle() const { return m_handle; }

const char* EffectData::getName() const { return m_name.m_str; }

EffectData::~EffectData() {
    if (!m_unregistered) {
        EffectManager::get()->removeData(this);
        if (effect::SystemManager::getPtr() != nullptr && m_handle != nullptr) {
            effect::SystemManager::getPtr()->es_free(m_handle);
            m_handle = nullptr;
        }
    }
}

}  // namespace fw
