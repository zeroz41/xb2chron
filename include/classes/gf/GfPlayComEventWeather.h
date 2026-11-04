#ifndef CLASSES_GF_GFPLAYCOMEVENTWEATHER_H
#define CLASSES_GF_GFPLAYCOMEVENTWEATHER_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace gf { enum WEATYPE : int; }

namespace gf {
// table 0x7100B58360; slot 1 is GfPlayCom's destructor (this one's is implicit)
class GfPlayComEventWeather : public GfPlayCom {
public:
    explicit GfPlayComEventWeather(WEATYPE weather) : GfPlayCom(46, false), m_weather(weather) {}
    // 2.0.0's symbols name it. What it does: news a 0x18-byte GfPlayComEventWeather holding the weather (no callers in
    // the code; nothing reads its other arguments).
    static GfPlayComEventWeather* create(WEATYPE weather);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComEventWeather";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag) { return true; }  // slot 6
    static mm::mtl::RTTI m_rtti;

    WEATYPE m_weather;  // start sets it unless it is 0x15; the name is not the original's
};
}  // namespace gf

#endif
