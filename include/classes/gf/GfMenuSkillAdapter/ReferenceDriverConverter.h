#ifndef CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuSkillAdapter.h"

namespace gf {
// table 0x7100B5DBC0
class GfMenuSkillAdapter::ReferenceDriverConverter {
public:
    virtual ~ReferenceDriverConverter();  // slot 0
    virtual void getDriverId();  // slot 2
    virtual void getKizunaLine();  // slot 3
    virtual void getKizunaLevel();  // slot 4
    virtual void getRound();  // slot 5
};
}  // namespace gf

#endif
