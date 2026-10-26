#ifndef LAYER_LAYERRESSECTEXTURE_H
#define LAYER_LAYERRESSECTEXTURE_H

#include "grlib/CGLibDblUniformBlock.h"

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
class LayerTextureObj;

// a second texture's parameters (0x1C bytes; the names are not the original's)
struct LayerResSecTexParm {
    unsigned char pad_0[0x8];
    float m_parm[4];  // 0x8: update copies them to the uniform block
    unsigned char pad_18[0x4];
};
// where a resource's second-texture parameters sit (the names are not the original's)
struct LayerResSecTexTable {
    unsigned char pad_0[0x18];
    unsigned int m_parmOfs;  // 0x18: LayerResSecTexParm table, from this table
};
struct LayerResSecTexHead {
    unsigned char pad_0[0x2C];
    unsigned int m_tableOfs;  // 0x2C: LayerResSecTexTable, from the header
};

// a layer's second texture (LayerShdManager::setSecTexture) and its uniform block (the field names are not the
// original's)
class LayerResSecTexture {
public:
    ~LayerResSecTexture();
    void resourceInit();
    void update();
    grlib::CGLibTextureBuffer* getTexture();

    const LayerResSecTexHead* m_res;  // 0x0
    LayerTextureObj* m_texObj;        // 0x8
    unsigned short m_parmIndex;       // 0x10
    unsigned short m_hasParm;         // 0x12: else update writes 1, 1, 0, 0
    float m_value;                    // 0x14: update writes it after the parameters
    grlib::CGLibDblUniformBlock m_uniform;  // 0x18
};
}  // namespace layer

#endif
