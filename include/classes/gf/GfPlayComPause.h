#ifndef CLASSES_GF_GFPLAYCOMPAUSE_H
#define CLASSES_GF_GFPLAYCOMPAUSE_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B583A8; GfSequentialPlay::pushPause and popPause make it (0 pops)
class GfPlayComPause : public GfPlayCom {
public:
    explicit GfPlayComPause(unsigned int pause) : GfPlayCom(1, true), m_pause(pause) {}
    static GfPlayComPause* create(unsigned int pause);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComPause";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    unsigned int m_pause;
};
}  // namespace gf

#endif
