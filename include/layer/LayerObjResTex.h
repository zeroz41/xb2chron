#ifndef LAYER_LAYEROBJRESTEX_H
#define LAYER_LAYEROBJRESTEX_H

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
class LayerTextureObj;

// the added textures of a LayerObjTopDef (0x2C0) or LayerObjTopPolyObj (0x2B8): 0x48 bytes, the next field of
// both follows it. The field layout is not known yet.
class LayerObjResTex {
public:
    void setAddTexture(const void* res, unsigned int index);
    void setAddTexture(grlib::CGLibTextureBuffer& texture, unsigned int index);
    void clear();
    void updateTexutre(grlib::CGLibTextureBuffer** textures, LayerTextureObj* textureObj);

    unsigned char pad_0[0x48];
};
}  // namespace layer

#endif
