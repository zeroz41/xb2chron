#ifndef CLASSES_LAYER_LAYEROBJSORTMEMOBJ_H
#define CLASSES_LAYER_LAYEROBJSORTMEMOBJ_H

#include "classes/layer/LayerSortObj.h"

namespace layer {
// table 0x7100B802B0
class LayerObjSortMemObj : public ::layer::LayerSortObj {
public:
    virtual ~LayerObjSortMemObj() {}  // slot 0: the table holds LayerSortObj's
    virtual void finalRender();  // slot 4
};
}  // namespace layer

#endif
