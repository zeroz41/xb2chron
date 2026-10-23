#ifndef CLASSES_GF_GFPLAYCOMFIELDSEQ_H
#define CLASSES_GF_GFPLAYCOMFIELDSEQ_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/IFieldSeq.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B57EC8
class GfPlayComFieldSeq : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComFieldSeq> {
public:
    GfPlayComFieldSeq(IFieldSeq* seq, GF_OBJ_HANDLE* handle) : GfPlayCom(28, false), m_seq(seq), m_handle(handle) {}
    static GfPlayComFieldSeq* create(IFieldSeq* seq, GF_OBJ_HANDLE* handle);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComFieldSeq";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    IFieldSeq* m_seq;
    GF_OBJ_HANDLE* m_handle;
    unsigned int m_pause;  // from GfGameScene::createPlayerPause
};
}  // namespace gf

#endif
