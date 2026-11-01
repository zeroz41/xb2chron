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
    // fn_7100564088 and createBladeNArts call newHandle, then DataParamAcc::getBlade, then store the fields, which
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
    static void createCrystal();
    // placeholders (callers: one dispatch at 0x710000FDEC): fn_7100564360 counts type-1 once, then type for every
    // blade fn_7100563BB4 lists for the handle; the wrappers pass a fixed type and value 1
    static void fn_7100563BB4(mm::mtl::FixedVector<unsigned short, 422>&, GF_OBJ_HANDLE*, bool);
    static unsigned long createBladeArts(GF_OBJ_HANDLE*, unsigned int);
    static unsigned long fn_7100564088(GF_OBJ_HANDLE*, unsigned int);
    static unsigned long createBladeNArts(GF_OBJ_HANDLE*);
    static void fn_7100564354(GF_OBJ_HANDLE*);
    static void fn_7100564360(GF_OBJ_HANDLE*, unsigned int, unsigned int);
    static void fn_71005645DC(GF_OBJ_HANDLE*);
    static void fn_71005645E8(GF_OBJ_HANDLE*);
    static void fn_71005645F0(GF_OBJ_HANDLE*, unsigned int);
    static void fn_7100564920(GF_OBJ_HANDLE*);
    static void fn_7100564928(GF_OBJ_HANDLE*);
    static void fn_7100564ACC();
    static void fn_7100564AE8(GF_OBJ_HANDLE*);
    static void fn_7100564AF4();
    static void fn_7100564B10(GF_OBJ_HANDLE*);
    static void fn_7100564B1C(GF_OBJ_HANDLE*);
    static void fn_7100564B28(GF_OBJ_HANDLE*);
    static void fn_7100564C9C(GF_OBJ_HANDLE*, unsigned int);
    static void fn_7100564CAC(GF_OBJ_HANDLE*);
    static void fn_7100564DC0(GF_OBJ_HANDLE*, unsigned int);
    static void fn_7100564FE8(GF_OBJ_HANDLE*, unsigned int);
    // placeholders, members because they follow fn_7100564FE8 in this class's run of gf_req_scom and, like it, add to
    // GfDataAchievement::addTotalCount; their one caller is GfGameScene::BattleAchievement::addDamage (a type-3 object's
    // damage with its value, then the handle alone when the damage has attack flag 2; fn_71005653A4 the latter for the
    // notice's handle)
    static void fn_7100565210(GF_OBJ_HANDLE*, unsigned int);
    static void fn_71005653A4(GF_OBJ_HANDLE*);
    static void fn_7100565534(GF_OBJ_HANDLE*);

    // type-0x22 requests not yet counted: exec adds them as one (GfAchievManager::incAchiev(0x22, 1))
    static unsigned int s_countSalvageShop;

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    int m_value2;
    unsigned char pad_24[0x4];
    // the blades the count applies to (exec passes them to GfAchievManager::incAchievWithBlade when there are any)
    mm::mtl::FixedVector<unsigned short, 422> m_blades;
};

// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions: they make no request and take
// no this; their code sits among SCOM_ACHIEV_INC's functions in gf_req_scom and their one caller is the same dispatch
// (fn_710000FDEC) that calls SCOM_ACHIEV_INC's achievement wrappers. What they do: while a quest is ordered
// (GfQuestInfo::isQuestOrder), raise a local flag 8 counter by one up to 0xFF: quest 0x8ED flag 0x87C
// (fn_7100566480) and quest 0x8F0 flag 0x87D (fn_71005664E8), both only for handle -1 or the party leader driver
// (GfGameManager::getPartyLeaderDriver); quest 0x8F3 flag 0x87E (fn_7100566550), 0x8F6 / 0x87F (fn_7100566594),
// 0x8F9 / 0x880 (fn_71005665D8).
void fn_7100566480(GF_OBJ_HANDLE* handle);
void fn_71005664E8(GF_OBJ_HANDLE* handle);
void fn_7100566550();
void fn_7100566594();
void fn_71005665D8();
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions for the same reasons (no
// request, no this; between SCOM_ACHIEV_INC's functions). What they do: fill a blade list with
// GfDataBlade::fn_71002376E8 and pass it to GfAchievManager::incAchievWithBlade(type, 1, list): type 0x9B
// (fn_7100566168, caller the dispatch fn_710000FDEC) or the type given (fn_7100566424, caller
// minigame::tora::MinigameUpdatableObject::update).
void fn_7100566168();
void fn_7100566424(unsigned int type);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function for the same reasons (no
// request, no this; between SCOM_ACHIEV_INC's functions). What it does: counts the local flags 2/1..100 that are 2,
// adds local flag 0x20/0x141, and sets achievement total 75 to that: GfDataAchievement::fn_710024B71C(75, 0), then
// addTotalCount(75, count). Caller: GfGameScene::playEventSequenceEnd.
void fn_71005663BC();
}  // namespace gf

#endif
