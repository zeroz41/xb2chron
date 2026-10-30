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
    float m_alpha[2];      // 0x2C: by double buffer index (setDefAlpha)
    unsigned char pad_34[0xC];
};

class DrResMdoMeshObj {
public:
    int getIdx(const char* name) const;
    DrResMdoMeshParts* m_parts;  // field names are not the original's
    int m_num;
    static void release(DrResMdoMeshObj*& obj);
};
}  // namespace ml

#endif
