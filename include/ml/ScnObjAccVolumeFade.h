#ifndef ML_SCNOBJACCVOLUMEFADE_H
#define ML_SCNOBJACCVOLUMEFADE_H

#include "mm/Col3.h"
#include "mm/Vec3.h"

namespace ml { class ScnObjModel; }
namespace ml { class DrMdlObj; }

namespace ml {

// a model's volume fade (vanish) parameters: gf::GfVolumeFade fills them from fw::VolumeFadeParams field by
// field (none of the names is the original's)
struct VolumeFadeParams {
    mm::Col3 m_colors[5];
    mm::Vec3 m_color0;
    mm::Vec3 m_color1;
    float m_values0[5];
    float m_values1[5];
    float m_values2[5];
    float m_value0;
    float m_value1;
    int m_value2;  // setParams copies it to MdoVanishEffectWrk::m_volumeTexIdx
};

// access to a model's volume fade: the model's material set (ScnObjModel's at 0x3D8)
class ScnObjAccVolumeFade {
public:
    ScnObjAccVolumeFade(ScnObjModel* model);
    ~ScnObjAccVolumeFade();
    int getMax() const;
    void setParams(const VolumeFadeParams& params, int index);
    void setRatio(float ratio, int index);
    float getRatio(unsigned int index) const;

    DrMdlObj* m_material;  // the constructor's model's draw object
};

}  // namespace ml

#endif
