#ifndef CLASSES_GF_GFOBJSETUPMAPOBJ_H
#define CLASSES_GF_GFOBJSETUPMAPOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// no table in 3.0.1: 1.0.0's GfObjSetup::createSetupParam(GF_OBJ_HANDLE*, const GfInitParamMapObj&) made it, 3.0.1
// keeps only its m_rtti (gf_obj_setup.cpp's static initializer: "GfObjSetupMapObj", based on GfObjSetup's)
class GfObjSetupMapObj : public ::gf::GfObjSetup {
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
