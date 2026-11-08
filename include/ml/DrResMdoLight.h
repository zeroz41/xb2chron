#ifndef ML_DRRESMDOLIGHT_H
#define ML_DRRESMDOLIGHT_H

namespace ml {
class DrResEtcParams;
class DrLightObj;

// A model's lights, built in a work buffer (create): the light table of the model (mdo) data and the light
// resource of its etc data. Field, flag and resource struct names are not the original's.
class DrResMdoLight {
public:
    // the model data's header: its light table sits m_lightOfs bytes from it
    struct MdoHeader {
        unsigned char pad_0[0x2C];
        unsigned int m_lightOfs;  // 0x2C
    };
    struct MdoLights {
        unsigned int m_num;  // 0x0: one DrLightObj pointer each follows the object in its work buffer
    };
    // the etc data's header: its light resource sits m_lightOfs bytes from it
    struct EtcHeader {
        unsigned char pad_0[0x30];
        unsigned int m_lightOfs;  // 0x30
    };

    // the etc data's light resource: m_num lights (0x4C each) at m_lightOfs and as many matrices at m_matOfs
    struct EtcLights {
        unsigned char pad_0[0x4];
        int m_num;                // 0x4
        unsigned int m_lightOfs;  // 0x8
        unsigned int m_matOfs;    // 0xC
    };
    // one light of it; lgtCreate copies the fields to the DrLightObjPnt/DrLightObjSpt it makes
    struct EtcLight {
        unsigned char pad_0[0x4];
        unsigned char m_flags;  // 0x4, bit 1: setSubtractOn
        unsigned char pad_5[0x1];
        short m_type;           // 0x6: 0 a point light, else a spot light
        float m_color[3];       // 0x8, times m_intensity
        float m_intensity;      // 0x14
        float m_rate;           // 0x18: the point light's m_lightRate, the spot light's m_spotParam
        float m_param2;         // 0x1C: m_lightParam2
        float m_param;          // 0x20: m_lightParam (1 when 0)
        float m_spotPadE0;      // 0x24: the spot light's pad_e0
        float m_angle;          // 0x28: the spot light's m_angle
        float m_size;           // 0x2C: m_size when not 0
        unsigned char pad_30[0x1C];
    };

    enum {
        FLAG_CREATED = 1 << 0,  // lgtCreate made the lights
        FLAG_DISP = 1 << 1,     // setDisp
    };

    DrResMdoLight() : m_lights(nullptr), m_num(0), m_flags(FLAG_DISP) {}
    static unsigned int calcWorkSize(const unsigned char* mdo);
    // builds the object at work; returns the bytes it takes (calcWorkSize)
    static unsigned int create(unsigned char* work, const unsigned char* mdo, const unsigned char* etc);
    static void release(DrResMdoLight*& obj);
    void setDisp(bool disp);
    // makes the lights of the etc data's light resource with DrMan's DrLightMan, once
    void lgtCreate();

    typedef void (*LgtValFunc)(float* value, DrResEtcParams* params);
    static void lgtCall_col_r(float* value, DrResEtcParams* params);
    static void lgtCall_col_g(float* value, DrResEtcParams* params);
    static void lgtCall_col_b(float* value, DrResEtcParams* params);
    static void lgtCall_col_inv(float* value, DrResEtcParams* params);

    static LgtValFunc s_pCallLgtVal[4];

    DrLightObj** m_lights;          // 0x0, m_num of them, after the object in its work buffer
    const MdoLights* m_mdoLights;   // 0x8
    const EtcLights* m_etcLights;   // 0x10, the etc data's light resource
    short m_num;                    // 0x18
    unsigned short m_flags;         // 0x1A
    unsigned char pad_1C[0x4];
};
}  // namespace ml

#endif
