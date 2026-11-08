#ifndef CLASSES_GF_GFPLAYCOMEVENT_H
#define CLASSES_GF_GFPLAYCOMEVENT_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/IGfEvent.h"
#include "mm/mtl/FixStr.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B578D0: GfPlayCom's slots, then gevPlayEvent (slot 7: the override of IGfEvent's slot 36, which a
// new virtual of a secondary base gets in the primary table); the IGfEvent table at +0x60
class GfPlayComEvent : public GfPlayCom, public ::gf::IGfEvent {
public:
    // out of line (0x710031930C; create calls it)
    GfPlayComEvent(unsigned int id, unsigned int, unsigned int, const char* bgm, const mm::Vec3* pos, float time);
    static GfPlayComEvent* create(unsigned int id, unsigned int, unsigned int, bool flag);
    // 2.0.0's symbols name it. What it does: allocates the 0x90-byte command (as 1.0.0's create(unsigned int, unsigned
    // int, unsigned int, bool) did; 3.0.1 has no other create).
    static GfPlayComEvent* create(unsigned int id, unsigned int, unsigned int, const char* bgm,
                                         const mm::Vec3* pos, float time);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComEvent();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComEvent";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    virtual void gevPlayEvent(gf::GEV gev, unsigned int id);  // slot 7 (IGfEvent slot 36)
    static mm::mtl::RTTI m_rtti;
    static int m_activate;  // the symbol's own name
    unsigned int m_event;  // what isExistEvent compares (the name is not the original's)
    // start passes them, with m_pos and m_time, to GfGameEvent::play (the names are not the original's)
    unsigned int pad_1C;
    unsigned int pad_20;
    bool m_eventStarted;  // gevPlayEvent sets it on GEV 10 (the name is not the original's)
    // the constructor: the party leader is in battle or a boss enemy exists; it then sets GfGameScene's
    // m_battleEventBgm (the name is not the original's)
    bool m_battle;
    // the BGM gevPlayEvent hands to GfFieldBgm::playFieldBgmForce on GEV 14, then clears (the name is not the original's)
    mm::mtl::FixStr<64> m_bgm;
    mm::Vec3 m_pos;  // start passes its address (16 bytes on a 16-byte boundary: inferred a Vec3; the name is not the original's)
    float m_time;  // start passes it in s0 (the name is not the original's)
};
}  // namespace gf

#endif
