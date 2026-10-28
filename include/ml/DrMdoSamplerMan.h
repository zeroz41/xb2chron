#ifndef ML_DRMDOSAMPLERMAN_H
#define ML_DRMDOSAMPLERMAN_H

#include "ml/DrMdoResList.h"
#include "ml/DrResMdoSampler.h"

namespace ml {
class DrMan;

// The model sampler manager (no table: its constructor stores none). Field names are not the original's.
class DrMdoSamplerMan {
public:
    DrMdoSamplerMan(DrMan* drMan);
    ~DrMdoSamplerMan();
    void begin();

    DrMdoResList<DrResMdoSampler> m_samplerList;  // 0x0
    DrMan* m_pDrMan;                              // 0x10
};
}  // namespace ml

#endif
