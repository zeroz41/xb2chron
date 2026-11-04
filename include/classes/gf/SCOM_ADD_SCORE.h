#ifndef CLASSES_GF_TUNK_B6AFA0_H
#define CLASSES_GF_TUNK_B6AFA0_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AFA0 (no RTTI name): a type-0x54 request whose exec passes m_value to GfWeapon's unit's GfGameUtil::addScore (a
// MsgGameBtlArena to the arena game mode); create queues it (2.0.0's symbols name the class and create)
class SCOM_ADD_SCORE : public ::gf::SCOM {
public:
    explicit SCOM_ADD_SCORE(int value) : SCOM(SCOM_TYPE(0x54)), m_value(value) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // 0x20-byte request; nothing for 0. Callers: btl::ChallengeBattleManager (AddEtherCube, AddScore)
    static unsigned long create(unsigned int value);

    int m_value;  // the name is not the original's: the create function's argument
};
}  // namespace gf

#endif
