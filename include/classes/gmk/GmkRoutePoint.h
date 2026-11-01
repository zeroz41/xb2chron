#ifndef CLASSES_GMK_GMKROUTEPOINT_H
#define CLASSES_GMK_GMKROUTEPOINT_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "mm/Vec3.h"

namespace gmk {
// table 0x7100B6D890
class GmkRoutePoint : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {
    public:
        // inline and empty: initGmkBdatInfo reads the table pointer (getBindedBdatFp) and stores nothing
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {}
    };
    // its data in the gimmick section (m_createInfo.m_data): debugDraw draws a line from m_pos - pad_10 to
    // m_pos + pad_10 (pad_10's meaning not known)
    struct Data {
        mm::Vec3 m_pos;  // the point's position: GmkRoute::getRoutePointPos copies it (the name is not the original's)
        mm::Vec3 pad_10;
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    GmkRoutePoint() : pad_48(nullptr) {}  // inline: resize/extend construct in place with these stores
    virtual ~GmkRoutePoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x17);
    // an 8-byte field the constructor clears (Vector<T>::resize stores 0 at 0x48); meaning unknown
    void* pad_48;
};
}  // namespace gmk

#endif
