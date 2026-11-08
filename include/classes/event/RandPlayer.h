#ifndef CLASSES_EVENT_RANDPLAYER_H
#define CLASSES_EVENT_RANDPLAYER_H

#include "classes/event/CmdQueue.h"
#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3D3A0
class RandPlayer {
public:
    // the four commands are members (RandManager's constructor stores their tables at RandPlayer+0x8..0x20); their
    // definitions moved here from RandPlayer/Warp.h, Wait.h and Reset.h, which include this header
    // table 0x7100B3F020
    class Warp : public ::event::ICmd {
    public:
        virtual ~Warp() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual int update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3F058
    class Wait : public ::event::ICmd {
    public:
        virtual ~Wait() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual int update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3F090
    class Reply : public ::event::ICmd {
    public:
        virtual ~Reply() {}  // slot 0 (inline: its D0 0x710014B068 is in the unit's inline tail)
        virtual int update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3F0C8
    class Reset : public ::event::ICmd {
    public:
        virtual ~Reset() {}  // slot 0 (inline: its D0 0x710014B06C is in the unit's inline tail)
        virtual int update(event::ICmd::Param const&);  // slot 3
    };
    RandPlayer() : m_flags(0) {}
    virtual ~RandPlayer();  // slot 0
    // RandManager::play starts the row it picked
    void play(int id, bool);
    // 1.0.0's RandPlayer::clear/update/isPlaying (out of line there; 3.0.1 inlines them)
    void clear() {
        m_queue.clear();
        m_flags = 0;
    }
    void update() {
        if (m_flags & 1) {
            m_queue.update();
            if (m_queue.empty()) {
                m_flags &= ~1;
            }
        }
    }
    bool isPlaying() const { return m_flags & 1; }
    // the message file Reply::update hands TextManager::reply ("fld_randomtalk", symbol _ZN5event10RandPlayer6MSBDATE)
    static const char* MSBDAT;
    Warp m_warp;  // 0x8 (the name is not the original's)
    Wait m_wait;  // 0x10 (the name is not the original's)
    Reply m_reply;  // 0x18 (the name is not the original's)
    Reset m_reset;  // 0x20 (the name is not the original's)
    CmdQueue<8, 0> m_queue;  // 0x28 (the name is not the original's)
    unsigned int m_flags;    // 0x978 bit 0: playing (the name is not the original's)
};
}  // namespace event

#endif
