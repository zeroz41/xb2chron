#ifndef CLASSES_GF_GFPLAYCOMSALVAGE_H
#define CLASSES_GF_GFPLAYCOMSALVAGE_H

#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57DB0
class GfPlayComSalvage : public GfPlayCom {
public:
    static GfPlayComSalvage* create(GF_OBJ_HANDLE* handle);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComSalvage";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    unsigned int m_pause;  // from GfGameScene::createPlayerPause
};
}  // namespace gf

#endif
