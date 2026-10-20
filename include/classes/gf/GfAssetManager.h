#ifndef CLASSES_GF_GFASSETMANAGER_H
#define CLASSES_GF_GFASSETMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfAssetManager; }

namespace gf {
// table 0x7100B43558
class GfAssetManager : public ::mm::mtl::PtrSingleton< ::gf::GfAssetManager>, public ::ml::IWorkEvent {
public:
    virtual ~GfAssetManager();  // slot 0
};
}  // namespace gf

#endif
