#ifndef CLASSES_LAYER_LAYEROBJMANAGER_H
#define CLASSES_LAYER_LAYEROBJMANAGER_H
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerLinkList.h"
#include "layer/LayerRenderView.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerBase; }
namespace layer { class LayerManager; }
namespace layer { class LayerSortMan; }
namespace ml { class IDrDrawWorkInfo; }
namespace ml { class CriticalSection; }

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
    // the lock LayerAccLayoutObj's create functions hold (a function-local static)
    static ml::CriticalSection& getCriticalSection();
    // the objects LayerAccLayoutObj makes under a layout (the caller adds them to its child list)
    static LayerBase* createStaticObj(const void* resource);
    static LayerBase* createStaticMaskObj(const void* resource);
    static LayerBase* createStaticFontObj();
    static LayerBase* createStaticLayoutObj();
    static LayerBase* createStaticTexObj(const grlib::CGLibTextureBuffer& texture);
    static LayerBase* createStaticMemObj(unsigned int width, unsigned int height, LayerMemType type);
    static LayerBase* createStaticPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                                          unsigned short indexCount, LayerPrimitiveType type);

    // The field names are not the original's.
    const ml::IDrDrawWorkInfo* m_drawInfo;  // finalRender's (the constructor leaves it unset)
    LayerManager* m_manager;  // the constructor's
    LayerSortMan* m_sortMan;  // 0x10: made by the constructor (512 2D and 256 3D entries); setDrawList's 3D space
    // its object lists, laid out as LayerFontManager's (the names are LayerFontManager's)
    LayerLinkList<LayerBase> m_objList;
    LayerLinkList<LayerBase> m_setupList[2];
    LayerLinkList<LayerBase> m_deleteList;
    LayerRenderView m_view;  // 0x78: apply resets it and passes it to every object (the name is not the original's)
};
}  // namespace layer

#endif
