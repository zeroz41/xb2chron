#ifndef CLASSES_LAYER_LAYERFONTMANAGER_H
#define CLASSES_LAYER_LAYERFONTMANAGER_H

#include "layer/LayerBase.h"
#include "layer/LayerLinkList.h"

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

    // deletes every object of its lists (1.0.0's allRelease; inline in 3.0.1's destructor)
    void allRelease() {
        deleteAll(m_objList);
        deleteAll(m_setupList[0]);
        deleteAll(m_setupList[1]);
        deleteAll(m_deleteList);
        deleteAll(m_styleList);
    }
    // deletes list's objects and empties it (the name is not the original's)
    static void deleteAll(LayerLinkList<LayerBase>& list) {
        for (LayerBase* obj = list.m_head; obj != nullptr;) {
            LayerBase* next = obj->m_next;
            delete obj;
            obj = next;
        }
        list.m_num = 0;
        list.m_head = nullptr;
        list.m_tail = nullptr;
    }

    // The names are not the original's.
    LayerLinkList<LayerBase> m_objList;  // 0x0: the set-up objects (update moves them from m_setupList)
    // 0x18: the objects made while LayerManager::s_nStkIdx names each, before update sets them up
    LayerLinkList<LayerBase> m_setupList[2];
    LayerLinkList<LayerBase> m_deleteList;  // 0x48: the released objects update deletes the frame after
    // the first font object (0x60) and icon object (0x68) made, what LayerAccFontObj::setMsg draws with when the
    // object has none: the second stands in for both the font and the icon object there
    const LayerBase* m_defaultResObj;
    const LayerBase* m_defaultObj;
    const LayerFontStyleObj* m_defaultStyle;
    LayerLinkList<LayerBase> m_styleList;  // 0x78
    LayerManager* m_manager;  // 0x90: the constructor's
};
}  // namespace layer

#endif
