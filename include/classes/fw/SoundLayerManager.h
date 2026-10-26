#ifndef CLASSES_FW_SOUNDLAYERMANAGER_H
#define CLASSES_FW_SOUNDLAYERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class SoundLayerManager; }

namespace fw {
// table 0x7100B42D50
class SoundLayerManager : public ::mm::mtl::PtrSingleton< ::fw::SoundLayerManager> {
public:
    virtual ~SoundLayerManager();  // slot 0
    void update(unsigned int layerMask);  // Framework::update runs it per layer
    // the components of each layer (GfComSound links its node into its layer's; the count is Ghidra's reading of
    // the constructor's 31 constructions, unverified; the name is not the original's)
    mm::mtl::IntrusiveList<mm::mtl::IntrusiveListNodeBase> m_layers[31];
};
}  // namespace fw

#endif
