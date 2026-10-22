#ifndef CLASSES_GF_GFDATAMANAGER_H
#define CLASSES_GF_GFDATAMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfDataManager; }
namespace gf { class SDataGame; }

namespace gf {
// table 0x7100B4DA08
class GfDataManager : public ::mm::mtl::PtrSingleton< ::gf::GfDataManager>, public ::gf::IGfEvent {
public:
    virtual ~GfDataManager();  // slot 0
    virtual void vf2();  // slot 2
    static SDataGame* getDataGame();  // GfDataStore's
};
}  // namespace gf

#endif
