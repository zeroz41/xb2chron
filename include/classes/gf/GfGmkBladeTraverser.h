#ifndef CLASSES_GF_GFGMKBLADETRAVERSER_H
#define CLASSES_GF_GFGMKBLADETRAVERSER_H

namespace gmk { class AGmkBase; }

namespace gf {
// table 0x7100B51A70
class GfGmkBladeTraverser {
public:
    virtual void onTraverse(gmk::AGmkBase const&);  // slot 0
};
}  // namespace gf

#endif
