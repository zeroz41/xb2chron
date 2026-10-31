#ifndef ML_MDSMATVARIABLETBL_H
#define ML_MDSMATVARIABLETBL_H

namespace ml {
// One stock material variable of a material (DrMdoSetup::s_pStockMaterial's unimate_ callbacks are given it). Only
// the fields the callbacks read are known; the size and the field names are not the original's.
struct MdsMatVariableTbl {
    unsigned short pad_0;
    // 0x2: the first value's slot (from MdsMatInfoHeader::m_uniformOfs) in MdoWrkMatRes::m_pUniformVal, or the
    // material's texture entry (unimate_DollTexWork)
    unsigned short m_valIdx;
    unsigned short pad_4;
    unsigned short m_num;  // 0x6: number of values (unimate_texMatrix copies 8 floats per value)
};
}  // namespace ml

#endif
