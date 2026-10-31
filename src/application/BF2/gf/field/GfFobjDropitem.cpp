#include "gf/GfFobjSeManager.h"
#include "gf/GfFobjGottenEffectManager.h"
#include "gf/GfDropitemEmitter.h"
#include "classes/gf/GfDropitemParams.h"
#include "classes/gf/GfFobjDropitem.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfFobjSeManager::GfFobjSeManager(const CreateInfo* info) : m_pack(nullptr) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfFobjSeManager::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    const char* name = GfFieldSound::fn_710027C7D4();
    m_pack = fw::SoundManager::sys()->findPack(name, nullptr);
    if (m_pack == nullptr) {
        dispose();
        return;
    }
    m_seInfos.setAllocator(getAllocator(ALLOCATOR(0)));
    m_seInfos.reserve(info.m_maxSe);
    m_seTimes.setAllocator(getAllocator(ALLOCATOR(0)));
}

void GfFobjSeManager::dispose() {
    if (m_seInfos.size() != 0) {
        if (fw::SoundManager::sys() != nullptr) {
            for (SeInfo& se : m_seInfos) {
                fw::SoundManager::sys()->stopSe(se.m_soundId, 0.5f);
            }
        }
        m_seInfos.destroy();
    }
    m_info = CreateInfo();
}

void GfFobjSeManager::fn_7100282EA8() {
    const char* name = GfFieldSound::fn_710027C7D4();
    m_pack = fw::SoundManager::sys()->findPack(name, nullptr);
}

void GfFobjSeManager::update(float deltaTime) {
    if (m_info.m_maxSe == 0) {
        return;
    }
    for (mm::mtl::Vector<SeInfo>::iterator it = m_seInfos.begin(); it != m_seInfos.end(); ++it) {
        if (!fw::SoundManager::sys()->isPlaying(it->m_soundId)) {
            it = m_seInfos.erase(it);
            --it;
        }
    }
    typedef mm::mtl::Map<unsigned short, float>::tree_type Tree;
    Tree& tree = m_seTimes.m_tree;
    Tree::node* n = nullptr;
    if (tree.m_root != &Tree::m_sentinel) {
        n = tree.m_root;
        while (n->left != &Tree::m_sentinel) {
            n = n->left;
        }
    }
    for (; n != nullptr; n = tree.next(n)) {
        n->value.second += deltaTime;
    }
}

GfFobjGottenEffectManager::GfFobjGottenEffectManager(const CreateInfo* info) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfFobjGottenEffectManager::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_effectRes[0] = fw::EffectManager::sys()->search("cmn_200_030", nullptr);
    m_effectRes[1] = fw::EffectManager::sys()->search("cmn_200_031", nullptr);
    m_effectRes[2] = fw::EffectManager::sys()->search("cmn_200_032", nullptr);
    m_effects.setAllocator(getAllocator(ALLOCATOR(0)));
    m_effects.reserve(info.m_capacity);
}

void GfFobjGottenEffectManager::dispose() {
    if (m_effects.size() != 0) {
        for (EffectInfo& effect : m_effects) {
            fw::EffectManager::sys()->kill(effect.m_handle);
        }
        m_effects.destroy();
    }
    m_info = CreateInfo();
}

GfDropitemParams::~GfDropitemParams() {
    m_params.destroy();
}

void GfDropitemEmitter::update(float dt) {
    if (m_info.m_items != nullptr && m_info.m_itemCount > 0) {
        m_timer += dt;
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

void GfDropitemEmitter::seqWaitEndDrop(float dt) {
    if (m_timer < m_endTime) {
        return;
    }
    m_isEmitted = true;
    m_seq = nullptr;
}

GfFobjDropitem::~GfFobjDropitem() {}

}  // namespace gf
