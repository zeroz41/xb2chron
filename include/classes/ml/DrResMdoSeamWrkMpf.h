#ifndef CLASSES_ML_DRRESMDOSEAMWRKMPF_H
#define CLASSES_ML_DRRESMDOSEAMWRKMPF_H

namespace ml { class DrResMdoSeamMemObj; }

namespace ml {
// table 0x7100B7DBC0
class DrResMdoSeamWrkMpf {
public:
    virtual ~DrResMdoSeamWrkMpf();  // slot 0
    void setEtcMpfCache(int idx, DrResMdoSeamMemObj* mem);
    void setMpfPoliCache(int idx, DrResMdoSeamMemObj* mem);

    unsigned char pad_8[0x54];
    // 0x5C: DrMdoCtlSeamRead::waitMpfEtcStream/waitMpfPoliStream set bit 0 when the stream ends without data (the
    // name is not the original's)
    unsigned int m_cacheFlags;
};
}  // namespace ml

#endif
