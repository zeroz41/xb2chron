#ifndef ML_DRMDOCTLMPFWINDCALC_H
#define ML_DRMDOCTLMPFWINDCALC_H

#include "mm/Mat44.h"

namespace ml {
// One of DrMdoMpfMan's 64 wind calculators (0xF0 bytes: DrMdoMpfMan's constructor inits them 0xF0 apart from 0x100).
// Field names are not the original's.
class DrMdoCtlMpfWindCalc {
public:
    void init();
    void calcUpdate(float, float, float);

    unsigned char pad_0[0x70];
    // 0x70: DrMdoMpfMan::updateUniformWork transposes both into the wind uniform block
    mm::Mat44 m_windMat[2];
};
}  // namespace ml

#endif
