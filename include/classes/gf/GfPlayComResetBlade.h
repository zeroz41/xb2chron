#ifndef CLASSES_GF_GFPLAYCOMRESETBLADE_H
#define CLASSES_GF_GFPLAYCOMRESETBLADE_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedVector.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B581D8
class GfPlayComResetBlade : public GfPlayCom {
public:
    static GfPlayComResetBlade* create(unsigned int blade, int mode);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComResetBlade();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    int pad_10;
    unsigned int m_blade;  // addResetBlade's first argument (the name is not the original's)
    // whether the reset of a party slot's blade (0-2) is running
    static bool isPlaying(unsigned int slot);
    static mm::mtl::FixedVector<signed char, 3> s_execFlag;
};
}  // namespace gf

#endif
