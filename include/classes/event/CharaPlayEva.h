#ifndef CLASSES_EVENT_CHARAPLAYEVA_H
#define CLASSES_EVENT_CHARAPLAYEVA_H

#include "classes/event/ICmd.h"
#include "classes/event/CharaEvaPlayer.h"

namespace event {
// table 0x7100B3E6B8; CharaObj holds one at 0x750
class CharaPlayEva : public ::event::ICmd {
public:
    CharaPlayEva() : pad_8(0), pad_10() {}
    virtual ~CharaPlayEva() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned int pad_8;
    unsigned char pad_c[0x4];
    unsigned long pad_10[4];
    unsigned char pad_30[0x10];
    // the destructor runs its destructor (the name is not the original's)
    CharaEvaPlayer m_player;  // 0x40
};
}  // namespace event

#endif
