#ifndef CLASSES_GMK_GMKROUTE_H
#define CLASSES_GMK_GMKROUTE_H

#include "classes/gmk/AGmkBase.h"
#include "mm/Col4.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkRouteGob; }
namespace gmk { class GmkRoutePoint; }

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
    GmkRoute() : pad_48(nullptr) {}  // inline: resize/extend construct in place with these stores
    // what m_createInfo.m_data points at for a route (getRoutePointNum/isClosed/getRoutePoint read it; the struct
    // and field names are not the original's)
    struct Data {
        unsigned int m_pointBegin;  // 0x0: its first point's index in the binded route point list
        unsigned int m_pointEnd;    // 0x4: one past its last point
        unsigned int pad_8;
        unsigned int m_flags;       // 0xC: bit 0: closed (isClosed)
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    unsigned int getRoutePointNum() const;
    bool isClosed() const;
    // draws the route (debugDraw passes mm::Col4::yellow while the gimmick is valid)
    void debugDrawRoute(const mm::Col4& color) const;
    // its point at index (from its first one) in the binded route point list, none past the list's end
    // (the return type: its call of getInst does not become a tail call, so the source converts getInst's answer)
    const GmkRoutePoint* getRoutePoint(unsigned int index) const;
    // the route's position nearest to pos (GmkRoutedNpc's distance tests pass the player's position)
    bool getNearestPos(mm::Vec3& nearest, const mm::Vec3& pos) const;
    virtual ~GmkRoute();  // slot 0
    // the position of one of its route points (LocatorBat_EnemySpeciesID::update asks a routed enemy for point 0)
    bool getRoutePointPos(mm::Vec3& pos, unsigned int index) const;
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    virtual IGmkList* getBindedRoutePointList() const;  // slot 11
    // an 8-byte field the constructor clears (Vector<T>::resize stores 0 at 0x48); meaning unknown
    void* pad_48;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(22);
};
}  // namespace gmk

#endif
