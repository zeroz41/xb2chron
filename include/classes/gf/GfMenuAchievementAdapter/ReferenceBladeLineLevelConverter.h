#ifndef CLASSES_GF_GFMENUACHIEVEMENTADAPTER_REFERENCEBLADELINELEVELCONVERTER_H
#define CLASSES_GF_GFMENUACHIEVEMENTADAPTER_REFERENCEBLADELINELEVELCONVERTER_H

#include "classes/gf/GfMenuAchievementAdapter.h"

namespace gf {
// table 0x7100B59C48
class GfMenuAchievementAdapter::ReferenceBladeLineLevelConverter {
public:
    virtual ~ReferenceBladeLineLevelConverter();  // slot 0
    virtual void getBladeId();  // slot 2
    virtual void getKizunaLine();  // slot 3
    virtual void getKizunaLevel();  // slot 4
};
}  // namespace gf

#endif
