#ifndef CLASSES_FW_TRANSFORMMANAGER_H
#define CLASSES_FW_TRANSFORMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/fw/TransformUpdater.h"

namespace fw { class TransformManager; }

namespace fw {
// table 0x7100B417A0
class TransformManager : public ::mm::mtl::PtrSingleton< ::fw::TransformManager> {
public:
    virtual ~TransformManager();  // slot 0
    void update(unsigned int layerMask);  // Framework::update runs it per layer

    // updater linked last into layer's list (inline: GfComTransform::setup and changeLayer; the name is not the
    // original's)
    void addUpdater(unsigned int layer, TransformUpdater* updater) { m_layers[layer].push_back(updater); }
    // updater unlinked from layer's list (inline: GfComTransform::cleanup and changeLayer; the name is not the
    // original's)
    void removeUpdater(unsigned int layer, TransformUpdater* updater) { m_layers[layer].remove(updater); }

    // one list per layer (update walks all 32 against its mask; GfComTransform links its updater into its layer's;
    // the name is not the original's)
    // (the symbols name mm::mtl::FixedArray<fw::TransformManager::Group, 32>: Framework::createManager's
    // value-initialized new calls its out-of-line constructor)
    class Group : public ::mm::mtl::IntrusiveList<TransformUpdater> {};
    mm::mtl::FixedArray<Group, 32> m_layers;
};
}  // namespace fw

#endif
