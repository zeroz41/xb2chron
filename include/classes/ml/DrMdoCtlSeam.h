#ifndef CLASSES_ML_DRMDOCTLSEAM_H
#define CLASSES_ML_DRMDOCTLSEAM_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"
#include "ml/DrResMdoSeamMemMan.h"
#include "classes/ml/DrResMdoSeamRead.h"

namespace ml { class DrResMdoSeamWrkBase; }

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoSeamWrkInst;

// table 0x7100B7BA10
class DrMdoCtlSeam : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlSeam();  // slot 0
    void resourceRelease();
    // DrMdoCtlSeamAll::dispOffUpdate: true when DrMdoCtlSeamAll::callDeleteUpdate is to run (the meaning is inferred)
    bool calcBegin();
    void calcEnd();
    void releaseFreeSeamMemObj(DrResMdoSeamMemObj* obj);

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
            unsigned int pad_0;
            unsigned int m_size;  // 0x4
        };
        // a texture entry (0x14 bytes); m_heightSize is the height texture's memory
        struct TexSize {
            unsigned int pad_0;
            unsigned int m_size;        // 0x4
            unsigned int pad_8;
            unsigned int m_heightSize;  // 0xC
            unsigned int pad_10;
        };
        unsigned char pad_0[0x54];
        unsigned int m_vertexTblOfs;   // 0x54: ResSize entries, by DrResMdoSeamVertex::m_dataIdx
        unsigned char pad_58[0x4];
        unsigned int m_textureTblOfs;  // 0x5C: TexSize entries, by DrResMdoSeamTexture::m_dataIdx
        unsigned char pad_60[0x2C];
        unsigned int m_lightTblOfs;    // 0x8C: MdsSeamLgtMapData entries, by DrResMdoSeamWrkLight::m_dataIdx
        unsigned char pad_90[0x4];
        unsigned int m_texListTblOfs;  // 0x94: ResSize entries, by DrResMdoSeamTexList::m_dataIdx
    };

    // the names are not the original's
    unsigned char pad_18C[0x1C];
    const MapHead* m_pMapHead;  // 0x1A8
    unsigned char pad_1B0[0xF0];
    // 0x2A0: the base works in use (DrMdoCtlSeamAll::callShadowCacheUpdate walks them; the name is not the original's)
    DrResMdoSeamWrkBase* m_pBaseList;
    unsigned char pad_2A8[0x68];
    DrResMdoSeamWrkInst* m_pInstList;  // 0x310: the instance works in use (DrMdoCtlSeamAll::occRender walks them)
    unsigned char pad_318[0x380];
    DrResMdoInstAnmObj m_instAnm;  // 0x698: releaseSeam releases it; ScnObjAccSeamPos reads it (m_mdlType 3)
    EtcPosList m_etcPos;           // 0x6C8 (m_mdlType 3)
    unsigned char pad_6D8[0x8];
    // 0x6E0: the destructor destroys it; releaseFreeSeamMemObj frees its blocks
    DrResMdoSeamMemMan m_memMan;
    unsigned char pad_B28[0x10];
    // 0xB38: DrMdoCtlSeamInstMap::beginResAll keeps the material resources it replaces here and endResAll puts them
    // back
    MdoWrkMatRes* m_pSavedWrkMatRes;
    unsigned char pad_B40[0x80];
    unsigned int* m_pLightBits;      // 0xBC0: a bit per light table entry, set by waitLightStream
    unsigned char pad_BC8[0x8];
    unsigned short* m_pVertexNo;     // 0xBD0: by vertex table entry, the DrResMdoSeamVertex::m_no + 1 holding it
    unsigned char pad_BD8[0x8];
    unsigned short* m_pTextureNo;    // 0xBE0: by texture table entry, the DrResMdoSeamTexture::m_no + 1 holding it
    unsigned char pad_BE8[0x8];
    unsigned short* m_pTexListNo;    // 0xBF0: by texture list entry, the DrResMdoSeamTexList::m_no + 1 holding it
    unsigned char pad_BF8[0x14];
    unsigned short m_lightNum;       // 0xC0C: waitLightStream counts the lights in
    unsigned char pad_C0E[0x8];
    short m_offScreenCnt;            // 0xC16: DrMdoCtlSeamAll::noOffScreenUpdate counts its calls
    unsigned char pad_C18[0x1C];
    int m_textureMemSize;            // 0xC34: the texture memory read in
    int m_vertexMemSize;             // 0xC38: the vertex memory read in
    unsigned char pad_C3C[0x30];
    int m_lightMemSize;              // 0xC6C: the light memory read in
    unsigned char pad_C70[0xC];
    // 0xC7C: DrMdoCtlSeamRead::wait*Stream set bit 16 when a stream ends without its data (and bit 10 while
    // DrMan::m_seamReadErrMode is high enough); DrMdoCtlSeamAll::callRenderSeamAll tests bit 3
    unsigned int m_seamFlags;
    unsigned char pad_C80[0x8];
    int m_lightGroup;                // 0xC88: 1 from the constructor; waitLightStream gives it to the light's object
    unsigned char pad_C8C[0x4];
    // 0xC90/0xC98: one bit per shadow cache already rendered, for the base and the instance works:
    // DrMdoCtlSeamAll::callShadowCacheUpdate clears the bits it is given, DrMdoCtlSeamRead::waitBaseVertexStream and
    // waitInstPosStream clear all once their stream is in (the names are not the original's)
    unsigned long m_baseShadowCacheDone;
    unsigned long m_instShadowCacheDone;
    unsigned char pad_CA0[0x30];
    // 0xCD0: the destructor destroys it; DrMdoCtlSeamAll::setDeleteCall cancels its reads
    DrResMdoSeamRead m_seamRead;
};
}  // namespace ml

#endif
