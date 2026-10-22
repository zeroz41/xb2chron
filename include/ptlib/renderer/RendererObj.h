#ifndef PTLIB_RENDERER_RENDEREROBJ_H
#define PTLIB_RENDERER_RENDEREROBJ_H

namespace ptlib { class DrDrawWorkInfoEF; }

namespace ptlib { namespace renderer {

// the renderer's graphics objects (particle_renderer_obj.cpp)
class RenderGrObj {
public:
    ~RenderGrObj();
    void term();

    unsigned char pad_0[0x258];
    const DrDrawWorkInfoEF* m_pDrInfo;  // RenderManager::setDrInfo writes it
    unsigned char pad_260[0x20];
};

}}  // namespace ptlib::renderer

#endif
