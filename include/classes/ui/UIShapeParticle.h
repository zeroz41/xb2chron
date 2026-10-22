#ifndef CLASSES_UI_UISHAPEPARTICLE_H
#define CLASSES_UI_UISHAPEPARTICLE_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIShape.h"

namespace ui {
// table 0x7100B753D0; the particles of an emitter UIParticleManager runs, one quad each
class UIShapeParticle : public ::ui::UIShape {
public:
    // an emitter from the particle data (size bytes) for an object of width by height
    UIShapeParticle(void* data, unsigned int size, unsigned int width, unsigned int height);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShapeParticle();  // slot 1
    virtual void update(unsigned int);  // slot 3
    static mm::mtl::RTTI m_rtti;
    int m_emitter;          // its emitter's handle in UIParticleManager (-1: none)
    unsigned int m_width;   // the constructor's: the quads' x is divided by it
    unsigned int m_height;  // the constructor's: the quads' y is divided by it
};
}  // namespace ui

#endif
