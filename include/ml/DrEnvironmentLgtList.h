#ifndef ML_DRENVIRONMENTLGTLIST_H
#define ML_DRENVIRONMENTLGTLIST_H

namespace ml { class DrLightObj; }

namespace ml {
// A light record of the environment resource. Only what DrEnvironmentObjLgt reads is declared; the field names are
// not the original's.
struct LgtObjData {
    unsigned int m_paramOfs;  // 0x0, offset of the light's LgtParamData from the resource (setupPoint)
    int m_type;  // 0x4, indexes DrEnvironmentObjLgt's per light type callback tables
    unsigned char m_flags;  // 0x8, bit 0: the s_pCallEnvChk callbacks test the view's distance to the light
    unsigned char m_calcFlags;  // 0x9, bit 2: calcLgtObj skips the s_pCallEnvChk test (rate 1)
    unsigned char m_animFlags;  // 0xA, bit 0: animated frame (calcLgtObj); bit 2: callback_Chk_Point runs DrEnvironmentAnim::calcAnimTransPnt
    unsigned char m_flags2;  // 0xB, bit 4: setupPoint sets DrLightObj::FLAG_SUBTRACT
    float m_color[3];  // 0xC, setupPoint scales it by m_intensity
    float m_intensity;  // 0x18
    unsigned char pad_1c[0x6];
    unsigned short m_group;  // 0x22, a light of a group other than DrEnvironmentObj::m_group is skipped (FLAG 4)
    float m_param;  // 0x24, setupPoint stores it in DrLightObjPnt::m_lightParam (1 when 0)
    unsigned short m_animIdx;  // 0x28, with m_animFlags bit 0: calcLgtObj advances DrEnvironmentAnim::m_rangeFrame[m_animIdx]
};

// A light's parameter record (LgtObjData::m_paramOfs). Only what setupPoint reads is declared; the type and field
// names are not the original's.
struct LgtParamData {
    unsigned short m_kind;  // 0x0, 1: setupPoint sets the light's m_flags bit 1
    unsigned char pad_2[0x6];
    float m_speIntensity;  // 0x8
    float m_paramC;  // 0xC
};

// The position record of a light (DrEnvironmentLgtList::m_posData). Only what the s_pCallEnvChk callbacks read is
// declared; the field names are not the original's.
struct LgtPosData {
    float m_mat[16];  // 0x0, the light's matrix (setupPoint)
    unsigned char pad_40[0xC];
    float m_range;  // 0x4C, callback_Chk_Point adds it to m_radius and clip tests the light with it
    float m_pos[3];  // 0x50
    float m_radius;  // 0x5C, the distance test's radius
    unsigned short m_id;  // 0x60, callback_Chk_Point tests bit m_id - 1 of DrEnvironmentObj::m_work2's bit array
    unsigned short m_dispIdx;  // 0x62, a set bit of DrMan::m_dispOffBits hides the light
};

// A node of the light position tree (0x24 bytes, DrEnvironmentObj::m_posTree): calcTreePos updates the node's
// lights and descends into each child whose box holds the view position. The field names are not the original's.
struct LgtPosTreeRange {
    float m_max[3];  // 0x0
    float m_min[3];  // 0xC
    unsigned int m_childOfs;  // 0x18, offset of the children's unsigned short node indices from the resource
    unsigned int m_lgtOfs;  // 0x1C, offset of the lights' int indices from the resource
    unsigned short m_childNum;  // 0x20
    unsigned short m_lgtNum;  // 0x22
};

// One light of a DrEnvironmentObjLgt (0x20 bytes, DrEnvironmentObjLgt::debugRenderLgt2D walks them so). Only what
// DrEnvironmentObjLgt reads is declared; the field names are not the original's.
class DrEnvironmentLgtList {
public:
    const LgtObjData* m_data;  // 0x0
    const LgtPosData* m_posData;  // 0x8
    DrLightObj* m_light;  // 0x10, the light the callbacks render
    float m_rate;  // 0x18, the s_pCallEnvChk callbacks store it
    int m_idx;  // 0x1C, its index in DrEnvironmentObj::m_lgtList (updatePosLgt tests its m_calcBits bit)
};
}  // namespace ml

#endif
