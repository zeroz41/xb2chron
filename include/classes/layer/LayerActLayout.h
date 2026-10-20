#ifndef CLASSES_LAYER_LAYERACTLAYOUT_H
#define CLASSES_LAYER_LAYERACTLAYOUT_H

#include "classes/layer/LayerObj.h"

namespace layer { class LyrActionData; }

namespace layer {
// table none (its derived classes')
class LayerActLayout : public ::layer::LayerObj {
public:
    virtual ~LayerActLayout();  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
};
}  // namespace layer

#endif
