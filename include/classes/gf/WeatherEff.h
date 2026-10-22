#ifndef CLASSES_GF_WEATHEREFF_H
#define CLASSES_GF_WEATHEREFF_H

#include "classes/gf/WeatherObj.h"

namespace gf {
// table 0x7100B52700; its destructor is the implicit one (the table's slot 0 is WeatherObj's)
class WeatherEff : public ::gf::WeatherObj {
public:
    WeatherEff() : m_isWait(false), m_alpha(1.0f), m_handle(0) {}  // 1.0.0's (WeatherInfo's constructor inlines it)
    virtual void create(gf::WEATYPE type);  // slot 2
    virtual void destroy();  // slot 3
    virtual void fadeout(float time);  // slot 4
    virtual void update(const WeatherUpdateInfo& info, float volume);  // slot 5
    virtual bool isPlay() const;  // slot 6
    virtual void setForceName(char const*);  // slot 7
    virtual void setPause(bool);  // slot 8
    bool isEraseEffect() const;  // 1.0.0's
    bool isDispEffect() const;  // 1.0.0's
    void applyAlpha(const WeatherUpdateInfo& info);  // 1.0.0's
    void applySpeed(const WeatherUpdateInfo& info);  // 1.0.0's

    gf::WEATYPE m_type;  // create's
    // set while the effect waits out of sight (in a room, or the weather hidden): it fades out, and is created
    // again when the weather shows (the name is not the original's)
    bool m_isWait;
    float m_alpha;  // the effect's alpha (EffectManager::setAlpha)
    unsigned int m_handle;  // the effect EffectManager::create made, 0 for none
};
}  // namespace gf

#endif
