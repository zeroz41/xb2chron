#ifndef GF_GFACHIEVSTATS_H
#define GF_GFACHIEVSTATS_H

namespace gf { class AchievQuest; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MsgObjectNotifyDamage; }

namespace gf {
// the affinity chart quests' counts kept in the game's stats (functions, by their symbols)
class GfAchievStats {
public:
    // the party's blades counted for statistics 38 to 48, in that order (the names are not the original's)
    struct BladeCounts {
        unsigned int m_num;            // the blades (38)
        unsigned int m_gender1;        // GfDataBlade::getGender 1 (39)
        unsigned int m_gender2;        // GfDataBlade::getGender 2 (40)
        unsigned int m_race2;          // GfDataBlade::getRace 2 (41)
        unsigned int m_weaponType[7];  // GfDataBlade::getBladeWpnType 10 to 16 (42 to 48)
    };
    // counts num of an item got (crystals, treasures and collectibles)
    static void checkItem(unsigned int item, int num);
    // the quest's count from the stats; negative when the stats keep none for it
    static int getAchievementTotalCount(const AchievQuest& quest);
    // counts a talk with an NPC (GfPlayComTalk::start: the talk's NPC id and object)
    static void checkTalk(unsigned int npc, GF_OBJ_HANDLE* handle);
    // empty in this build
    static void checkFallLength(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDamage& damage);
    // counts num items bought from a shop and the price paid (the parameter names are not the original's)
    static void checkBuyItemFromShop(unsigned int item, unsigned int num, unsigned int, unsigned int price);
    // the same for items sold
    static void checkSellItemFromShop(unsigned int item, unsigned int num, unsigned int, unsigned int price);
    // counts the party's blades by kind once one is activated
    static void checkBladeActivate(unsigned int blade);
    // the count to add and the total of statistic stats for a quest's count value (prev: the count before, max:
    // the count to reach; the parameter names are not the original's)
    static void getAchievementAddCount(unsigned int& add, unsigned int& total, unsigned int stats, unsigned int value,
                                       unsigned int prev, unsigned int max);

private:
    // Placeholder name: nothing names it. A member because only this class's functions call it (no object). What
    // it does: the party's blades (GfDataBlade::getListParty, getListReserver, removeSameBlade) without blade,
    // counted into counts.
    static void fn_710028AF64(BladeCounts& counts, unsigned int blade);
};
}  // namespace gf

#endif
