#ifndef CLASSES_FW_LIGHTMANAGER_H
#define CLASSES_FW_LIGHTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B417E0; its base at 0x10 is its singleton (the destructor stores PtrSingleton<fw::LightManager>'s
// table 0x7100B41858 there and clears its instance)
class LightManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::LightManager> {
public:
    virtual ~LightManager();  // slot 0
    virtual void update(fw::UpdateInfo const&, unsigned int) {}  // slot 8
};
}  // namespace fw

#endif
