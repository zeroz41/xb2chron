#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/ManagerRegister.h"
#include "classes/fw/LayerSetManager.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/layer/LayerManager.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

LayerSetManager::LayerSetManager() : m_layerManager(nullptr) {}

bool LayerSetManager::initialize() {
    if (m_layerManager == nullptr) {
#line 31
        m_layerManager = new (Framework::getAllocator(), 16, __FILE__, __LINE__)
            layer::LayerManager(Framework::get()->m_scn, FrameworkMemory::getMem(1), 0xE00000);
    }
    return true;
}

bool LayerSetManager::finalize() {
    if (m_layerManager != nullptr) {
        delete m_layerManager;
        m_layerManager = nullptr;
    }
    return true;
}

void LayerSetManager::tail() {
    if (!isFinalized() && m_layerManager != nullptr) {
        m_layerManager->tail();
    }
}

LayerSetManager::~LayerSetManager() {}

}  // namespace fw
