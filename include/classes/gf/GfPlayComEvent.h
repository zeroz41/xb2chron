#ifndef CLASSES_GF_GFPLAYCOMEVENT_H
#define CLASSES_GF_GFPLAYCOMEVENT_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::GfPlayComEvent no evidence names yet
class TUnk_B578D0 : public GfPlayCom {
public:
    virtual void vf7();
};
// table 0x7100B578D0; base at 0x0 unknown (TUnk_B578D0)
class GfPlayComEvent : public TUnk_B578D0, public ::gf::IGfEvent {
public:
    static GfPlayComEvent* create(unsigned int id, unsigned int, unsigned int, bool flag);
    // fn_7100319674 in the 3.0.1 symbols: 1.0.0's addEvent(char const*, ...) calls this name at the same site
    static GfPlayComEvent* create(const char* name, unsigned int, unsigned int, bool flag);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComEvent();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    virtual void vf7();  // slot 7
    static mm::mtl::RTTI m_rtti;
    static int m_activate;  // the symbol's own name
    unsigned int m_event;  // what isExistEvent compares (the name is not the original's)
};
}  // namespace gf

#endif
