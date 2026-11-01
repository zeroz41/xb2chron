#ifndef LAYER_LAYERRCEMANAGER_H
#define LAYER_LAYERRCEMANAGER_H

#include "layer/LayerLinkList.h"

namespace layer {
class LayerManager;

// built from layer::LayerManager (its code shares LayerShdManager's file); the field names are not the original's
class LayerRceManager {
public:
    LayerRceManager(LayerManager* manager);
    ~LayerRceManager();
    void update();

    // what the lists link (update reads a mask at 0x30 against LayerManager::s_nDebIdx; the name is not the original's)
    struct Work;

    LayerManager* m_pManager;  // 0x00, the constructor's argument
    LayerLinkList<Work> m_freeList;  // 0x08, update moves the works it takes out of the lists here
    LayerLinkList<Work> m_lists[3];  // 0x20, by LayerManager::s_nDebIdx (update deletes the last one's works)
};
}  // namespace layer

#endif
