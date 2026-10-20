#ifndef CLASSES_GF_GFFIELDWEATHER_H
#define CLASSES_GF_GFFIELDWEATHER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldWeather; }

namespace gf {
// table 0x7100B526C0
class GfFieldWeather : public ::mm::mtl::PtrSingleton< ::gf::GfFieldWeather> {
public:
    virtual ~GfFieldWeather();  // slot 0
};
}  // namespace gf

#endif
