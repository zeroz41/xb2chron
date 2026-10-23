#ifndef CLASSES_LAYER_LAYEROBJWORK_H
#define CLASSES_LAYER_LAYEROBJWORK_H

#include "classes/layer/LayerActBase.h"

namespace layer {
// table 0x7100B801A0
class LayerObjWork : public ::layer::LayerActBase {
public:
    virtual ~LayerObjWork();  // slot 0
    void setAddTexture(const void* texture, unsigned int index);
};
}  // namespace layer

#endif
