#ifndef CLASSES_GMK_GMKMANAGER_H
#define CLASSES_GMK_GMKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/IGmkList.h"
#include "mm/mtl/Vector.h"

namespace gmk { class GmkManager; }

namespace gmk {
// table 0x7100B6BBD0
class GmkManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkManager> {
public:
    virtual ~GmkManager();  // slot 0
    bool isGmkSetsReady() const;
    // calls f with every gimmick of a kind in every gimmick set; false while the sets are not ready
    template <typename F>
    bool traverseGmkInst(GmkType type, F& f) const {
        if (!isGmkSetsReady()) {
            return false;
        }
        for (const GmkSet* const* it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
            if (*it == nullptr) {
                continue;
            }
            const IGmkList* list = (*it)->getGmkList(type);
            if (list == nullptr) {
                continue;
            }
            unsigned int num = list->getInstNum();
            for (unsigned int i = 0; i < num; ++i) {
                const AGmkBase* gmk = list->getInst(i);
                if (gmk != nullptr) {
                    f(*gmk);
                }
            }
        }
        return true;
    }

    unsigned char pad_8[0x188];
    // the BDAT table of the map's gimmick sets: a row per set, a column per gimmick kind naming its resource and
    // one ("<kind>_bdat") naming its BDAT table (GmkSet::createGmkLists reads it; the name is not the original's)
    unsigned char* m_gmkSetBdatFp;  // 0x190
    unsigned char pad_198[0xf1c0];
    mm::mtl::Vector<GmkSet*> m_gmkSets;  // the gimmick sets (the name is not the original's)
};
}  // namespace gmk

#endif
