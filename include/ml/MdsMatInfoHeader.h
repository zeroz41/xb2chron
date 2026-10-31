#ifndef ML_MDSMATINFOHEADER_H
#define ML_MDSMATINFOHEADER_H

namespace ml {
// One material's header in a model resource (0x74 bytes: DrMdoMat::updateMatCallBack steps through an array of
// them). Only the fields DrMdoMat's material callbacks read are known; the field names are not the original's.
struct MdsMatInfoHeader {
    unsigned char pad_0[0x4];
    // 0x04, bit 15: the shadow and pre-pass shader setters pick the second fetch table (DrMdoShdSetShadow::
    // s_pShwFethcTbl[1], 1.0.0's s_pShwFethcMof) and pass 1 to DrResShdPrePass::setupShader (name inferred)
    unsigned int m_shdFlags;
    unsigned char pad_8[0x1];
    unsigned char m_flags;  // 0x09, DrMdoSetup::varStTex_DitherTex tests bit 2
    unsigned char pad_A[0x2];
    float m_color[4];  // 0x0C, scaled by DrMdoMat::matCall_CalcColor
    // 0x1C, the shadow and pre-pass *T setters pass it to DrShdDataList::getAlphaTestUniform (name inferred)
    float m_alphaRef;
    // 0x20, from MdoWrkMatRes::m_pMatData: this material's MdsMatTexEntry list; DrMdoSetup::unimate_DollTexWork
    // indexes it by MdsMatVariableTbl::m_valIdx (name inferred)
    unsigned int m_texEntryOfs;
    unsigned char pad_24[0x1C];
    unsigned int m_uniformOfs;  // 0x40, this material's first slot in MdoWrkMatRes::m_pUniformVal
    unsigned char pad_44[0x12];
    // 0x56: this material's entry in MdoWrkMatRes::m_pAvatarMap (DrMdoSetup::unimate_AvatarMapWrk; name inferred)
    unsigned short m_avatarMapIdx;
    unsigned short m_callBackIdx;  // 0x58, first (callback, slot) pair of the material's list
    unsigned short m_callBackNum;  // 0x5A, number of pairs
    unsigned char pad_5C[0x6];
    // 0x62, the texture entry DrMdoShdSet::setOneTexShaderSet binds (name inferred)
    unsigned short m_texEntryIdx;
    unsigned short m_timeSlot;  // 0x64, uniform slot (from m_uniformOfs) of the time the *Time callbacks scale by
    unsigned char pad_66[0xE];
};
}  // namespace ml

#endif
