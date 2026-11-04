#ifndef CLASSES_GF_WEATHEROBJ_H
#define CLASSES_GF_WEATHEROBJ_H

namespace fw { class UpdateInfo; }
namespace gf { enum WEATYPE : int; }

namespace gf {
// what a weather's effect and sound are updated with (WeatherInfo builds one from a frame's fw::UpdateInfo: the
// speed, the time step, two flags clear). 1.0.0 passed the fw::UpdateInfo and the fade-out flag; 3.0.1's callers
// pass this instead (no bool argument is set up at any call). 2.0.0's symbols name the type; the field names are not
// the original's.
struct WeatherUpdate {
    WeatherUpdate(const fw::UpdateInfo& info);
    float m_speed;  // the update speed (WeatherEff::update sets the effect's speed to it)
    float m_deltaTime;  // the frame's time step
    bool m_isFadeout;  // set while the weather fades out: WeatherSnd::update does not restart its sound
    bool m_isTimeStop;  // GfFieldWeather::updateWeather's: WeatherInfo::update does not advance the weather's time
};

// table none (its derived classes')
class WeatherObj {
public:
    virtual ~WeatherObj() {}  // slot 0
    virtual void create(gf::WEATYPE) = 0;  // slot 2
    virtual void destroy() = 0;  // slot 3
    // 3.0.1 passes the fade time (WeatherSnd stops its sound over it; 1.0.0's took none and faded over 4.0)
    virtual void fadeout(float time) = 0;  // slot 4
    virtual void update(const WeatherUpdate& info, float volume) = 0;  // slot 5
    virtual bool isPlay() const = 0;  // slot 6
    virtual void setForceName(char const*) {}  // slot 7
    virtual void setPause(bool) = 0;  // slot 8
};
}  // namespace gf

#endif
