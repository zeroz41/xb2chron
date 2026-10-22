#include "classes/ui/UIShapeSimpleFace.h"
#include "classes/ui/UIShape.h"
#include "layer/LayerPolyVertex.h"
#include "ui/UIUtil.h"

namespace ui {

// whether the segments a-b and c-d cross (the name is not the original's)
static inline bool isCross(const layer::LayerPolyVertex& a, const layer::LayerPolyVertex& b,
                           const layer::LayerPolyVertex& c, const layer::LayerPolyVertex& d) {
    float ta = (c.x - d.x) * (a.y - c.y) + (c.y - d.y) * (c.x - a.x);
    float tb = (c.x - d.x) * (b.y - c.y) + (c.y - d.y) * (c.x - b.x);
    float tc = (a.x - b.x) * (c.y - a.y) + (a.y - b.y) * (a.x - c.x);
    float td = (a.x - b.x) * (d.y - a.y) + (a.y - b.y) * (a.x - d.x);
    return tc * td < 0.0f && ta * tb < 0.0f;
}

UIShapeSimpleFace::UIShapeSimpleFace(unsigned int count) : m_faceDirty(true) {
    setupBuffer(count, count * 3 - 6);
    m_faceVertices.setAllocator(UIUtil::getProgAllocator());
    m_faceVertices.reserve(count);
    for (unsigned int i = 0; i < count; i++) {
        m_faceVertices[i].x = m_faceVertices[i].y = 0.0f;
        m_faceVertices[i].r = m_faceVertices[i].g = m_faceVertices[i].b = m_faceVertices[i].a = 0xFF;
        m_faceVertices[i].u = m_faceVertices[i].v = 0.0f;
    }
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_indices.size()) / 3; i++) {
        unsigned int index[3] = {i, i + 1, i + 2};
        writeIndex(index, 3, i * 3);
    }
}

UIShapeSimpleFace::~UIShapeSimpleFace() {}

void UIShapeSimpleFace::writeFaceVertex(const layer::LayerPolyVertex* vertex, unsigned int count, unsigned int offset) {
    if (vertex != nullptr && count != 0) {
        for (unsigned int i = 0; i < count; i++) {
            unsigned int index = offset + i;
            if (index >= m_faceVertices.size()) {
                return;
            }
            m_faceVertices[index] = vertex[i];
        }
        m_faceDirty = true;
    }
}

void UIShapeSimpleFace::update(unsigned int) {
    if (m_faceDirty) {
        writeVertex(&m_faceVertices[0], m_faceVertices.size(), 0);
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_vertices.size()) - 1; i++) {
            unsigned int top = i;
            for (unsigned int j = i + 1; j < static_cast<unsigned int>(m_vertices.size()); j++) {
                if (m_vertices[j].y < m_vertices[top].y) {
                    top = j;
                } else if (m_vertices[j].y == m_vertices[top].y && m_vertices[j].x > m_vertices[top].x) {
                    top = j;
                }
            }
            if (i != top) {
                layer::LayerPolyVertex vertex = m_vertices[i];
                writeVertex(&m_vertices[top], 1, i);
                writeVertex(&vertex, 1, top);
            }
        }
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_vertices.size()) - 3; i++) {
            if (isCross(m_vertices[i], m_vertices[i + 2], m_vertices[i + 1], m_vertices[i + 3])) {
                layer::LayerPolyVertex vertex = m_vertices[i];
                writeVertex(&m_vertices[i + 1], 1, i);
                writeVertex(&vertex, 1, i + 1);
            }
        }
        m_faceDirty = false;
    }
}

mm::mtl::RTTI UIShapeSimpleFace::m_rtti("UIShapeSimpleFace", &UIShape::m_rtti, nullptr);

}  // namespace ui
