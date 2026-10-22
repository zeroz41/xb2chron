#ifndef CLASSES_GF_GFFIELDWEATHER_H
#define CLASSES_GF_GFFIELDWEATHER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldWeather; }

namespace gf {
// table 0x7100B526C0
class GfFieldWeather : public ::mm::mtl::PtrSingleton< ::gf::GfFieldWeather> {
public:
    virtual ~GfFieldWeather();  // slot 0
    static unsigned int getCurrentWtrType(bool);
    static bool isDispWeather();  // whether the weather shows (WeatherEff and WeatherSnd play only then)  // the weather now (GfMenuBdat::getIconIDFromWeatherType takes it)
};
}  // namespace gf

#endif
