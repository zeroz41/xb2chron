#ifndef GRLIB_CGLIBDECSHADER_H
#define GRLIB_CGLIBDECSHADER_H

#include "grlib/CGLibShader.h"

namespace grlib {

// a shader with declarations (0x68 bytes): its programs by the declarations' current values
class CGLibDecShader {
public:
    unsigned int getDeclarationOfs(const char* name) const;
    void setDeclarationIdx(unsigned int ofs, unsigned int idx);
    // the program the declarations select (inline: the name is not the original's)
    CGLibShader& getCurrentShader() { return *(m_pShaders + m_current); }
    const CGLibShader& getCurrentShader() const { return *(m_pShaders + m_current); }

    unsigned char pad_0[0x38];
    CGLibShader* m_pShaders;
    unsigned char pad_40[0x18];
    unsigned int m_current;  // the index of the program the declarations select
    unsigned char pad_5c[0xC];
};

// a shader table entry: a declared shader and the program it selects (the field names are not the original's; the
// size is not known)
class CGLibDecShdExtTbl {
public:
    CGLibDecShader* m_pDecShader;  // 0x0
    unsigned int m_current;  // 0x8
};

}  // namespace grlib

#endif
