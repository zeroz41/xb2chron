#ifndef CLASSES_GF_GFOBJSETUPNPC_H
#define CLASSES_GF_GFOBJSETUPNPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfInitParamNpc.h"

namespace gf {
// table 0x7100B6A5C8
class GfObjSetupNpc : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupNpc() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupNpc(const GfInitParamNpc& param);

    // the state the object starts in: "S_idle" (the name is not the original's)
    mm::mtl::FixStr<32> m_stateName;
    // the parameter's pad_98 (createSetupParam copies it)
    void* pad_90;
};
}  // namespace gf

#endif
