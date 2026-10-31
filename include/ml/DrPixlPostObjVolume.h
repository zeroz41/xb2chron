#ifndef ML_DRPIXLPOSTOBJVOLUME_H
#define ML_DRPIXLPOSTOBJVOLUME_H

#include "ml/DrPixlPostObj.h"
#include "mm/Vec3.h"

namespace ml { class DrPixlRenderTarget; }

namespace ml {
// DrPixlPostMan::m_volume. Only what DrPixlPostMan uses is declared.
class DrPixlPostObjVolume : public DrPixlPostObj {
public:
    ~DrPixlPostObjVolume();

    // 0x18, the constructor creates the three and sets them up with DrPixlFormat::s_VolumeFormat (name inferred)
    DrPixlRenderTarget* m_volumeBuff[3];
    mm::Vec3 m_pos;  // 0x30, DrPixlPostMan::setVolumePos (the name is not the original's)
};
}  // namespace ml

#endif
