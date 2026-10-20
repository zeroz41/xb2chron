#ifndef CLASSES_GF_WEATHERSND_H
#define CLASSES_GF_WEATHERSND_H

#include "classes/gf/WeatherObj.h"

namespace fw { class UpdateInfo; }
namespace gf { enum WEATYPE : int; }

namespace gf {
// table 0x7100B52758
class WeatherSnd : public ::gf::WeatherObj {
public:
    virtual ~WeatherSnd();  // slot 0
    virtual void create(gf::WEATYPE);  // slot 2
    virtual void destroy();  // slot 3
    virtual void fadeout();  // slot 4
    virtual void update(fw::UpdateInfo const&, float, bool);  // slot 5
    virtual void isPlay() const;  // slot 6
    virtual void setPause(bool);  // slot 8
};
}  // namespace gf

#endif
