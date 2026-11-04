#ifndef CLASSES_GF_SCOM_CLEAR_TIME_H
#define CLASSES_GF_SCOM_CLEAR_TIME_H

namespace gf {

// 2.0.0's symbols name it: only its create function is in the binary (no table, no request is queued).
class SCOM_CLEAR_TIME {
public:
    // passes value to GfWeapon's unit's GfGameUtil::applyClearTimeForArena. Caller: btl::ChallengeBattleManager::UpdateProc
    static void create(unsigned int value);
};

}  // namespace gf

#endif
