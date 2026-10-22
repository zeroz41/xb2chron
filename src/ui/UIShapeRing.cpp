#include "classes/ui/UIShape.h"
#include "classes/ui/UIShapeRing.h"
#include "layer/LayerPolyVertex.h"
#include "math.h"

namespace ui {

UIShapeRing::UIShapeRing(unsigned int division, float weight)
    : m_division(division * 4), m_weight(weight) {
    m_weightScale = m_builtWeightScale = 1.0f;
    m_scale = m_builtScale = 1.0f;
    setupBuffer(m_division * 2, m_division * 6);
    unsigned int vertexCount = m_division * 2;
    for (unsigned int i = 0; i < m_division; i++) {
        unsigned int index[6] = {
            (i * 2) % vertexCount,     (i * 2 + 2) % vertexCount, (i * 2 + 1) % vertexCount,
            (i * 2 + 2) % vertexCount, (i * 2 + 1) % vertexCount, (i * 2 + 3) % vertexCount,
        };
        writeIndex(index, 6, i * 6);
    }
    buildVertex();
}

void UIShapeRing::buildVertex() {
    float step = 360.0f / m_division * 0.0174532924f;
    float angle = 1.57079637f;
    layer::LayerPolyVertex vertex;
    vertex.u = 0.0f;
    vertex.color = 0xFFFFFFFF;
    vertex.v = 0.0f;
    for (unsigned int i = 0; i < m_division; i++) {
        float c = cosf(angle);
        float s = -sinf(angle);
        float half = m_weight * 0.5f * m_weightScale;
        vertex.x = c * m_scale + c * half;
        vertex.y = s * m_scale + s * half;
        vertex.u = 0.0f;
        vertex.v = 0.0f;
        writeVertex(&vertex, 1, i * 2);
        half = m_weight * 0.5f * m_weightScale;
        vertex.x = c * m_scale - c * half;
        vertex.y = s * m_scale - s * half;
        vertex.u = 0.0f;
        vertex.v = 1.0f;
        writeVertex(&vertex, 1, i * 2 + 1);
        angle += step;
    }
}

UIShapeRing::~UIShapeRing() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

void UIShapeRing::setScale(float scale) {
    m_scale = scale;
}

void UIShapeRing::setWeightScale(float weightScale) {
    m_weightScale = weightScale;
}

void UIShapeRing::update(unsigned int) {
    if (m_scale != m_builtScale || m_weightScale != m_builtWeightScale) {
        buildVertex();
        m_builtScale = m_scale;
        m_builtWeightScale = m_weightScale;
    }
}

}  // namespace ui
