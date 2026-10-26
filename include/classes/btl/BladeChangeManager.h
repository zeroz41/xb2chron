#ifndef CLASSES_BTL_BLADECHANGEMANAGER_H
#define CLASSES_BTL_BLADECHANGEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BladeChangeManager; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3A8C0
class BladeChangeManager : public ::mm::mtl::PtrSingleton< ::btl::BladeChangeManager> {
public:
    virtual ~BladeChangeManager();  // slot 0
    static void Create();
    static void Destroy();
    bool IsRegister(gf::GF_OBJ_HANDLE* handle) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's StateField::onDead has no such call).
    // A member because its address is in blade_change_manager's unit and StateField::onDead calls it on
    // PtrSingleton<BladeChangeManager>::sys(). What it does: walks the manager's 0x40-byte entries (count at +0x288)
    // for one holding the handle (at entry +0x8 with byte +0x40 clear, +0x10, or +0x18 with byte +0x41 clear); for
    // that entry it returns false when CharacterManager::GetCharacterConst(handle) is none, else the negation of
    // fn_7100028D0C(character, 0); true when no entry holds it. StateField::onDead handles a death only when true.
    bool fn_7100019180(gf::GF_OBJ_HANDLE* handle);
};
}  // namespace btl

#endif
