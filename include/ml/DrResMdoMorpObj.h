#ifndef ML_DRRESMDOMORPOBJ_H
#define ML_DRRESMDOMORPOBJ_H

namespace ml {
struct MdoWrkMatRes;
class DrResEtcPamObj;
// Only release is declared so far.
class DrResMdoMorpObj {
public:
    struct MdoMorphData;
    // one morph target's blend weight (0x20 bytes; names are not the original's): DrMdoMorphing::parmsUpdate
    // copies m_weight to m_prevWeight, isBlendCheck compares them
    struct Target {
        float m_weight;      // 0x0
        float m_prevWeight;  // 0x4
        const void* m_data0;   // 0x8: m_data->m_ofs0 bytes from the MdoMorphs
        const void* m_data1;   // 0x10: m_data->m_ofs1 bytes from the MdoMorphs
        const MdoMorphData* m_data;  // 0x18
    };

    // the model data's header: its morph resource sits m_morphOfs bytes from it (names are not the original's)
    struct MdoHeader {
        unsigned char pad_0[0x80];
        unsigned int m_morphOfs;  // 0x80
    };
    struct MdoMorphs {
        unsigned int m_dataOfs;  // 0x0: m_num MdoMorphData from the MdoMorphs
        unsigned int m_num;      // 0x4: one Target each follows the object in its work buffer
        unsigned int m_flags;    // 0x8: bit 0 -> m_oldPos
    };
    // one morph target's data (0x1C bytes)
    struct MdoMorphData {
        unsigned int m_ofs0;  // 0x0
        unsigned int m_ofs1;  // 0x4
        unsigned char pad_8[0x14];
    };
    static unsigned int calcWorkSize(const unsigned char* mdo);
    static void release(DrResMdoMorpObj*& obj);
    static unsigned int create(unsigned char* work, const unsigned char* mdo);

    void update(MdoWrkMatRes* wrkMatRes, DrResEtcPamObj* pamObj);

    // Names are not the original's.
    unsigned char m_flag0;     // 0x0: zeroed by create
    bool m_blended;            // 0x1: update blended the vertices last time
    bool m_oldPos;             // 0x2: MdoMorphs::m_flags bit 0: update restores the old positions after a blend
    unsigned char pad_3[0x5];
    Target* m_pTarget;         // 0x8 (the name is not the original's)
    unsigned int m_targetNum;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
