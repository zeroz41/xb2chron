#ifndef ML_DRRESMDOVERTEX_H
#define ML_DRRESMDOVERTEX_H

namespace grlib { class CGLibVtxVertex; }
namespace grlib { class CGLibVtxIndex; }
namespace grlib { class CGLibVtlMemPool; }
namespace grlib { class CGLibOneUniformBlock; }
namespace grlib { class CGLibOneUniformArray; }

namespace ml {
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
        unsigned char pad_4[0x8];
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

    void* m_link0;  // 0x0: zeroed by the constructor
    DrResMdoVertex* m_pNext;  // 0x8: zeroed by the constructor; DrMdoVertexMan's list link (the name is not the original's)
    const unsigned char* m_resData;  // 0x10: the constructor's data
    int m_state;  // 0x18: 1 after construction
    void* m_work;  // 0x20: allocated by setupVertex, freed by vertexRelease
    const unsigned char* m_vtxData;  // 0x28
    const BindEntry* m_bindTbl;  // 0x30
    const unsigned char* m_etcData;  // 0x38
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
    void* m_stream;  // 0x78: update reloads the buffers only when it is set
};
}  // namespace ml

#endif
