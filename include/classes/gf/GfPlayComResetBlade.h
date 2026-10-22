#ifndef CLASSES_GF_GFPLAYCOMRESETBLADE_H
#define CLASSES_GF_GFPLAYCOMRESETBLADE_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedVector.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B581D8
class GfPlayComResetBlade {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual void vf1();  // slot 1
    virtual void vf2();  // slot 2
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static mm::mtl::FixedVector<signed char, 3> s_execFlag;
};
}  // namespace gf

#endif
