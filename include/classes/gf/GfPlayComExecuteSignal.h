#ifndef CLASSES_GF_GFPLAYCOMEXECUTESIGNAL_H
#define CLASSES_GF_GFPLAYCOMEXECUTESIGNAL_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B58100
class GfPlayComExecuteSignal : public ::gf::GfPlayCom {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComExecuteSignal();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
