#ifndef CLASSES_GF_GFPLAYCOMWAIT_H
#define CLASSES_GF_GFPLAYCOMWAIT_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B58438
class GfPlayComWait : public GfPlayCom {
public:
    explicit GfPlayComWait(float time) : GfPlayCom(3, false), m_time(time) {}
    static GfPlayComWait* create(float time);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComWait";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    float m_time;  // counts down by the frame time; the name is not the original's
};
}  // namespace gf

#endif
