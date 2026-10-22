#ifndef CLASSES_GF_GFCOMWIND_H
#define CLASSES_GF_GFCOMWIND_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"

namespace fw { class WindProbe; }

namespace gf {
// table 0x7100B66438
class GfComWind : public ::gf::GfComponent {
public:
    // what setup makes the probe with (WindFactory::createProbe's arguments)
    struct SetupInfo {
        float radius;
        unsigned int capacity;
        bool isMain;
    };
    GfComWind();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComWind();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    void setup(const SetupInfo& info);
    void cleanup();
    static mm::mtl::RTTI m_rtti;

    fw::WindProbe* m_probe;  // setup makes it on the object's transform's frame; cleanup releases it
};
}  // namespace gf

#endif
