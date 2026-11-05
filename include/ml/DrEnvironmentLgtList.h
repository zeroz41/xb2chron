#ifndef ML_DRENVIRONMENTLGTLIST_H
#define ML_DRENVIRONMENTLGTLIST_H

namespace ml { class DrLightObj; }

namespace ml {
// A light record of the environment resource. Only what DrEnvironmentObjLgt reads is declared; the field names are
// not the original's.
struct LgtObjData {
    unsigned int m_paramOfs;  // 0x0, offset of the light's LgtParamData from the resource (setupPoint)
    int m_type;  // 0x4, indexes DrEnvironmentObjLgt's per light type callback tables
    union {
        struct {
            unsigned char m_flags;  // 0x8, bit 0: the s_pCallEnvChk callbacks test the view's distance to the light
            unsigned char m_calcFlags;  // 0x9, bit 2: calcLgtObj skips the s_pCallEnvChk test (rate 1)
            unsigned char m_animFlags;  // 0xA, bit 0: animated frame (calcLgtObj); bit 2: callback_Chk_Point runs DrEnvironmentAnim::calcAnimTransPnt
            unsigned char m_flags2;  // 0xB, bit 4: setupPoint sets DrLightObj::FLAG_SUBTRACT
        };
        // 0x8, the four flag bytes as one word: setupSpot tests its bits 12..15 and 28 with word loads (the name is
        // not the original's)
        unsigned int m_flagBits;
    };
    float m_color[3];  // 0xC, setupPoint scales it by m_intensity
    float m_intensity;  // 0x18
    unsigned char pad_1c[0x6];
    unsigned short m_group;  // 0x22, a light of a group other than DrEnvironmentObj::m_group is skipped (FLAG 4)
    float m_param;  // 0x24, setupPoint stores it in DrLightObjPnt::m_lightParam (1 when 0)
    unsigned short m_animIdx;  // 0x28, with m_animFlags bit 0: calcLgtObj advances DrEnvironmentAnim::m_rangeFrame[m_animIdx]
    unsigned char pad_2a[0x6];  // changeMemCall's record stride is 0x30
};

// A light's parameter record (LgtObjData::m_paramOfs). Only what setupPoint reads is declared; the type and field
// names are not the original's.
struct LgtParamData {
    unsigned short m_kind;  // 0x0, 1: setupPoint sets the light's m_flags bit 1
    unsigned char pad_2[0x6];
    float m_speIntensity;  // 0x8
    float m_paramC;  // 0xC
    // a spot light's (setupSpot copies them to DrLightObjSpt; the names are not the original's)
    float m_angle;  // 0x10
    float m_spotParam;  // 0x14
    unsigned char pad_18[0x4];
    float m_falloff;  // 0x1C, 4 when not above 0
    float m_lightParam2;  // 0x20
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
    unsigned char pad_64[0xC];  // changeMemCall's record stride is 0x70
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

// The header of a DrEnvironmentObjLgt's resource (DrEnvironmentObj::m_resource). Only what DrEnvironmentObjLgt reads
// is declared; the type and field names are not the original's.
struct LgtResHeader {
    unsigned char pad_0[0x8];
    unsigned int m_lgtOfs;  // 0x8, offset of the LgtResLgtSection
    unsigned int m_posOfs;  // 0xC, offset of the LgtResPosSection
    unsigned char pad_10[0x4];
    // 0x14, offset of the global fog section; the section's first word is the offset of its LgtGlbFogObj records
    unsigned int m_fogOfs;
    unsigned char pad_18[0x4];
    unsigned int m_timeOfs;  // 0x1C, offset of the time section (DrEnvironmentTime's)
    unsigned int m_animOfs;  // 0x20, offset of the LgtResAnimSection (else LgtResLgtSection::m_animOfs)
    unsigned int m_ofs24;  // 0x24, offset of a section whose second word changeMemCall resolves into m_work3
    unsigned char pad_28[0x2];
    unsigned char m_flags;  // 0x2A, bit 0: the resource has a clip list (DrResWrkClipList::changeMemCall)
    unsigned char pad_2b[0x1];
    unsigned int m_clipNum;  // 0x2C, passed to DrResWrkClipList::changeMemCall
};

// The light section of the resource (LgtResHeader::m_lgtOfs). The type and field names are not the original's.
struct LgtResLgtSection {
    unsigned char pad_0[0x4];
    int m_dataOfs;  // 0x4, offset of the LgtObjData records
    unsigned char pad_8[0x20];
    unsigned int m_animOfs;  // 0x28, the LgtResAnimSection when the header has none
};

// The light position section of the resource (LgtResHeader::m_posOfs). The type and field names are not the
// original's.
struct LgtResPosSection {
    int m_num;  // 0x0, the number of lights
    int m_posOfs;  // 0x4, offset of the LgtPosData records
    unsigned char pad_8[0x4];
    int m_treeOfs;  // 0xC, offset of the LgtPosTreeRange nodes
};

// The animation section of the resource: five tables, each a count and an offset (DrEnvironmentAnim's
// m_frameRange, m_animInf, m_hermiteKeys, m_animData3, m_animData4). The type and field names are not the original's.
struct LgtResAnimSection {
    struct Table {
        unsigned int m_num;
        unsigned int m_ofs;
    };
    Table m_table[5];
};

// A resource section whose second word is an offset (the time section, LgtResHeader::m_ofs24's). The type and field
// names are not the original's.
struct LgtResOfsSection {
    unsigned int m_num;
    unsigned int m_ofs;  // 0x4
};

// A global fog record of the resource (0x5C bytes; DrEnvironmentObjLgt::update passes each to its
// s_pCallFogCall callback). Only what is read is declared; the field names are not the original's.
struct LgtGlbFogObj {
    unsigned char pad_0[0x4A];
    unsigned short m_type;  // 0x4A, indexes DrEnvironmentObjLgt::s_pCallFogCall
    unsigned char pad_4c[0x10];
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
