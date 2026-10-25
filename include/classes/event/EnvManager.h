#ifndef CLASSES_EVENT_ENVMANAGER_H
#define CLASSES_EVENT_ENVMANAGER_H

namespace event { enum MSG_TYPE : int; }
namespace gf { enum WEATHERID : int; enum WEATYPE : int; }

namespace event {
// a base of event::EnvManager no evidence names yet
class TUnk_B3C730 {
public:
    virtual ~TUnk_B3C730();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::EnvManager no evidence names yet
class TUnk_B3C758 {
public:
    virtual ~TUnk_B3C758();
};
// table 0x7100B3C730; base at 0x0 unknown (TUnk_B3C730), base at 0x8 unknown (TUnk_B3C758)
class EnvManager : public TUnk_B3C730, public TUnk_B3C758 {
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
};
}  // namespace event

#endif
