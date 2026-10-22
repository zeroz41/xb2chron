#ifndef PTLIB_RENDERER_SHADERMANAGER_H
#define PTLIB_RENDERER_SHADERMANAGER_H

namespace grlib { class CGLibDecShader; }

namespace ptlib { namespace renderer {

// which effect shader (ScreenRenderManager draws with 7 and 15); no value has a name yet
enum EffShdType {};

// the effect library's shaders (particle_renderer_obj.cpp's RenderGrObj keeps one)
class ShaderManager {
public:
    void init();
    grlib::CGLibDecShader* getShaderByIndex(EffShdType type);

    unsigned char pad_0[0x48];
    grlib::CGLibDecShader* m_pShaders;  // getShaderByIndex's, by EffShdType
};

}}  // namespace ptlib::renderer

#endif
