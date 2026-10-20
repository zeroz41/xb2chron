#ifndef CLASSES_FW_SOUNDLAYERMANAGER_H
#define CLASSES_FW_SOUNDLAYERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class SoundLayerManager; }

namespace fw {
// table 0x7100B42D50
class SoundLayerManager : public ::mm::mtl::PtrSingleton< ::fw::SoundLayerManager> {
public:
    virtual ~SoundLayerManager();  // slot 0
};
}  // namespace fw

#endif
