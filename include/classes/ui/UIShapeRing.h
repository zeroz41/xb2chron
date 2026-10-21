#ifndef CLASSES_UI_UISHAPERING_H
#define CLASSES_UI_UISHAPERING_H

#include "mm/mtl/RTTI.h"
namespace ui {
// table 0x7100B75400
class UIShapeRing {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShapeRing();  // slot 1
    virtual void update(unsigned int);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif
