#ifndef CLASSES_LAYER_LAYERACTBASE_H
#define CLASSES_LAYER_LAYERACTBASE_H

#include "classes/layer/LayerObj.h"

namespace layer { class LyrActionData; }

namespace layer {
// table none (its derived classes')
class LayerActBase : public ::layer::LayerObj {
public:
    virtual ~LayerActBase();  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*) {}  // slot 10
};
}  // namespace layer

#endif
