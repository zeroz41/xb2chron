#ifndef GRLIB_CGLIBSHADER_H
#define GRLIB_CGLIBSHADER_H

namespace grlib {

// one shader program (0xD8 bytes): where its textures and uniform blocks are bound
class CGLibShader {
public:
    unsigned int getTextureLocation(const char* name) const;
    unsigned int getUniformBlockOfs(const char* name) const;

    unsigned char pad_0[0xD8];
};

}  // namespace grlib

#endif
