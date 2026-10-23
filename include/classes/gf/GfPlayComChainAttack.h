#ifndef CLASSES_GF_GFPLAYCOMCHAINATTACK_H
#define CLASSES_GF_GFPLAYCOMCHAINATTACK_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B58148
class GfPlayComChainAttack : public GfPlayCom {
public:
    GfPlayComChainAttack() : GfPlayCom(40, true), pad_10(0), m_state(0) {}
    static GfPlayComChainAttack* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "ChainAttack";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    int pad_10;
    int m_state;  // start sets 3; the name is not the original's
};
}  // namespace gf

#endif
