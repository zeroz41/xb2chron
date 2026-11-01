#ifndef ML_DRENVIRONMENTLGTLIST_H
#define ML_DRENVIRONMENTLGTLIST_H

namespace ml { class DrLightObj; }

namespace ml {
// A light record of the environment resource. Only what DrEnvironmentObjLgt reads is declared; the field names are
// not the original's.
struct LgtObjData {
    unsigned char pad_0[0x4];
    int m_type;  // 0x4, indexes DrEnvironmentObjLgt's per light type callback tables
    unsigned char m_flags;  // 0x8, bit 0: the s_pCallEnvChk callbacks test the view's distance to the light
    unsigned char pad_9;
    unsigned char m_animFlags;  // 0xA, bit 2: callback_Chk_Point runs DrEnvironmentAnim::calcAnimTransPnt
    unsigned char pad_b[0x17];
    unsigned short m_group;  // 0x22, a light of a group other than DrEnvironmentObj::m_group is skipped (FLAG 4)
};

// The position record of a light (DrEnvironmentLgtList::m_posData). Only what the s_pCallEnvChk callbacks read is
// declared; the field names are not the original's.
struct LgtPosData {
    unsigned char pad_0[0x4C];
    float m_range;  // 0x4C, callback_Chk_Point adds it to m_radius and clip tests the light with it
    float m_pos[3];  // 0x50
    float m_radius;  // 0x5C, the distance test's radius
    unsigned short m_id;  // 0x60, callback_Chk_Point tests bit m_id - 1 of DrEnvironmentObj::m_work2's bit array
    unsigned short m_dispIdx;  // 0x62, a set bit of DrMan::m_dispOffBits hides the light
};

// One light of a DrEnvironmentObjLgt (0x20 bytes, DrEnvironmentObjLgt::debugRenderLgt2D walks them so). Only what
// DrEnvironmentObjLgt reads is declared; the field names are not the original's.
class DrEnvironmentLgtList {
public:
    const LgtObjData* m_data;  // 0x0
    const LgtPosData* m_posData;  // 0x8
    DrLightObj* m_light;  // 0x10, the light the callbacks render
    float m_rate;  // 0x18, the s_pCallEnvChk callbacks store it
    unsigned char pad_1c[0x4];
};
}  // namespace ml

#endif
