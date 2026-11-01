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
    };
    void releasePoly(layPolyWork& work);

    // what Unlock*/setIndexInfo mark as updated, each bit shifted by LayerManager::s_nStkIdx (not the original's)
    enum {
        UPDATE_VERTEX = 0x4,  // UnlockVertex
        UPDATE_INDEX = 0x10,  // UnlockIndex
        UPDATE_INDEX_INFO = 0x40,  // setIndexInfo
    };
    // The field names follow the functions that use them (not the original's).
    unsigned int m_updateFlags;  // UPDATE_*
    unsigned char pad_254[0x4];
    const void* m_viewData;  // applyParams copies LayerRenderView::m_viewData (the name is not the original's)
    LayerObjSortPolyObj m_sortObj;  // 0x260: what setDrawList puts in the sort lists (the name is not the original's)
    unsigned char pad_278[0x8];
    grlib::CGLibDblUniformBlock m_uniform;  // 0x280: applyParams updates it (the name is not the original's)
    LayerObjResTex m_resTex;  // 0x2B8: setTexutre adds to it, the destructor clears it (the name is not the original's)
    layPolyWork m_polyWork;  // 0x300: the destructor releases it (the name is not the original's)
    LayerPolyVertex* m_vertices[2];  // LockVertex, indexed by LayerManager::s_nStkIdx
    unsigned short* m_indices[2];  // LockIndex, indexed by LayerManager::s_nStkIdx
    unsigned char pad_340[0x4];
    unsigned short m_indexStart[2];  // setIndexInfo
    unsigned short m_indexCount[2];  // setIndexInfo
    unsigned char pad_34C[0xC];
    void* m_locked;  // the buffer Lock* returned to setVertex/setIndex, cleared by Unlock*
    unsigned char pad_360[0x8];
    void* m_polyBuffer;  // 0x368: the destructor deallocates it (createPolyObj allocates 0x370; the name is not the original's)
};
}  // namespace layer

#endif
