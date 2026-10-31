#ifndef CLOUD_CLOUDMDLDATAOBJ_H
#define CLOUD_CLOUDMDLDATAOBJ_H

#include "grlib/CGLibVtlMemPool.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxIndex.h"

namespace cloud {

class CloudMdlParts;

// one part's record in a cloud model's data (0xD0; the name is CloudUniform::createMdlPolyUniform's parameter type).
// The field names are not the original's.
class CMLObjData {
public:
    unsigned char pad_0[0x50];
    float m_pos[3];                // 0x50
    unsigned char pad_5C[0x14];
    float m_params0[7];            // 0x70
    float m_param;                 // 0x8C
    float m_params1[7];            // 0x90
    unsigned short m_dispBit;      // 0xAC
    unsigned char pad_AE[0x6];
    unsigned short m_meshIdx;      // 0xB4, the CloudMdlDataObj::MeshInfo index
    unsigned char m_type;          // 0xB6
    unsigned char m_flags;         // 0xB7: bit 0 picks the part's scroll type
    unsigned char pad_B8[0x18];
};

// a cloud model's data (0x88: CloudObjMan::createMdlData allocates it), kept in CloudObjMan's model data list. The
// field names are not the original's.
class CloudMdlDataObj {
public:
    // the data's header (create reads it; the names are not the original's)
    struct Header {
        unsigned char pad_0[0xC];
        unsigned int m_objDataOfs;  // 0xC, the CMLObjData records
        int m_objDataNum;           // 0x10
        unsigned int m_meshOfs;     // 0x14, the MeshInfo records
        unsigned char pad_18[0x4];
        unsigned int m_vtxOfs;      // 0x1C, the VtxHeader
    };
    struct VtxHeader {
        unsigned int m_infoOfs;  // 0x0, m_num VtxInfo records
        unsigned int m_num;      // 0x4
        unsigned int m_bufOfs;   // 0x8, the vertex and index memory
        unsigned int m_bufSize;  // 0xC
    };
    struct VtxInfo {
        unsigned int m_vtxOfs;   // 0x0
        unsigned int m_vtxSize;  // 0x4
        unsigned int m_idxOfs;   // 0x8
        unsigned int m_idxSize;  // 0xC, bytes of 16-bit indices
    };
    // one draw: the vertex buffer and the indices of it
    struct MeshInfo {
        unsigned short m_vtxIdx;  // 0x0, the VtxBuf index
        unsigned short m_count;   // 0x2
        unsigned int m_start;     // 0x4, the first index
    };
    // one vertex buffer and its index buffer (0x50)
    struct VtxBuf {
        grlib::CGLibVtxVertex m_vertex;  // 0x0
        grlib::CGLibVtxIndex m_index;    // 0x28
    };

    CloudMdlDataObj();
    ~CloudMdlDataObj();
    void releaseData();
    void create(const void* data);
    // marks the data released for the current double-buffer index (update then lets it go)
    void release();
    // false once the data is no longer used (CloudObjMan::update then releases it)
    bool update();
    // DrMdoCtlCldMdl::update/dispOffUpdate pass true/false
    void setCallDisp(bool disp);

    // inline (CloudMdlParts::createUniform, no symbol; the name is not the original's)
    const CMLObjData& getObjData(unsigned short index) const { return m_pObjData[index]; }

    CloudMdlDataObj* m_pPrev;          // 0x0
    CloudMdlDataObj* m_pNext;          // 0x8
    void* m_pList;                     // 0x10, the CloudList holding it
    grlib::CGLibVtlMemPool m_memPool;  // 0x18
    const void* m_pFile;               // 0x48
    const CMLObjData* m_pObjData;      // 0x50
    const MeshInfo* m_pMesh;           // 0x58
    void* m_pAlloc;                    // 0x60, holds m_ppParts then m_pVtxBuf
    VtxBuf* m_pVtxBuf;                 // 0x68
    CloudMdlParts** m_ppParts;         // 0x70
    int m_vtxNum;                      // 0x78
    int m_partsNum;                    // 0x7C
    unsigned int m_flags;              // 0x80: bit 0 shown; 0x40 << CloudMan::s_nDblStIdx released
    unsigned char pad_84[0x4];
};

}  // namespace cloud

#endif
