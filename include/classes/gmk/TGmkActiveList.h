#ifndef CLASSES_GMK_TGMKACTIVELIST_H
#define CLASSES_GMK_TGMKACTIVELIST_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk {
// a template: 5 instances in the module
template <typename T0>
class TGmkActiveList : public ::mm::mtl::PtrSingleton< ::gmk::TGmkActiveList< T0>> {
public:
    // inline: GmkManager's constructor inlines it (no symbol)
    TGmkActiveList() : pad_20(false) {}
    // inline: GmkManager's constructor emits it with the table (a `;` body: an empty one would be the base's D2,
    // the original has a D2 of its own)
    virtual ~TGmkActiveList() { ; }  // slot 0
    // gmk unlinked from the active list when it is in it (the gimmicks' dispose and disposeGmkPhantom inline it; a
    // null check first: GmkEvent::disposeGmkPhantom tests its gimmick before the node). The name is not the original's.
    static void removeGmk(T0* gmk) {
        if (gmk != nullptr && gmk->intoNode()) {
            if (TGmkActiveList* list = TGmkActiveList::sys()) {
                list->m_list.remove(gmk);
            }
        }
    }
    // 0x8: the active gimmicks (the name is not the original's)
    mm::mtl::IntrusiveList<T0> m_list;
    bool pad_20;
};
}  // namespace gmk

#endif
