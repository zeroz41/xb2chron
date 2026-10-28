#ifndef ML_DRPIXLMDLSAMPLER_H
#define ML_DRPIXLMDLSAMPLER_H

namespace ml {
// DrMan's model sampler state (DrMan::m_pMdlSampler). Only what DrMdoSamplerMan uses is recovered.
class DrPixlMdlSampler {
public:
    // true when the samplers changed: DrMdoSamplerMan::begin then sets every model sampler up again
    bool update();
};
}  // namespace ml

#endif
