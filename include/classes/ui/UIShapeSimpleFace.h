#ifndef CLASSES_UI_UISHAPESIMPLEFACE_H
#define CLASSES_UI_UISHAPESIMPLEFACE_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Array.h"
#include "classes/ui/UIShape.h"
#include "layer/LayerPolyVertex.h"

namespace ui {
// table 0x7100B75430; a face of the constructor's number of corners (its vertices): writeFaceVertex sets the
// corners, update sorts them into a triangle strip
class UIShapeSimpleFace : public ::ui::UIShape {
public:
    UIShapeSimpleFace(unsigned int count);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShapeSimpleFace();  // slot 1
    virtual void update(unsigned int);  // slot 3
    void writeFaceVertex(const layer::LayerPolyVertex* vertex, unsigned int count, unsigned int offset);
    static mm::mtl::RTTI m_rtti;
    // the corners writeFaceVertex writes; update copies them into the shape's vertices (the name is not the
    // original's)
    mm::mtl::Array<layer::LayerPolyVertex> m_faceVertices;
    bool m_faceDirty;  // set by the constructor and writeFaceVertex, cleared by update (the name is not the original's)
};
}  // namespace ui

#endif
