#ifndef CLASSES_GMK_GMKSELINEPOINT_H
#define CLASSES_GMK_GMKSELINEPOINT_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkSeLinePointGobCustom; }

namespace gmk {
// table 0x7100B700B0
class GmkSeLinePoint : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {
    public:
        // inline and empty: initGmkBdatInfo reads the table pointer (getBindedBdatFp) and stores nothing
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {}
    };
    virtual ~GmkSeLinePoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(17);
};
}  // namespace gmk

#endif
