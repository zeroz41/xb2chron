#ifndef CLASSES_GF_GFMENUOBJCHAINICON_CHAINICONINFO_H
#define CLASSES_GF_GFMENUOBJCHAINICON_CHAINICONINFO_H

#include "classes/gf/GfMenuManyObjects/InfoType.h"
#include "classes/gf/GfMenuObjChainIcon.h"

namespace gf {
// table 0x7100B60D88: an open chain icon in GfMenuManyObjects' queue 2
class GfMenuObjChainIcon::ChainIconInfo : public ::gf::GfMenuManyObjects::InfoType {
public:
    ChainIconInfo() {}
    ChainIconInfo(unsigned int handle) : InfoType(handle) {}
};
}  // namespace gf

#endif
