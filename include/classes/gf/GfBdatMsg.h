#ifndef CLASSES_GF_GFBDATMSG_H
#define CLASSES_GF_GFBDATMSG_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class QuestID; }

namespace gf {
// table 0x7100B471A8; its singleton is the primary base, so the table's third slot is IDataBdat's override
class GfBdatMsg : public ::mm::mtl::PtrSingleton<GfBdatMsg>, public ::gf::IDataBdat {
public:
    GfBdatMsg();
    virtual ~GfBdatMsg();  // slot 0
    virtual void bdatRefresh();  // slot 2
    static void destroyFP();
    static void createFP();
    static unsigned char* getFpEnemy();
    static const char* getNameQuest(QuestID quest, unsigned int id);
    static unsigned char* getFpQuest(QuestID quest);
    static unsigned char* getFpQuest(unsigned int id);
    static unsigned char* getFpMapInfo();
    static const char* getNameMapInfo(unsigned int id);
    static unsigned char* getFpCollection();
    static unsigned char* getFpCrystal();
    static unsigned char* getFpPrecious();
    static unsigned char* getFpInfo();
    static unsigned char* getFpEvent();
    static unsigned char* getFpPcWpn();
    static unsigned char* getFpPcWpnChip();
    static unsigned char* getFpPcWpnType();
    static unsigned char* getFpSalvage();
    static unsigned char* getFpTresure();
    static unsigned char* getFpBooster();
    static unsigned char* getFpFavorite();
    static unsigned char* getFpOrb();
    static unsigned char* getFpPcEquip();
    static unsigned char* getFpCommonBladeName();
    static unsigned char* getFpMerceName();
    static unsigned char* getFpFieldSkill();
    static const char* getNameFieldSkill(unsigned int id);
    static unsigned char* getFpAchievement();
    static unsigned char* getFpChrDr();
    static unsigned char* getFpBtlClass();
    static unsigned char* getFpBlArtsMs();
    static unsigned char* getFpBlSpArtsMs();
    static unsigned char* getFpBlSkill();
    static unsigned char* getFpBtlEnhanceCap();
    static unsigned char* getFpBlBuffMs();
    static unsigned char* getFpBlBuffCap();
    static unsigned char* getFpBtlHanaRole();
    static unsigned char* getFpBtlHanaNArts();
    static unsigned char* getFpBtlHanaAtr();
    static unsigned char* getFpBtlSkillDr();
    // the message files createFP opens, each held in a block of its own
    static unsigned char** m_fpBldBladeName;
    static unsigned char** m_fpBldMerceName;
    static unsigned char** m_fpFldEnemyName;
    static unsigned char** m_fpFldNpcName;
    static unsigned char** m_fpFldQuest;
    static unsigned char** m_fpFldMapInfo;
    static unsigned char** m_fpFldLandmark;
    static unsigned char** m_fpFldFieldSkill;
    static unsigned char** m_fpItmCollection;
    static unsigned char** m_fpItmCrystal;
    static unsigned char** m_fpItmPrecious;
    static unsigned char** m_fpItmInfo;
    static unsigned char** m_fpItmEvent;
    static unsigned char** m_fpItmPcWpn;
    static unsigned char** m_fpItmPcWpnChip;
    static unsigned char** m_fpItmPcWpnType;
    static unsigned char** m_fpItmSalvage;
    static unsigned char** m_fpItmTresure;
    static unsigned char** m_fpItmFavorite;
    static unsigned char** m_fpItmBooster;
    static unsigned char** m_fpItmOrb;
    static unsigned char** m_fpItmPcEquip;
    static unsigned char** m_fpChrDr;
    static unsigned char** m_fpChrBl;
    static unsigned char** m_fpBtlClass;
    static unsigned char** m_fpBlArtsMs;
    static unsigned char** m_fpBlSpArtsMs;
    static unsigned char** m_fpBlSkill;
    static unsigned char** m_fpDrArtsMs;
    static unsigned char** m_fpBtlEnhanceCap;
    static unsigned char** m_fpFldQuestNormal;
    static unsigned char** m_fpFldQuestMini;
    static unsigned char** m_fpFldQuestBlade;
    static unsigned char** m_fpFldQuestAchievement;
    static unsigned char** m_fpFldQuestMercenaries;
    static unsigned char** m_fpBtlBuffMs;
    static unsigned char** m_fpBtlBuffCap;
    static unsigned char** m_fpFldAchievement;
    static unsigned char** m_fpBtlHanaRole;
    static unsigned char** m_fpBtlHanaNArts;
    static unsigned char** m_fpBtlHanaArts;
    static unsigned char** m_fpBtlHanaAtr;
    static unsigned char** m_fpBtlHanaAssist;
    static unsigned char** m_fpBtlSkillDr;
    static unsigned char** m_fpBtlEnGenus;
};
}  // namespace gf

#endif
