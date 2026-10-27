#ifndef CLASSES_GMK_CLOUDCOND_H
#define CLASSES_GMK_CLOUDCOND_H

#include "classes/gf/GfFieldWeather.h"

namespace gmk {
// table 0x7100B6F208; GmkEnemyInsts::BdatInfo holds one (its row's "popCloud" flag)
class CloudCond {
public:
    // the cloud sea the row asks for: -1 any, else GfFieldWeather::getCurrentCloudSea must equal 0 or 1 (no copy
    // of it exists: inline; the name is not the original's)
    bool isMatch() const {
        if (m_cloudSea == -1) {
            return true;
        }
        int cloudSea = gf::GfFieldWeather::getCurrentCloudSea();
        if (m_cloudSea == 1) {
            return cloudSea == 1;
        }
        if (m_cloudSea == 0) {
            return cloudSea == 0;
        }
        return false;
    }
    virtual ~CloudCond() {}  // slot 0
    int m_cloudSea;  // 0x8: 1 when the row's "popCloud" flag is set (the name is not the original's)
};
}  // namespace gmk

#endif
