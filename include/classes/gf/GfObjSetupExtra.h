#ifndef CLASSES_GF_GFOBJSETUPEXTRA_H
#define CLASSES_GF_GFOBJSETUPEXTRA_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamExtra.h"

namespace gf {
// table 0x7100B6A788
class GfObjSetupExtra : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupExtra() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupExtra(const GfInitParamExtra& param);
    // the mount index of the model: createSetupParam copies the param's append's getMountIndex() (the name is not
    // the original's)
    unsigned int m_mountIndex;
};
}  // namespace gf

#endif
