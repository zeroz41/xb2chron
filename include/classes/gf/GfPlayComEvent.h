#ifndef CLASSES_GF_GFPLAYCOMEVENT_H
#define CLASSES_GF_GFPLAYCOMEVENT_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::GfPlayComEvent no evidence names yet
class TUnk_B578D0 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual ~TUnk_B578D0();
    virtual void getFuncName() const = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void update(fw::UpdateInfo const&, bool) = 0;
    virtual void vf7();
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// table 0x7100B578D0; base at 0x0 unknown (TUnk_B578D0)
class GfPlayComEvent : public TUnk_B578D0, public ::gf::IGfEvent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComEvent();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
    virtual void vf7();  // slot 7
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
