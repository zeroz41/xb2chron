#ifndef CLASSES_LAYER_LAYEROBJTOPPOLYOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPPOLYOBJ_H

#include "classes/layer/LayerObj.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { struct LayerPolyVertex; }
namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B80088
class LayerObjTopPolyObj : public ::layer::LayerObj {
public:
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
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9

    // what Unlock*/setIndexInfo mark as updated, each bit shifted by LayerManager::s_nStkIdx (not the original's)
    enum {
        UPDATE_VERTEX = 0x4,  // UnlockVertex
        UPDATE_INDEX = 0x10,  // UnlockIndex
        UPDATE_INDEX_INFO = 0x40,  // setIndexInfo
    };
    // The field names follow the functions that use them (not the original's).
    unsigned char pad_248[0x8];
    unsigned int m_updateFlags;  // UPDATE_*
    unsigned char pad_254[0xCC];
    LayerPolyVertex* m_vertices[2];  // LockVertex, indexed by LayerManager::s_nStkIdx
    unsigned short* m_indices[2];  // LockIndex, indexed by LayerManager::s_nStkIdx
    unsigned char pad_340[0x4];
    unsigned short m_indexStart[2];  // setIndexInfo
    unsigned short m_indexCount[2];  // setIndexInfo
    unsigned char pad_34C[0xC];
    void* m_locked;  // the buffer Lock* returned to setVertex/setIndex, cleared by Unlock*
};
}  // namespace layer

#endif
