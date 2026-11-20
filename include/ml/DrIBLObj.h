#ifndef ML_DRIBLOBJ_H
#define ML_DRIBLOBJ_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {
class DrIBLColiAcc;
class DrMan;
struct _EnvColiListTreeData;
struct _IBLPrimHeader;

// One IBL resource ('GIBL', version 10000): two texture arrays of m_texNum textures built from it and the
// collision accessor. Only what the destructor uses is declared; the field names are not the original's.
class DrIBLObj {
public:
    // the resource's header (layout from initialize; the names are not the original's)
    struct ResHeader {
        unsigned int magic;  // 0x0: 'GIBL'
        unsigned int version;  // 0x4: 10000
        unsigned int num;  // 0x8: the textures, the primitives and the collision bits
        unsigned int texOfs;  // 0xC: num TexEntry
        unsigned char pad_10[0x4];
        unsigned int primOfs;  // 0x14: num _IBLPrimHeader
        unsigned int treeNum;  // 0x18
        unsigned int treeOfs;  // 0x1C
        unsigned int invalidTreeNum;  // 0x20
        unsigned int invalidTreeOfs;  // 0x24
    };
    // a texture pair of the resource, 0x28 bytes (layout from initialize; the names are not the original's)
    struct TexEntry {
        unsigned char pad_0[0x10];
        unsigned int ofsA;  // 0x10: m_texA's image
        unsigned int sizeA;  // 0x14
        unsigned int ofsB;  // 0x18: m_texB's image
        unsigned int sizeB;  // 0x1C
        unsigned char pad_20[0x8];
    };
    enum {
        RES_MAGIC = 0x4C424947,  // 'GIBL'
        RES_VERSION = 10000,
    };

    ~DrIBLObj();
    void initialize(DrMan* drMan);

    const void* m_data;  // 0x0, the resource
    const TexEntry* m_texEntry;  // 0x8
    const _IBLPrimHeader* m_prims;  // 0x10
    const _EnvColiListTreeData* m_tree;  // 0x18
    unsigned char pad_20[0x20];
    unsigned int m_texNum;  // 0x40, from the resource's header (+0x8)
    grlib::CGLibTextureBuffer* m_texA;  // 0x48, new[] m_texNum
    grlib::CGLibTextureBuffer* m_texB;  // 0x50, new[] m_texNum
    unsigned int m_flags;  // 0x58, initialize sets bit 0
    DrIBLColiAcc* m_coliAcc;  // 0x60
};
}  // namespace ml

#endif
