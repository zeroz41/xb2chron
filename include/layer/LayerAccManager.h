#ifndef LAYER_LAYERACCMANAGER_H
#define LAYER_LAYERACCMANAGER_H

#include "layer/LayerAccLayoutObj.h"

namespace layer { class LayerBase; }

namespace layer {
// the coordinates layer objects are placed in (UIUtil::initLayerLib sets 0; no value has a name yet)
enum LayerCoordinate : unsigned int;  // unsigned: LayerObjUtil::getLayoutInfo indexes its table with it zero-extended

// access to the layer manager: makes objects outside any layout (UIPolygonObject's without a parent)
class LayerAccManager {
public:
    LayerAccManager();
    void setCoordinate(LayerCoordinate coordinate);
    LayerCoordinate getCoordinate() const;
    float getScreenWidth() const;
    float getScreenHeight() const;
    void setGamma(float gamma);
    LayerBase* createObj(const void* resource);  // the objects made, or null
    LayerBase* createMaskObj(const void* resource);
    LayerBase* createLayoutObj();
    // the font objects made from a font resource's data (UIFontManager::update's)
    LayerBase* createFontResObj(const void* data);
    LayerBase* createFontStyleObj(const void* data);
    LayerBase* createFontColorMapObj(const void* data);
    LayerBase* createFontIconObj(const void* data);
    LayerBase* createTexObj(const grlib::CGLibTextureBuffer& texture);
    LayerBase* createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                             unsigned short indexCount, LayerPrimitiveType type);  // the object made, or null
    // a memory object of that size (fw::MovieManager::open draws its movie into one)
    LayerBase* createMemObj(unsigned int width, unsigned int height, LayerMemType type);
};
}  // namespace layer

#endif
