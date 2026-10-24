#ifndef CLASSES_GF_GFPLAYCOMMENUCOMMONFROMPARAM_H
#define CLASSES_GF_GFPLAYCOMMENUCOMMONFROMPARAM_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/MenuCommonWindowParam.h"
#include "mm/mtl/FixedQueue.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57D68
class GfPlayComMenuCommonFromParam : public GfPlayCom {
public:
    GfPlayComMenuCommonFromParam(const MenuCommonWindowParam& param, unsigned int handle) : GfPlayCom(24, false), m_param(param), m_handle(handle & 0xFFFFFF) {}
    static GfPlayComMenuCommonFromParam* create(const MenuCommonWindowParam& param);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuCommonFromParam();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuCommon";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    MenuCommonWindowParam m_param;  // start() opens the window from it
    unsigned int m_handle;  // GfSequentialPlay::addMenuCommon answers it (the name is not the original's)
    static unsigned int s_gblHandle;  // as GfPlayComMenuCommon's
    static mm::mtl::FixedQueue<unsigned int, 32> s_list;  // handles of the open windows; create() pushes
};
}  // namespace gf

#endif
