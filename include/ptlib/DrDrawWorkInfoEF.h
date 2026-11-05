#ifndef PTLIB_DRDRAWWORKINFOEF_H
#define PTLIB_DRDRAWWORKINFOEF_H

namespace grlib { class CGLibRenderTarget; }

namespace ptlib {

// what the effect library draws with: the frame's render targets and the screen's size (only what
// ScreenRenderManager reads is here; the names are not the original's, the ones of the targets follow the shader
// textures RenderSeparate binds them to)
class DrDrawWorkInfoEF {
public:
    grlib::CGLibRenderTarget* m_pTarget;  // RenderSeparate draws to it
    unsigned char pad_8[0x10];
    grlib::CGLibRenderTarget* m_pDownDepth;  // "dwnDep"
    grlib::CGLibRenderTarget* m_pOrgDepth;   // "orgDep"
    unsigned char pad_28[0x18];
    grlib::CGLibRenderTarget* m_pTarget1;  // RenderSeparate's second target, with m_pDepthBloom
    unsigned char pad_48[0x10];
    grlib::CGLibRenderTarget* m_pTarget2;  // RenderSeparate's last target when there is one
    grlib::CGLibRenderTarget* m_pCapture;  // 0x60: RenderGrObj::draw_capture draws the captured screen to it
    grlib::CGLibRenderTarget* m_pDepthColor;  // "depCol"; its size is the separation's
    grlib::CGLibRenderTarget* m_pDepthBloom;  // "depBlm", none without bloom
    unsigned char pad_78[0x158];
    unsigned int m_effectBufOfs;  // 0x1D0: where BackBuffer::createAll puts its textures in the pool
    unsigned char pad_1D4[0x370];
    float m_fadeFrames;  // 0x544: RenderGrObj::draw_common_uparam's divisor (the name is not the original's)
    unsigned char pad_548[0x8];
    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
    unsigned char pad_558[0x8];
    // the view being drawn: 0 is the main one, the only one effect::SystemManager runs its commands for (the name is
    // not the original's)
    int m_view;
    unsigned char pad_564[0xC];
    bool* m_pCaptured;  // 0x570: RenderGrObj::draw_capture sets it
};

}  // namespace ptlib

#endif
