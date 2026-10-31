#ifndef CLASSES_GF_GFOBJSETUPDRIVER_H
#define CLASSES_GF_GFOBJSETUPDRIVER_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamDriver.h"

namespace gf {
// table 0x7100B6A508
class GfObjSetupDriver : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupDriver() {}  // slot 1
    GfObjSetupDriver(const GfInitParamDriver& param);
    static mm::mtl::RTTI m_rtti;

    // the parameter's pad_1a0 (createSetupParam copies it)
    unsigned char pad_6c;
    unsigned char pad_6d;
    unsigned char pad_6e;
    int pad_70;
    // a copy of the parameter the driver was made with (the constructor assigns it; the name is not the
    // original's)
    GfInitParamDriver m_param;
};
}  // namespace gf

#endif
