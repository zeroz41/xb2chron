#ifndef ML_DRRESMDOSAMPLER_H
#define ML_DRRESMDOSAMPLER_H

namespace grlib { class CGLibSampler; }

namespace ml {
// A model sampler resource; DrMdoSamplerMan keeps them in a list. Only what DrMdoSamplerMan uses is recovered.
class DrResMdoSampler {
public:
    DrResMdoSampler(const unsigned char* data);
    ~DrResMdoSampler();
    void setupSampler(const unsigned char* data);
    void setup();

    DrResMdoSampler* m_pPrev;  // 0x0: DrMdoSamplerMan's list link (the name is not the original's)
    DrResMdoSampler* m_pNext;  // 0x8: DrMdoSamplerMan's list link (the name is not the original's)
    // Field names below are not the original's.
    const unsigned char* m_data;      // 0x10: the constructor's data
    int pad_18;                       // 0x18: the constructor sets 1
    void* m_samplerBuf;               // 0x20: the samplers' allocation, freed by the destructor
    int m_samplerNum;                 // 0x28
    grlib::CGLibSampler* m_samplers;  // 0x30: m_samplerNum of them
};
}  // namespace ml

#endif
