#ifndef CLASSES_GF_GFEXTENDRESOURCE_H
#define CLASSES_GF_GFEXTENDRESOURCE_H

#include "mm/mtl/RTTI.h"

namespace gf {
// what an asset pack carries beyond its resources (1.0.0's gf::AssetPackInfo::setExtendResource(unsigned int,
// gf::GfExtendResource*)): its m_rtti ("GfExtendResource", no bases; here lbl_7100C24DE0) is the base
// GfExtendPacking's m_rtti names. Its table and members are not identified yet.
class GfExtendResource {
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
