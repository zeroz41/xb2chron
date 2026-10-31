#ifndef ML_DRSHDMDODECEXTTBL_H
#define ML_DRSHDMDODECEXTTBL_H

#include "grlib/CGLibDecShader.h"

namespace ml {
class DrShdFetchObj;
class DrShdFetchMan;
struct MdsMatVertexInfo;

// A model material's shader (0x70 bytes: grlib::CGLibShdListBase<DrShdMdoDecRes> steps its list by it) and its
// vertex fetch. The constructor and destructor are inline in 3.0.1 (out of line in 1.0.0). The name of the field is
// not the original's.
class DrShdMdoDecRes : public grlib::CGLibDecShader {
public:
    DrShdMdoDecRes() : m_pFetchObj(nullptr) {}
    ~DrShdMdoDecRes() { releaseObj(); }
    // releases the shader and hands the vertex fetch back to DrShdFetchMan
    void releaseObj();
    void setVertexParam(DrShdFetchMan* fetchMan, int num, const MdsMatVertexInfo* info);

    DrShdFetchObj* m_pFetchObj;  // 0x68, the vertex fetch setVertexParam takes from DrShdFetchMan
};

// A material shader's extension table (setupShderInfo stores its DrShdMdoDecRes). The field names are not the
// original's.
class DrShdMdoDecExtTbl : public grlib::CGLibDecShdExtTbl {
public:
    unsigned int getValGlobalParam(int idx);
    void bindShader();

    DrShdMdoDecRes* m_pRes;  // 0x18
    unsigned char pad_20[0x8];
    unsigned int* m_pValGlobalParam;  // 0x28
};
}  // namespace ml

#endif
