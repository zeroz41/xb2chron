#ifndef CLASSES_GF_GFEXTENDRESOURCE_H
#define CLASSES_GF_GFEXTENDRESOURCE_H

#include "mm/mtl/RTTI.h"

namespace gf {
// what an asset pack carries beyond its resources (1.0.0's gf::AssetPackInfo::setExtendResource(unsigned int,
// gf::GfExtendResource*)): its m_rtti ("GfExtendResource", no bases; here lbl_7100C24DE0) is the base
// GfExtendPacking's m_rtti names. It has no table of its own in the image: GfExtendPacking's (destructors, then
// getRTTI) is the shape it gives its derived classes.
class GfExtendResource {
public:
    explicit GfExtendResource(int kind) : m_kind(kind) {}
    virtual ~GfExtendResource() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    static mm::mtl::RTTI m_rtti;

    int m_kind;  // GfExtendPacking's constructor sets 1 (the name is not the original's)
};
}  // namespace gf

#endif
