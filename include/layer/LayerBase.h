#ifndef LAYER_LAYERBASE_H
#define LAYER_LAYERBASE_H

namespace layer {
// the base of the layer objects: LayerObj, LayerObjLayout and LayerObjWork's tables hold its (empty) destructor, and
// UIObject passes its LayerBase to LayerAccLayoutBinary::setLayoutObj as a LayerObj
class LayerBase {
public:
    virtual ~LayerBase() {}  // slot 0
    // its owner's end of it: UIFontManager's destructor calls slot 2 of the font objects LayerAccManager made, as
    // LayerObj's slot 2 (release)
    virtual void release() = 0;  // slot 2
};
}  // namespace layer

#endif
