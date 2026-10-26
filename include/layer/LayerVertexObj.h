#ifndef LAYER_LAYERVERTEXOBJ_H
#define LAYER_LAYERVERTEXOBJ_H

namespace grlib { class CGLibVtlMemPool; class CGLibVtxIndex; class CGLibVtxVertex; }

namespace layer {
class LayerManager;
class LayerVertexMan;

// a vertex resource's header: vertex and index buffer tables (offsets from the header) and the GPU data the buffers
// sit in. The names are not the original's
struct LayerResVertexHead {
    unsigned int m_vertexOfs;  // 0x0: LayerResVertexInfo table
    int m_vertexNum;           // 0x4
    unsigned int m_indexOfs;   // 0x8: LayerResIndexInfo table
    int m_indexNum;            // 0xC
    unsigned int m_dataOfs;    // 0x10
    unsigned int m_dataSize;   // 0x14
};
// one vertex buffer (0xC bytes; the names are not the original's)
struct LayerResVertexInfo {
    unsigned int m_offset;  // 0x0: into the data
    unsigned int m_count;   // 0x4
    unsigned char m_type;   // 0x8: s_nVertexSize's index
    unsigned char pad_9[0x3];
};
// one index buffer (8 bytes; the names are not the original's)
struct LayerResIndexInfo {
    unsigned int m_offset;  // 0x0: into the data
    unsigned int m_count;   // 0x4
};

// the stride of each vertex type (LayerResVertexInfo::m_type)
extern unsigned short s_nVertexSize[4];

// a layer object's vertex buffers, shared by everything that uses the resource: LayerVertexMan counts the users
// (0x68 bytes; the field names are not the original's)
class LayerVertexObj {
public:
    LayerVertexObj(const unsigned char* res, LayerManager* manager, LayerVertexMan* owner);
    ~LayerVertexObj() {}
    void setupVertex(const unsigned char* res, LayerManager* manager);
    void vertexRelease();
    void release();
    void begin();
    // binds the vertex buffer of the index unless it is bound already (layer::LayerShdManager::setupVertex)
    bool setVertex(unsigned int index);
    void render(unsigned int index);

    // one user fewer (never below 0); true when none is left (the name is not the original's)
    bool subRef() {
        m_refCount--;
        if (m_refCount < 0) {
            m_refCount = 0;
        }
        return m_refCount <= 0;
    }

    LayerVertexObj* m_prev;            // 0x0
    LayerVertexObj* m_next;            // 0x8
    const unsigned char* m_key;        // 0x10: the resource createVertexObj looks it up by
    int m_refCount;                    // 0x18
    short m_curVertex;                 // 0x1C: the bound vertex buffer, -1 after begin
    void* m_mem;                       // 0x20: the pool, then the vertex and index buffers
    int m_vertexNum;                   // 0x28
    int m_indexNum;                    // 0x2C
    const LayerResVertexHead* m_res;   // 0x30
    const LayerResVertexInfo* m_vertexInfo;  // 0x38
    const LayerResIndexInfo* m_indexInfo;    // 0x40
    grlib::CGLibVtxVertex* m_vertices;  // 0x48
    grlib::CGLibVtxIndex* m_indices;    // 0x50
    grlib::CGLibVtlMemPool* m_pool;     // 0x58
    LayerVertexMan* m_owner;            // 0x60
};
}  // namespace layer

#endif
