#ifndef CLASSES_GF_GFPLAYCOMIRACAMPSAVE_H
#define CLASSES_GF_GFPLAYCOMIRACAMPSAVE_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"

namespace gf {
// table 0x7100B57B28
class GfPlayComIraCampSave : public GfPlayCom {
public:
    explicit GfPlayComIraCampSave(bool skip) : GfPlayCom(11, false), m_req(-1) {
        m_skip = skip && s_activate <= 0;  // only when no other one is active
        s_activate++;
    }
    // 2.0.0's symbols name them. Static members: they allocate this class (table 0x7100B57B28, kind 11). What they do:
    // the first news one that never skips the solo-party request, the second one that skips it unless no other is
    // running (s_activate < 1).
    static GfPlayComIraCampSave* createForEvent();
    static GfPlayComIraCampSave* createForTutorial();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComIraCampSave();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "IraCampSave";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // how many exist (the constructor counts up, the destructor down; start acts only while it is 1). Proposed
    // name, not the original's: the symbols leave it unnamed (lbl_7100EA4B30)
    static int s_activate;

    unsigned int m_req;  // start's GfReqCommand::reqSoloParty handle; the name is not the original's
    bool m_skip;  // start makes no request when it is set; the name is not the original's
};
}  // namespace gf

#endif
