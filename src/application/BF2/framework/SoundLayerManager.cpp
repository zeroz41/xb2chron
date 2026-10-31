#include "classes/fw/SoundLayerManager.h"

namespace fw {

SoundLayerManager::SoundLayerManager() {}

SoundLayerManager::~SoundLayerManager() {}

void SoundLayerManager::update(unsigned int layerMask) {
    for (unsigned int i = 0; i < 32; ++i) {
        if (layerMask & (1 << i)) {
            mm::mtl::IntrusiveList<SoundUpdater>& list = m_layers[i];
            for (mm::mtl::IntrusiveList<SoundUpdater>::iterator it = list.begin(); it != list.end(); ++it) {
                SoundUpdater& updater = *it;
                updater.m_keep = updater.m_delegate.isValid() ? updater.m_delegate() != 0 : false;
            }
            for (mm::mtl::IntrusiveList<SoundUpdater>::iterator it = list.begin(); it != list.end();) {
                if (it->m_keep) {
                    ++it;
                } else {
                    it->m_linked = false;
                    it = list.erase(it);
                }
            }
        }
    }
}

}  // namespace fw
