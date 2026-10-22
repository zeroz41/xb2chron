#include "classes/fw/EffectLodManager.h"
#include "classes/fw/EffectManager.h"

namespace fw {

EffectLodManager::EffectLodManager() {
    m_pack = nullptr;
    m_model = nullptr;
}

EffectLodManager::~EffectLodManager() {
    term();
}

void EffectLodManager::term() {
    mm::mtl::IntrusiveList<Entry>::iterator it = m_entries.begin();
    while (it != m_entries.end()) {
        Entry* entry = &*it;
        mm::mtl::PtrSingleton<EffectManager>::get()->remove(entry->m_handle);
        it = m_entries.erase(it);
        delete entry;
    }
    it = m_entries.begin();
    while (it != m_entries.end()) {
        it = m_entries.erase(it);
    }
    m_pack = nullptr;
    m_model = nullptr;
}

}  // namespace fw
