#ifndef ML_MDSMATTEXTUREINFO_H
#define ML_MDSMATTEXTUREINFO_H

namespace ml {

// One texture of a material (8 bytes: DrShdMdoDecExtTbl::setTextureList steps through an array of them). The field
// names are not the original's.
struct MdsMatTextureInfo {
    unsigned short m_texIdx;  // 0x0: the texture in the material's texture list
    unsigned short m_mipSamplerIdx;  // 0x2: the sampler a texture with mipmaps takes
    unsigned short m_samplerIdx;  // 0x4: the sampler otherwise
    unsigned char pad_6[0x2];
};

}  // namespace ml

#endif
