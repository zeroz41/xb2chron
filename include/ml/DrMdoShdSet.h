#ifndef ML_DRMDOSHDSET_H
#define ML_DRMDOSHDSET_H

namespace ml {
class DrMdlObj;
class DrShdDataList;
struct MdoWrkMatRes;
struct MdsMatInfoHeader;

// The model shader setters' base (1.0.0 names DrMdoShdSet::setOneTexShaderSet; the derived setters pass their own
// this). Only what is written so far is declared; field names are not the original's.
class DrMdoShdSet {
public:
    void setOneTexShaderSet(int texEntry, unsigned int location);

    DrMdlObj* m_pMdl;            // 0x0: the model being drawn; its m_curShaderIdx caches the last shader set
    MdoWrkMatRes* m_pWrkMatRes;  // 0x8
};

// The pre-pass shader setters (preshd_*).
class DrMdoShdSetPrePass : public DrMdoShdSet {
public:
    // Passed through to DrResShdPrePass::setupShader; the values are not recovered.
    enum PrePassType {};

    void preshd_Obj(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list, PrePassType type);
    void preshd_Inst(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list, PrePassType type);
    void preshd_InstT(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list, PrePassType type);
};

// The shadow shader setters (shwShd_*). The tables are indexed by the shader number the setters get.
class DrMdoShdSetShadow : public DrMdoShdSet {
public:
    void shwShd_Obj(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list);
    void shwShd_Inst(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list);
    void shwShd_InstT(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list);

    static const unsigned char s_pShwUseShdader[30];  // DrShdDataList::getShwObj index
    static const unsigned char s_pShwFethcDef[30];    // DrShdDataList::getFetchShader index
    static const unsigned char s_pShwFethcMof[30];    // the same while MdsMatInfoHeader::m_shdFlags bit 15 is set
    static const unsigned char s_pShwTypeDec[30];     // high nibble: setDecAType, low nibble: setDecBType
    static const unsigned char* s_pShwFethcTbl[2];    // s_pShwFethcDef, s_pShwFethcMof
};
}  // namespace ml

#endif
