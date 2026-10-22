#ifndef LAYER_LAYERACCMANAGER_H
#define LAYER_LAYERACCMANAGER_H

#include "layer/LayerAccLayoutObj.h"

namespace layer { class LayerBase; }

namespace layer {
// access to the layer manager: makes objects outside any layout (UIPolygonObject's without a parent)
class LayerAccManager {
public:
    LayerAccManager();
    LayerBase* createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                             unsigned short indexCount, LayerPrimitiveType type);  // the object made, or null
};
}  // namespace layer

#endif
