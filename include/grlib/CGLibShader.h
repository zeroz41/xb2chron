#ifndef GRLIB_CGLIBSHADER_H
#define GRLIB_CGLIBSHADER_H

#include "nvn/nvn.h"

namespace grlib {

// one shader program (0xD8 bytes): where its textures and uniform blocks are bound
class CGLibShader {
public:
    unsigned int getTextureLocation(const char* name) const;
    unsigned int getUniformBlockOfs(const char* name) const;

    unsigned char pad_0[0x14];
    // the stages the program holds and the NVN program CGLibCtlShader::setShader binds (the names are not the
    // original's)
    unsigned int m_stages;  // 0x14
    NVNprogram m_program;  // 0x18
};

}  // namespace grlib

#endif
