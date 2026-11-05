#ifndef CLASSES_ML_DRRESMDOSEAMWRKINST_H
#define CLASSES_ML_DRRESMDOSEAMWRKINST_H

#include "mtl/MemManager.h"
#include "mm/Vec3.h"
#include "ml/DrResMdoSeamWrkPosInst.h"

namespace ml {
class DrResMdoInstAnmObj;
struct MdoWrkMatRes;
class DrResMdoSeamMemObj;
class DrResMdoVertex;
class DrPixlShadowObj;
class DrMdoCtlSeamInstMap;
class DrResMdoSeamParmRead;
// the head of a seam instance map's data (name from setupWork's symbol; the field names are not the original's)
struct MdsSeamInstMapHead {
    unsigned char pad_0[0x18];
    unsigned int m_baseOfs;    // 0x18: offset of the base positions' data
    unsigned int m_vertexOfs;  // 0x1C: offset of the vertex data, 0 when there is none
    unsigned char pad_20[0x18];
    unsigned int m_etcOfs;     // 0x38: offset of the m_etcNum EtcInfo
    int m_etcNum;              // 0x3C
    unsigned char pad_40[0x14];
    unsigned int m_offColiOfs;  // 0x54: offset of the off-collision table, 0 when there is none
};
// table 0x7100B7DB48
class DrResMdoSeamWrkInst {
public:
    // an entry (0x40 bytes) of the seam map head's instance map table (DrMdoCtlSeam::MapHead::m_instMapTblOfs); the
    // names are not the original's
    struct MapEntry {
        unsigned char pad_0[0x34];
        unsigned int m_ofs;   // 0x34: where the instance map data starts (DrMdoCtlSeamRead::callInstMapStream)
        unsigned int m_size;  // 0x38
        unsigned char pad_3C[0x4];
    };
    // a model info (0x20 bytes); the name is not the original's
    struct MdlInfo {
        unsigned char pad_0[0x20];
    };
    // one etc position block of the seam map's data (0x20 bytes; the names are not the original's)
    struct EtcInfo {
        int m_cacheIdx;  // the cache index DrMdoCtlSeamRead::waitInstPosStream hands to setEtcPosCache
        unsigned char pad_4[0x1C];
    };
    // an etc position's fade state (8 bytes; the names are not the original's)
    struct FadeItem {
        unsigned int m_flags;  // bit 1: still placed (calcEtcInstPosUpdate drops the item without it), bit 2: fading in
        float m_alpha;
    };
    // the fade states calcEtcInstPosUpdate steps (the names are not the original's)
    struct FadeList {
        unsigned char pad_0[0x8];
        FadeItem** m_items;  // 0x8
        unsigned char pad_10[0x4];
        int m_num;           // 0x14
    };
    // the off-collision table of the seam map's data (the names are not the original's)
    struct OffColiTbl {
        int m_num;
        unsigned int m_boxOfs;  // 0x4: offset of the m_num OffColiBox from the data's head
    };
    // an oriented box of the off-collision table (0x50 bytes; the names are not the original's)
    struct OffColiBox {
        float m_axis[3][4];      // 0x0: the box's axes, one per row
        float m_center[3];       // 0x30
        unsigned int m_skipBit;  // 0x3C: the DrResMdoSeamParmRead::m_offColiBits bit that skips the box
        float m_extent[3];       // 0x40
        unsigned int m_readBit;  // 0x4C: the bit of m_readOff (from bit 7) set when the position is inside
    };
    DrResMdoSeamWrkInst();
    virtual ~DrResMdoSeamWrkInst();  // slot 0
    void release();
    void releaseCache(DrMdoCtlSeamInstMap* ctl);
    void changeMemCall();
    void calcCacheInfo();
    bool callReadOffColiTest(const mm::Vec3& pos, const DrResMdoSeamParmRead* parm);
    void calcEtcInstPosUpdate(DrMdoCtlSeamInstMap* ctl);
    void beginMdl();
    // the next of the m_mdlNum model infos (0x20 bytes each), null after the last
    MdlInfo* getMdlInfo();
    void callShadowCacheInstUpdate(unsigned long mask);
    // DrMdoCtlSeamRead::waitInstPosStream: false when the position stream's data cannot be kept (the block is freed)
    bool setEtcPosCache(mtl::ALLOC_HANDLE handle, int cacheIdx, DrResMdoSeamMemObj* memObj, const DrResMdoInstAnmObj* anm);
    void occRender();
    void seachDefShadowInstMapRender(DrPixlShadowObj* shadow, DrMdoCtlSeamInstMap* ctl);
    // 0x08: the next work of DrMdoCtlSeam::m_instPool.m_list (the name is not the original's)
    DrResMdoSeamWrkInst* m_pLink;
    DrResMdoSeamWrkInst* m_pBackLink;  // 0x10: the previous work (the name is not the original's)
    const MapEntry* m_mapEntry;  // 0x18: set by DrMdoCtlSeamRead::callInstMapStream (the name is not the original's)
    const MdsSeamInstMapHead* m_header;  // 0x20: the seam map's data (m_memObj's), set by changeMemCall (the name is not the original's)
    const DrResMdoSeamWrkPosInst::BaseData* m_baseData;  // 0x28: the base positions' data (the name is not the original's)
    const unsigned char* pad_30;  // 0x30: m_baseData + its offset at 0x8
    const unsigned char* pad_38;  // 0x38: m_baseData + its offset at 0x10
    unsigned char pad_40[0x10];
    // 0x50: DrMdoCtlSeamAll::occRender renders with it; freed by release (the name is not the original's)
    MdoWrkMatRes* m_pWrkMatRes;
    void* pad_58;  // 0x58: freed by release
    DrResMdoVertex* m_vertex;  // 0x60: deleted by release (the name is not the original's)
    int m_dataIdx;  // 0x68: its m_mapEntry's index (DrMdoCtlSeamRead::callInstMapStream; the name is not the original's)
    unsigned char pad_6C[0x4];
    void* pad_70;
    unsigned char pad_78[0xC];
    unsigned int m_readSize;  // 0x84: m_mapEntry's size (DrMdoCtlSeamRead::callInstMapStream; the name is not the original's)
    unsigned short pad_88;
    // 0x8A: waitInstPosStream sets bit 5 when the position stream ends without its data (the name is not the
    // original's)
    unsigned short m_cacheFlags;
    unsigned char pad_8C[0x4];
    void** m_bufList;  // 0x90: m_bufNum buffers freed by release (the name is not the original's)
    int m_bufNum;      // 0x98 (the name is not the original's)
    unsigned char pad_9C[0x4C];
    unsigned int* m_etcBits;  // 0xE8: one bit per etc position block set up (the name is not the original's)
    unsigned char pad_F0[0x18];
    DrResMdoSeamMemObj* m_memObj;  // 0x108: the block holding the seam map's data (the name is not the original's)
    unsigned char pad_110[0x8];
    // 0x118: 1 + m_header->m_etcNum position works, the base positions first (the name is not the original's)
    DrResMdoSeamWrkPosInst* m_posInsts;
    DrResMdoSeamWrkPosInst** m_posInstList;  // 0x120: the m_posInstNum position works set up (the name is not the original's)
    void* pad_128;
    // 0x130: a work pointing back at this one; release clears its link (the name is not the original's)
    DrResMdoSeamWrkInst* m_pPair;
    unsigned char pad_138[0x8];
    int m_posInstNum;         // 0x140 (the name is not the original's)
    unsigned char pad_144[0x8];
    int m_mdlNum;             // 0x14C (the name is not the original's)
    unsigned short m_mdlCnt;  // 0x150: beginMdl clears it (the name is not the original's)
    unsigned char pad_152[0x4];
    unsigned short m_readOff;  // 0x156: callReadOffColiTest sets a bit from bit 7 (the name is not the original's)
    unsigned int m_shadowCacheDone;  // 0x158: callShadowCacheInstUpdate clears the bits it is given (the name is not the original's)
    unsigned char pad_15C[0x3C];
    FadeList* m_fadeList;     // 0x198 (the name is not the original's)
    MdlInfo* m_mdlInfo;       // 0x1A0 (the name is not the original's)
    unsigned char pad_1A8[0x8];
    void* pad_1B0;
    void* pad_1B8;
    // 0x1C8 bytes: DrMdoCtlSeam's instance work pool destroys its works at that stride
    unsigned char pad_1C0[0x8];
};
}  // namespace ml

#endif
