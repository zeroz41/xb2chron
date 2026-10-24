#ifndef CLASSES_GF_GFPLAYCOMRESETBLADEPLAYERSTOP_H
#define CLASSES_GF_GFPLAYCOMRESETBLADEPLAYERSTOP_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57840
class GfPlayComResetBladePlayerStop : public GfPlayCom {
public:
    explicit GfPlayComResetBladePlayerStop(bool stop) : GfPlayCom(6, true), m_stop(stop) {}
    static GfPlayComResetBladePlayerStop* create(bool stop);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComResetBladePlayerStop";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag) { return true; }  // slot 6
    static mm::mtl::RTTI m_rtti;

    bool m_stop;  // GfSequentialPlay's name for the parameter
};
}  // namespace gf

#endif
