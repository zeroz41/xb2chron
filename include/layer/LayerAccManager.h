#ifndef LAYER_LAYERACCMANAGER_H
#define LAYER_LAYERACCMANAGER_H

#include "layer/LayerAccLayoutObj.h"

namespace layer { class LayerBase; }

namespace layer {
// the coordinates layer objects are placed in (UIUtil::initLayerLib sets 0; no value has a name yet)
enum LayerCoordinate : int;

// access to the layer manager: makes objects outside any layout (UIPolygonObject's without a parent)
class LayerAccManager {
public:
    LayerAccManager();
    void setCoordinate(LayerCoordinate coordinate);
    LayerBase* createObj(const void* resource);  // the objects made, or null
    LayerBase* createMaskObj(const void* resource);
    LayerBase* createLayoutObj();
    LayerBase* createTexObj(const grlib::CGLibTextureBuffer& texture);
    LayerBase* createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                             unsigned short indexCount, LayerPrimitiveType type);  // the object made, or null
};
}  // namespace layer

#endif
