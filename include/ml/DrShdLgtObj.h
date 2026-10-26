#ifndef ML_DRSHDLGTOBJ_H
#define ML_DRSHDLGTOBJ_H

#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibDecShader.h"

namespace mm { class Mat44; }

namespace ml {
class DrMan;
class DrResFetch;

// One of DrShdLgtMan's light shaders (0x158 bytes: grlib::CGLibShdListBase<DrShdLgtObj> steps its list by it): a
// declared shader and four double-buffered uniform blocks. The constructor and destructor are inline (the list's
// createPacShader and release build and destroy them in place). The field names are not the original's.
class DrShdLgtObj : public grlib::CGLibDecShader {
public:
    DrShdLgtObj() {
        m_uniformIdx[0] = -1;
        m_uniformIdx[1] = -1;
    }
    ~DrShdLgtObj() { lgtRelease(); }
    // releases the uniform blocks and the shader (inline in 3.0.1; 1.0.0 has it out of line)
    void lgtRelease() {
        m_uniform[0].release();
        m_uniform[1].release();
        m_uniform[2].release();
        m_uniform[3].release();
        m_uniformIdx[0] = -1;
        m_uniformIdx[1] = -1;
        release();
    }
    void shaderSetup(DrResFetch* fetch);
    void setShaderGlobalIBLIndexVS(DrMan* drMan, const mm::Mat44& mtx, unsigned char* buff, unsigned int size);

    grlib::CGLibDblUniformBlock m_uniform[4];  // 0x68
    long m_uniformIdx[2];  // 0x148, -1 while not set up
};
}  // namespace ml

#endif
