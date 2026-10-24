#ifndef CLASSES_GMK_GMKAREAWEATHER_H
#define CLASSES_GMK_GMKAREAWEATHER_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkAreaWeatherGob; }

namespace gmk {
// table 0x7100B6DEC0
class GmkAreaWeather : public ::gmk::AGmkBase {
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
    unsigned char pad_48[0x98];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
