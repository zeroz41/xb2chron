#ifndef CLASSES_ML_DRMDOCTLSEAM_H
#define CLASSES_ML_DRMDOCTLSEAM_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"
#include "ml/DrResMdoSeamMemMan.h"
#include "classes/ml/DrResMdoSeamRead.h"
#include "ml/DrResMdoSeamParmRead.h"
#include "mm/mtl/FixedVector.h"

namespace ml { class DrResMdoSeamWrkBase; }
namespace cloud { class CloudMdlDataObj; }

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoSeamWrkInst;
class DrResMdoSeamVertex;
class DrResMdoSeamTexture;
class DrResMdoSeamTexList;
class DrResMdoSeamWrkLow;
class DrResMdoSeamWrkMpf;
class DrResMdoSeamWrkEnv;
class DrResMdoSeamWrkLight;
class DrEnvironmentObj;
class DrEnvColiObj;
class DrCalcClipObj;
class DrCalcCpPlaneObj;
class DrGlobalIBLPack;
class DrResMdoInstMdlInfo;
class DrResEtcTexList;

// table 0x7100B7BA10
class DrMdoCtlSeam : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlSeam();  // slot 0
    void resourceRelease();
    // DrMdoCtlSeamAll::dispOffUpdate: true when DrMdoCtlSeamAll::callDeleteUpdate is to run (the meaning is inferred)
    bool calcBegin();
    void calcEnd();
    void releaseFreeSeamMemObj(DrResMdoSeamMemObj* obj);
    void releaseFreeSeamVertex(DrResMdoSeamVertex* vertex, bool);
    void releaseFreeSeamTexture(DrResMdoSeamTexture* texture, bool);
    void releaseFreeSeamTexList(DrResMdoSeamTexList* list, bool);
    void updateTexutreSeam();
    void updateVertexSeam();
    void releaseSeam();

    // a placed effect position (0x10; ScnObjAccPartsEtcPos reads it). Type and field names are not the original's.
    struct EtcPos {
        // the record (offsets from the record itself)
        struct Data {
            unsigned int objNameOfs;  // 0x0
            unsigned int effNameOfs;  // 0x4
            float range;              // 0x8
            unsigned int matrixMax;   // 0xC
            unsigned int matrixOfs;   // 0x10: matrixMax Mat44s
            float nearClip[2];        // 0x14
            float farClip[2];         // 0x1C
            unsigned int dispIdxOfs;  // 0x24: a u16 DrMan display index per matrix (0 = always shown)
        };
        const Data* m_data;  // 0x0
        bool m_dispOn;       // 0x8: shown whatever the display bits say
    };
    // the seam's effect positions (ScnObjAccSeamEtcPos reads it; names are not the original's)
    struct EtcPosList {
        EtcPos* m_entries;   // 0x0
        unsigned int m_max;  // 0x8
    };

    // the seam map's header, read through the offsets of its tables (DrMdoCtlSeamRead::wait*Stream). The type
    // and field names are not the original's.
    struct MapHead {
        // a vertex or texture list entry (8 bytes); m_size is the memory it takes
        struct ResSize {
            unsigned int m_ofs;   // 0x0: where the data starts (call*Stream read it from there)
            unsigned int m_size;  // 0x4
        };
        // a texture entry (0x14 bytes); m_heightSize is the height texture's memory
        struct MdlEntry {
            unsigned char pad_0[0x34];
            unsigned int m_ofs;   // 0x34
            unsigned int m_size;  // 0x38
        };
        struct LowEntry {
            unsigned char pad_0[0x28];
            unsigned int m_ofs;   // 0x28
            unsigned int m_size;  // 0x2C
            unsigned char pad_30[0x18];
        };
        struct TexSize {
            unsigned int m_ofs;  // 0x0: where the image starts (callTexutreStream)
            unsigned int m_size;        // 0x4
            unsigned int m_heightOfs;   // 0x8: where the height image starts
            unsigned int m_heightSize;  // 0xC
            unsigned int pad_10;
        };
        unsigned char pad_0[0x1C];
        unsigned int m_baseMapTblOfs;     // 0x1C: DrResMdoSeamWrkBase::MapEntry entries (callBaseMapStream)
        unsigned char pad_20[0x4];
        unsigned int m_instMapTblOfs;     // 0x24: DrResMdoSeamWrkInst::MapEntry entries (callInstMapStream)
        unsigned char pad_28[0xC];
        unsigned int m_envMdlTblOfs;      // 0x34: MdlEntry entries (callEnvMdlStream)
        unsigned char pad_38[0x1C];
        unsigned int m_vertexTblOfs;   // 0x54: ResSize entries, by DrResMdoSeamVertex::m_dataIdx
        unsigned char pad_58[0x4];
        unsigned int m_textureTblOfs;  // 0x5C: TexSize entries, by DrResMdoSeamTexture::m_dataIdx
        unsigned char pad_60[0x8];
        unsigned int m_mpfMdlTblOfs;      // 0x68: MdlEntry entries (callMpfMdlStream, waitMpfMdlStream)
        unsigned char pad_6C[0x4];
        unsigned int m_instPosTblOfs;     // 0x70: ResSize entries (callInstPosStream)
        unsigned char pad_74[0x4];
        unsigned int m_mpfEtcTblOfs;      // 0x78: ResSize entries (callMpfEtclStream)
        unsigned char pad_7C[0x10];
        unsigned int m_lightTblOfs;    // 0x8C: MdsSeamLgtMapData entries, by DrResMdoSeamWrkLight::m_dataIdx
        unsigned char pad_90[0x4];
        unsigned int m_texListTblOfs;  // 0x94: ResSize entries, by DrResMdoSeamTexList::m_dataIdx
        unsigned char pad_98[0x24];
        unsigned int m_lowMdlTblOfs;      // 0xBC (callLowMdlStream)
        unsigned char pad_C0[0x8];
        unsigned int m_mpfPoliTblOfs;     // 0xC8: ResSize entries (callMpfPolilStream)
        unsigned char pad_CC[0x4];
        unsigned int m_baseVertexTblOfs;  // 0xD0: ResSize entries (callBaseVertexStream)
    };

    // the names are not the original's
    unsigned char pad_18C[0x1C];
    const MapHead* m_pMapHead;  // 0x1A8
    // 0x1B0..0x1DC, 0x1E8..0x214, 0x220..0x24C: the texture, texture list and vertex resource pools, laid out like
    // the low pool below (DrMdoCtlSeamRead::callTexutreStream, callTexListStream and callVertexStream take a free
    // resource and give it back when the read fails; the names are not the original's)
    DrResMdoSeamTexture* m_textureFreeHead;  // 0x1B0
    DrResMdoSeamTexture* m_textureFreeTail;  // 0x1B8
    DrResMdoSeamTexture* m_textureList;      // 0x1C0
    DrResMdoSeamTexture* m_textureUsedTail;  // 0x1C8
    // 0x1D0: the texture resources, by DrResMdoSeamTexture::m_no (m_pTextureNo holds m_no + 1; the name is not the
    // original's)
    DrResMdoSeamTexture* m_pTextures;
    int m_textureUsedNum;  // 0x1D8
    int m_textureFreeNum;  // 0x1DC
    unsigned char pad_1E0[0x8];
    DrResMdoSeamTexList* m_texListFreeHead;  // 0x1E8
    DrResMdoSeamTexList* m_texListFreeTail;  // 0x1F0
    DrResMdoSeamTexList* m_texListList;      // 0x1F8
    DrResMdoSeamTexList* m_texListUsedTail;  // 0x200
    DrResMdoSeamTexList* m_texListWorks;     // 0x208
    int m_texListUsedNum;                    // 0x210
    int m_texListFreeNum;                    // 0x214
    unsigned char pad_218[0x8];
    DrResMdoSeamVertex* m_vertexFreeHead;  // 0x220
    DrResMdoSeamVertex* m_vertexFreeTail;  // 0x228
    // 0x230: the vertex resources in use; updateVertexSeam walks them through DrResMdoSeamVertex::m_prev (0x08), so
    // by DrResChankList's naming this is a list's tail (the name is not the original's)
    DrResMdoSeamVertex* m_pVertexList;
    DrResMdoSeamVertex* m_vertexUsedTail;  // 0x238
    DrResMdoSeamVertex* m_vertexWorks;     // 0x240
    int m_vertexUsedNum;                   // 0x248
    int m_vertexFreeNum;                   // 0x24C
    unsigned char pad_250[0x40];
    // 0x290..0x2BC, 0x300..0x32C, 0x338..0x364, 0x3A8..0x3D4: the base, instance, mpf and light work pools, laid out
    // like the low pool below (DrMdoCtlSeamRead::callBaseMapStream, callInstMapStream, callMpfMdlStream and
    // callLightStream take a free work; the names are not the original's)
    DrResMdoSeamWrkBase* m_baseFreeHead;  // 0x290
    DrResMdoSeamWrkBase* m_baseFreeTail;  // 0x298
    // 0x2A0: the base works in use (DrMdoCtlSeamAll::callShadowCacheUpdate walks them; the name is not the original's)
    DrResMdoSeamWrkBase* m_pBaseList;
    DrResMdoSeamWrkBase* m_baseUsedTail;  // 0x2A8
    DrResMdoSeamWrkBase* m_baseWorks;     // 0x2B0
    int m_baseUsedNum;                    // 0x2B8
    int m_baseFreeNum;                    // 0x2BC
    unsigned char pad_2C0[0x8];
    // 0x2C8..0x2F4, 0x370..0x39C: the low and env work pools around their lists in use: the free works, the last
    // work in use, the work array and the counts in use and free (DrMdoCtlSeamRead::callLowMdlStream and
    // callEnvMdlStream take a free work; the original keeps each pool in a 0x38-byte type whose name is unknown, the
    // field names are not the original's)
    DrResMdoSeamWrkLow* m_lowFreeHead;
    DrResMdoSeamWrkLow* m_lowFreeTail;
    // 0x2D8, 0x348, 0x380, 0x3B8: the low, mpf, env and light works in use, each walked through the work's 0x08
    // (DrMdoCtlSeamAll::releaseSeamAll; the names are not the original's)
    DrResMdoSeamWrkLow* m_pLowList;
    DrResMdoSeamWrkLow* m_lowUsedTail;  // 0x2E0
    DrResMdoSeamWrkLow* m_lowWorks;     // 0x2E8
    int m_lowUsedNum;                   // 0x2F0
    int m_lowFreeNum;                   // 0x2F4
    unsigned char pad_2F8[0x8];
    DrResMdoSeamWrkInst* m_instFreeHead;  // 0x300
    DrResMdoSeamWrkInst* m_instFreeTail;  // 0x308
    DrResMdoSeamWrkInst* m_pInstList;  // 0x310: the instance works in use (DrMdoCtlSeamAll::occRender walks them)
    DrResMdoSeamWrkInst* m_instUsedTail;  // 0x318
    DrResMdoSeamWrkInst* m_instWorks;     // 0x320
    int m_instUsedNum;                    // 0x328
    int m_instFreeNum;                    // 0x32C
    unsigned char pad_330[0x8];
    DrResMdoSeamWrkMpf* m_mpfFreeHead;  // 0x338
    DrResMdoSeamWrkMpf* m_mpfFreeTail;  // 0x340
    DrResMdoSeamWrkMpf* m_pMpfList;  // 0x348
    DrResMdoSeamWrkMpf* m_mpfUsedTail;  // 0x350
    DrResMdoSeamWrkMpf* m_mpfWorks;     // 0x358
    int m_mpfUsedNum;                   // 0x360
    int m_mpfFreeNum;                   // 0x364
    unsigned char pad_368[0x8];
    DrResMdoSeamWrkEnv* m_envFreeHead;  // 0x370
    DrResMdoSeamWrkEnv* m_envFreeTail;  // 0x378
    DrResMdoSeamWrkEnv* m_pEnvList;  // 0x380
    DrResMdoSeamWrkEnv* m_envUsedTail;  // 0x388
    DrResMdoSeamWrkEnv* m_envWorks;  // 0x390
    int m_envUsedNum;  // 0x398
    int m_envFreeNum;  // 0x39C
    unsigned char pad_3A0[0x8];
    DrResMdoSeamWrkLight* m_lightFreeHead;  // 0x3A8
    DrResMdoSeamWrkLight* m_lightFreeTail;  // 0x3B0
    DrResMdoSeamWrkLight* m_pLightList;  // 0x3B8
    DrResMdoSeamWrkLight* m_lightUsedTail;  // 0x3C0
    DrResMdoSeamWrkLight* m_lightWorks;     // 0x3C8
    int m_lightUsedNum;                     // 0x3D0
    int m_lightFreeNum;                     // 0x3D4
    unsigned char pad_3D8[0x20];
    // 0x3F8..0x658: the seam's own objects, released and cleared by resourceRelease (the names are not the
    // original's)
    DrEnvironmentObj* m_envObj;   // 0x3F8
    DrEnvColiObj* m_envColi;      // 0x400
    DrCalcClipObj* m_calcClip;    // 0x408
    unsigned char pad_410[0x8];
    DrCalcCpPlaneObj* m_cpPlane;  // 0x418
    // 0x420: the view's DrGlobalIBLMan made them (resourceRelease gives them back)
    mm::mtl::FixedVector<DrGlobalIBLPack*, 32> m_iblPacks;
    mm::mtl::FixedVector<DrEnvironmentObj*, 32> m_envObjs;  // 0x528
    unsigned char pad_630[0x8];
    DrResMdoInstMdlInfo* m_instMdlInfo;  // 0x638: resourceRelease calls its releaseCall
    unsigned char pad_640[0x18];
    DrResEtcTexList* m_etcTexList;       // 0x658
    unsigned char pad_660[0x38];
    DrResMdoInstAnmObj m_instAnm;  // 0x698: releaseSeam releases it; ScnObjAccSeamPos reads it (m_mdlType 3)
    EtcPosList m_etcPos;           // 0x6C8 (m_mdlType 3)
    unsigned char pad_6D8[0x8];
    // 0x6E0: the destructor destroys it; releaseFreeSeamMemObj frees its blocks
    DrResMdoSeamMemMan m_memMan;
    unsigned char pad_B28[0x8];
    cloud::CloudMdlDataObj* m_cldMdlData;  // 0xB30: released by resourceRelease (the name is not the original's)
    // 0xB38: DrMdoCtlSeamInstMap::beginResAll keeps the material resources it replaces here and endResAll puts them
    // back
    MdoWrkMatRes* m_pSavedWrkMatRes;
    unsigned char pad_B40[0x50];
    unsigned int* m_pMpfBits;        // 0xB90: a bit per mpf model table entry, set by waitMpfMdlStream
    unsigned char pad_B98[0x28];
    unsigned int* m_pLightBits;      // 0xBC0: a bit per light table entry, set by waitLightStream
    unsigned char pad_BC8[0x8];
    unsigned short* m_pVertexNo;     // 0xBD0: by vertex table entry, the DrResMdoSeamVertex::m_no + 1 holding it
    unsigned char pad_BD8[0x8];
    unsigned short* m_pTextureNo;    // 0xBE0: by texture table entry, the DrResMdoSeamTexture::m_no + 1 holding it
    unsigned char pad_BE8[0x8];
    unsigned short* m_pTexListNo;    // 0xBF0: by texture list entry, the DrResMdoSeamTexList::m_no + 1 holding it
    unsigned char pad_BF8[0xE];
    unsigned short m_mpfNum;         // 0xC06: waitMpfMdlStream counts the mpf models in
    unsigned char pad_C08[0x4];
    unsigned short m_lightNum;       // 0xC0C: waitLightStream counts the lights in
    // 0xC0E..0xC14: calcEnd's frame counters: 0xC12 counts frames with no stream started (m_seamFlags bit 16) up to
    // 4, then sets bit 15; 0xC14 counts frames after that up to 900, then sets bit 17. 0xC0E/0xC10 do the same for
    // bit 10 with bits 11 and 20 (bit 11 clear: DrMan::setSeamMapStmOk(true)). The names are not the original's.
    short m_stmIdleCnt;
    short m_stmBusyCnt;
    short m_readIdleCnt;
    short m_readBusyCnt;
    short m_offScreenCnt;            // 0xC16: DrMdoCtlSeamAll::noOffScreenUpdate counts its calls
    unsigned char pad_C18[0x2];
    // 0xC1A, 0xC1E, 0xC20: DrMdoCtlSeamRead::updateReadCall clears m_readSkip while reading is off and counts the
    // others down; callHeightTexutreStream sets m_heightReadWait to 60 when it cannot start (the names are not the
    // original's)
    short m_readSkip;
    unsigned char pad_C1C[0x2];
    short m_readWaitCnt;
    short m_heightReadWait;
    unsigned char pad_C22[0x8];
    short m_readErrWait;  // 0xC2A: calcEnd sets 30 when a stream could not start (bit 21; the name is not the original's)
    unsigned char pad_C2C[0x8];
    int m_textureMemSize;            // 0xC34: the texture memory read in
    int m_vertexMemSize;             // 0xC38: the vertex memory read in
    unsigned char pad_C3C[0x4];
    // 0xC40, 0xC44, 0xC50: cleared by DrMdoCtlSeamAll::releaseSeamAll once the base, low and env works are freed
    // (0xC40 again after the mpf works); by m_vertexMemSize, the memory sizes of those works (the names are not the
    // original's)
    int m_baseMemSize;
    int m_lowMemSize;
    unsigned char pad_C48[0x4];
    int m_mpfMemSize;  // 0xC4C: the mpf model memory read in (waitMpfMdlStream; the name is not the original's)
    int m_envMemSize;
    unsigned char pad_C54[0x8];
    // 0xC5C..0xC68: DrMdoCtlSeamMpfMap::updateMpfMapRenderList adds each mpf work's m_renderNum (the name is not the
    // original's)
    int m_mpfRenderNum[4];
    int m_lightMemSize;              // 0xC6C: the light memory read in
    unsigned char pad_C70[0xC];
    // 0xC7C: DrMdoCtlSeamRead::wait*Stream set bit 16 when a stream ends without its data (and bit 10 while
    // DrMan::m_seamReadErrMode is high enough); DrMdoCtlSeamAll::callRenderSeamAll tests bit 3
    unsigned int m_seamFlags;
    unsigned char pad_C80[0x4];
    // 0xC84: a bit per stream kind (_wkSeamReadCall::m_type) started or still waiting (the name is not the
    // original's)
    unsigned int m_readTypeBits;
    int m_lightGroup;                // 0xC88: 1 from the constructor; waitLightStream gives it to the light's object
    unsigned char pad_C8C[0x4];
    // 0xC90/0xC98: one bit per shadow cache already rendered, for the base and the instance works:
    // DrMdoCtlSeamAll::callShadowCacheUpdate clears the bits it is given, DrMdoCtlSeamRead::waitBaseVertexStream and
    // waitInstPosStream clear all once their stream is in (the names are not the original's)
    unsigned long m_baseShadowCacheDone;
    unsigned long m_instShadowCacheDone;
    unsigned char pad_CA0[0xC];
    // 0xCAC..0xCC4: the last 4 streams DrMdoCtlSeamRead::call*Stream could not start (no memory or no read): their
    // kind and size, m_readErrIdx the next slot (the names are not the original's)
    short m_readErrIdx;
    short m_readErrType[4];
    unsigned char pad_CB6[0x2];
    unsigned int m_readErrSize[4];
    // 0xCC8: updateVertexSeam frees every vertex resource while it is set (the name is not the original's)
    bool m_releaseVertexAll;
    unsigned char pad_CC9[0x7];
    // 0xCD0: the destructor destroys it; DrMdoCtlSeamAll::setDeleteCall cancels its reads
    DrResMdoSeamRead m_seamRead;
    unsigned char pad_D28[0x8];
    // 0xD30: destroyed by the destructor (DrMdoCtlSeamBaseMap.h); updateVertexSeam keeps the vertex resources 10
    // frames instead of 60 while it holds positions (the name is not the original's)
    DrResMdoSeamParmRead m_parmRead;
};
}  // namespace ml

#endif
