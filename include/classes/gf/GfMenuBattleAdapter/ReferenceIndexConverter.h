#ifndef CLASSES_GF_GFMENUBATTLEADAPTER_REFERENCEINDEXCONVERTER_H
#define CLASSES_GF_GFMENUBATTLEADAPTER_REFERENCEINDEXCONVERTER_H

#include "classes/gf/GfMenuBattleAdapter.h"

namespace gf {
// table 0x7100B5A878
class GfMenuBattleAdapter::ReferenceIndexConverter {
public:
    virtual ~ReferenceIndexConverter();  // slot 0
    virtual void getIndex(int&);  // slot 2
};
}  // namespace gf

#endif
