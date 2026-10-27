#ifndef CLASSES_GMK_GMKROUTE_H
#define CLASSES_GMK_GMKROUTE_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkRouteGob; }

namespace gmk {
// table 0x7100B6C810
class GmkRoute : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {
    public:
        // inline and empty: initGmkBdatInfo reads the table pointer (getBindedBdatFp) and stores nothing
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {}
    };
    virtual ~GmkRoute();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    virtual void getBindedRoutePointList() const;  // slot 11
    unsigned char pad_48[0x8];  // fields: size from its derived classes
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(22);
};
}  // namespace gmk

#endif
