#ifndef CLASSES_GMK_GMKROUTEDFOOTPRINTPOINT_H
#define CLASSES_GMK_GMKROUTEDFOOTPRINTPOINT_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"

namespace gmk {
// table 0x7100B6D2A0
class GmkRoutedFootPrintPoint : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {
    public:
        // inline and empty: initGmkBdatInfo reads the table pointer (getBindedBdatFp) and stores nothing
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {}
    };
    virtual ~GmkRoutedFootPrintPoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x37);
    unsigned char pad_48[0xd];  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
