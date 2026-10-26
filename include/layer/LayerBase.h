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
    // its place in its manager's LayerLinkList (LayerFontManager's lists; the names are those LayerLinkList uses)
    LayerBase* m_prev;  // 0x8
    LayerBase* m_next;  // 0x10
    // its kind: UIObject::importDisplaySize reads a memory object's size (5) and a font object's (2) through their
    // accessors (the name is not the original's)
    int m_objType;
};
}  // namespace layer

#endif
