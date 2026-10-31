#ifndef ML_DRRESMDOMESHOBJ_H
#define ML_DRRESMDOMESHOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoMeshParts {
public:
    void setDefAlpha(float alpha);
    const char* m_name;  // ScnObjAccResSubMesh::getExtName returns it (the name is not the original's)
    unsigned char pad_8[0x20];
    // Field names below are not the original's.
    unsigned int m_flags;  // 0x28: setDefAlpha sets bit 1 << DrMan::s_nDblStockIdx
    float m_alpha[3];      // 0x2C: [0], [1] by double buffer index (setDefAlpha); DrResEtcPamObj::mdonode_etcpam_etcmesh_disp sets all three
    unsigned char pad_38[0x8];
};

class DrResMdoMeshObj {
public:
    // the model data's header: m_partsNum mesh parts (struct and field names are not the original's)
    struct MdoHeader {
        unsigned char pad_0[0x64];
        unsigned int m_partsOfs;  // 0x64
        unsigned int m_partsNum;  // 0x68: one DrResMdoMeshParts each after the object
        unsigned int pad_6C;
        unsigned int m_extNum;    // 0x70: 0x40 more work bytes each
    };
    // the object and its parts; 0 when the model has none
    static unsigned int calcWorkSize(const unsigned char* mdo);
    int getIdx(const char* name) const;
    DrResMdoMeshParts* m_parts;  // field names are not the original's
    int m_num;
    static void release(DrResMdoMeshObj*& obj);
};
}  // namespace ml

#endif
