#ifndef CLASSES_LAYER_LAYEROBJSORTTEXOBJ_H
#define CLASSES_LAYER_LAYEROBJSORTTEXOBJ_H

#include "classes/layer/LayerSortObj.h"

namespace layer {
// table 0x7100B802E8
class LayerObjSortTexObj : public ::layer::LayerSortObj {
public:
    virtual ~LayerObjSortTexObj();  // slot 0
    virtual void finalRender();  // slot 4
};
}  // namespace layer

#endif
