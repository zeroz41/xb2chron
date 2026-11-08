#ifndef CLASSES_GF_SCOM_ACHIEV_INC_H
#define CLASSES_GF_SCOM_ACHIEV_INC_H

#include "classes/gf/SCOM.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }

namespace gf {
class GF_OBJ_HANDLE;
// table 0x7100B6AA60
class SCOM_ACHIEV_INC : public ::gf::SCOM {
public:
    // inline: every create function builds its request in place; each type-0x22 request counts once more
    SCOM_ACHIEV_INC(unsigned int type, int value) : SCOM(SCOM_TYPE(0x37)), m_value(type), m_value2(value) {
        if (type == 0x22) {
            ++s_countSalvageShop;
        }
    }
    // the same with the request handle passed in and the blade it counts for (0: none): createBladeArts,
    // createBladeArtsSp and createBladeNArts call newHandle, then DataParamAcc::getBlade, then store the fields, which
    // only this argument order gives
    SCOM_ACHIEV_INC(unsigned long handle, unsigned int type, int value, unsigned int blade)
        : SCOM(SCOM_TYPE(0x37), handle), m_value(type), m_value2(value) {
        if (type == 0x22) {
            ++s_countSalvageShop;
        }
        if (blade != 0) {
            m_blades.push_back(blade);
        }
    }
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a request that adds value to achievement counter type (type 0x22 also counts salvage-shop requests)
    static unsigned long create(unsigned int type, int value, unsigned int);
    // the same for every blade in the party (GfDataBlade::getListPartyAll)
    static unsigned long createParty(unsigned int type, int value);
    static void addTotalCount(unsigned int type, unsigned int value);
    // counts and queues achievement 49 (value 1) and adds 50 for every blade in the party
    static void createBladeCreate();
    static void createCrystal();
    // counts achievement 99 once and 100 for every blade fn_7100563BB4 lists for the handle (the enemy killer)
    static void createKillEnemy(GF_OBJ_HANDLE*);
    // placeholders (callers: one dispatch at 0x710000FDEC): fn_7100564360 counts type-1 once, then type for every
    // blade fn_7100563BB4 lists for the handle; the wrappers pass a fixed type and value 1
    static void fn_7100563BB4(mm::mtl::FixedVector<unsigned short, 422>&, GF_OBJ_HANDLE*, bool);
    static unsigned long createBladeArts(GF_OBJ_HANDLE*, unsigned int);
    static unsigned long createBladeArtsSp(GF_OBJ_HANDLE*, unsigned int);
    static unsigned long createBladeNArts(GF_OBJ_HANDLE*);
    static void createElementalCombo(GF_OBJ_HANDLE*);
    static void fn_7100564360(GF_OBJ_HANDLE*, unsigned int, unsigned int);
    static void createElementalComboFinish(GF_OBJ_HANDLE*);
    static void createFightCombo(GF_OBJ_HANDLE*);
    static void fn_71005645F0(GF_OBJ_HANDLE*, unsigned int);
    static void createFightComboFinish(GF_OBJ_HANDLE*);
    static void createChainAttack(GF_OBJ_HANDLE*);
    static void createButtonChallenge();
    static void createHelp(GF_OBJ_HANDLE*);
    static void createPotGet();
    static void createAvoid(GF_OBJ_HANDLE*);
    static void createGuard(GF_OBJ_HANDLE*);
    static void createBladeChange(GF_OBJ_HANDLE*);
    static void createRecover(GF_OBJ_HANDLE*, unsigned int);
    static void createBackAttack(GF_OBJ_HANDLE*);
    static void createDamageMax(GF_OBJ_HANDLE*, unsigned int);
    static void createDamageAdd(GF_OBJ_HANDLE*, unsigned int);
    // placeholders, members because they follow createDamageAdd in this class's run of gf_req_scom and, like it, add to
    // GfDataAchievement::addTotalCount; their one caller is GfGameScene::BattleAchievement::addDamage (a type-3 object's
    // damage with its value, then the handle alone when the damage has attack flag 2; createCriticalHit the latter for the
    // notice's handle)
    static void createDamageGet(GF_OBJ_HANDLE*, unsigned int);
    static void createCriticalHit(GF_OBJ_HANDLE*);
    static void createCriticalGet(GF_OBJ_HANDLE*);
    static void createBattle();  // GfGameScene::gevBattleEnd calls it after a battle with damage counted
    // placeholder, a member because it follows createCriticalGet in this class's run of gf_req_scom and has its shape:
    // counts achievement 0x76 once and 0x77 for every blade fn_7100563BB4 lists for the handle; its one caller is the
    // dispatch at 0x710000FDEC
    static void createKizuna(GF_OBJ_HANDLE*);

    // 2.0.0's symbols name them. Static members: they make no request; their code sits among SCOM_ACHIEV_INC's functions in gf_req_scom and their one caller is the same dispatch
    // (AchieveCondition) that calls SCOM_ACHIEV_INC's achievement wrappers. What they do: while a quest is ordered
    // (GfQuestInfo::isQuestOrder), raise a local flag 8 counter by one up to 0xFF: quest 0x8ED flag 0x87C
    // (createDriverCombo2) and quest 0x8F0 flag 0x87D (createDriverCombo4), both only for handle -1 or the party leader driver
    // (GfGameManager::getPartyLeaderDriver); quest 0x8F3 flag 0x87E (createBladeCombo2), 0x8F6 / 0x87F (createBladeCombo3),
    // 0x8F9 / 0x880 (createFusionCombo).
    static void createDriverCombo2(GF_OBJ_HANDLE* handle);
    static void createDriverCombo4(GF_OBJ_HANDLE* handle);
    static void createBladeCombo2(GF_OBJ_HANDLE* handle);
    static void createBladeCombo3(GF_OBJ_HANDLE* handle);
    static void createFusionCombo(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name them. Static members for the same reasons (no request; between SCOM_ACHIEV_INC's functions). What they do: fill a blade list with
    // GfDataBlade::getListParty and pass it to GfAchievManager::incAchievWithBlade(type, 1, list): type 0x9B
    // (createOverKill, caller the dispatch AchieveCondition) or the type given (createTiger, caller
    // minigame::tora::MinigameUpdatableObject::update).
    static void createOverKill();
    // 2.0.0's symbols name it (not written yet, code at 0x7100566230): GfArenaBattle::execBattleSequence passes m_key's
    // id when m_result is 2. What it does: counts achievements 0x9F and 0x9E and, for ids below 0x1C, the id's
    // achievement from two tables, then queues a SCOM_ACHIEV_INC.
    static void createCbClearStage(unsigned int id);
    // 2.0.0's symbols name it: StateArenaReturnBattle::onStep calls it each step with GfGameManager::getBattleArenaEtherCube's answer
    static void createCbCube(unsigned int value);
    static void createTiger(unsigned int type);
    // 2.0.0's symbols name it. A static member for the same reasons (no request; between SCOM_ACHIEV_INC's functions). What it does: counts the local flags 2/1..100 that are 2,
    // adds local flag 0x20/0x141, and sets achievement total 75 to that: GfDataAchievement::setTotalCount(75, 0), then
    // addTotalCount(75, count). Caller: GfGameScene::playEventSequenceEnd.
    static void createKizunaTalk();

    // type-0x22 requests not yet counted: exec adds them as one (GfAchievManager::incAchiev(0x22, 1))
    static unsigned int s_countSalvageShop;

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    int m_value2;
    unsigned char pad_24[0x4];
    // the blades the count applies to (exec passes them to GfAchievManager::incAchievWithBlade when there are any)
    mm::mtl::FixedVector<unsigned short, 422> m_blades;
};

}  // namespace gf

#endif
