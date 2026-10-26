#ifndef ML_DRSHDMDODECEXTTBL_H
#define ML_DRSHDMDODECEXTTBL_H

#include "grlib/CGLibDecShader.h"

namespace ml {
class DrShdFetchObj;

// A model material's shader resources (only what DrShdMdoDecExtTbl::bindShader reads is declared; the name of the
// field is not the original's).
class DrShdMdoDecRes {
public:
    unsigned char pad_0[0x68];
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
