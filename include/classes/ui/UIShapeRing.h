#ifndef CLASSES_UI_UISHAPERING_H
#define CLASSES_UI_UISHAPERING_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIShape.h"

namespace ui {
// table 0x7100B75400; a ring of quads around the unit circle times m_scale, m_weight * m_weightScale wide
class UIShapeRing : public ::ui::UIShape {
public:
    UIShapeRing(unsigned int division, float weight);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UIShapeRing();  // slot 1
    virtual void update(unsigned int);  // slot 3
    void buildVertex();
    void setScale(float scale);
    void setWeightScale(float weightScale);
    static mm::mtl::RTTI m_rtti;
    unsigned int m_division;      // its quads: four times the constructor's division
    float m_weight;               // the constructor's: the ring's width
    float m_weightScale;          // setWeightScale's: scales the width
    float m_scale;                // setScale's: the ring's radius
    float m_builtScale;           // m_scale and m_weightScale as buildVertex last built the vertices; update
    float m_builtWeightScale;     //   rebuilds when either changed
};
}  // namespace ui

#endif
