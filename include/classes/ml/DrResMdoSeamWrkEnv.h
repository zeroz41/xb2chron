#ifndef CLASSES_ML_DRRESMDOSEAMWRKENV_H
#define CLASSES_ML_DRRESMDOSEAMWRKENV_H

#include "mm/Vec3.h"
#include "mtl/MemManager.h"
#include "ml/DrResMdoSeamMemMan.h"

namespace grlib { class CGLibTriUniformArray; }

namespace ml {
class DrResMdoSeamMemObj;
struct MdoWrkMatRes;
// The head of a seam env map's data (DrResMdoSeamMemObj::m_pData); the field names are not the original's.
struct MdsSeamEnvMapHead {
    // 0x0..0x18: offsets of data blocks from the head: [1], [0], [3], [6] and [4] go to
    // DrMdoMat::resetBaseMapMaterial, [2] (0 when there is none) is the MdsSeamInstMatBlock of the material
    // resources (DrMdoCtlSeamEnvMap::readEnvMapCheck)
    unsigned int m_dataOfs[7];
};
// The env map data setupWork reads; the field name is not the original's.
struct MdsSeamEnvMapData {
    unsigned char pad_0[0x38];
    unsigned int dispNum;  // 0x38 (setupWork copies it)
};

// table 0x7100B7DB20. 0xA0 bytes (setInfo writes 0x90..0x9C). Field names are not the original's.
// 0x8/0x10 are DrResChankList node links (a base, as in DrCalcTexStmObj: the constructor zeroes them before it
// stores the table).
class DrResMdoSeamWrkEnv : public DrResChankList<DrResMdoSeamWrkEnv>::Node {
public:
    DrResMdoSeamWrkEnv();
    virtual ~DrResMdoSeamWrkEnv();  // slot 0
    void release();
    void setupWork(MdoWrkMatRes* matRes, grlib::CGLibTriUniformArray* triArray, mtl::ALLOC_HANDLE handle,
                   const MdsSeamEnvMapHead* head, const MdsSeamEnvMapData* data);
    void changeMemCall(const MdsSeamEnvMapHead* head);
    void setInfo(const mm::Vec3& pos0, const mm::Vec3& pos1, bool flag, unsigned int type);
    unsigned int chkDispState();
    void setDispState();
    // returns true when the work is set and force is set; otherwise flags FLAG_READ once the memory object is read
    bool update(const mm::Vec3& pos, bool force);

    enum { FLAG_MEM_MASK = 0x3, FLAG_READ = 1 << 4 };

    const MdsSeamEnvMapHead* m_head;      // 0x18
    const MdsSeamEnvMapData* m_data;      // 0x20
    void* m_matBits;                      // 0x28: one bit per material, allocated by setupWork
    void* m_matBitsTop;                   // 0x30: the same block
    void* m_work0;                        // 0x38: released by release
    void* m_work1;                        // 0x40: released by release
    void* m_work2;                        // 0x48: cleared by release
    unsigned int m_dataIdx;  // 0x50: its MapHead::m_envMdlTblOfs entry (callEnvMdlStream)
    unsigned char pad_54[0x4];
    MdoWrkMatRes* m_matRes;               // 0x58: released by release
    DrResMdoSeamMemObj* m_memObj;         // 0x60: cleared by release; update tests its read-in flag
    unsigned int m_type;                  // 0x68 (setInfo)
    unsigned int m_flags;                 // 0x6C: bits 0-1 cleared by changeMemCall, bit DrMan::s_nDblNowIdx shown
    unsigned int m_dispNum;               // 0x70 (MdsSeamEnvMapData::dispNum)
    bool m_infoFlag;                      // 0x74 (setInfo)
    unsigned char pad_75[0xB];
    mm::Vec3 m_pos0;                      // 0x80 (setInfo)
    mm::Vec3 m_pos1;                      // 0x90 (setInfo)
};
}  // namespace ml

#endif
