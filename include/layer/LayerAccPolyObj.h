#ifndef LAYER_LAYERACCPOLYOBJ_H
#define LAYER_LAYERACCPOLYOBJ_H

namespace layer { class LayerBase; }
namespace layer { class LayerObjTopPolyObj; }
namespace layer { struct LayerPolyVertex; }
namespace grlib { class CGLibTextureBuffer; }

namespace layer {
// access to a polygon layer object: its vertices and indices (locked while written) and its texture
class LayerAccPolyObj {
public:
    LayerAccPolyObj(LayerBase* layer);
    void LockVertex();
    void setVertex(unsigned int index, const LayerPolyVertex& vertex);
    void UnlockVertex();
    void LockIndex();
    void setIndex(unsigned int index, unsigned short value);
    void UnlockIndex();
    void setIndexInfo(unsigned short start, unsigned short count);  // the indices drawn
    void setTexutre(const void* texture);  // a texture resource
    void setTexutre(grlib::CGLibTextureBuffer& texture);

    LayerBase* m_layer;  // the constructor's
    LayerObjTopPolyObj* m_polyObj;  // the constructor's layer again, as the polygon object it is
};
}  // namespace layer

#endif
