#ifndef CLASSES_GF_GFPLAYCOMWAITEVENT_H
#define CLASSES_GF_GFPLAYCOMWAITEVENT_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf { class GF_OBJ_HANDLE; }
namespace gf {
// table 0x7100B577B0
class GfPlayComWaitEvent : public GfPlayCom {
public:
    GfPlayComWaitEvent(float time, GF_OBJ_HANDLE* handle)
        : GfPlayCom(4, false) {
        s_activate++;
        m_time = time;
        m_handle = handle;
        m_req = -1;
    }
    static GfPlayComWaitEvent* create(float time, GF_OBJ_HANDLE* handle);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComWaitEvent();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComWaitEvent";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // the commands alive (the constructor counts up, the destructor down; GfQuestManager::checkQuestComplete and
    // SCOM_CHAR_DEAD::create read it). The name is not the original's (3.0.1 leaves it unnamed, lbl_7100EA4A60;
    // the other counting commands' is s_activate)
    static int s_activate;

    float m_time;  // create's names
    GF_OBJ_HANDLE* m_handle;
    unsigned int m_req;  // GfReqCommand::reqWaitEvent's handle; the name is not the original's
};
}  // namespace gf

#endif
