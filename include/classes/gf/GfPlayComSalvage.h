#ifndef CLASSES_GF_GFPLAYCOMSALVAGE_H
#define CLASSES_GF_GFPLAYCOMSALVAGE_H

#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57DB0
class GfPlayComSalvage : public GfPlayCom {
public:
    // inline: create builds it (type 25); the wait starts at 3 frames
    explicit GfPlayComSalvage(GF_OBJ_HANDLE* handle) : GfPlayCom(25, false), m_handle(handle), m_wait(3), m_step(0) {}
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
    GF_OBJ_HANDLE* m_handle;  // the salvage point (update binds its gimmick, GfGameSalvage::startSalvage takes it)
    // update's frame countdown (3 at first, 45 while an environment condition holds; the names are not the original's)
    int m_wait;
    int m_step;  // update's step: 0 wait, 1 wait for the condition, 2 salvaging
};
}  // namespace gf

#endif
