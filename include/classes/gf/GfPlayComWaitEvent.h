#ifndef CLASSES_GF_GFPLAYCOMWAITEVENT_H
#define CLASSES_GF_GFPLAYCOMWAITEVENT_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf { class GF_OBJ_HANDLE; }
namespace gf {
// table 0x7100B577B0
class GfPlayComWaitEvent : public GfPlayCom {
public:
    static GfPlayComWaitEvent* create(float time, GF_OBJ_HANDLE* handle);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComWaitEvent();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
