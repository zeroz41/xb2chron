#ifndef CLASSES_UI_UISHAPE_H
#define CLASSES_UI_UISHAPE_H

#include "mm/mtl/RTTI.h"

namespace layer { struct LayerPolyVertex; }

namespace ui {
// table 0x7100B753A0; a polygon a UIPolygonObject draws: its derived shapes size its buffers and write them
class UIShape {
public:
    UIShape();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShape();  // slot 1
    virtual void update(unsigned int);  // slot 3
    void setupBuffer(unsigned int vertexCount, unsigned int indexCount);
    void writeIndex(const unsigned int* index, unsigned int count, unsigned int offset);
    void writeVertex(const layer::LayerPolyVertex* vertex, unsigned int count, unsigned int offset);
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_08[0x38];  // the buffers; the constructor clears them
};
}  // namespace ui

#endif
