#ifndef CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERLINELEVELCONVERTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERLINELEVELCONVERTER_H

#include "classes/gf/GfMenuSkillAdapter.h"

namespace gf {
// table 0x7100B5DC00
class GfMenuSkillAdapter::ReferenceDriverLineLevelConverter {
public:
    virtual ~ReferenceDriverLineLevelConverter();  // slot 0
    virtual void getDriverId();  // slot 2
    virtual void getKizunaLine();  // slot 3
    virtual void getKizunaLevel();  // slot 4
    virtual void getRound();  // slot 5
};
}  // namespace gf

#endif
