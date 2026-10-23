#ifndef CLASSES_GF_GFPLAYCOMMINIGAME_H
#define CLASSES_GF_GFPLAYCOMMINIGAME_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B58650
class GfPlayComMiniGame : public GfPlayCom {
public:
    GfPlayComMiniGame() : GfPlayCom(39, false) {}
    static GfPlayComMiniGame* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComMiniGame";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

};
}  // namespace gf

#endif
