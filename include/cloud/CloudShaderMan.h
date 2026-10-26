#ifndef CLOUD_CLOUDSHADERMAN_H
#define CLOUD_CLOUDSHADERMAN_H

#include "classes/grlib/CGLibShdListData.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibVtxFetch.h"

namespace grlib { class CGLibTextureBuffer; }

namespace cloud {
// which shader of CloudShaderMan's list; the enumerators are not known
enum CloudShaderType {};
// which of CloudShaderMan's samplers; the enumerators are not known
enum CloudSamplerType {};

// CloudMan's shader list (no virtual table: its destructor is not in any table)
class CloudShaderMan {
public:
    CloudShaderMan();
    ~CloudShaderMan();
    void releaseShader();
    void update();
    void createShader();
    void setTexture(unsigned int location, const grlib::CGLibTextureBuffer& texture, CloudSamplerType type);
    grlib::CGLibDecShader* setShader(CloudShaderType type, unsigned int declIdx0, unsigned int declIdx1,
                                     unsigned int declIdx2);
    grlib::CGLibDecShader* selectRenderPlane(CloudShaderType type, unsigned int lvNum, unsigned int holeMode,
                                             unsigned int blndMode);
    grlib::CGLibDecShader* selectDebug(CloudShaderType type, unsigned int debugMode, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectColor(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectParticles(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectShadow(CloudShaderType type, unsigned int shadowOn, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectRenderSky(CloudShaderType type, unsigned int lvNum, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectMdlSphere(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectDetailMap(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectGlbFog(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectOutput(CloudShaderType type, unsigned int outMode, unsigned int earlyZOn,
                                        unsigned int);
    grlib::CGLibDecShader* selectDownDepth(CloudShaderType type, unsigned int sampleType, unsigned int,
                                           unsigned int);
    grlib::CGLibDecShader* selectBlur(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectCounter(CloudShaderType type, unsigned int mdlCalc, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectPlnDepth(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectUpScale(CloudShaderType type, unsigned int, unsigned int, unsigned int);

    typedef grlib::CGLibDecShader* (CloudShaderMan::*SelectFunc)(CloudShaderType, unsigned int, unsigned int,
                                                                 unsigned int);
    // setShader's select function of each shader type
    static SelectFunc s_CallSelect[16];
    // the vertex fetch each shader type is drawn with
    static unsigned int s_reShdFtxTbl[16];

    // the names below are not the original's
    unsigned int* m_pShdWork;            // 0x0, createShader allocates a word per shader (its use is not known)
    grlib::CGLibShdListData m_shdList;   // 0x8
    bool m_isEnable;                     // 0x60, set by the constructor (its use is not known)
    grlib::CGLibVtxFetch m_vtxFetch[4];  // 0x68, by s_reShdFtxTbl
    grlib::CGLibSampler m_samplers[8];   // 0xA8, by CloudSamplerType
};
}  // namespace cloud

#endif
