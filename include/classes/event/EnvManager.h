#ifndef CLASSES_EVENT_ENVMANAGER_H
#define CLASSES_EVENT_ENVMANAGER_H

namespace event { enum MSG_TYPE : int; }
namespace gf { enum WEATHERID : int; enum WEATYPE : int; }

#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/event/EnvTransferEvent.h"
#include "classes/event/EnvTransferField.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3C730; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::EnvManager>
class EnvManager : public IManager, public mm::mtl::Singleton<EnvManager> {
public:
    // the colour filter's switch (the evt_env plugin's setColorFilter passes 1 to set one, 2 to clear it); no
    // enumerator is named
    enum COLORFILTER_TYPE : int {};
    // out of line (mm::mtl::Singleton<event::EnvManager>::getPtr's static calls it)
    EnvManager();
    virtual ~EnvManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // the evt_env script plugin's commands
    void setClock(const char* clock);
    void setClockStop(bool stop);
    void setMapWeatherID(gf::WEATHERID id, float frame);
    void setWeatherType(gf::WEATYPE type);
    void setColorFilter(COLORFILTER_TYPE type, int no, int frame, float rate);
    void setMotBlur(bool enable);
    void setToneMap(bool enable, float value);
    void resetScene();
    // the vignette effect (cmn_205_000 for 5000, cmn_205_001 for 5001) setColorFilter type 1 plays for its two ints
    void playVignette(int num, int farNum);
    // out of line (OnEventProc branches to them)
    void clear();
    void update();
    void render();
    // 1.0.0's EnvManager::login (0x71000AC00C); 3.0.1 inlines it into OnEventProc: the field's time and weather
    void login() {
        m_field.m_weatherID = (gf::WEATHERID)1;
        m_field.m_hour = 0;
        m_field.m_min = 0;
        if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
            time->getTime(m_field.m_hour, m_field.m_min);
            m_field.m_weatherID = gf::GfFieldWeather::getCurrentMapWeatherID(false);
            m_field.m_cloudSea = gf::GfFieldWeather::getCurrentCloudSea();
        }
    }
    // bit 0: setClockStop's state; bit 1: clear() turns the scene's auto reset off; bit 2: setWeatherType sets it;
    // bit 3: clear() ends GfFieldGimmick's event fade; bit 4: setMotBlur's (set while disabled); bit 5: setToneMap's
    // (the name is not the original's)
    unsigned int m_flags;  // 0x10
    unsigned int m_debugFlags;  // 0x14 bit 0: render() draws the clock, weather and cloud sea (the name is not the original's)
    // the clock setClock set last; the constructor and clear() set both to -1 (the names are not the original's)
    int m_hour;  // 0x18
    int m_min;  // 0x1c
    // 1 or 2: the cloud sea EnvTransfer::load set (2 when the transfer's is 0); clear() turns it off when set (the
    // name is not the original's)
    int m_cloudSea;  // 0x20
    // the colour filter's state: 0 off, 1 on (setColorFilter type 1), 2 fading out (type 2; update() turns it off
    // once m_filterCount reaches m_filterTime); clear() turns it off when set (the name is not the original's)
    int m_colorFilter;  // 0x24
    // the two ints setColorFilter type 1 hands to gf::GfGameEvent::setColorFilter and playVignette (-1 after
    // the constructor and clear(); the names are not the original's)
    int m_filterNum;  // 0x28
    int m_filterFarNum;  // 0x2c
    float m_filterTime;  // 0x30 setColorFilter's frame count (the name is not the original's)
    int m_filterCount;  // 0x34 frames update() counted since the fade out began (the name is not the original's)
    // the vignette effect playVignette created; clear() hands it to fw::EffectManager::remove when set (the name
    // is not the original's)
    unsigned int m_effect;  // 0x38
    float m_toneMap;  // 0x3c setToneMap's value (the name is not the original's)
    EnvTransferEvent m_event;  // 0x40 (the name is not the original's)
    EnvTransferField m_field;  // 0x60 login() stores the field's time and weather (the name is not the original's)
};
}  // namespace event

#endif
