#ifndef ML_DRRESMDOTEXSIMPLE_H
#define ML_DRRESMDOTEXSIMPLE_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {
// A simple texture resource; DrMdoTexSimpleMan keeps them in lists. Only what DrMdoTexSimpleMan uses is recovered.
class DrResMdoTexSimple {
public:
    ~DrResMdoTexSimple();
    void createTex();

    // 0x0/0x8: DrMdoTexSimpleMan's list links (the names are not the original's)
    DrResMdoTexSimple* m_pPrev;  // 0x0
    DrResMdoTexSimple* m_pNext;  // 0x8
    // Field and flag names below are not the original's.
    enum {
        FLAG_CREATED = 1 << 0,  // createTex
        FLAG_CLEAR_MASK = 0xD,  // the destructor clears these
    };
    grlib::CGLibTextureBuffer m_tex;  // 0x10
    const void* m_image;              // 0x80: createTex's image
    unsigned int m_imageSize;         // 0x88
    unsigned int m_flags;             // 0x8C
};
}  // namespace ml

#endif
