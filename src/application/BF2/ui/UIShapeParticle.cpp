#include "classes/ui/UIParticleData.h"
#include "classes/ui/UIShape.h"
#include "classes/ui/UIShapeParticle.h"
#include "classes/ui/UIParticleManager.h"

namespace ui {

UIShapeParticle::UIShapeParticle(void* data, unsigned int size, unsigned int width, unsigned int height)
    : m_emitter(-1), m_width(width), m_height(height) {
    UIParticleData particleData;
    particleData.deserialize(data, size);
    m_emitter = UIParticleManager::sys()->create(particleData);
    if (m_emitter != -1) {
        unsigned int count = (particleData.m_life + particleData.m_lifeRange) * particleData.m_rate;
        setupBuffer(count * 4, count * 6);
        for (unsigned int i = 0; i < count; i++) {
            unsigned int index[6] = {i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 1, i * 4 + 2, i * 4 + 3};
            writeIndex(index, 6, i * 6);
        }
    }
}

UIShapeParticle::~UIShapeParticle() {
    if (m_emitter != -1) {
        UIParticleManager::sys()->remove(m_emitter);
    }
}

mm::mtl::RTTI UIShapeParticle::m_rtti("UIShapeParticle", &UIShape::m_rtti, nullptr);

}  // namespace ui
