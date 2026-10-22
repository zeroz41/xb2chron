#ifndef PTLIB_RENDERER_SCREENRENDERMANAGER_H
#define PTLIB_RENDERER_SCREENRENDERMANAGER_H

#include "grlib/CGLibSampler.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxFetch.h"

namespace grlib { class CGLibTextureBuffer; }
namespace mm { class Col4; class Mat44; class Vec3; class Vec4; }
namespace ptlib { class DrDrawWorkInfoEF; class StaticAllocObj; }
namespace ptlib { namespace material { class MaterialTexture; } }

namespace ptlib { namespace screen {

// draws full-screen quads for the effect library: one instance, made by init in a block of its own
// (screen_render_manager.cpp)
class ScreenRenderManager {
public:
    ScreenRenderManager() : m_pAlloc(nullptr) {}

    static void init();
    // the slot that holds the instance, null before init and after term
    static ScreenRenderManager*& getPtr();
    // the quad's buffers and samplers, in alloc's block
    void InitSub(StaticAllocObj* alloc);
    static void term();
    static bool isValid();
    // the texture over the screen rectangle rect (x, y, width, height in its first row), tinted
    void RenderScreen(const DrDrawWorkInfoEF* pDrInfo, const mm::Mat44& rect, const mm::Vec3& position,
                      const mm::Col4& color, const grlib::CGLibTextureBuffer* texture, bool blend, mm::Vec4 param);
    void RenderCapScreen(const DrDrawWorkInfoEF* pDrInfo, const grlib::CGLibTextureBuffer* texture0,
                         const grlib::CGLibTextureBuffer* texture1);
    void RenderScreenDebug(const DrDrawWorkInfoEF* pDrInfo, const mm::Mat44& rect, const mm::Vec3& position,
                           const mm::Col4& color, material::MaterialTexture* texture, bool blend, mm::Vec4 param);
    void RenderSeparate(const DrDrawWorkInfoEF* pDrInfo);

    // the field names are not the original's
    grlib::CGLibSampler m_samplers[4];
    grlib::CGLibVtxVertex m_vertex;  // the quad's four corners
    grlib::CGLibVtxIndex m_index;
    grlib::CGLibVtxFetch m_fetch;
    StaticAllocObj* m_pAlloc;  // the block it lives in; term destroys it
};

}}  // namespace ptlib::screen

#endif
