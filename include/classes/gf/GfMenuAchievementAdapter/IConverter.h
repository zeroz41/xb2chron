#ifndef CLASSES_GF_GFMENUACHIEVEMENTADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUACHIEVEMENTADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuAchievementAdapter.h"

namespace gf {
// No table of its own: the derived converters supply the blade and affinity chart coordinates for update.
class GfMenuAchievementAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getBladeId() = 0;  // slot 2
    virtual unsigned int getKizunaLine() = 0;  // slot 3
    virtual unsigned int getKizunaLevel() = 0;  // slot 4
};
}  // namespace gf

#endif
