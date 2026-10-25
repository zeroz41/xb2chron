#ifndef CLASSES_ML_DRAPCACHE_H
#define CLASSES_ML_DRAPCACHE_H

namespace grlib { class CGLibSampler; class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B7E928
class DrAPCache {
public:
    virtual ~DrAPCache() {}  // slot 0

    void endZRender();
    void shadowBegin();  // DrPixlMan::shadowDirBegin
    void endThicknessRenderFirst();
    void endThicknessRenderSecond();
    void endMdlZRender();
    void endGBuffRender();
    void setRefractionRender();
    void endRefractionRender();
    void setTexture(const grlib::CGLibTextureBuffer& texture, const grlib::CGLibSampler& sampler, unsigned int location);
    void beginTexSampling(int, int);
    void beginCubeTextureSampling(bool);
    void begin3DTextureSampling();
    void begin3DTexturePointSampling();
    void begin3DTextureWarpSampling();
    void beginCubeTexturePointSampling(bool);
    void beginDepthCompare();
    void beginBorderWhite();
    void beginBorderBlack();
    void beginBorderDepthMax();
    void beginBorderDepthMinusMax();
    void setGBuffRender(unsigned int);
    void setMipMapOn(const grlib::CGLibTextureBuffer& texture);
    void setTexture(const grlib::CGLibTextureBuffer& texture, unsigned int location);

    // The field names are not the original's: they follow the functions that write them.
    unsigned char pad_8[0x8];
    int m_cullType;  // 0x10: setupCulling's cached value
    unsigned char pad_14[0xC];
    unsigned int m_gBuffRender;  // 0x20: setGBuffRender's cached value
    unsigned char pad_24[0xC];
    grlib::CGLibSampler* m_pSampler;  // 0x30: setTexture's sampler table
    unsigned short m_texSampling[2];  // 0x38: beginTexSampling's first argument (both)
    unsigned short m_texWrap;  // 0x3C: beginTexSampling's second argument
    unsigned short m_mipMap;  // 0x3E: setMipMapOn
    unsigned short m_specialSampler;  // 0x40: the 3D/cube/depth-compare/border sampler (0 = none)
    unsigned short m_specialSamplerKind;  // 0x42: 1 for the 3D samplers, 2 for the cube samplers
};
}  // namespace ml

#endif
