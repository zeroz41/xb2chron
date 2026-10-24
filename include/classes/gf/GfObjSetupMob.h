#ifndef CLASSES_GF_GFOBJSETUPMOB_H
#define CLASSES_GF_GFOBJSETUPMOB_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfInitParamMob.h"

namespace gf {
// table 0x7100B6A608
class GfObjSetupMob : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupMob() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupMob(const GfInitParamMob& param);

    // the state the object starts in: "S_idle" (the name is not the original's)
    mm::mtl::FixStr<32> m_stateName;
    // 100 at construction; what it means is not known yet
    unsigned char pad_90;
};
}  // namespace gf

#endif
