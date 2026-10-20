#ifndef CLASSES_UI_UIPARTICLEMANAGER_H
#define CLASSES_UI_UIPARTICLEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIParticleManager; }

namespace ui {
// table 0x7100B74FF8
class UIParticleManager : public ::mm::mtl::PtrSingleton< ::ui::UIParticleManager> {
public:
    virtual ~UIParticleManager();  // slot 0
};
}  // namespace ui

#endif
