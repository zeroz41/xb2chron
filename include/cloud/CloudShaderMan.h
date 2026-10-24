#ifndef CLOUD_CLOUDSHADERMAN_H
#define CLOUD_CLOUDSHADERMAN_H

#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibVtxFetch.h"

namespace cloud {
// which shader of CloudShaderMan's list; the enumerators are not known
enum CloudShaderType {};

// CloudMan's shader list (no virtual table: its destructor is not in any table)
class CloudShaderMan {
public:
    grlib::CGLibDecShader* selectRenderPlane(CloudShaderType type, unsigned int lvNum, unsigned int holeMode,
                                             unsigned int blndMode);
    grlib::CGLibDecShader* selectDebug(CloudShaderType type, unsigned int debugMode, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectColor(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectShadow(CloudShaderType type, unsigned int shadowOn, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectRenderSky(CloudShaderType type, unsigned int lvNum, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectMdlSphere(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectDetailMap(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectGlbFog(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectOutput(CloudShaderType type, unsigned int outMode, unsigned int earlyZOn,
                                        unsigned int);
    grlib::CGLibDecShader* selectBlur(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectPlnDepth(CloudShaderType type, unsigned int, unsigned int, unsigned int);
    grlib::CGLibDecShader* selectUpScale(CloudShaderType type, unsigned int, unsigned int, unsigned int);

    // the vertex fetch each shader type is drawn with
    static unsigned int s_reShdFtxTbl[];

    // the names below are not the original's
    unsigned char pad_0[0x48];
    grlib::CGLibDecShader* m_pShaders;  // 0x48, one per CloudShaderType
    unsigned char pad_50[0x18];
    grlib::CGLibVtxFetch m_vtxFetch[4];  // 0x68, by s_reShdFtxTbl
};
}  // namespace cloud

#endif
