#ifndef CLASSES_LAYER_LAYEROBJTOPDEF_H
#define CLASSES_LAYER_LAYEROBJTOPDEF_H

#include "classes/layer/LayerActDef.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FE98
class LayerObjTopDef : public ::layer::LayerActDef {
public:
    virtual ~LayerObjTopDef();  // slot 0
    void finalRender();
    virtual void resourceInit();  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7

    // The field names follow LayerAccDefObj's accessors (its objects of type 1; not the original's).
    unsigned char pad_248[0x58];
    float m_param;  // setParm
    unsigned short m_iconNum;  // setIconNum / getIconNum
    unsigned short m_iconMax;  // getIconMax
    unsigned short m_gauge;  // setGauge / getGauge (a LAYER_GAUGE)
};
}  // namespace layer

#endif
