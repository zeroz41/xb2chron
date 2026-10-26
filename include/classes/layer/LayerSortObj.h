#ifndef CLASSES_LAYER_LAYERSORTOBJ_H
#define CLASSES_LAYER_LAYERSORTOBJ_H

namespace layer { class LayerObj; }

namespace layer {
// table none (its derived classes')
class LayerSortObj {
public:
    virtual ~LayerSortObj() {}  // slot 0
    virtual void alphaRender() {}  // slot 2
    virtual void lastRender() {}  // slot 3
    virtual void finalRender() = 0;  // slot 4 (LayerSortMan::finalRender calls it down the list)

    // the next object in its LayerSortMan list (set2DSpace/set3DSpace chain it; the name is not the original's)
    LayerSortObj* m_next;
    // the object it draws: the derived classes' finalRender draws it (the name is not the original's)
    LayerObj* m_obj;
};
}  // namespace layer

#endif
