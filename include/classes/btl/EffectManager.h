#ifndef CLASSES_BTL_EFFECTMANAGER_H
#define CLASSES_BTL_EFFECTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class EffectManager; }

namespace btl {
// table 0x7100B3BB38
class EffectManager : public ::mm::mtl::PtrSingleton< ::btl::EffectManager> {
public:
    virtual ~EffectManager();  // slot 0
};
}  // namespace btl

#endif
