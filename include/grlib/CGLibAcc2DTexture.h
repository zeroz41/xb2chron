#ifndef GRLIB_CGLIBACC2DTEXTURE_H
#define GRLIB_CGLIBACC2DTEXTURE_H

#include "grlib/CGLibAccUtilTexture.h"

namespace grlib { class CGLibTextureBuffer; }

namespace grlib {

// access to a 2D texture's texels while locked (0xB0 bytes: lock stores the buffer at 0xA8). Field names are
// not the original's.
class CGLibAcc2DTexture : public CGLibAccUtilTexture {
public:
    CGLibAcc2DTexture();
    ~CGLibAcc2DTexture();
    bool lock(CGLibTextureBuffer& buffer);
    void unlock();
    // the texel at x, y set to value
    void setInt(int value, unsigned int x, unsigned int y);
    // the first channel of the texel at x, y (2.0.0 names it; 3.0.1's callers inline it)
    void getFloat(float& value, unsigned int x, unsigned int y);

    void* m_pUnused[2];                // 0x90: zeroed by the constructor, read by nothing (3.0.1 or 1.0.0)
    bool m_isLock;                     // 0xA0
    bool m_isWrite;                    // 0xA1: unlock flushes the texture's memory
    bool m_unusedFlag;                 // 0xA2: zeroed by the constructor, read by nothing
    CGLibTextureBuffer* m_pBuffer;     // 0xA8
};

}  // namespace grlib

#endif
