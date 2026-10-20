#ifndef CLASSES_GMK_GMKAREAWEATHER_H
#define CLASSES_GMK_GMKAREAWEATHER_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6DEC0
class GmkAreaWeather : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkAreaWeather();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
};
}  // namespace gmk

#endif
