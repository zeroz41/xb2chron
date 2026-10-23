#ifndef CLASSES_GF_GFPLAYCOMEXECUTESIGNAL_H
#define CLASSES_GF_GFPLAYCOMEXECUTESIGNAL_H

#include "classes/gf/GfPlayCom.h"
namespace gf { class GfSequentialPlaySignal; }

namespace gf {
// table 0x7100B58100
class GfPlayComExecuteSignal : public GfPlayCom {
public:
    GfPlayComExecuteSignal(bool start, GfSequentialPlaySignal* signal) : GfPlayCom(38, true), m_start(start), m_signal(signal) {}
    static GfPlayComExecuteSignal* create(bool start, GfSequentialPlaySignal* signal);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComExecuteSignal";
        return func;
    }
    virtual void start();  // slot 4
    static mm::mtl::RTTI m_rtti;

    bool m_start;  // true: startSignal's command, false: endSignal's; the name is not the original's
    GfSequentialPlaySignal* m_signal;
};
}  // namespace gf

#endif
