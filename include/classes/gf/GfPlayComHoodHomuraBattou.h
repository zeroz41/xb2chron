#ifndef CLASSES_GF_GFPLAYCOMHOODHOMURABATTOU_H
#define CLASSES_GF_GFPLAYCOMHOODHOMURABATTOU_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B58220; GfSequentialPlay::addHoodHomuraBattou makes it
class GfPlayComHoodHomuraBattou : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComHoodHomuraBattou> {
public:
    GfPlayComHoodHomuraBattou();  // out of line (0x710031D58C)
    static GfPlayComHoodHomuraBattou* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "HoodHomuraBattou";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

};
}  // namespace gf

#endif
