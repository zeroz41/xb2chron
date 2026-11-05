#ifndef CLASSES_GMK_GMKSQUADMANAGER_H
#define CLASSES_GMK_GMKSQUADMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkSquadManager; class GmkSquad; }

namespace gmk {
// table 0x7100B6E450
class GmkSquadManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkSquadManager> {
public:
    virtual ~GmkSquadManager();  // slot 0
    // not virtual: the destructor calls it directly
    void clearGmkSquads();
    // 0x8: the squads (GmkManager's constructor builds it; GmkSquad::create links one, GmkSquad::dispose unlinks it;
    // the name is not known)
    mm::mtl::IntrusiveList<GmkSquad> m_list;
};
}  // namespace gmk

#endif
