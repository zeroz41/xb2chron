#ifndef CLASSES_GF_GFOBJSETUPEVENTOBJ_H
#define CLASSES_GF_GFOBJSETUPEVENTOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "mm/mtl/FixStr.h"

namespace gf {
// table 0x7100B6A7C8
class GfObjSetupEventObj : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupEventObj() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupEventObj(const GfInitParamEventObj& param);
    // the asset setup's archive file without folder and extension (createSetupParam; the name is not the
    // original's)
    mm::mtl::FixStr<128> m_arcName;
};
}  // namespace gf

#endif
