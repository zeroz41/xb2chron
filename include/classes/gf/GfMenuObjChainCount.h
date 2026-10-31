#ifndef CLASSES_GF_GFMENUOBJCHAINCOUNT_H
#define CLASSES_GF_GFMENUOBJCHAINCOUNT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// The chain attack's count menu. 1.0.0 has its constructor, initialize (which registers a MainListener on LAY_main),
// open and close; 3.0.1 keeps only MainListener's reciveEvent and destructor, so its members are not declared here.
class GfMenuObjChainCount : public ::gf::GfMenuObject {
public:
    class MainListener;
};
}  // namespace gf

#endif
