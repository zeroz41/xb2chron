#include "gf/FileStaticVec3.h"
#include "mm/mtl/FixedList.h"
#include "classes/gf/GfFieldWeather.h"

namespace gf {

struct WeatherInfo;

namespace _gffwt {

mm::mtl::FixedList<WeatherInfo*, 16> s_list;

}  // namespace _gffwt

GfFieldWeather::~GfFieldWeather() {}

}  // namespace gf
