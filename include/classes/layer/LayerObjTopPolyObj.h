#ifndef CLASSES_LAYER_LAYEROBJTOPPOLYOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPPOLYOBJ_H

#include "classes/layer/LayerObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "layer/LayerObjResTex.h"
#include "classes/layer/LayerObjSortPolyObj.h"

namespace grlib { class CGLibTextureBuffer; }
namespace grlib { class CGLibVtxVertex; }
namespace grlib { class CGLibVtxIndex; }
namespace layer { struct LayerPolyVertex; }
namespace layer { class LayerRenderView; }
namespace layer { class LayerResViewPortInfo; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B80088
class LayerObjTopPolyObj : public ::layer::LayerObj {
public:
    // LayerObjManager::createStaticPolyObj
    LayerObjTopPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount, unsigned short indexCount,
                       LayerPrimitiveType type);
    virtual ~LayerObjTopPolyObj();  // slot 0
    void finalRender();
    void LockVertex();
    void setVertex(unsigned int index, const LayerPolyVertex& vertex);
    void UnlockVertex();
    void LockIndex();
    void setIndex(unsigned int index, unsigned short value);
    void UnlockIndex();
    void setIndexInfo(unsigned short start, unsigned short count);
    void setTexutre(const void* texture);
    void setTexutre(grlib::CGLibTextureBuffer& texture);
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyPartsSetup();  // slot 8
    // rebuilds the vertex buffer (applyPartsSetup)
    void updateVertexBuffer();
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9

    // the polygon's vertex and index buffers, two of each (releasePoly deletes them; the field names are not the
    // original's)
    struct layPolyWork {
        grlib::CGLibVtxVertex* m_vertex[2];  // 0x0
        grlib::CGLibVtxIndex* m_index[2];    // 0x10
        // what setVertex/setIndex write (LockVertex/LockIndex, indexed by LayerManager::s_nStkIdx); updateVertexBuffer
        // copies them into the buffers through the work (its m_vertex and m_vertices share one base)
        LayerPolyVertex* m_vertices[2];  // 0x20
        unsigned short* m_indices[2];  // 0x30
    };
    void releasePoly(layPolyWork& work);

    // what Unlock*/setIndexInfo mark as updated, each bit shifted by LayerManager::s_nStkIdx (not the original's)
    enum {
        UPDATE_VERTEX = 0x4,  // UnlockVertex
        UPDATE_INDEX = 0x10,  // UnlockIndex
        UPDATE_INDEX_INFO = 0x40,  // setIndexInfo
        // updateVertexBuffer sets them when it switched m_vertexBufIdx/m_indexBufIdx (the names are not the original's)
        UPDATE_VERTEX_BUF = 0x1,
        UPDATE_INDEX_BUF = 0x2,
    };
    // The field names follow the functions that use them (not the original's).
    unsigned int m_updateFlags;  // UPDATE_*
    unsigned char pad_254[0x4];
    // applyParams copies LayerRenderView::m_viewData; finalRender sets it as the viewport (the name is not the
    // original's)
    LayerResViewPortInfo* m_viewData;
    LayerObjSortPolyObj m_sortObj;  // 0x260: what setDrawList puts in the sort lists (the name is not the original's)
    // the first added texture (updateVertexBuffer; finalRender draws with it when set; the name is not the original's)
    grlib::CGLibTextureBuffer* m_texture;
    grlib::CGLibDblUniformBlock m_uniform;  // 0x280: applyParams updates it (the name is not the original's)
    LayerObjResTex m_resTex;  // 0x2B8: setTexutre adds to it, the destructor clears it (the name is not the original's)
    layPolyWork m_polyWork;  // 0x300: the destructor releases it (the name is not the original's)
    unsigned char pad_340[0x4];
    unsigned short m_indexStart[2];  // setIndexInfo
    unsigned short m_indexCount[2];  // setIndexInfo
    // what updateVertexBuffer took over from the UPDATE_* entries: the index range finalRender draws and which
    // m_polyWork buffer of each kind holds the data (the names are not the original's)
    unsigned short m_drawIndexStart;  // 0x34C
    unsigned short m_drawIndexCount;  // 0x34E
    unsigned short m_vertexBufIdx;  // 0x350
    unsigned short m_indexBufIdx;  // 0x352
    unsigned char pad_354[0x4];
    void* m_locked;  // the buffer Lock* returned to setVertex/setIndex, cleared by Unlock*
    unsigned char pad_360[0x8];
    void* m_polyBuffer;  // 0x368: the destructor deallocates it (createPolyObj allocates 0x370; the name is not the original's)
};
}  // namespace layer

#endif
