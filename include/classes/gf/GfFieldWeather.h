#ifndef CLASSES_GF_GFFIELDWEATHER_H
#define CLASSES_GF_GFFIELDWEATHER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldWeather; enum WEATYPE : int; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; enum CLOUD_SEA : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B526C0
class GfFieldWeather : public ::mm::mtl::PtrSingleton< ::gf::GfFieldWeather> {
public:
    // GfPlayComEventWeather::start passes its weather and no name
    static void setWeatherForEvent(WEATYPE type, const char* name);
    virtual ~GfFieldWeather();  // slot 0
    static unsigned int getCurrentWtrType(bool);
    static int getCurrentCloudSea();
    static void setCloudSea(unsigned int map, CLOUD_SEA cloudSea);  // GfGameUtilCloudSea::getCloudSea forwards here
    // GfFieldManager's forwards (its initialize, finalize, clear, setupGame and gev* functions call them)
    static void build(const GfSetupParam& param);
    static void setWeather(WEATYPE type, bool flag);  // the fld script plugin's setWeather (name from the symbols)
    static void destroy();
    static void clear();
    // 1.0.0's GfFieldManager::setupGame calls setupGame() where 3.0.1's calls this, and the bodies make the same calls
    static void setupGame();
    static void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    static void gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    static void gevPause(unsigned int flags0, unsigned int flags1);
    static void update(const fw::UpdateInfo& info);
    static bool isDispWeather();  // whether the weather shows (WeatherEff and WeatherSnd play only then)  // the weather now (GfMenuBdat::getIconIDFromWeatherType takes it)
};
}  // namespace gf

#endif
