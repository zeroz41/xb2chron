#ifndef CLASSES_GF_GFPLAYCOMSCRIPTTUTORIALSEQ_H
#define CLASSES_GF_GFPLAYCOMSCRIPTTUTORIALSEQ_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/RTTI.h"
namespace gf { class GF_SCOM_HANDLE; }

namespace gf {
// table 0x7100B582D0
class GfPlayComScriptTutorialSeq : public GfPlayCom {
public:
    GfPlayComScriptTutorialSeq(const char* name, int startId)
        : GfPlayCom(30, false), m_script(reinterpret_cast<GF_SCOM_HANDLE*>(-1)) {
        s_refCount++;
        m_name = name;
        m_startId = startId;
    }
    // 2.0.0's symbols name it. A static member: it allocates this class
    // (table 0x7100B582D0, kind 30). What it does: news a 0x60-byte command holding the script name and the
    // after-event start id start passes to GfGameEvent::setAfterEventStartID.
    static GfPlayComScriptTutorialSeq* create(const char* name, unsigned int startId);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComScriptTutorialSeq();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComScriptTutorialSeq";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // the commands alive (the constructor counts up, the destructor down). 2.0.0's symbols name it
    static int s_refCount;

    mm::mtl::FixStr<64> m_name;  // the script start runs (SCOM_SCRIPT 3); the name is not the original's
    int m_startId;  // GfGameEvent::setAfterEventStartID's; the name is not the original's
    GF_SCOM_HANDLE* m_script;  // start's SCOM_SCRIPT request; the name is not the original's
};
}  // namespace gf

#endif
