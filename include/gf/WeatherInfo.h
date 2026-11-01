#ifndef GF_WEATHERINFO_H
#define GF_WEATHERINFO_H

namespace fw { class UpdateInfo; }
namespace gf { enum WEATYPE : int; }
namespace gf { enum WEATHERID : int; }
namespace gf { class WeatherEff; }
namespace gf { class WeatherSnd; }
namespace gf { struct WeatherUpdateInfo; }

namespace gf {
// one weather on GfFieldWeather's list: its effect and its sound, its time and its fade
struct WeatherInfo {
    WeatherInfo(WEATYPE type, unsigned int mapId, WEATHERID id, float time, float timeMax, float fadeTime);
    ~WeatherInfo();
    void destroyEnv();  // 1.0.0's
    bool isTimeRangeOK() const;  // whether the time of day allows the weather
    bool isTimeup() const;
    // Placeholder name: 1.0.0's fadeoutEnv() (same callers, same body) took no time, so its name is not carried
    // over. What it does: fades the effect and the sound out over time and sets the fade times.
    void fn_7100281FD8(float time);
    void update(const WeatherUpdateInfo& info);  // 1.0.0's took the fw::UpdateInfo and the fade-out flag
    bool updateFadein(const fw::UpdateInfo& info);  // true once faded in
    void createEnv();  // 1.0.0's
    bool updateFadeout(const fw::UpdateInfo& info);  // true once faded out
    bool isTimeEnd() const;
    bool isPlaySE() const;  // 1.0.0's
    void setForceEffect(const char* name);
    void resetParam(float time, float timeMax, float fadeTime);
    void setPause(bool pause);

    char m_resource[8];  // the map's resource name (GfBdatMaplist::getMaplistresource)
    WEATYPE m_type;
    WEATHERID m_id;
    float m_time;  // how long the weather has been on
    float m_timeMax;  // how long it lasts (none when 0)
    unsigned int m_mapId;
    unsigned int pad_1c;
    float m_alpha;  // the fade: 0 to 1
    float m_fadeTime;  // the fade's time so far
    float m_fadeTimeMax;  // the fade's length
    WeatherEff* m_eff;
    WeatherSnd* m_snd;
};
}  // namespace gf

#endif
