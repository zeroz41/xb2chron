#ifndef CLASSES_GF_GFPLAYCOMAFTEREVENTSCRIPT_H
#define CLASSES_GF_GFPLAYCOMAFTEREVENTSCRIPT_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf { class GF_SCOM_HANDLE; }
namespace gf {
// table 0x7100B57888
class GfPlayComAfterEventScript : public GfPlayCom {
public:
    explicit GfPlayComAfterEventScript(unsigned int id)
        : GfPlayCom(8, false), pad_10(0), m_id(id), m_script(reinterpret_cast<GF_SCOM_HANDLE*>(-1)) {
        s_activate++;
    }
    static GfPlayComAfterEventScript* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComAfterEventScript();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComAfterEventScript";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the commands alive

    int pad_10;
    unsigned int m_id;  // the event (GfDataEvent's after-script getters); the name is not the original's
    GF_SCOM_HANDLE* m_script;  // the SCOM_SCRIPT request start makes; the name is not the original's
};
}  // namespace gf

#endif
