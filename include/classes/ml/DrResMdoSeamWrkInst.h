#ifndef CLASSES_ML_DRRESMDOSEAMWRKINST_H
#define CLASSES_ML_DRRESMDOSEAMWRKINST_H

#include "mtl/MemManager.h"

namespace ml {
class DrResMdoInstAnmObj;
struct MdoWrkMatRes;
class DrResMdoSeamMemObj;
class DrResMdoSeamWrkPosInst;
// table 0x7100B7DB48
class DrResMdoSeamWrkInst {
public:
    // a model info (0x20 bytes); the name is not the original's
    struct MdlInfo {
        unsigned char pad_0[0x20];
    };
    virtual ~DrResMdoSeamWrkInst();  // slot 0
    void release();
    void beginMdl();
    // the next of the m_mdlNum model infos (0x20 bytes each), null after the last
    MdlInfo* getMdlInfo();
    void callShadowCacheInstUpdate(unsigned long mask);
    // DrMdoCtlSeamRead::waitInstPosStream: false when the position stream's data cannot be kept (the block is freed)
    bool setEtcPosCache(mtl::ALLOC_HANDLE handle, int cacheIdx, DrResMdoSeamMemObj* memObj, const DrResMdoInstAnmObj* anm);
    void occRender();
    // 0x08: the next work of DrMdoCtlSeam::m_pInstList (the name is not the original's)
    DrResMdoSeamWrkInst* m_pLink;
    unsigned char pad_10[0x40];
    // 0x50: DrMdoCtlSeamAll::occRender renders with it (the name is not the original's)
    MdoWrkMatRes* m_pWrkMatRes;
    unsigned char pad_58[0x32];
    // 0x8A: waitInstPosStream sets bit 5 when the position stream ends without its data (the name is not the
    // original's)
    unsigned short m_cacheFlags;
    unsigned char pad_8C[0x94];
    DrResMdoSeamWrkPosInst** m_posInstList;  // 0x120: the m_posInstNum position works set up (the name is not the original's)
    unsigned char pad_128[0x18];
    int m_posInstNum;         // 0x140 (the name is not the original's)
    unsigned char pad_144[0x8];
    int m_mdlNum;             // 0x14C (the name is not the original's)
    unsigned short m_mdlCnt;  // 0x150: beginMdl clears it (the name is not the original's)
    unsigned char pad_152[0x6];
    unsigned int m_shadowCacheDone;  // 0x158: callShadowCacheInstUpdate clears the bits it is given (the name is not the original's)
    unsigned char pad_15C[0x44];
    MdlInfo* m_mdlInfo;       // 0x1A0 (the name is not the original's)
};
}  // namespace ml

#endif
