#ifndef CLASSES_FW_SOUNDLAYERMANAGER_H
#define CLASSES_FW_SOUNDLAYERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/fw/SoundUpdater.h"

namespace fw { class SoundLayerManager; }

namespace fw {
// table 0x7100B42D50
class SoundLayerManager : public ::mm::mtl::PtrSingleton< ::fw::SoundLayerManager> {
public:
    virtual ~SoundLayerManager();  // slot 0
    SoundLayerManager();
    void update(unsigned int layerMask);  // Framework::update runs it per layer

    // the sound updaters of each of the 32 layers (GfComSound links its own into its layer's; the name is not
    // the original's)
    mm::mtl::FixedArray<mm::mtl::IntrusiveList<SoundUpdater>, 32> m_layers;
};
}  // namespace fw

#endif
