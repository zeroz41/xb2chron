#ifndef CLASSES_GMK_GMKPHANTOMMANAGER_H
#define CLASSES_GMK_GMKPHANTOMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkPhantomManager; }
namespace gmk { class GmkPhantom; }

namespace gmk {
// table 0x7100B6BF90
class GmkPhantomManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkPhantomManager> {
public:
    virtual ~GmkPhantomManager();  // slot 0
    // every GmkPhantom (each one's constructor links itself last; the name is not the original's)
    mm::mtl::IntrusiveList<GmkPhantom> m_phantoms;
};
}  // namespace gmk

#endif
