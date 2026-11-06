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
    unsigned char pad_18[0x2C];
};
}  // namespace ml

#endif
