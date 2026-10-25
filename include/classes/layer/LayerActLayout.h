#ifndef CLASSES_LAYER_LAYERACTLAYOUT_H
#define CLASSES_LAYER_LAYERACTLAYOUT_H

#include "classes/layer/LayerObj.h"

namespace layer { class LyrActionData; }

namespace layer {
// table none (its derived classes')
class LayerActLayout : public ::layer::LayerObj {
public:
    virtual ~LayerActLayout();  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
    // commands a layout object does not run: each only steps cmd past itself
    bool actcmd_notcmd01(const unsigned char*& cmd);
    bool actcmd_notcmd03(const unsigned char*& cmd);
    bool actcmd_notcmd02(const unsigned char*& cmd);
};
}  // namespace layer

#endif
