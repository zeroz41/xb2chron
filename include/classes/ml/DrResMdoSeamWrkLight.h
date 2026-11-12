#ifndef CLASSES_ML_DRRESMDOSEAMWRKLIGHT_H
#define CLASSES_ML_DRRESMDOSEAMWRKLIGHT_H

namespace ml {
class DrEnvironmentObj;
class DrResMdoSeamMemObj;
class DrResMdoSeamParmRead;

// the seam light map resource (only the field DrResMdoSeamWrkLight::setupWork reads is known; its name is not the
// original's)
struct MdsSeamLgtMapData {
    // 0x0, 0xC: the light's box; DrMdoCtlSeamLight::readLightCheck reads the light when a read position is inside it
    float m_max[3];
    float m_min[3];
    unsigned int m_ofs;  // 0x18: where the light data starts (DrMdoCtlSeamRead::callLightStream reads it from there)
    int id;  // 0x1C: DrMdoCtlSeamRead::waitLightStream adds it to the light memory read in
    // 0x20: a bit of DrMan's display-off bits; readLightCheck skips the light while it is set (0: never)
    unsigned short m_bitIdx;
    unsigned char pad_22[0x16];  // waitLightStream steps the light table by 0x38 bytes
};

// table 0x7100B7DB70
// The field names are not the original's.
class DrResMdoSeamWrkLight {
public:
    DrResMdoSeamWrkLight();
    virtual ~DrResMdoSeamWrkLight();  // slot 0
    void release();
    void setupWork(const MdsSeamLgtMapData* data);
    // true when the light is to be released (the parameter names are not the original's)
    bool update(const DrResMdoSeamParmRead* parm, const unsigned int* offBits, bool readAll);

    static float SEAM_LIGHT_READ_CHECK;

    DrResMdoSeamWrkLight* m_prev;     // 0x08: list links, zeroed by the constructor
    DrResMdoSeamWrkLight* m_next;     // 0x10
    const MdsSeamLgtMapData* m_data;  // 0x18: setupWork's argument
    DrEnvironmentObj* m_envObj;       // 0x20: made by setupWork from m_memObj's data, released by release
    DrResMdoSeamMemObj* m_memObj;     // 0x28
    int m_dataIdx;                    // 0x30: its entry in the seam map's light table; zeroed by the constructor
    int m_id;                         // 0x34: MdsSeamLgtMapData::id
    short pad_38;                     // 0x38: zeroed by the constructor and setupWork
    short pad_3A;                     // 0x3A: zeroed by release too
};
}  // namespace ml

#endif
