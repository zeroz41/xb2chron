#ifndef CLASSES_GMK_GMKPHANTOMMANAGER_H
#define CLASSES_GMK_GMKPHANTOMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/FixedArray.h"
#include "fw/ColiCheck.h"

namespace gmk { class GmkPhantomManager; }
namespace gmk { class GmkPhantom; }

namespace gmk {
// table 0x7100B6BF90
class GmkPhantomManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkPhantomManager> {
public:
    virtual ~GmkPhantomManager();  // slot 0
    // GmkManager::seqUpdate calls it first
    void update(float dt);
    // every GmkPhantom (each one's constructor links itself last; the name is not the original's)
    mm::mtl::IntrusiveList<GmkPhantom> m_phantoms;
    // 0x20: update's fw::ColiCheck::testSpherePhantom results, one per party member's position (update passes the
    // array to GmkPhantom::update; the name is not the original's)
    mm::mtl::FixedArray<fw::TColiCheckResult<256>, 3> m_results;
};
}  // namespace gmk

#endif
