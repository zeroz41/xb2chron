#ifndef ML_MDSMATTECHNIQUE_H
#define ML_MDSMATTECHNIQUE_H

namespace ml {
// One technique of a material resource (0x44 bytes: DrShdMdoDecShdObj's constructor steps through an array of them,
// one per shader of the list). The field names are not the original's.
struct MdsMatTechnique {
    unsigned int m_vtxInfoOfs;  // 0x0: its MdsMatVertexInfo array, from the material table data
    int m_vtxInfoNum;           // 0x4
    unsigned char pad_8[0x8];
    // 0x10: its stock variables (MdsMatVariableTbl), from MdoWrkMatRes::m_pTechData; DrMdoSetup::createUniformBlock
    // writes one per entry
    unsigned int m_varTblOfs;
    int m_varTblNum;  // 0x14
    // 0x18/0x1C: the static texture ids (unsigned shorts, from MdoWrkMatRes::m_pTechData) DrMdoSetup::setShader
    // binds through DrMdoSetup::s_pStaticTexture, and their count (names inferred)
    unsigned int m_staticTexOfs;
    unsigned int m_staticTexNum;
    // 0x20/0x24: the uniform block entries (MdsMatValShaderCate, from m_pTechData) setShader binds through
    // DrMdoSetup::s_pUniBkMat, and their count (names inferred)
    unsigned int m_uniBkOfs;
    int m_uniBkNum;
    unsigned char pad_28[0xC];
    // 0x34/0x38: the static image ids setShader binds through DrMdoSetup::s_pStaticImage, and their count (names
    // inferred)
    unsigned int m_staticImgOfs;
    unsigned int m_staticImgNum;
    unsigned char pad_3C[0x8];
};
}  // namespace ml

#endif
