#ifndef CLASSES_GF_GFPLAYCOMMOVERSWITCH_H
#define CLASSES_GF_GFPLAYCOMMOVERSWITCH_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// no table in this version (its RTTI string and m_rtti remain); members from 1.0.0's gf::GfPlayComMoverSwitch symbols
class GfPlayComMoverSwitch {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMoverSwitch();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
