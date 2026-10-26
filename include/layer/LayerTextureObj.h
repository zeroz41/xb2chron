#ifndef LAYER_LAYERTEXTUREOBJ_H
#define LAYER_LAYERTEXTUREOBJ_H

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
class LayerManager;
class LayerTextureMan;

// a texture resource's header: an info table (offset from the header) of m_num textures. The names are not the
// original's
struct LayerResTextureHead {
    unsigned int m_infoOfs;  // 0x0
    int m_num;               // 0x4
};
// one texture of a LayerResTextureHead (0xC bytes): its image, from the header (the names are not the original's)
struct LayerResTextureInfo {
    unsigned char pad_0[0x4];
    unsigned int m_dataOfs;   // 0x4
    unsigned int m_dataSize;  // 0x8
};

// the textures of one texture resource, shared by everything that uses it: LayerTextureMan counts the users
// (0x48 bytes; the field names are not the original's)
class LayerTextureObj {
public:
    LayerTextureObj(const unsigned char* res, LayerManager* manager, LayerTextureMan* owner);
    ~LayerTextureObj();
    void setupTexture(const unsigned char* res, LayerManager* manager);
    void textureRelease();
    void release();
    void setupResource();
    // the index-th of its textures
    const grlib::CGLibTextureBuffer* getTexture(int index) const;
    grlib::CGLibTextureBuffer* getTexture(int index);

    // one user fewer (never below 0); true when none is left (the name is not the original's)
    bool subRef() {
        m_refCount--;
        if (m_refCount < 0) {
            m_refCount = 0;
        }
        return m_refCount <= 0;
    }

    LayerTextureObj* m_prev;          // 0x0
    LayerTextureObj* m_next;          // 0x8
    const unsigned char* m_key;       // 0x10: the resource createTextureObj looks it up by
    int m_refCount;                   // 0x18
    unsigned char pad_1C[0x4];
    const LayerResTextureHead* m_res;  // 0x20
    bool m_needSetup;                 // 0x28: until setupResource has made the images
    int m_texNum;                     // 0x2C
    grlib::CGLibTextureBuffer* m_textures;  // 0x30: m_texNum, in m_mem
    void* m_mem;                      // 0x38
    LayerTextureMan* m_owner;         // 0x40
};
}  // namespace layer

#endif
