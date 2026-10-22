#ifndef PTLIB_RENDERER_RENDERERSTREAM_H
#define PTLIB_RENDERER_RENDERERSTREAM_H

namespace ptlib { class StaticAllocObj; }

namespace ptlib { namespace renderer {

// the renderer's shared sampler, vertex fetch and index state (particle_renderer_stream.cpp)
class EffStateManager {
public:
    EffStateManager();
    ~EffStateManager();
    static EffStateManager* get();
    void init(StaticAllocObj* pAlloc);
};

}}  // namespace ptlib::renderer

#endif
