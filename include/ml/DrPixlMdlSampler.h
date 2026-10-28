#ifndef ML_DRPIXLMDLSAMPLER_H
#define ML_DRPIXLMDLSAMPLER_H

namespace ml {
// DrMan's model sampler state (DrMan::m_pMdlSampler). Only what DrMdoSamplerMan uses is recovered.
class DrPixlMdlSampler {
public:
    // true when the samplers changed: DrMdoSamplerMan::begin then sets every model sampler up again
    DrPixlMdlSampler();
    bool update();

    // the sampler settings (the field names are not the original's; the constructor sets 4, 1, false)
    struct State {
        int m_value0;
        int m_value1;
        bool m_flag;
    };
    State m_cur;   // 0x0, what the models are set up with
    State m_next;  // 0xC, update copies it into m_cur when they differ
};
}  // namespace ml

#endif
