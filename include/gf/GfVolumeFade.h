#ifndef GF_GFVOLUMEFADE_H
#define GF_GFVOLUMEFADE_H

#include "fw/VolumeFadeParams.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace ml { class ScnObjModel; }

namespace gf {

// a volume fade effect (an fw::EffectManager parameter set; 0: none)
enum VFEFF : int {};
// who asks for a fade (each keeps its own ratios; the five multiply)
enum VFACC : int {};
// a part of the model (-1: all six)
enum VFPARTS : int {};

// a key of a fade: when, and the ratio then
struct VFKEYDATA {
    float m_time;   // seconds
    float m_ratio;
};

// no table: an object's model fading out by parts (a volume fade): each VFACC's ratio per part, multiplied, sets the
// parts' opacity on the object's model component, and the effect type's parameters go to the model
class GfVolumeFade {
public:
    GfVolumeFade(GF_OBJ_HANDLE* handle, ml::ScnObjModel* model);
    // out of line in 1.0.0
    void initializeParam() {
        for (int acc = 0; acc < 5; acc++) {
            for (int parts = 0; parts < 6; parts++) {
                m_ratio[acc][parts] = 1.0f;
            }
        }
        m_effectType = VFEFF(0);
        m_dirty = true;
    }
    void setEffectType(VFEFF type);
    static bool setupVolumeFadeParamForDead(ml::VolumeFadeParams& params, VFEFF type);
    void setFadeRatio(VFACC acc, VFPARTS parts, float ratio);
    void applyFadeRatio();
    float getFadeRatio(VFACC acc, VFPARTS parts) const;
    float getFadeRatioForParts(VFPARTS parts) const;
    // out of line in 1.0.0
    static void copyVolumeFadeParams(ml::VolumeFadeParams& dst, const fw::VolumeFadeParams& src) {
        for (int i = 0; i < 5; i++) {
            dst.m_colors[i] = src.m_colors[i];
            dst.m_values0[i] = src.m_values0[i];
            dst.m_values1[i] = src.m_values1[i];
            dst.m_values2[i] = src.m_values2[i];
        }
        dst.m_color0 = mm::Vec3(src.m_color0.r, src.m_color0.g, src.m_color0.b);
        dst.m_color1 = mm::Vec3(src.m_color1.r, src.m_color1.g, src.m_color1.b);
        dst.m_value0 = src.m_value0;
        dst.m_value1 = src.m_value1;
        dst.m_value2 = src.m_value2;
    }
    static void setupKeyFrame(mm::mtl::FixedVector<VFKEYDATA, 4>& keys, VFEFF type);

    GF_OBJ_HANDLE* m_handle;
    ml::ScnObjModel* m_model;
    bool m_dirty;           // a ratio changed since applyFadeRatio last applied them
    mm::mtl::FixedArray<mm::mtl::FixedArray<float, 6>, 5> m_ratio;  // by VFACC and VFPARTS, 1 at first
    ml::VolumeFadeParams m_params;  // setEffectType's effect's
    VFEFF m_effectType;
};

}  // namespace gf

#endif
