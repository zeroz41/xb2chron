#ifndef CLASSES_LAYER_LAYEROBJSORTDEF_H
#define CLASSES_LAYER_LAYEROBJSORTDEF_H

#include "classes/layer/LayerSortObj.h"

namespace layer {
// table 0x7100B80208
class LayerObjSortDef : public ::layer::LayerSortObj {
public:
    virtual ~LayerObjSortDef() {}  // slot 0: the table holds LayerSortObj's
    virtual void finalRender();  // slot 4
};
}  // namespace layer

#endif
