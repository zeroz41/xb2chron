#ifndef LAYER_LAYERTEXTUREOBJ_H
#define LAYER_LAYERTEXTUREOBJ_H

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
// an object's textures (only what LayerObjTopMaskObj calls is declared; called directly, so not virtual)
class LayerTextureObj {
public:
    void setupResource();
    // the index-th of its textures (0x70 bytes each, from the pointer at 0x30)
    grlib::CGLibTextureBuffer* getTexture(int index);
};
}  // namespace layer

#endif
