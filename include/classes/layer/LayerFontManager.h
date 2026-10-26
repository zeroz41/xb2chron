#ifndef CLASSES_LAYER_LAYERFONTMANAGER_H
#define CLASSES_LAYER_LAYERFONTMANAGER_H

namespace layer { class LayerBase; }
namespace layer { class LayerFontIconObj; }
namespace layer { class LayerFontStyleObj; }

namespace layer {
class LayerManager;
// makes the font objects (LayerAccManager's font create functions forward to it); no table
class LayerFontManager {
public:
    LayerFontManager(LayerManager* manager);
    ~LayerFontManager();
    void update();
    LayerBase* createFontResObj(const void* data);
    LayerBase* createFontIconObj(const void* data);
    LayerBase* createStyleObj(const void* data);
    LayerBase* createFontColMapObj(const void* data);

    unsigned char pad_0[0x68];
    // what LayerAccFontObj::setMsg draws with when the object has none (the names are not the original's): the
    // first stands in for both the font and the icon object
    const LayerBase* m_defaultObj;
    const LayerFontStyleObj* m_defaultStyle;
};
}  // namespace layer

#endif
