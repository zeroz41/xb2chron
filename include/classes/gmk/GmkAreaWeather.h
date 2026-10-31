#ifndef CLASSES_GMK_GMKAREAWEATHER_H
#define CLASSES_GMK_GMKAREAWEATHER_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
namespace gmk { class GmkAreaWeatherGob; }

namespace gmk {
// table 0x7100B6DEC0
// 16-aligned through its GmkPhantom (TGmkList::createGmk reserves its Vector with alignment 16)
class alignas(16) GmkAreaWeather : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkAreaWeather();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(30);
    // 0x50: create creates it with no listener unless the set's CreateInfo::m_flag is set, dispose disposes it
    // (the name is not the original's)
    GmkPhantom m_phantom;
};
}  // namespace gmk

#endif
