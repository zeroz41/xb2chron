#ifndef CLASSES_GMK_GMKSALVAGELIST_H
#define CLASSES_GMK_GMKSALVAGELIST_H

#include "classes/gmk/GmkSalvage.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkSalvage; }
namespace gmk { class GmkSalvageGobCustom; }

namespace gmk {
// table 0x7100B6C9F8
class GmkSalvageList : public ::gmk::TGmkList<gmk::GmkSalvage, gmk::GmkSalvage::BdatInfo, 1447838035u, 2u, gmk::GmkSalvageGobCustom> {
public:
    virtual ~GmkSalvageList();  // slot 0
    virtual void update(float);  // slot 11
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16
    virtual void disposeGmk();  // slot 17
};
}  // namespace gmk

#endif
