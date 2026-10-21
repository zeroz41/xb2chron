#ifndef CLASSES_GF_GFEXTENDPACKING_H
#define CLASSES_GF_GFEXTENDPACKING_H

#include "mm/mtl/RTTI.h"
namespace gf {
// table 0x7100B69EE0
class GfExtendPacking {
public:
    virtual ~GfExtendPacking();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
