#ifndef ML_DRRESMDOSEAMWRKPOSINST_H
#define ML_DRRESMDOSEAMWRKPOSINST_H

namespace ml {
// The instance positions of a seam map (0x80 bytes: DrResMdoSeamWrkInst::setEtcPosCache sets them up 0x80 apart).
// Only what DrResFetch.cpp's recovered functions use is recovered (the field names are not the original's).
class DrResMdoSeamWrkPosInst {
public:
    unsigned char pad_0[0x58];
    void** m_shadowCacheBuf;            // 0x58: one buffer per shadow cache
    unsigned int m_shadowCacheBufSize;  // 0x60: bytes of each buffer, 0 when there are none
    unsigned char pad_64[0x1C];
};
}  // namespace ml

#endif
