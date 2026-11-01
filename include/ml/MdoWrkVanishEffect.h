#ifndef ML_MDOWRKVANISHEFFECT_H
#define ML_MDOWRKVANISHEFFECT_H

namespace ml {
// A model work's vanish effect (0xE0 bytes; DrResEtcPamObj::mdonode_etcpam_volfadeanm indexes an array of them).
// Only the fields volfadeanm uses; their names are not the original's.
class MdoWrkVanishEffect {
public:
    unsigned char pad_0[0xA4];
    float m_alpha;  // 0xA4: volfadeanm sets it from m_baseAlpha and the parameter, clamped to 0..1
    unsigned char pad_A8[0x28];
    float m_baseAlpha;  // 0xD0
    unsigned char pad_D4[0xC];
};
}  // namespace ml

#endif
