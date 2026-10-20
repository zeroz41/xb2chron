#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_ENEMYLISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_ENEMYLISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B818
class GfMenuCharDataAdapter::EnemyListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
};
}  // namespace gf

#endif
