#ifndef CLASSES_LAYER_LAYEROBJSORTPOLYOBJ_H
#define CLASSES_LAYER_LAYEROBJSORTPOLYOBJ_H

#include "classes/layer/LayerSortObj.h"

namespace layer {
// table 0x7100B80320
class LayerObjSortPolyObj : public ::layer::LayerSortObj {
public:
    virtual ~LayerObjSortPolyObj() {}  // slot 0: the table holds LayerSortObj's
    virtual void finalRender();  // slot 4
};
}  // namespace layer

#endif
