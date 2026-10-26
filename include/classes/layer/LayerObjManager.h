#ifndef CLASSES_LAYER_LAYEROBJMANAGER_H
#define CLASSES_LAYER_LAYEROBJMANAGER_H
#include "layer/LayerAccLayoutObj.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerBase; }
namespace layer { class LayerManager; }
namespace ml { class IDrDrawWorkInfo; }

namespace layer {
// makes the layer objects (LayerAccManager's create functions forward to it); no table
class LayerObjManager {
public:
    LayerObjManager(LayerManager* manager);
    ~LayerObjManager();
    void begin();
    void apply(const ml::IDrDrawWorkInfo* info);
    void finalRender(const ml::IDrDrawWorkInfo* info);
    void end();  // the end of a frame: nothing to do
    LayerBase* createObj(const void* resource);
    LayerBase* createMaskObj(const void* resource);
    LayerBase* createLayoutObj();
    LayerBase* createTexObj(const grlib::CGLibTextureBuffer& texture);
    LayerBase* createMemObj(unsigned int width, unsigned int height, LayerMemType type);
    LayerBase* createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                             unsigned short indexCount, LayerPrimitiveType type);
};
}  // namespace layer

#endif
