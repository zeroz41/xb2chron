#ifndef CLASSES_GF_GFEXTENDRESOURCE_H
#define CLASSES_GF_GFEXTENDRESOURCE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/RTTI.h"

namespace gf {
// what an asset pack carries beyond its resources (1.0.0's gf::AssetPackInfo::setExtendResource(unsigned int,
// gf::GfExtendResource*)): its m_rtti ("GfExtendResource", no bases; here lbl_7100C24DE0) is the base
// GfExtendPacking's m_rtti names. It has no table of its own in the image: GfExtendPacking's (destructors, then
// getRTTI) is the shape it gives its derived classes.
// Counted: AssetPackInfo::releaseExtResource releases each one (reference_object.h line 60, slot 1 deletes); a new one
// holds the first reference (GfExtendPacking's constructor stores the count 1).
class GfExtendResource : public mm::mtl::ReferenceObject {
public:
    GfExtendResource() { addRef(); }
    virtual ~GfExtendResource() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
