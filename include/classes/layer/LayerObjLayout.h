#ifndef CLASSES_LAYER_LAYEROBJLAYOUT_H
#define CLASSES_LAYER_LAYEROBJLAYOUT_H

#include "classes/layer/LayerActBase.h"
#include "layer/LayerAccLayoutObj.h"

namespace layer {
// table 0x7100B7FCC8
class LayerObjLayout : public ::layer::LayerActBase {
public:
    virtual ~LayerObjLayout();  // slot 0

    // The field names follow LayerAccLayoutObj's accessors (not the original's).
    unsigned char pad_258[0x58];
    float m_viewPortX;  // setViewPort
    float m_viewPortY;
    float m_viewPortWidth;
    float m_viewPortHeight;
    LAYER_ANCHOR m_anchorMode;  // setAutoAnchorMode
    unsigned short m_priorityTblCount[2];  // createPriorityTbl, indexed by LayerManager::s_nStkIdx
};
}  // namespace layer

#endif
