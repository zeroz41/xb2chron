#ifndef PTLIB_RENDERER_RENDERERMANAGER_H
#define PTLIB_RENDERER_RENDERERMANAGER_H

namespace ptlib { class DrDrawWorkInfoEF; class FxParam; class StaticAllocObj; }
namespace ptlib { namespace renderer { class EffStateManager; class RenderGrObj; } }

namespace ptlib { namespace renderer {

// the particle renderer's root: one instance, made by init in a block of its own (particle_renderer_manager.cpp)
class RenderManager {
public:
    // the instance; asserts that there is one
    static RenderManager* get();
    // the slot that holds the instance, null before init and after term
    static RenderManager*& getPtr();
    static void init(const DrDrawWorkInfoEF* pDrInfo, FxParam* pFxParam);
    void setDrInfo(const DrDrawWorkInfoEF* pDrInfo);
    static void term();
    RenderGrObj* getRenderGrObj();

    FxParam* m_pFxParam;
    RenderGrObj* m_pGrObj;
    StaticAllocObj* m_pAlloc;  // the block everything below lives in; term destroys it
    EffStateManager* m_pEffState;
};

}}  // namespace ptlib::renderer

#endif
