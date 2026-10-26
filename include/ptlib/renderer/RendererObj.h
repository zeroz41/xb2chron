#ifndef PTLIB_RENDERER_RENDEREROBJ_H
#define PTLIB_RENDERER_RENDEREROBJ_H

#include "grlib/CGLibRenderTarget.h"
#include "ptlib/renderer/ShaderManager.h"

namespace ptlib { class DrDrawWorkInfoEF; class FxParam; class StaticAllocObj; }
namespace ptlib { namespace emitter { class EmitterManager; } }

namespace ptlib { namespace renderer {

// the renderer's own render targets, made in the renderer's block by createAll (the field names are not the
// original's: they follow the sizes and formats createAll gives them)
class BackBuffer {
public:
    ~BackBuffer() { release(); }
    // destroys the targets (inline in RenderGrObj::term and the destructor; the name is not the original's)
    void release() {
        if (m_pHalfColor != nullptr) {
            if (m_pHalfDepth != nullptr) {
                m_pHalfDepth->~CGLibRenderTarget();
            }
            if (m_pHalfColor != nullptr) {
                m_pHalfColor->~CGLibRenderTarget();
            }
            if (m_pTiny != nullptr) {
                m_pTiny->~CGLibRenderTarget();
            }
            if (m_pTiny2 != nullptr) {
                m_pTiny2->~CGLibRenderTarget();
            }
            m_pHalfColor = nullptr;
            m_pTiny = nullptr;
            m_pHalfDepth = nullptr;
            m_pTiny2 = nullptr;
            m_isReleased = true;
        }
    }
    void createAll(StaticAllocObj* pAlloc, float width, float height, float width2, float height2,
                   unsigned int offset);

    grlib::CGLibRenderTarget* m_pHalfColor;  // 0x00: half the screen, format 5
    unsigned char pad_8[0x8];
    grlib::CGLibRenderTarget* m_pTiny;       // 0x10: 8x8, format 1
    grlib::CGLibRenderTarget* m_pHalfDepth;  // 0x18: half the screen, format 0x3F
    grlib::CGLibRenderTarget* m_pTiny2;      // 0x20: 8x8, format 0x26
    bool m_isReleased;                        // 0x28
};

// the renderer's graphics objects (particle_renderer_obj.cpp)
class RenderGrObj {
public:
    ~RenderGrObj();
    void term();
    BackBuffer* getBackBuffer();
    void fxcore_setup_target_update(int view);
    void draw(emitter::EmitterManager& manager, FxParam& param, int view, int pass);
    void drawKizunaLine(int view);
    void drawSortAndNormal(emitter::EmitterManager& manager, int view, FxParam& param, int pass);
    void draw_capture();

    BackBuffer m_backBuffer;  // 0x0
    unsigned char pad_30[0x80];
    ShaderManager m_shaderManager;  // 0xB0: the effect shaders (the name is not the original's)
    unsigned char pad_250[0x8];
    const DrDrawWorkInfoEF* m_pDrInfo;  // 0x258: RenderManager::setDrInfo writes it
    unsigned char pad_260[0x8];
    StaticAllocObj* m_pAlloc;  // 0x268: the block createAll makes the targets in
    int m_blendState;          // 0x270: draw and draw_capture reset it (the name is not the original's)
    unsigned char pad_274[0xC];
};

}}  // namespace ptlib::renderer

#endif
