#include "classes/fw/TransformManager.h"
#include "classes/fw/TransformUpdater.h"

namespace fw {

void TransformManager::update(unsigned int layerMask) {
    for (int i = 0; i < 32; ++i) {
        if ((1 << i) & layerMask) {
            for (mm::mtl::IntrusiveList<TransformUpdater>::iterator it = m_layers[i].begin(); it != m_layers[i].end();
                 ++it) {
                (*it).resolveWorldTrasform();
            }
        }
    }
}

}  // namespace fw
