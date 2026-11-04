#ifndef CLASSES_GF_WEATHERSND_H
#define CLASSES_GF_WEATHERSND_H

#include "classes/gf/WeatherObj.h"
#include "gf/SoundHandle.h"

namespace gf {
// table 0x7100B52758; its destructor is the implicit one (the table's slot 0 is WeatherObj's)
class WeatherSnd : public ::gf::WeatherObj {
public:
    WeatherSnd() : m_type(), m_isNoSound(false), m_volume(1.0f) {}  // 1.0.0's (WeatherInfo's constructor inlines it)
    virtual void create(gf::WEATYPE type);  // slot 2
    virtual void destroy();  // slot 3
    virtual void fadeout(float time);  // slot 4
    virtual void update(const WeatherUpdate& info, float volume);  // slot 5
    virtual bool isPlay() const;  // slot 6
    virtual void setPause(bool);  // slot 8
    bool isRoomSe() const;  // 1.0.0's
    bool isEraseSe() const;  // 1.0.0's
    bool isCreateSe(float volume) const;  // 1.0.0's
    void applyVolume(const WeatherUpdate& info, float volume);  // 1.0.0's

    SoundHandle m_handle;  // the weather's loop (GfSound::playSe)
    gf::WEATYPE m_type;  // create's
    // set when the type has no sound or it did not play: create does not try again until the type changes (the
    // name is not the original's)
    bool m_isNoSound;
    float m_volume;  // the loop's volume, faded between 0 and 1
};
}  // namespace gf

#endif
