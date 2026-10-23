#ifndef CLASSES_GF_GFPLAYCOMCOLLECT_H
#define CLASSES_GF_GFPLAYCOMCOLLECT_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfGameScene.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B57DF8; GfSequentialPlay::addCollect makes it
class GfPlayComCollect : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComCollect> {
public:
    explicit GfPlayComCollect(GF_OBJ_HANDLE* handle) : GfPlayCom(26, false), m_handle(handle) {}
    static GfPlayComCollect* create(GF_OBJ_HANDLE* handle);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComCollect";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    unsigned int m_pause;  // from GfGameScene::createPlayerPause
    GF_OBJ_HANDLE* m_handle;
};
}  // namespace gf

#endif
