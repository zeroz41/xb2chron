#ifndef ML_DRRESMDOVERTEX_H
#define ML_DRRESMDOVERTEX_H

namespace grlib { class CGLibVtxVertex; }
namespace grlib { class CGLibVtxIndex; }
namespace grlib { class CGLibVtlMemPool; }
namespace grlib { class CGLibOneUniformBlock; }
namespace grlib { class CGLibOneUniformArray; }

namespace ml {
class DrCalcStmListObj;
// A model's vertex resource: vertex and index buffers set up from the resource data in a memory pool.
// The field names and the WeightHead type are not the original's.
class DrResMdoVertex {
public:
    // the weight block of the resource data: getWeightVertex/getWeightVertexInfo read it
    struct WeightHead {
        unsigned char pad_0[0x4];
        unsigned int infoOffset;  // 0x4: offset of the 0x28-byte infos from the data
        unsigned short vertexNo;  // 0x8: the weight vertex buffer
        unsigned char pad_A[0x2];
        unsigned int tableOffset;  // 0xC: offset of the 9-per-row info index table
    };
    // one 0x28-byte weight info (getWeightVertexInfo)
    struct WeightInfo {
        unsigned char pad_0[0x28];
    };
    // one 0xC-byte entry of the bind table (0x30): setEtcVertexBind binds its extra vertex buffer
    struct BindEntry {
        unsigned short pad_0;
        unsigned short vertexNo;  // 0x2
        unsigned short uniformNo;  // 0x4: setMofBlendVertexBind's uniform block and etc entry
        unsigned char pad_6[0x6];
    };
    // one 0x10-byte entry of the etc data (0x38): setMofBlendVertexBind binds its uniform block with this stride
    struct EtcEntry {
        unsigned char pad_0[0x8];
        int stride;  // 0x8
        unsigned char pad_C[0x4];
    };
    // the head of the vertex data (0x28): the weight vertex buffer number per weight index from 0x10 (0 = none)
    // (the count of weightVertexNo is inferred from morphOfs that follows it)
    struct VertexHead {
        unsigned char pad_0[0x10];
        unsigned short weightVertexNo[12];  // 0x10
        unsigned int morphOfs;  // 0x28: offset of the MorphHead from the data
    };
    // the morph block of the vertex data (DrMdoMorphing's passes walk its entries)
    struct MorphHead {
        int entryNum;            // 0x0
        unsigned int entryOfs;   // 0x4: offset of the MorphEntry list from the data
        unsigned char pad_8[0x4];
        unsigned int bufferOfs;  // 0xC: offset of the MorphBuffer list from the data
    };
    // one morph entry (0x14 bytes): its uniform blocks in MdoWrkMatRes::m_pMofBlendArray start at uniformNo
    // (the default vertices, then the old positions, then one per target)
    struct MorphEntry {
        unsigned char pad_0[0x4];
        unsigned int uniformNo;   // 0x4
        int targetNum;            // 0x8
        unsigned int targetOfs;   // 0xC: offset of the targets' unsigned short numbers from the data
        signed char declIdx;      // 0x10: the stream-out shader's declaration
        unsigned char pad_11[0x3];
    };
    // one 0x10-byte buffer info, indexed like the uniform blocks
    struct MorphBuffer {
        unsigned char pad_0[0x4];
        int vertexNum;  // 0x4
        unsigned char pad_8[0x8];
    };
    // the extra vertex buffer and uniform block (0x70)
    struct EtcBlock {
        grlib::CGLibVtxVertex* vertex;
        grlib::CGLibOneUniformBlock* uniform;
    };

    DrResMdoVertex(const unsigned char* data);
    ~DrResMdoVertex();
    void setupVertex(const unsigned char* data);
    void vertexRelease();
    void changeMemVertex(const unsigned char* data);
    void update();
    void beginVertexSetup();
    void render(int index);
    void renderIns(int index, int instances);
    int getVertexMax(int index) const;
    grlib::CGLibVtxVertex* getWeightVertex();
    const WeightInfo* getWeightVertexInfo(int no, int lv);
    void setVertexBind(int index);
    void setEtcVertexBind(int index, int slot);
    // binds the uniform block of the bind entry as a vertex stream (the morph blend weights, as the name says)
    void setMofBlendVertexBind(grlib::CGLibOneUniformArray* array, int index, int slot);
    // binds the weight vertex buffer of the index; returns its vertex count (0 when it has none)
    int setWeightVertexBind(int index);

    DrResMdoVertex* m_pPrev;  // 0x0: zeroed by the constructor; DrMdoVertexMan's list link (the name is not the original's)
    DrResMdoVertex* m_pNext;  // 0x8: zeroed by the constructor; DrMdoVertexMan's list link (the name is not the original's)
    const unsigned char* m_resData;  // 0x10: the constructor's data
    int m_state;  // 0x18: 1 after construction; a reference count (DrMdoVertexMan::releaseVertexObj drops it)
    void* m_work;  // 0x20: allocated by setupVertex, freed by vertexRelease
    const unsigned char* m_vtxData;  // 0x28
    const BindEntry* m_bindTbl;  // 0x30
    const EtcEntry* m_etcData;  // 0x38
    const WeightHead* m_weight;  // 0x40
    unsigned short m_vertexNum;  // 0x48
    unsigned short m_indexNum;  // 0x4A
    unsigned short m_etcVertexNum;  // 0x4C
    short m_bindVertex;  // 0x4E: -1 when no vertex buffer is bound
    grlib::CGLibVtxVertex* m_vertex;  // 0x50
    grlib::CGLibVtxIndex* m_index;  // 0x58
    grlib::CGLibVtxVertex* m_etcVertex;  // 0x60
    grlib::CGLibVtlMemPool* m_memPool;  // 0x68
    EtcBlock* m_etc;  // 0x70
    DrCalcStmListObj* m_stream;  // 0x78: update reloads the buffers only when it is set
};
}  // namespace ml

#endif
