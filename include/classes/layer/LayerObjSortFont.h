#ifndef CLASSES_LAYER_LAYEROBJSORTFONT_H
#define CLASSES_LAYER_LAYEROBJSORTFONT_H

#include "classes/layer/LayerSortObj.h"

namespace layer {
// table 0x7100B80278
class LayerObjSortFont : public ::layer::LayerSortObj {
public:
    virtual ~LayerObjSortFont() {}  // slot 0: the table holds LayerSortObj's
    virtual void finalRender();  // slot 4
};
}  // namespace layer

#endif
