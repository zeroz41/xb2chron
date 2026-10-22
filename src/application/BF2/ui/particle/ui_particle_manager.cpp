#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIParticleManager.h"
#include "classes/ui/UIParticleEmitter.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/Pnt.h"
#include "ui/UIUtil.h"

namespace ui {

UIParticleManager::UIParticleManager() : m_nextHandle(1), m_loadReduction(0.0f) {}

UIParticleManager::~UIParticleManager() {
    if (m_emitters.m_size != 0) {
        for (mm::mtl::IntrusiveList<EmitterNode>::iterator it = m_emitters.begin(); it != m_emitters.end();) {
            EmitterNode* node = it.operator->();
            it = m_emitters.erase(it);
            // destroyed and freed without the null check a delete expression makes
            node->~EmitterNode();
            operator delete(node);
        }
    }
}

void UIParticleManager::update(const fw::UpdateInfo& info) {
    for (mm::mtl::IntrusiveList<EmitterNode>::iterator it = m_emitters.begin(); it != m_emitters.end(); ++it) {
        (*it).m_emitter->update(info);
    }
}

int UIParticleManager::create(const UIParticleData& data) {
    UIParticleEmitter* emitter = UIParticleEmitter::create(data);
    if (emitter == nullptr) {
        return -1;
    }
#line 78
    EmitterNode* node = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) EmitterNode();
    node->m_handle = m_nextHandle;
    node->m_emitter = emitter;
    node->m_weight = 1.0f;
    float rate = 1.0f - m_loadReduction;
    emitter->m_rate = rate + (1.0f - rate) * node->m_weight;
    m_emitters.push_back(node);
    int handle = node->m_handle;
    m_nextHandle++;
    return handle;
}

void UIParticleManager::remove(int handle) {
    for (mm::mtl::IntrusiveList<EmitterNode>::iterator it = m_emitters.begin(); it != m_emitters.end(); ++it) {
        EmitterNode& node = *it;
        if (node.m_handle == handle) {
            m_emitters.erase(it);
            delete &node;
            return;
        }
    }
}

UIParticleEmitter* UIParticleManager::getEmitter(int handle) {
    for (mm::mtl::IntrusiveList<EmitterNode>::iterator it = m_emitters.begin(); it != m_emitters.end(); ++it) {
        if ((*it).m_handle == handle) {
            return it->m_emitter;
        }
    }
    return nullptr;
}

void UIParticleManager::setEmitterPos(int handle, const mm::Pnt<short>& pos) {
    for (mm::mtl::IntrusiveList<EmitterNode>::iterator it = m_emitters.begin(); it != m_emitters.end(); ++it) {
        if ((*it).m_handle == handle) {
            UIParticleEmitter* emitter = it->m_emitter;
            emitter->m_x = pos.x;
            emitter->m_y = pos.y;
        }
    }
}

void UIParticleManager::setEmitterRot(int handle, float rot) {
    for (mm::mtl::IntrusiveList<EmitterNode>::iterator it = m_emitters.begin(); it != m_emitters.end(); ++it) {
        if ((*it).m_handle == handle) {
            it->m_emitter->m_rot = rot;
        }
    }
}

}  // namespace ui
