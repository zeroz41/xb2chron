#include "classes/ui/UIShape.h"
#include "layer/LayerPolyVertex.h"
#include "mm/mtl/Array.h"
#include "ui/UIUtil.h"

namespace ui {

UIShape::UIShape() : m_dirty(false) {}

UIShape::~UIShape() {
    if (m_vertices.size() != 0) {
        m_vertices.clear();
    }
    if (m_indices.size() != 0) {
        m_indices.clear();
    }
}

void UIShape::setupBuffer(unsigned int vertexCount, unsigned int indexCount) {
    m_vertices.setAllocator(UIUtil::getProgAllocator());
    m_indices.setAllocator(UIUtil::getProgAllocator());
    m_vertices.reserve(vertexCount);
    m_indices.reserve(indexCount);
    for (unsigned int i = 0; i < vertexCount; i++) {
        m_vertices[i].x = m_vertices[i].y = 0.0f;
        m_vertices[i].r = m_vertices[i].g = m_vertices[i].b = m_vertices[i].a = 0xFF;
        m_vertices[i].u = m_vertices[i].v = 0.0f;
    }
    for (unsigned int i = 0; i < indexCount; i++) {
        m_indices[i] = 0;
    }
    m_indexRange = indexCount;
    m_dirty = true;
}

void UIShape::writeVertex(const layer::LayerPolyVertex* vertex, unsigned int count, unsigned int offset) {
    if (vertex != nullptr && count != 0) {
        m_dirty = true;
        for (unsigned int i = 0; i < count; i++) {
            unsigned int index = offset + i;
            if (index >= m_vertices.size()) {
                return;
            }
            m_vertices[index] = vertex[i];
        }
    }
}

void UIShape::writeIndex(const unsigned int* index, unsigned int count, unsigned int offset) {
    if (index != nullptr && count != 0) {
        m_dirty = true;
        for (unsigned int i = 0; i < count; i++) {
            unsigned int at = offset + i;
            if (at >= m_indices.size()) {
                return;
            }
            m_indices[at] = index[i];
        }
    }
}

void UIShape::setIndexRange(unsigned int count) {
    m_indexRange = count > m_indices.size() ? static_cast<unsigned int>(m_indices.size()) : count;
}

void UIShape::update(unsigned int) {}

mm::mtl::RTTI UIShape::m_rtti("UIShape", nullptr, nullptr);

}  // namespace ui
