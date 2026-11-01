#ifndef CLASSES_GMK_GMKANTIBLADEAREAMANAGER_H
#define CLASSES_GMK_GMKANTIBLADEAREAMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkAntiBladeAreaManager; class GmkAntiBladeArea; }

namespace gmk {
// table 0x7100B519B8
class GmkAntiBladeAreaManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkAntiBladeAreaManager> {
public:
    GmkAntiBladeAreaManager() : m_active(nullptr) {}
    virtual ~GmkAntiBladeAreaManager();  // slot 0
    void dispose();
    // area unlinked when it is linked, the first remaining area (none when empty) made the active one
    // (GmkAntiBladeArea::onLeavePhantom inlines it: a null check of the area before its node, as in
    // TGmkActiveList::removeGmk; inline, defined in GmkElevator.cpp; the name is not the original's)
    static inline void removeArea(GmkAntiBladeArea* area);
    // the areas addGmk registered (GfFieldGimmick's constructor builds it; the name is not the original's)
    // (dispose erases each element, the node at GmkAntiBladeArea's 0x50 base)
    ::mm::mtl::IntrusiveList< ::gmk::GmkAntiBladeArea> m_areas;
    // the area the player is in, none outside every area (GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea reads
    // its row id; the name is not the original's)
    GmkAntiBladeArea* m_active;
};
}  // namespace gmk

#endif
