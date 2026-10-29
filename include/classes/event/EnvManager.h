#ifndef CLASSES_EVENT_ENVMANAGER_H
#define CLASSES_EVENT_ENVMANAGER_H

namespace event { enum MSG_TYPE : int; }
namespace gf { enum WEATHERID : int; enum WEATYPE : int; }

#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
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
    // out of line (OnEventProc branches to them)
    void clear();
    void update();
    void render();
    // 1.0.0's EnvManager::login (0x71000AC00C); 3.0.1 inlines it into OnEventProc: the field's time and weather
    void login() {
        m_weatherID = (gf::WEATHERID)1;
        m_hour = 0;
        m_min = 0;
        if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
            time->getTime(m_hour, m_min);
            m_weatherID = gf::GfFieldWeather::getCurrentMapWeatherID(false);
            m_cloudSea = gf::GfFieldWeather::getCurrentCloudSea();
        }
    }
    // bit 0: setClockStop's state; bit 2: setWeatherType sets it; bit 4: setMotBlur's (set while disabled); bit 5:
    // setToneMap's (the name is not the original's)
    unsigned int m_flags;  // 0x10
    unsigned char pad_14[0x28];
    float m_toneMap;  // 0x3c setToneMap's value (the name is not the original's)
    unsigned char pad_40[0x28];
    unsigned int m_hour;  // 0x68 (the name is not the original's)
    unsigned int m_min;  // 0x6c (the name is not the original's)
    gf::WEATHERID m_weatherID;  // 0x70 (the name is not the original's)
    int m_cloudSea;  // 0x74 (the name is not the original's)
};
}  // namespace event

#endif
