#ifndef CLASSES_GF_GFPLAYCOMRETURNTITLE_H
#define CLASSES_GF_GFPLAYCOMRETURNTITLE_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/ParamReturnTitle.h"
#include "classes/gf/GfMenuObjPopup.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B589A0; GfSequentialPlay::addReturnTitle makes it
class GfPlayComReturnTitle : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComReturnTitle> {
public:
    explicit GfPlayComReturnTitle(const ParamReturnTitle& param) : GfPlayCom(36, false), m_param(param), m_wait(0) {}
    static GfPlayComReturnTitle* create(const ParamReturnTitle& param);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComReturnTitle";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    ParamReturnTitle m_param;
    int m_wait;  // frames left once no voice plays; the name is not the original's
};
}  // namespace gf

#endif
