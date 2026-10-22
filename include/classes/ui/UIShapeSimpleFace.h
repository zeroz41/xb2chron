#ifndef CLASSES_UI_UISHAPESIMPLEFACE_H
#define CLASSES_UI_UISHAPESIMPLEFACE_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIShape.h"

namespace layer { struct LayerPolyVertex; }

namespace ui {
// table 0x7100B75430; a face of the constructor's number of corners (its vertices)
class UIShapeSimpleFace : public ::ui::UIShape {
public:
    UIShapeSimpleFace(unsigned int count);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShapeSimpleFace();  // slot 1
    virtual void update(unsigned int);  // slot 3
    void writeFaceVertex(const layer::LayerPolyVertex* vertex, unsigned int count, unsigned int offset);
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_40[0x20];  // the constructor's buffer and flag
};
}  // namespace ui

#endif
