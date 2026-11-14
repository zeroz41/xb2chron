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
    struct Work {
        Work* m_prev;  // 0x00
        Work* m_next;  // 0x08
        unsigned char pad_10[0x20];
        // tests the bit of a LayerManager::s_nDebIdx (inline in update; the name is not the original's)
        bool isFlag(int bit) const { return (m_flags & (1 << bit)) != 0; }
        unsigned int m_flags;  // 0x30, a bit per LayerManager::s_nDebIdx: update moves the work to m_deleteList
    };

    LayerManager* m_pManager;  // 0x00, the constructor's argument
    LayerLinkList<Work> m_freeList;  // 0x08, update moves the works it takes out of the lists here
    // 0x20, by LayerManager::s_nDebIdx; the constructor empties them in its body (the stores come after
    // m_deleteList's: the 0x50 list first)
    LayerLinkList<Work> m_lists[2];
    LayerLinkList<Work> m_deleteList;  // 0x50, update deletes its works first (the name is not the original's)
};
}  // namespace layer

#endif
