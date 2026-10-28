#ifndef ML_DRRESMDOSAMPLER_H
#define ML_DRRESMDOSAMPLER_H

namespace ml {
// A model sampler resource; DrMdoSamplerMan keeps them in a list. Only what DrMdoSamplerMan uses is recovered.
class DrResMdoSampler {
public:
    ~DrResMdoSampler();
    void setup();

    unsigned char pad_0[0x8];
    DrResMdoSampler* m_pNext;  // 0x8: DrMdoSamplerMan's list link (the name is not the original's)
};
}  // namespace ml

#endif
