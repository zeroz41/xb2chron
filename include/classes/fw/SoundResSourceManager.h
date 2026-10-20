#ifndef CLASSES_FW_SOUNDRESSOURCEMANAGER_H
#define CLASSES_FW_SOUNDRESSOURCEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class SoundResSourceManager; }

namespace fw {
// table 0x7100B43440
class SoundResSourceManager : public ::mm::mtl::PtrSingleton< ::fw::SoundResSourceManager> {
public:
    virtual ~SoundResSourceManager();  // slot 0
};
}  // namespace fw

#endif
