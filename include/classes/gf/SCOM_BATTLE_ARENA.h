#ifndef CLASSES_GF_TUNK_B6AD28_H
#define CLASSES_GF_TUNK_B6AD28_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AD28 (no RTTI name): a type-0x55 request whose exec sends the arena game mode (GfGameArena) a
// MsgUnk_1000034 carrying m_type and m_param; five create placeholders queue it with a fixed type and parameter 0
class SCOM_BATTLE_ARENA : public ::gf::SCOM {
public:
    explicit SCOM_BATTLE_ARENA(unsigned int type) : SCOM(SCOM_TYPE(0x55)), m_type(type), m_param(0) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long createWin();
    static unsigned long createLose();
    static unsigned long createRetry();
    static unsigned long createGiveUp();
    static unsigned long createLoseStart();

    // the names are not the original's: the message's type and its first parameter word
    unsigned int m_type;
    unsigned int m_param;
};
}  // namespace gf

#endif
