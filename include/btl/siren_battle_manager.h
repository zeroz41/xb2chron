#ifndef BTL_SIREN_BATTLE_MANAGER_H
#define BTL_SIREN_BATTLE_MANAGER_H

// The functions of application/BF2/battle/siren_battle_manager.cpp other units call. Its class has no name in the symbols (no
// table, no singleton symbol) and 1.0.0 has no such file, so its functions are free placeholders in btl.

namespace btl {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its unit's class has no name.
// What it does: allocates the unit's object (the new cites "battle/siren_battle_manager.cpp"), whose PtrSingleton
// constructor asserts get()==0. btl::BattleManager::Initialize calls it last, after UIManager::Create.
void fn_71000A52CC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: as fn_71000A52CC. What it does:
// deletes that object; btl::BattleManager::Finalize calls it first, before UIManager::Destroy (the reverse of the create order).
void fn_71000A571C();
}  // namespace btl

#endif
