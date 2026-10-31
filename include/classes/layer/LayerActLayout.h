#ifndef CLASSES_LAYER_LAYERACTLAYOUT_H
#define CLASSES_LAYER_LAYERACTLAYOUT_H

#include "classes/layer/LayerObjLayout.h"

namespace layer { class LyrActionData; }

namespace layer {
// table none (its derived classes'). Its base LayerObjLayout is inferred: ~LayerObjTopLayout calls
// LayerObjLayout::workLayoutRelease with its this unadjusted and deletes LayerObjLayout's lists.
class LayerActLayout : public ::layer::LayerObjLayout {
public:
    virtual ~LayerActLayout() {}  // slot 0: inline (no table in 3.0.1; ~LayerObjTopLayout inlines it)
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
    // commands a layout object does not run: each only steps cmd past itself
    bool actcmd_notcmd01(const unsigned char*& cmd);
    bool actcmd_notcmd03(const unsigned char*& cmd);
    bool actcmd_notcmd02(const unsigned char*& cmd);
};
}  // namespace layer

#endif
