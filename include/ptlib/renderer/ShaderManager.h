#ifndef PTLIB_RENDERER_SHADERMANAGER_H
#define PTLIB_RENDERER_SHADERMANAGER_H

#include "classes/grlib/CGLibShdListData.h"
#include "ptlib/ParticleSystem.h"

namespace ptlib { namespace renderer {

// which effect shader (ScreenRenderManager draws with 7 and 15); no value has a name yet
enum EffShdType {};

// the effect library's shaders (particle_renderer_obj.cpp's RenderGrObj keeps one)
class ShaderManager {
public:
    // the offsets of a shader's declarations, by the names init asks for (the field names are not the original's)
    struct DeclOfs {
        unsigned int m_veriationMode;    // "VERIATION_MODE"
        unsigned int m_softMode;         // "SOFT_MODE"
        unsigned int m_shadowMode;       // "SHADOW_MODE"
        unsigned int m_clipMode;         // "CLIP_MODE"
        unsigned int m_usingTemporalAA;  // "USING_TEMPORAL_AA"
    };

    ~ShaderManager() { m_shdList.release(); }
    void init();
    // releases the shaders and frees the package (inline in RenderGrObj::term; the name is not the original's)
    void term() {
        m_shdList.release();
        if (m_pFile != nullptr) {
            ParticleManager::resFree(m_pFile);
            m_pFile = nullptr;
        }
    }
    grlib::CGLibDecShader* getShaderByIndex(EffShdType type);

    void* m_pFile;                     // 0x0: "/effect/shader/shd_effect.wishp"
    grlib::CGLibShdListData m_shdList;  // 0x8: getShaderByIndex's, by EffShdType
    DeclOfs m_declOfs[16];             // 0x60
};

}}  // namespace ptlib::renderer

#endif
