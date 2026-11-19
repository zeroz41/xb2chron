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

    // setupSampler's data: m_num Entry records at m_ofs from the data (the names are not the original's)
    struct Data {
        int m_num;
        unsigned int m_ofs;
    };
    // one sampler's record (8 bytes): bit 7 border clamp, bit 5 mirror clamp, bits 0-3 the s/t clamps, bit 4 point
    // filter, bit 6 no model sampler setting (the names are not the original's)
    struct Entry {
        unsigned int m_flags;
        float m_lod;  // 0x4: setLOD's bias when the model sampler setting has its flag set
    };

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
