#ifndef ML_DRSHDDATAOBJ_H
#define ML_DRSHDDATAOBJ_H

#include "grlib/CGLibDecShader.h"

namespace grlib { class CGLibVtxFetch; }

namespace ml {
class DrResFetch;

// One of DrShdDataList's shaders: a grlib::CGLibDecShader (setupShader/setupComputeShader pass `this` on as the
// CGLibDecShader& unchanged; grlib::CGLibShdListBase<DrShdDataObj> lists them like CGLibShdListData lists
// CGLibDecShaders) and the vertex fetches it draws with. DrShdDataList's arrays of them are 0x78 bytes apart.
class DrShdDataObj : public grlib::CGLibDecShader {
public:
    void setupShader(unsigned int fetch);
    void setupShader(DrResFetch* fetch);
    void setupComputeShader();

    grlib::CGLibVtxFetch* m_pFetch[2];  // 0x68 (the name is not the original's)
};
}  // namespace ml

#endif
