#ifndef CLASSES_GF_GFMENUOBJCOMMONLIST_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONLIST_LISTLISTENER_H

#include "classes/gf/GfMenuObjCommonList.h"

namespace gf {
// table 0x7100B61450
class GfMenuObjCommonList::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
