#ifndef ML_DRRESETCTEXLIST_H
#define ML_DRRESETCTEXLIST_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {

// A texture list resource: m_texture holds one texture per entry of the resource's table, found by id
// (getTextureID) or by name (1.0.0's getTextureName). Field and type names are not the original's.
class DrResEtcTexList {
public:
    // the resource's header: the entry table sits m_entryOfs bytes from it
    struct Header {
        unsigned char pad_0[0xC];
        unsigned int m_entryOfs;  // 0x0C
    };
    // an entry of the table (0x18 bytes)
    struct Entry {
        unsigned char pad_0[0x8];
        unsigned int m_nameOfs;  // 0x08: the name, from the header
        unsigned int m_id;       // 0x0C
        unsigned char pad_10[0x8];
    };

    ~DrResEtcTexList();
    void releaseTexture();
    void release();
    grlib::CGLibTextureBuffer* getTextureID(unsigned int id);

    unsigned char pad_0[0x8];
    DrResEtcTexList* m_pNext;  // 0x08: DrMdoTextureMan's list link (the name is not the original's)
    grlib::CGLibTextureBuffer* m_texture;  // 0x10: m_num of them, in m_buf
    const Header* m_header;                // 0x18
    int m_num;                             // 0x20
    void* m_buf;                           // 0x28: the allocation (freed by releaseTexture)
    unsigned int m_flags;                  // 0x30: bit 0 released
};
}  // namespace ml

#endif
