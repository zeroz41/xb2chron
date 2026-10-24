#ifndef CLASSES_GF_GFPLAYCOMEVENTFADE_H
#define CLASSES_GF_GFPLAYCOMEVENTFADE_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58318
class GfPlayComEventFade : public GfPlayCom {
public:
    // the field names are not the original's
    GfPlayComEventFade() : GfPlayCom(0, false), m_state(0), m_wait(0.0f), m_fadeTime(0.0f), m_timeout(0.0f), m_mapId(0), m_time(0.0f) {}
    static GfPlayComEventFade* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComEventFade";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // started commands: start() counts up, end() down (the name is not the original's)
    static int s_start;
    int m_state;       // update's steps: 0 waits to start the fade, 1 waits for the field, 2 counts m_wait down
    float m_wait;      // GfGameEvent::getFadeInWaitSec
    float m_fadeTime;  // GfGameEvent::getFadeInSec
    float m_timeout;   // 10 seconds, counted down while the party is not ready
    int m_mapId;       // the map when it started
    float m_time;      // counted up by update
};
}  // namespace gf

#endif
