#ifndef CLASSES_LAYER_LAYEROBJLAYOUT_H
#define CLASSES_LAYER_LAYEROBJLAYOUT_H

#include "classes/layer/LayerActBase.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerLinkList.h"
#include "layer/LayerViewPort.h"

namespace layer { class LyrLayoutPosData; }

namespace layer {
// table 0x7100B7FCC8
class LayerObjLayout : public ::layer::LayerActBase {
public:
    LayerObjLayout();
    virtual ~LayerObjLayout() {}  // slot 0: inline (its deleting destructor sits in the unit's tail)

    void workLayoutRelease();

    // The field names follow LayerAccLayoutObj's accessors (not the original's).
    // 0x258: deleted with m_childList by ~LayerObjTopLayout (the name is not the original's)
    LayerLinkList<LayerBase> m_objList;
    // 0x270: the objects LayerAccLayoutObj's create functions made while LayerManager::s_nStkIdx names each (the
    // name is not the original's)
    LayerLinkList<LayerBase> m_childList[2];
    // 0x2A0: what LayerObjTopLayout::workLayoutCreate keeps of its layout binary (the names are not the original's)
    const void* m_layoutData;  // the header's m_dataOfs
    const LyrLayoutPosData* m_posData;
    LayerViewPort m_viewPort;  // 0x2B0: setViewPort
    LAYER_ANCHOR m_anchorMode;  // setAutoAnchorMode
    unsigned short m_priorityTblCount[2];  // createPriorityTbl, indexed by LayerManager::s_nStkIdx
};
}  // namespace layer

#endif
