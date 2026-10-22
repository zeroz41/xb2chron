#ifndef CLASSES_GF_GFCOMVISIBLE_H
#define CLASSES_GF_GFCOMVISIBLE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"

namespace fw { class VisibleObject; }

namespace gf {
// table 0x7100B66808
class GfComVisible : public ::gf::GfComponent {
public:
    struct SetupInfo {};
    GfComVisible();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComVisible();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    void setup(const SetupInfo& info);
    void cleanup();
    bool isRender() const;
    static mm::mtl::RTTI m_rtti;

    fw::VisibleObject* m_visible;  // setup creates it at the object's layer, on its transform's frame
};
}  // namespace gf

#endif
