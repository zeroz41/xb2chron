#ifndef CLASSES_BTL_CHARACTERMANAGER_H
#define CLASSES_BTL_CHARACTERMANAGER_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class CharacterManager; class BattleCharacter; }
namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace btl {
// table 0x7100B3B280
class CharacterManager : public ::mm::mtl::PtrSingleton< ::btl::CharacterManager>, public ::fw::MessageObject {
public:
    virtual ~CharacterManager();  // slot 0
    static void Create();
    static void Destroy();
    // 1.0.0's name: 1.0.0's BattleManager::postUpdate calls it third, after DataManager's and BattleGlobal's
    static void PostUpdate(const fw::UpdateInfo& info);
    BattleCharacter* GetCharacterConst(int index) const;
    BattleCharacter* GetCharacterConst(gf::GF_OBJ_HANDLE* handle) const;
    // the character index of an AI script's character id (Utility::AI_GetCharacterHandle passes the id less 100
    // and false for an enemy)
    int GetCharacterIDByAiChrID(int id, bool isPlayer) const;
};
}  // namespace btl

#endif
