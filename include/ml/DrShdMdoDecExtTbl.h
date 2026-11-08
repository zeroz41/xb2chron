#ifndef ML_DRSHDMDODECEXTTBL_H
#define ML_DRSHDMDODECEXTTBL_H

#include "grlib/CGLibDecShader.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrShdFetchObj;
class DrShdMdoDecShdObj;
class DrResMdoSampler;
struct MdsMatTechnique;
struct MdsMatTextureInfo;
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
    void setupShderInfo(DrShdMdoDecRes* res, const MdsMatTechnique* tech, const unsigned char* tblData);
    unsigned int getValGlobalParam(int idx);
    void bindShader();
    void setTextureList(const MdsMatTextureInfo* info, grlib::CGLibTextureBuffer** textures, DrResMdoSampler* sampler);

    DrShdMdoDecRes* m_pRes;  // 0x18
    unsigned int* m_pTexLocation;  // 0x20, a location per texture setTextureList binds
    unsigned int* m_pValGlobalParam;  // 0x28
    // 0x30: the parameter indices of global parameter types 10, 11, 12, 27, 28 and 29
    unsigned char m_paramIdx[6];
    unsigned char m_texNum;  // 0x36
    unsigned char pad_37[0x1];
};

// A material's extension tables: one DrShdMdoDecExtTbl per shader of the shader object, followed by their value
// area (getDecWorkSize bytes of work). The field names are not the original's.
class DrShdMdoExtTblObj {
public:
    static int getDecWorkSize(int valNum, const unsigned char* pac);
    int setDecObj(DrShdMdoDecShdObj* shdObj, unsigned char* work, const unsigned char* tblData, int valNum,
                  const MdsMatTechnique* tech, const unsigned char* pac);

    DrShdMdoDecShdObj* m_pShdObj;  // 0x0
    DrShdMdoDecExtTbl* m_pExtTbl;  // 0x8
};
}  // namespace ml

#endif
