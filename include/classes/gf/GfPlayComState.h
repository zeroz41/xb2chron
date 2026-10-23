#ifndef CLASSES_GF_GFPLAYCOMSTATE_H
#define CLASSES_GF_GFPLAYCOMSTATE_H

#include "classes/gf/GfPlayCom.h"
namespace gf { enum GF_STATE : int; }  // as GfGameManager.h declares it

namespace gf {
// table 0x7100B583F0
class GfPlayComState : public GfPlayCom {
public:
    GfPlayComState(GF_STATE state, bool check) : GfPlayCom(2, true), m_state(state), m_check(check) {}
    static GfPlayComState* create(GF_STATE state, bool check);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComState";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    GF_STATE m_state;
    bool m_check;
};
}  // namespace gf

#endif
