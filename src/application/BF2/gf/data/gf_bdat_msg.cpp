#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatMsg.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
unsigned char** GfBdatMsg::m_fpBldBladeName;
unsigned char** GfBdatMsg::m_fpBldMerceName;
unsigned char** GfBdatMsg::m_fpFldEnemyName;
unsigned char** GfBdatMsg::m_fpFldNpcName;
unsigned char** GfBdatMsg::m_fpFldQuest;
unsigned char** GfBdatMsg::m_fpFldMapInfo;
unsigned char** GfBdatMsg::m_fpFldLandmark;
unsigned char** GfBdatMsg::m_fpFldFieldSkill;
unsigned char** GfBdatMsg::m_fpItmCollection;
unsigned char** GfBdatMsg::m_fpItmCrystal;
unsigned char** GfBdatMsg::m_fpItmPrecious;
unsigned char** GfBdatMsg::m_fpItmInfo;
unsigned char** GfBdatMsg::m_fpItmEvent;
unsigned char** GfBdatMsg::m_fpItmPcWpn;
unsigned char** GfBdatMsg::m_fpItmPcWpnChip;
unsigned char** GfBdatMsg::m_fpItmPcWpnType;
unsigned char** GfBdatMsg::m_fpItmSalvage;
unsigned char** GfBdatMsg::m_fpItmTresure;
unsigned char** GfBdatMsg::m_fpItmFavorite;
unsigned char** GfBdatMsg::m_fpItmBooster;
unsigned char** GfBdatMsg::m_fpItmOrb;
unsigned char** GfBdatMsg::m_fpItmPcEquip;
unsigned char** GfBdatMsg::m_fpChrDr;
unsigned char** GfBdatMsg::m_fpChrBl;
unsigned char** GfBdatMsg::m_fpBtlClass;
unsigned char** GfBdatMsg::m_fpBlArtsMs;
unsigned char** GfBdatMsg::m_fpBlSpArtsMs;
unsigned char** GfBdatMsg::m_fpBlSkill;
unsigned char** GfBdatMsg::m_fpDrArtsMs;
unsigned char** GfBdatMsg::m_fpBtlEnhanceCap;
unsigned char** GfBdatMsg::m_fpFldQuestNormal;
unsigned char** GfBdatMsg::m_fpFldQuestMini;
unsigned char** GfBdatMsg::m_fpFldQuestBlade;
unsigned char** GfBdatMsg::m_fpFldQuestAchievement;
unsigned char** GfBdatMsg::m_fpFldQuestMercenaries;
unsigned char** GfBdatMsg::m_fpBtlBuffMs;
unsigned char** GfBdatMsg::m_fpBtlBuffCap;
unsigned char** GfBdatMsg::m_fpFldAchievement;
unsigned char** GfBdatMsg::m_fpBtlHanaRole;
unsigned char** GfBdatMsg::m_fpBtlHanaNArts;
unsigned char** GfBdatMsg::m_fpBtlHanaArts;
unsigned char** GfBdatMsg::m_fpBtlHanaAtr;
unsigned char** GfBdatMsg::m_fpBtlHanaAssist;
unsigned char** GfBdatMsg::m_fpBtlSkillDr;
unsigned char** GfBdatMsg::m_fpBtlEnGenus;

// a message file's block, released
#define DELETE_FP(fp) \
    if (fp != nullptr) { \
        delete fp; \
        fp = nullptr; \
    }

void GfBdatMsg::destroyFP() {
    DELETE_FP(m_fpBtlEnGenus);
    DELETE_FP(m_fpBldMerceName);
    DELETE_FP(m_fpBldBladeName);
    DELETE_FP(m_fpFldEnemyName);
    DELETE_FP(m_fpFldNpcName);
    DELETE_FP(m_fpFldQuest);
    DELETE_FP(m_fpFldMapInfo);
    DELETE_FP(m_fpFldLandmark);
    DELETE_FP(m_fpFldFieldSkill);
    DELETE_FP(m_fpFldAchievement);
    DELETE_FP(m_fpItmCollection);
    DELETE_FP(m_fpItmCrystal);
    DELETE_FP(m_fpItmPrecious);
    DELETE_FP(m_fpItmInfo);
    DELETE_FP(m_fpItmEvent);
    DELETE_FP(m_fpItmPcWpn);
    DELETE_FP(m_fpItmPcWpnChip);
    DELETE_FP(m_fpItmPcWpnType);
    DELETE_FP(m_fpItmSalvage);
    DELETE_FP(m_fpItmTresure);
    DELETE_FP(m_fpItmFavorite);
    DELETE_FP(m_fpItmBooster);
    DELETE_FP(m_fpItmOrb);
    DELETE_FP(m_fpItmPcEquip);
    DELETE_FP(m_fpChrDr);
    DELETE_FP(m_fpChrBl);
    DELETE_FP(m_fpBtlClass);
    DELETE_FP(m_fpBlArtsMs);
    DELETE_FP(m_fpBlSpArtsMs);
    DELETE_FP(m_fpBlSkill);
    DELETE_FP(m_fpDrArtsMs);
    DELETE_FP(m_fpBtlEnhanceCap);
    DELETE_FP(m_fpFldQuestNormal);
    DELETE_FP(m_fpFldQuestMini);
    DELETE_FP(m_fpFldQuestBlade);
    DELETE_FP(m_fpFldQuestAchievement);
    DELETE_FP(m_fpFldQuestMercenaries);
    DELETE_FP(m_fpBtlBuffMs);
    DELETE_FP(m_fpBtlBuffCap);
    DELETE_FP(m_fpBtlHanaRole);
    DELETE_FP(m_fpBtlHanaNArts);
    DELETE_FP(m_fpBtlHanaArts);
    DELETE_FP(m_fpBtlHanaAtr);
    DELETE_FP(m_fpBtlHanaAssist);
    DELETE_FP(m_fpBtlSkillDr);
}

// one message file's block, allocated where the statement is
#define NEW_FP(id) new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) unsigned char*(GfDataBdat::getFP(id))

void GfBdatMsg::createFP() {
#line 188
    m_fpBldBladeName = NEW_FP(0x18C);
    m_fpBldMerceName = NEW_FP(0x18D);
    m_fpFldEnemyName = NEW_FP(0x1AD);
    m_fpFldNpcName = NEW_FP(0x1B5);
    m_fpFldQuest = NEW_FP(0x1B6);
    m_fpFldMapInfo = NEW_FP(0x1B4);
    m_fpFldLandmark = NEW_FP(0x1B3);
    m_fpFldFieldSkill = NEW_FP(0x1AF);
    m_fpFldAchievement = NEW_FP(0x1AA);
    m_fpItmCollection = NEW_FP(0x1C6);
    m_fpItmCrystal = NEW_FP(0x1C7);
    m_fpItmPrecious = NEW_FP(0x1D0);
    m_fpItmInfo = NEW_FP(0x1CA);
    m_fpItmEvent = NEW_FP(0x1C8);
    m_fpItmPcWpn = NEW_FP(0x1CD);
    m_fpItmPcWpnChip = NEW_FP(0x1CE);
    m_fpItmPcWpnType = NEW_FP(0x1CF);
    m_fpItmSalvage = NEW_FP(0x1D1);
    m_fpItmTresure = NEW_FP(0x1D2);
    m_fpItmFavorite = NEW_FP(0x1C9);
    m_fpItmBooster = NEW_FP(0x1C5);
    m_fpItmOrb = NEW_FP(0x1CB);
    m_fpItmPcEquip = NEW_FP(0x1CC);
    m_fpChrDr = NEW_FP(0x1A8);
    m_fpChrBl = NEW_FP(0x1A7);
    m_fpBtlClass = NEW_FP(0x197);
    m_fpBlArtsMs = NEW_FP(0x18E);
    m_fpBlSpArtsMs = NEW_FP(0x18F);
    m_fpBlSkill = NEW_FP(0x19E);
    m_fpDrArtsMs = NEW_FP(0x190);
    m_fpBtlEnhanceCap = NEW_FP(0x19B);
    m_fpFldQuestNormal = NEW_FP(0x1B7);
    m_fpFldQuestMini = NEW_FP(0x1B8);
    m_fpFldQuestBlade = NEW_FP(0x1B9);
    m_fpFldQuestAchievement = NEW_FP(0x1BA);
    m_fpFldQuestMercenaries = NEW_FP(0x1BB);
    m_fpBtlBuffMs = NEW_FP(0x196);
    m_fpBtlBuffCap = NEW_FP(0x195);
    m_fpBtlHanaRole = NEW_FP(0x1A2);
    m_fpBtlHanaNArts = NEW_FP(0x1A3);
    m_fpBtlHanaArts = NEW_FP(0x1A6);
    m_fpBtlHanaAtr = NEW_FP(0x1A4);
    m_fpBtlHanaAssist = NEW_FP(0x1A5);
    m_fpBtlSkillDr = NEW_FP(0x19D);
    m_fpBtlEnGenus = NEW_FP(0x19A);
}

void GfBdatMsg::bdatRefresh() {
    destroyFP();
    createFP();
}

unsigned char* GfBdatMsg::getFpEnemy() {
    return *m_fpFldEnemyName;
}

unsigned char* GfBdatMsg::getFpMapInfo() {
    return *m_fpFldMapInfo;
}

unsigned char* GfBdatMsg::getFpCollection() {
    return *m_fpItmCollection;
}

unsigned char* GfBdatMsg::getFpCrystal() {
    return *m_fpItmCrystal;
}

unsigned char* GfBdatMsg::getFpPrecious() {
    return *m_fpItmPrecious;
}

unsigned char* GfBdatMsg::getFpInfo() {
    return *m_fpItmInfo;
}

unsigned char* GfBdatMsg::getFpEvent() {
    return *m_fpItmEvent;
}

unsigned char* GfBdatMsg::getFpPcWpn() {
    return *m_fpItmPcWpn;
}

unsigned char* GfBdatMsg::getFpPcWpnChip() {
    return *m_fpItmPcWpnChip;
}

unsigned char* GfBdatMsg::getFpPcWpnType() {
    return *m_fpItmPcWpnType;
}

unsigned char* GfBdatMsg::getFpSalvage() {
    return *m_fpItmSalvage;
}

unsigned char* GfBdatMsg::getFpTresure() {
    return *m_fpItmTresure;
}

unsigned char* GfBdatMsg::getFpBooster() {
    return *m_fpItmBooster;
}

unsigned char* GfBdatMsg::getFpFavorite() {
    return *m_fpItmFavorite;
}

unsigned char* GfBdatMsg::getFpOrb() {
    return *m_fpItmOrb;
}

unsigned char* GfBdatMsg::getFpPcEquip() {
    return *m_fpItmPcEquip;
}

unsigned char* GfBdatMsg::getFpCommonBladeName() {
    return *m_fpBldBladeName;
}

unsigned char* GfBdatMsg::getFpMerceName() {
    return *m_fpBldMerceName;
}

unsigned char* GfBdatMsg::getFpFieldSkill() {
    return *m_fpFldFieldSkill;
}

unsigned char* GfBdatMsg::getFpAchievement() {
    return *m_fpFldAchievement;
}

unsigned char* GfBdatMsg::getFpChrDr() {
    return *m_fpChrDr;
}

unsigned char* GfBdatMsg::getFpBtlClass() {
    return *m_fpBtlClass;
}

unsigned char* GfBdatMsg::getFpBlArtsMs() {
    return *m_fpBlArtsMs;
}

unsigned char* GfBdatMsg::getFpBlSpArtsMs() {
    return *m_fpBlSpArtsMs;
}

unsigned char* GfBdatMsg::getFpBlSkill() {
    return *m_fpBlSkill;
}

unsigned char* GfBdatMsg::getFpBtlEnhanceCap() {
    return *m_fpBtlEnhanceCap;
}

unsigned char* GfBdatMsg::getFpBlBuffMs() {
    return *m_fpBtlBuffMs;
}

unsigned char* GfBdatMsg::getFpBlBuffCap() {
    return *m_fpBtlBuffCap;
}

unsigned char* GfBdatMsg::getFpBtlHanaRole() {
    return *m_fpBtlHanaRole;
}

unsigned char* GfBdatMsg::getFpBtlHanaNArts() {
    return *m_fpBtlHanaNArts;
}

unsigned char* GfBdatMsg::getFpBtlHanaAtr() {
    return *m_fpBtlHanaAtr;
}

unsigned char* GfBdatMsg::getFpBtlSkillDr() {
    return *m_fpBtlSkillDr;
}

}  // namespace gf
