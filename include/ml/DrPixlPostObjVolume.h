#ifndef ML_DRPIXLPOSTOBJVOLUME_H
#define ML_DRPIXLPOSTOBJVOLUME_H

#include "ml/DrPixlPostObj.h"
#include "mm/Vec3.h"

namespace ml {
// DrPixlPostMan::m_volume. Only what DrPixlPostMan uses is declared.
class DrPixlPostObjVolume : public DrPixlPostObj {
public:
    unsigned char pad_18[0x18];
    mm::Vec3 m_pos;  // 0x30, DrPixlPostMan::setVolumePos (the name is not the original's)
};
}  // namespace ml

#endif
