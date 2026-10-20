#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_ENBOOKLISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_ENBOOKLISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B848
class GfMenuCharDataAdapter::EnBookListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
};
}  // namespace gf

#endif
