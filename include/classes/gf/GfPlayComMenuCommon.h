#ifndef CLASSES_GF_GFPLAYCOMMENUCOMMON_H
#define CLASSES_GF_GFPLAYCOMMENUCOMMON_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedQueue.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57D20
class GfPlayComMenuCommon : public GfPlayCom {
public:
    static GfPlayComMenuCommon* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuCommon();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    int pad_10;
    int m_handle;  // GfSequentialPlay::addMenuCommon answers it (the name is not the original's)
    // whether a common window is open, and its result
    static bool isDisp(unsigned int id);
    static int getResult(unsigned int id);
    static mm::mtl::FixedQueue<unsigned int, 32> s_list;  // handles of the open windows; create() pushes
};
}  // namespace gf

#endif
