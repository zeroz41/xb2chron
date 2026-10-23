#ifndef CLASSES_GF_GFOBJSETUPGIMMICK_H
#define CLASSES_GF_GFOBJSETUPGIMMICK_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/DataParamAcc.h"

namespace gf {
// table 0x7100B6A648
class GfObjSetupGimmick : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupGimmick();  // slot 1
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_50[0xC];
    // the gimmick's type: DataObjGmk(GF_OBJ_HANDLE*) copies it (the name is not the original's)
    GimmickType m_gimmickType;
};
}  // namespace gf

#endif
