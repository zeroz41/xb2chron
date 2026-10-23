#ifndef CLASSES_LAYER_LAYEROBJSORTLAYOUT_H
#define CLASSES_LAYER_LAYEROBJSORTLAYOUT_H

#include "classes/layer/LayerSortObj.h"

namespace layer {
// table 0x7100B80240
class LayerObjSortLayout : public ::layer::LayerSortObj {
public:
    virtual ~LayerObjSortLayout() {}  // slot 0: the table holds LayerSortObj's
    virtual void finalRender();  // slot 4
};
}  // namespace layer

#endif
