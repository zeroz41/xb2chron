// not proven yet: its table differs from the original's (word 4: _ZN5layer12LayerObjMesh7releaseEv where the original has _ZN5layer8LayerObj7releaseEv)
#ifndef CLASSES_LAYER_LAYEROBJLAYOUT_H
#define CLASSES_LAYER_LAYEROBJLAYOUT_H

#include "classes/layer/LayerObjMesh.h"

namespace layer {
// table 0x7100B7FCC8
class LayerObjLayout : public ::layer::LayerObjMesh {
public:
    virtual ~LayerObjLayout();  // slot 0
};
}  // namespace layer

#endif
