#ifndef ML_MDSFIXANM_H
#define ML_MDSFIXANM_H

namespace ml {
// One hermite key of a material's fixed animation, 0x10 bytes: MdoWrkMatRes::m_pFixAnmKey holds them, an
// MdsFixAnmInf's run starts at its m_keyIdx (DrMdoAnim::getHermiteAttr). The type and field names are not the
// original's.
struct MdsFixAnmKey {
    float m_outTangent;      // 0x0: weighs t^3 - 2t^2 + t towards the next key
    float m_inTangent;       // 0x4: weighs t^3 - t^2 from the previous key
    float m_value;           // 0x8
    unsigned short m_frame;  // 0xC
    unsigned char m_flags;   // 0xE: bit 0 holds m_value up to the next key (no interpolation)
    unsigned char pad_F;
};

// One animated material value, 0x10 bytes: MdoWrkMatRes::m_pFixAnmInf holds them, DrMdoAnim::calcAnim walks an
// MdsFixAnmCate's run of them (the type name is the symbols'; the field names are not the original's).
struct MdsFixAnmInf {
    unsigned int m_keyIdx : 29;   // 0x0: first key in MdoWrkMatRes::m_pFixAnmKey
    unsigned int m_invert : 1;    // bit 29: an etc-param value is used as 1 - value, clamped to [0, 1]
    unsigned int m_etcParam : 1;  // bit 30: the value is DrResEtcPamObj's param m_keyNum, not a key run
    unsigned int m_hourFrame : 1; // bit 31: the frame is DrMan's hour times 240, not the material's own time
    unsigned int m_keyNum;        // 0x4: the run's key count (with m_etcParam: the etc-param index)
    unsigned int m_callIdx : 16;  // 0x8: the DrMdoAnim::s_pCallAnim callback
    unsigned int m_workOfs : 16;  // 0xA: the float the callback writes, in the caller's work
    unsigned short m_startFrame;  // 0xC
    unsigned short m_endFrame;    // 0xE
};

// A material's run of MdsFixAnmInf, 0xC bytes: DrMdoAnim::updateAnimEnd/updateAnimFast step through an array of
// them (the type name is the symbols'; the field names are not the original's).
struct MdsFixAnmCate {
    unsigned short pad_0;
    unsigned short m_infIdx;  // 0x2: first MdsFixAnmInf, and its frame in MdoWrkMatRes::m_pFixAnmFrame
    unsigned short m_infNum;  // 0x4
    // 0x6: the run's first float in the material's MdoWrkMatRes::m_pUniformVal (and m_pMatVal) slots
    unsigned short m_valOfs;
    // 0x8: updateAnimFast's nine plane parameters in MdoWrkMatRes::m_pSeamMatData, in floats
    unsigned int m_planeOfs;
};

// One material's run of MdsFixAnmCate in a seam instance map's material block (MdsSeamInstMatBlock::m_rangeOfs,
// indexed by MdsMatInfoHeader::m_fixAnmRange). The type and field names are not the original's.
struct MdsFixAnmRange {
    unsigned short m_cateIdx;  // 0x0: first MdsFixAnmCate at MdsSeamInstMatBlock::m_cateOfs
    unsigned short m_cateNum;  // 0x2
};
}  // namespace ml

#endif
