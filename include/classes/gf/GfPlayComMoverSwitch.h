#ifndef CLASSES_GF_GFPLAYCOMMOVERSWITCH_H
#define CLASSES_GF_GFPLAYCOMMOVERSWITCH_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// no table in this version (its RTTI string and m_rtti remain); members from 1.0.0's gf::GfPlayComMoverSwitch symbols
class GfPlayComMoverSwitch : public GfPlayCom {
public:
    static GfPlayComMoverSwitch* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMoverSwitch();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
