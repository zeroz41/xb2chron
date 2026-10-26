#ifndef CLASSES_GF_GFPLAYCOMWAITARENASTATEFIELD_H
#define CLASSES_GF_GFPLAYCOMWAITARENASTATEFIELD_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58B00; slot 1 is gf::GfPlayCom::~GfPlayCom() (this one's is implicit; start and end are inline)
class GfPlayComWaitArenaStateField : public GfPlayCom {
public:
    GfPlayComWaitArenaStateField() : GfPlayCom(52, false) {}
    static GfPlayComWaitArenaStateField* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "WaitArenaStateField";
        return func;
    }
    virtual void start() {}  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
