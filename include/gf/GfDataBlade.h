#ifndef GF_GFDATABLADE_H
#define GF_GFDATABLADE_H

#include "gf/AchievQuest.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class SDataBlade; }
namespace gf { struct BladeArtsSlot; }
namespace gf { struct BladeSkillSlot; }
namespace gf { struct SDataIdea; }
namespace gf { enum FAVORITE : int; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedArray; }}

namespace gf {

// a blade's affinity chart line: its quests by level (0x90 bytes; 1.0.0's GfDataBlade::setupAchievInfo names the
// class). The field names are not the original's.
struct AchievInfo {
    unsigned short m_achievementId;  // zero: the line has no chart (setupAchievInfo fills it only when set)
    unsigned char pad_2[0x2];
    AchievQuest m_quests[5];
};

// the blades' game data (functions, by its symbols)
class GfDataBlade {
public:
    // the blade's slot in the game data's blades (SDataGame::m_blades): the regular blades, then the rare ones,
    // then the common ones; 0 for any other id. Inline: every accessor carries its code (1.0.0's too), so the name
    // is not the original's.
    static unsigned int getBladeIndex(unsigned int blade) {
        if (blade - 1001 < 13) {
            return blade - 1001;
        }
        if (blade - 1014 < 176) {
            return blade - 994;
        }
        if (blade - 1197 < 226) {
            return blade - 1001;
        }
        return 0;
    }
    // fills list with the party's blades (SCOM_ACHIEV_INC::createParty and createCrystal)
    static void getListPartyAll(mm::mtl::FixedVector<unsigned short, 422>& list);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions. What it does: GfGameFlag::getLocal of the game data's flags (GfDataManager::getDataGame
    // + 0xFBBC4), width 16, index 1; TUnk_B64F08::fn_71004944B8 compares it with 2000.
    static unsigned short fn_7100231884();
    static bool getTaskSkillMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line);
    static bool getTaskResultMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                     unsigned int level);
    static unsigned int getSkillLineId(unsigned int blade, unsigned int line);
    // whether the blade is in the battle party (1.0.0's GfQuestInfo::incSuppressCount calls it on the quest's blade)
    static bool isBattleMember(unsigned int blade);
    static unsigned int getKizunaringCompleteNum(unsigned int blade);
    static unsigned int getKizunaringMax(unsigned int blade);
    // the scale of a blade's weapon (GfGameMount::attach scales the weapon's models by it at option 3)
    static float getWpnScale(unsigned int blade);
    static bool isRareBlade(unsigned int blade);
    // a game flag: Pyra's name shown as Mythra's (GfMenuObjNameSelect sets it from the name picked)
    static void setHomuriNameHikari(bool hikari);
    static bool isHomuriNameHikari();  // the flag setHomuriNameHikari sets (local flag 0x89FB, 1 bit)
    static bool isActivateUnuse(unsigned int blade);
    static bool isUnselect(unsigned int blade);
    // the driver the blade is set to, 0 for none
    static unsigned int getSetDriver(unsigned int blade);
    static AchievInfo* getAchievInfo(unsigned int blade, unsigned int line);
    // the blades with an affinity chart
    static void getListForAchievement(mm::mtl::FixedVector<unsigned short, 422>& list);
    static unsigned int getKeyReleaseLevel(unsigned int blade);
    static void setSkillLineLevel(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getBladeWpnType(unsigned int blade);
    static const char* getName(unsigned int blade, unsigned int kind);
    // the message table and row of the blade's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    static unsigned int getQuestRace(unsigned int blade);
    static SDataBlade* getSDataBlade(unsigned int blade);
    static unsigned int getHpMaxRev(unsigned int blade);
    static unsigned int getStrengthRev(unsigned int blade);
    static unsigned int getPowerEtherRev(unsigned int blade);
    static unsigned int getDexRev(unsigned int blade);
    static unsigned int getAgilityRev(unsigned int blade);
    static unsigned int getLuckRev(unsigned int blade);
    static bool getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>& orbs, unsigned int blade);
    static unsigned int getFootStep(unsigned int blade);
    static unsigned int getFootStepEffect(unsigned int blade);
    static unsigned int getRole(unsigned int blade);
    static const char* getVoiceStr(unsigned int blade);
    static const BladeArtsSlot* getArts(unsigned int blade, unsigned int index);
    static unsigned int getArtsEnhance(unsigned int blade, unsigned int index);
    static const BladeArtsSlot* getNArts(unsigned int blade, unsigned int index);
    static unsigned int getFavorite(unsigned int blade, FAVORITE favorite);
    static int getOffsetID(unsigned int blade);  // its menu offset id
    static unsigned int getBladePower(unsigned int blade);
    static bool isMale(unsigned int blade);
    static bool isFemale(unsigned int blade);
    static bool isAnimal(unsigned int blade);
    static unsigned int getAttribute(unsigned int blade);
    static bool getExtraParts(const SDataBlade& data, unsigned int part);
    static unsigned int getBladePower(SDataBlade& data);
    static unsigned int getRoleByWpnType(unsigned int wpnType);
    static bool isHikariCurrent();
    static void setHikariCurrent(bool value);
    static unsigned int getStartCommonBlade();
    static unsigned int getEndCommonBlade();
    static unsigned int getStartUiCommonBlade();
    static bool isCommonBlade(unsigned int blade);
    static bool isRegularBlade(unsigned int blade);
    static bool isValid(unsigned int blade);
    static bool isBladeID(unsigned int blade);
    static bool isNeedChangeWeapon(unsigned int blade);
    static unsigned int getActBlade2CommonBlade(unsigned int blade);
    static bool isEnableEngageRex(unsigned int blade);
    static unsigned int getBornTime(unsigned int blade);
    static SDataIdea* getSDataIdea(unsigned int blade);
    static bool isAttachedParty(unsigned int blade);
    static bool isActivateDriver(unsigned int blade);
    static const char* getResourceNameModel(unsigned int blade);
    static bool isKizunaringComplete(unsigned int blade);
    static bool isReleasedRareBlade(unsigned int blade);
    static unsigned int getTrustRank(unsigned int blade);
    static bool isSetBlade(unsigned int blade);
    static unsigned int getBladeWeapon(unsigned int blade);
    static const char* getResourceNameMotion(unsigned int blade);
    static const char* getResourceNameAddMotion(unsigned int blade);
    static unsigned int getRace(unsigned int blade);
    static float getScale(unsigned int blade);
    static unsigned int getSize(unsigned int blade);
    static unsigned int getEquipOrbMax(unsigned int blade);
    static unsigned int getCreateEvent(unsigned int blade);
    static unsigned int getNormalTalk(unsigned int blade);
    static unsigned int getTrustPoint(unsigned int blade);
    static bool isReleaseLock(unsigned int blade);
    static const char* getSePack(unsigned int blade);
    static void setEnableEngageRex(unsigned int blade, bool enable);
    static void setKizunaringComplete(unsigned int blade);
    static bool setActivateMercenaryTeam(unsigned int blade);
    static void setBladeWeapon(unsigned int blade, unsigned int weapon);
    static void setUnselect(unsigned int blade, bool unselect);
    static void setTrustPoint(unsigned int blade, unsigned int point);
    static bool getExtraParts(unsigned int blade, unsigned int part);
    static const BladeSkillSlot* getSkill(unsigned int blade, unsigned int index);
};

}  // namespace gf

#endif
