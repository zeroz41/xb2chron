#ifndef CLASSES_GF_GFOBJSETUPMAPLODANIM_H
#define CLASSES_GF_GFOBJSETUPMAPLODANIM_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamMapLodAnim.h"

namespace gf {
// table 0x7100B6A588
class GfObjSetupMapLodAnim : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupMapLodAnim() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupMapLodAnim(const GfInitParamMapLodAnim& param);

    // its LOD id: GfComBehaviorGmk::procMsgPcGetElvLift collects the objects whose id is an elevator's lift LOD's
    // (the name is not the original's)
    unsigned short m_lodId;
};
}  // namespace gf

#endif
