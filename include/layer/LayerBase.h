#ifndef LAYER_LAYERBASE_H
#define LAYER_LAYERBASE_H

namespace layer {
// the base of the layer objects: LayerObj, LayerObjLayout and LayerObjWork's tables hold its (empty) destructor, and
// UIObject passes its LayerBase to LayerAccLayoutBinary::setLayoutObj as a LayerObj
class LayerBase {
public:
    virtual ~LayerBase() {}  // slot 0
};
}  // namespace layer

#endif
