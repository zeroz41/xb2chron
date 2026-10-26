#ifndef CLASSES_ML_DRAPCACHE_H
#define CLASSES_ML_DRAPCACHE_H

namespace grlib { class CGLibDecShdExtTbl; class CGLibSampler; class CGLibTextureBuffer; }

namespace ml {
class DrResFetch;

// the culling setupCulling selects (0 back, 1 front, 2 off, other: no display); no value has a name yet
enum DrApCullType {};

// table 0x7100B7E928
class DrAPCache {
public:
    DrAPCache() {
        s_pIns = this;
        m_pSampler = 0;
        createSampler();
        begin();
    }
    virtual ~DrAPCache() {}  // slot 0

    void createSampler();
    void depthBegin();
    void beginZRender();
    void beginThicknessRenderFirst();
    void beginThicknessRenderSecond();
    void beginMdlZRender();
    void setMrtGBuffRender(unsigned int render, unsigned int mrt);
    void setupCulling(DrApCullType type);
    void setupDepthStencil(int stencilRef, int stencilMode, int depthWrite, int depthMode);
    void setupAlphaBlend(int blend);
    void setupShader(grlib::CGLibDecShdExtTbl* table, DrResFetch* fetch);

    static DrAPCache* s_pIns;
    // texture formats DrPixlMan's render targets use (the type is not known: 4-byte values)
    static const int TEXTYPE_R_8;
    static const int TEXTYPE_R_UI8;
    static const int TEXTYPE_RGBA_8;
    static const int TEXTYPE_RGB_5;
    static const int TEXTYPE_RGB_11;
    static const int TEXTYPE_RGB10A2_UNORM;
    static const int TEXTYPE_HALF_X1;
    static const int TEXTYPE_HALF_X4;
    static const int TEXTYPE_FLOAT_X1;
    static const int TEXTYPE_FLOAT_X2;
    static const int TEXTYPE_R_UI32;
    static const int TEXTYPE_RG_UI32;

    void endZRender();
    void shadowBegin();  // DrPixlMan::shadowDirBegin
    void endThicknessRenderFirst();
    void endThicknessRenderSecond();
    void endMdlZRender();
    void endGBuffRender();
    void setRefractionRender();
    void endRefractionRender();
    void setTexture(const grlib::CGLibTextureBuffer& texture, const grlib::CGLibSampler& sampler, unsigned int location);
    void begin();
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
    int m_alphaBlend;  // 0x08: setupAlphaBlend's cached value
    int pad_C;  // begin and setupAlphaBlend set it to -1
    int m_cullType;  // 0x10: setupCulling's cached value
    int m_stencilRef;  // 0x14: setupDepthStencil's cached values
    int m_stencilMode;  // 0x18
    int m_depthWrite;  // 0x1C
    unsigned int m_gBuffRender;  // 0x20: setGBuffRender's / setMrtGBuffRender's cached value
    int m_depthMode;  // 0x24: setupDepthStencil's last argument
    int pad_28;  // begin sets it to -1
    unsigned char pad_2C[0x4];
    grlib::CGLibSampler* m_pSampler;  // 0x30: setTexture's sampler table
    unsigned short m_texSampling[2];  // 0x38: beginTexSampling's first argument (both)
    unsigned short m_texWrap;  // 0x3C: beginTexSampling's second argument
    unsigned short m_mipMap;  // 0x3E: setMipMapOn
    unsigned short m_specialSampler;  // 0x40: the 3D/cube/depth-compare/border sampler (0 = none)
    unsigned short m_specialSamplerKind;  // 0x42: 1 for the 3D samplers, 2 for the cube samplers
};
}  // namespace ml

#endif
