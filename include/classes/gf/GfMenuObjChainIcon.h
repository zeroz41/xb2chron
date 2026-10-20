#ifndef CLASSES_GF_GFMENUOBJCHAINICON_H
#define CLASSES_GF_GFMENUOBJCHAINICON_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B60D18
class GfMenuObjChainIcon : public ::gf::GfMenuObject {
public:
    class ChainIconInfo;
    class ListListener;
    virtual ~GfMenuObjChainIcon();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
