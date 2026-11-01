#ifndef LAYER_LAYERRESADDTEXOBJ_H
#define LAYER_LAYERRESADDTEXOBJ_H

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
class LayerTextureObj;

// the resource a LayerResAddTexObj takes its textures from: the texture resource sits m_textureOfs on (0 for none;
// the names are not the original's)
struct LayerResAddTexHead {
    unsigned char pad_0[0x24];
    unsigned int m_textureOfs;  // 0x24
};

// an added texture of a layer object (LayerObjResTex): a resource's textures, shared through the texture manager, or
// a texture buffer of its own (the field names are not the original's)
class LayerResAddTexObj {
public:
    enum {
        FLAG_BUFFER = 0x400,  // m_buffer, not a resource (the name is not the original's)
    };

    LayerResAddTexObj(const void* res, unsigned int index);
    LayerResAddTexObj(grlib::CGLibTextureBuffer* buffer, unsigned int index);
    ~LayerResAddTexObj();
    void release();
    void setupResource();
    grlib::CGLibTextureBuffer* getTexObj(unsigned int index);

    // LayerObjResTex's lists link the objects through these (LayerObjResTex::clear walks m_next; both constructors
    // zero them; the names are not the original's)
    LayerResAddTexObj* m_prev;  // 0x0
    LayerResAddTexObj* m_next;  // 0x8
    union {
        const LayerResAddTexHead* m_res;  // 0x10
        grlib::CGLibTextureBuffer* m_buffer;  // 0x10 with FLAG_BUFFER
    };
    LayerTextureObj* m_texObj;  // 0x18: the resource's, from setupResource
    unsigned short m_index;     // 0x20
    unsigned short m_flags;     // 0x22: FLAG_
};
}  // namespace layer

#endif
