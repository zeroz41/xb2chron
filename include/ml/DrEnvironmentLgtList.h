#ifndef ML_DRENVIRONMENTLGTLIST_H
#define ML_DRENVIRONMENTLGTLIST_H

namespace ml { class DrLightObj; }

namespace ml {
// A light record of the environment resource. Only what DrEnvironmentObjLgt reads is declared; the field names are
// not the original's.
struct LgtObjData {
    unsigned char pad_0[0x4];
    int m_type;  // 0x4, indexes DrEnvironmentObjLgt's per light type callback tables
};

// One light of a DrEnvironmentObjLgt (0x20 bytes, DrEnvironmentObjLgt::debugRenderLgt2D walks them so). Only what
// DrEnvironmentObjLgt reads is declared; the field names are not the original's.
class DrEnvironmentLgtList {
public:
    const LgtObjData* m_data;  // 0x0
    const void* m_posData;  // 0x8
    DrLightObj* m_light;  // 0x10, the light the callbacks render
    float m_rate;  // 0x18, the s_pCallEnvChk callbacks store it
    unsigned char pad_1c[0x4];
};
}  // namespace ml

#endif
