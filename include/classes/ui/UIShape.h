#ifndef CLASSES_UI_UISHAPE_H
#define CLASSES_UI_UISHAPE_H

#include "mm/mtl/RTTI.h"
namespace ui {
// table 0x7100B753A0
class UIShape {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShape();  // slot 1
    virtual void update(unsigned int);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif
