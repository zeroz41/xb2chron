#ifndef CLASSES_GMK_GMKINSTDISPTRAVERSERBYBDATID_H
#define CLASSES_GMK_GMKINSTDISPTRAVERSERBYBDATID_H

namespace gmk { class AGmkBase; }

namespace gmk {
// table 0x7100B6F080
class GmkInstDispTraverserByBdatId {
public:
    virtual void onTraverse(gmk::AGmkBase const&);  // slot 0
};
}  // namespace gmk

#endif
