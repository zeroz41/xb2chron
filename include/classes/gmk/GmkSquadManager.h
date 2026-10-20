#ifndef CLASSES_GMK_GMKSQUADMANAGER_H
#define CLASSES_GMK_GMKSQUADMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkSquadManager; }

namespace gmk {
// table 0x7100B6E450
class GmkSquadManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkSquadManager> {
public:
    virtual ~GmkSquadManager();  // slot 0
};
}  // namespace gmk

#endif
