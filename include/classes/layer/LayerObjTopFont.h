#ifndef CLASSES_LAYER_LAYEROBJTOPFONT_H
#define CLASSES_LAYER_LAYEROBJTOPFONT_H

#include "classes/layer/LayerObjFont.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FF00
// Derives LayerObjFont: its destructor and applyParams hand this unadjusted to LayerObjFont::workRelease and
// LayerObjFont::updateShaderParms.
class LayerObjTopFont : public ::layer::LayerObjFont {
public:
    virtual ~LayerObjTopFont();  // slot 0
    void finalRender();
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyPartsSetup();  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
