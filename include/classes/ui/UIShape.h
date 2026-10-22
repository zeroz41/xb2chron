#ifndef CLASSES_UI_UISHAPE_H
#define CLASSES_UI_UISHAPE_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Array.h"
#include "layer/LayerPolyVertex.h"

namespace ui {
// table 0x7100B753A0; a polygon a UIPolygonObject draws: its derived shapes size its buffers and write them
class UIShape {
public:
    UIShape();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShape();  // slot 1
    virtual void update(unsigned int);  // slot 3
    void setupBuffer(unsigned int vertexCount, unsigned int indexCount);
    void writeVertex(const layer::LayerPolyVertex* vertex, unsigned int count, unsigned int offset);
    void writeIndex(const unsigned int* index, unsigned int count, unsigned int offset);
    void setIndexRange(unsigned int count);  // the indices drawn (at most the buffer's)
    static mm::mtl::RTTI m_rtti;
    mm::mtl::Array<layer::LayerPolyVertex> m_vertices;
    mm::mtl::Array<unsigned int> m_indices;
    unsigned int m_indexRange;  // setIndexRange; UIPolygonObject::apply draws this many indices
    bool m_dirty;  // the writes set it; UIPolygonObject::apply copies the buffers to its layer object and clears it
};
}  // namespace ui

#endif
