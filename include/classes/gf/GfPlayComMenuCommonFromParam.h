#ifndef CLASSES_GF_GFPLAYCOMMENUCOMMONFROMPARAM_H
#define CLASSES_GF_GFPLAYCOMMENUCOMMONFROMPARAM_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedQueue.h"
namespace fw { class UpdateInfo; }

namespace gf { class MenuCommonWindowParam; }
namespace gf {
// table 0x7100B57D68
class GfPlayComMenuCommonFromParam : public GfPlayCom {
public:
    static GfPlayComMenuCommonFromParam* create(const MenuCommonWindowParam& param);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuCommonFromParam();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_10[0x50];
    int m_handle;  // GfSequentialPlay::addMenuCommon answers it (the name is not the original's)
    static mm::mtl::FixedQueue<unsigned int, 32> s_list;  // handles of the open windows; create() pushes
};
}  // namespace gf

#endif
