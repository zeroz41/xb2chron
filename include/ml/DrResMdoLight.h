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

    typedef void (*LgtValFunc)(float* value, DrResEtcParams* params);
    static void lgtCall_col_r(float* value, DrResEtcParams* params);
    static void lgtCall_col_g(float* value, DrResEtcParams* params);
    static void lgtCall_col_b(float* value, DrResEtcParams* params);
    static void lgtCall_col_inv(float* value, DrResEtcParams* params);

    static LgtValFunc s_pCallLgtVal[4];

    DrLightObj** m_lights;          // 0x0, m_num of them, after the object in its work buffer
    const MdoLights* m_mdoLights;   // 0x8
    const unsigned char* m_etcLights;  // 0x10, the etc data's light resource
    short m_num;                    // 0x18
    unsigned short m_flags;         // 0x1A
    unsigned char pad_1C[0x4];
};
}  // namespace ml

#endif
