#ifndef CLASSES_UI_UISHAPEPARTICLE_H
#define CLASSES_UI_UISHAPEPARTICLE_H

#include "mm/mtl/RTTI.h"
namespace ui {
// table 0x7100B753D0
class UIShapeParticle {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShapeParticle();  // slot 1
    virtual void update(unsigned int);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif
