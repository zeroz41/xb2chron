#ifndef CLASSES_GF_GFPLAYCOMMENUPRECIOUS_H
#define CLASSES_GF_GFPLAYCOMMENUPRECIOUS_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57CD8
class GfPlayComMenuPrecious : public GfPlayCom {
public:
    static GfPlayComMenuPrecious* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuPrecious();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void vf5();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // how many are running (GfPlayFactory::createMenuPrecious queues its command list in mode 1 only while none is)
    static int s_activate;
};
}  // namespace gf

#endif
