#ifndef CLASSES_BTL_CHARACTERMANAGER_H
#define CLASSES_BTL_CHARACTERMANAGER_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/btl/BattleCharacter.h"
#include "mm/mtl/FixedVector.h"
#include <string.h>

namespace btl { class CharacterManager; class BattleCharacter; }
namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace btl {
// table 0x7100B3B280
class CharacterManager : public ::mm::mtl::PtrSingleton< ::btl::CharacterManager>, public ::fw::MessageObject {
public:
    enum {
        PLAYER_NUM = 20,  // slots 0-19 hold the players (Register's range for a non-enemy)
        CHARACTER_NUM = 90,  // slots 20-89 the enemies
    };
    // a character and whether its slot is in use (the names are not the original's)
    struct CHARACTER_SLOT {
        CHARACTER_SLOT() : m_isUsed(false) {}
        BattleCharacter m_chr;
        bool m_isUsed;
    };

    // Create builds it in place (1.0.0 has it out of line; 3.0.1 none)
    CharacterManager() : m_controlIndex(CHARACTER_NUM) {
        memset(&m_aiChrTable, 0xFF, sizeof(m_aiChrTable));
    }
    virtual ~CharacterManager();  // slot 0
    static void Create();
    static void Destroy();
    int Register(gf::GF_OBJ_HANDLE* handle, bool isEnemy);
    // frees the slot index Register gave handle (GfPropertyBattle::cleanup)
    void Release(int index, gf::GF_OBJ_HANDLE* handle);
    int SearchCharacter(gf::GF_OBJ_HANDLE* handle) const;
    // 1.0.0's names: 1.0.0's BattleManager::update calls PreUpdate first and Update second, as 3.0.1's calls them
    static void PreUpdate(const fw::UpdateInfo& info);
    void PreUpdateProc(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    void AssignAiChrID();
    // 1.0.0's name: 1.0.0's BattleManager::postUpdate calls it third, after DataManager's and BattleGlobal's
    static void PostUpdate(const fw::UpdateInfo& info);
    void PostUpdateProc(const fw::UpdateInfo& info);
    BattleCharacter* GetCharacterConst(int index) const;
    BattleCharacter* GetCharacterConst(gf::GF_OBJ_HANDLE* handle) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it reads the slots. What it
    // does: the first character in use among the players (isPlayer) or the enemies whose m_bdatID is bdatID, else
    // null (GROUP_BLADE_DATA::Initialize, GROUP_DATA::Update, TalkManager::RegisterSpecialWin call it).
    BattleCharacter* fn_710007B5DC(bool isPlayer, int bdatID) const;
    gf::GF_OBJ_HANDLE* GetCharacterHandle(int index) const;  // the handle of the character at index
    BattleCharacter* GetControlCharacter();
    bool IsControlCharacter(gf::GF_OBJ_HANDLE* handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it writes m_enhanceCount. What
    // it does: adds count to m_enhanceCount, holding it at 255 (BattleCharacter::SetupSpecialEnhanceData calls it).
    void fn_710007C020(int count);
    // the character index of an AI script's character id (Utility::AI_GetCharacterHandle passes the id less 100
    // and false for an enemy)
    int GetCharacterIDByAiChrID(int id, bool isPlayer) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it walks the enemy slots. What
    // it does: calls BattleCharacter::fn_710002B868 on every enemy in use (BattleGlobal::PreUpdateProc calls it).
    void fn_710007C1E0();
    bool IsExistBattleEnemy(bool* result, gf::GF_OBJ_HANDLE* handle, bool flag) const;

    CHARACTER_SLOT m_slots[CHARACTER_NUM];
    // the indices of the slots in use, sorted by their character's handle (SearchCharacter's binary search; the
    // name is not the original's)
    mm::mtl::FixedVector<unsigned char, CHARACTER_NUM> m_sortedSlots;
    // the slot index of each AI character id, 0xFF for none (1.0.0's SetAiChrTable(int, int, bool) fills it; the
    // names are not the original's)
    struct AI_CHR_TABLE {
        unsigned char m_player[PLAYER_NUM];
        unsigned char m_enemy[CHARACTER_NUM - PLAYER_NUM];
    };
    AI_CHR_TABLE m_aiChrTable;
    // the slot of the character the player controls, CHARACTER_NUM for none (the name is not the original's)
    unsigned char m_controlIndex;
    // fn_710007C020 adds to it, up to 255 (the name is not the original's)
    unsigned char m_enhanceCount;
};
}  // namespace btl

#endif
