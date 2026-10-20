#ifndef CLASSES_LAYER_LAYERSORTOBJ_H
#define CLASSES_LAYER_LAYERSORTOBJ_H

namespace layer {
// table none (its derived classes')
class LayerSortObj {
public:
    virtual ~LayerSortObj();  // slot 0
    virtual void alphaRender();  // slot 2
    virtual void lastRender();  // slot 3
};
}  // namespace layer

#endif
