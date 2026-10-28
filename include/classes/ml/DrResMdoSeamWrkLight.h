#ifndef CLASSES_ML_DRRESMDOSEAMWRKLIGHT_H
#define CLASSES_ML_DRRESMDOSEAMWRKLIGHT_H

namespace ml {
class DrEnvironmentObj;
class DrResMdoSeamMemObj;

// the seam light map resource (only the field DrResMdoSeamWrkLight::setupWork reads is known; its name is not the
// original's)
struct MdsSeamLgtMapData {
    unsigned char pad_0[0x1C];
    int id;  // 0x1C
};

// table 0x7100B7DB70
// The field names are not the original's.
class DrResMdoSeamWrkLight {
public:
    DrResMdoSeamWrkLight();
    virtual ~DrResMdoSeamWrkLight();  // slot 0
    void release();
    void setupWork(const MdsSeamLgtMapData* data);

    DrResMdoSeamWrkLight* m_prev;     // 0x08: list links, zeroed by the constructor
    DrResMdoSeamWrkLight* m_next;     // 0x10
    const MdsSeamLgtMapData* m_data;  // 0x18: setupWork's argument
    DrEnvironmentObj* m_envObj;       // 0x20: made by setupWork from m_memObj's data, released by release
    DrResMdoSeamMemObj* m_memObj;     // 0x28
    int pad_30;                       // 0x30: zeroed by the constructor
    int m_id;                         // 0x34: MdsSeamLgtMapData::id
    short pad_38;                     // 0x38: zeroed by the constructor and setupWork
    short pad_3A;                     // 0x3A: zeroed by release too
};
}  // namespace ml

#endif
