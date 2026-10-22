#ifndef PTLIB_RENDERER_RENDEREROBJ_H
#define PTLIB_RENDERER_RENDEREROBJ_H

#include "ptlib/renderer/ShaderManager.h"

namespace ptlib { class DrDrawWorkInfoEF; }

namespace ptlib { namespace renderer {

// the renderer's graphics objects (particle_renderer_obj.cpp)
class RenderGrObj {
public:
    ~RenderGrObj();
    void term();

    unsigned char pad_0[0xB0];
    ShaderManager m_shaderManager;  // the effect shaders (the name is not the original's)
    unsigned char pad_100[0x158];
    const DrDrawWorkInfoEF* m_pDrInfo;  // RenderManager::setDrInfo writes it
    unsigned char pad_260[0x20];
};

}}  // namespace ptlib::renderer

#endif
