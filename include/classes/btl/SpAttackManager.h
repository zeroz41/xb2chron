#ifndef CLASSES_BTL_SPATTACKMANAGER_H
#define CLASSES_BTL_SPATTACKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class SpAttackManager; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3BDA8
class SpAttackManager : public ::mm::mtl::PtrSingleton< ::btl::SpAttackManager> {
public:
    virtual ~SpAttackManager();  // slot 0
    static void Create();
    static void Destroy();
    bool IsRegister(gf::GF_OBJ_HANDLE* handle) const;

    unsigned char pad_8[0x200];
    // above zero while a special attack runs: Utility::AI_IsProcSpAttack tests it (the name is not the original's)
    int m_procCount;
};
}  // namespace btl

#endif
