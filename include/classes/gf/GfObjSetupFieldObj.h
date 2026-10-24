#ifndef CLASSES_GF_GFOBJSETUPFIELDOBJ_H
#define CLASSES_GF_GFOBJSETUPFIELDOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamFobj.h"

namespace gf {
// table 0x7100B6A688
class GfObjSetupFieldObj : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupFieldObj() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupFieldObj(const GfInitParamFobj& param);

    // the "paramid<n>" column of the parameter's BDAT row (createSetupParam; -1 at construction)
    int pad_6c;
    unsigned char pad_70[0x20];
    bool pad_90;
};
}  // namespace gf

#endif
