#ifndef ML_DRRESMPFSAMPLER_H
#define ML_DRRESMPFSAMPLER_H

#include "grlib/CGLibSampler.h"

namespace ml {
struct MdsMpfMatInfoHeader;

// The three samplers of an mpf material, set up from its info header's sampler flags. The field names are not the
// original's.
class DrResMpfSampler {
public:
    DrResMpfSampler(const MdsMpfMatInfoHeader* header);
    ~DrResMpfSampler();
    void setupSampler(const MdsMpfMatInfoHeader* header);

    unsigned char pad_0[0x8];
    grlib::CGLibSampler* m_sampler[3];  // 0x08
};
}  // namespace ml

#endif
