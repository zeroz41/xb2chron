#ifndef CLASSES_GF_GFMENUSKILLADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuSkillAdapter.h"

namespace gf {
// table none (its derived classes'): where a skill adapter's update takes its skill from
class GfMenuSkillAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getDriverId() = 0;  // slot 2
    virtual unsigned int getKizunaLine() = 0;  // slot 3
    virtual unsigned int getKizunaLevel() = 0;  // slot 4
    virtual unsigned int getRound() = 0;  // slot 5
};
}  // namespace gf

#endif
