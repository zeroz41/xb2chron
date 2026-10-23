#ifndef CLASSES_LAYER_LAYERFONTRESOBJ_H
#define CLASSES_LAYER_LAYERFONTRESOBJ_H

#include "layer/LayerBase.h"

namespace layer {
// table 0x7100B80670
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
class LayerFontResObj : public ::layer::LayerBase {
public:
    virtual ~LayerFontResObj();  // slot 0
    virtual void release();  // slot 2
    virtual void setupResource();  // slot 3
};
}  // namespace layer

#endif
