#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_GFOBJCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_GFOBJCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B728
class GfMenuCharDataAdapter::GfObjConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
    virtual void fromGfObj();  // slot 1
};
}  // namespace gf

#endif
