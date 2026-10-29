#ifndef GF_SDATAGAME_H
#define GF_SDATAGAME_H

#include "classes/gf/GfFieldTime.h"
#include "classes/gf/TUnk_B535D0.h"
#include "gf/GameFlag.h"
#include "gf/SDataBlade.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataParty.h"
#include "gf/QuestID.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Vec3.h"

namespace gf {
// one of the game data's task achievements: 12 bytes (fn_71002E9D10 steps them by 12); the fields are not known
// (the type name is not the original's)
struct TaskAchieve {
    unsigned char pad_0[0xC];
};

// the game's data, as GfDataManager::getDataGame hands it out (1.0.0's GfGameUtil::setupNewGameParam takes one;
// that getDataGame's is one is inferred)
// a saved event row of the game data, 0x64 bytes (GfDataEvent::isSavedEvent; the names are not the original's)
struct SDataGameSavedEvent {
    unsigned short m_event;
    unsigned char pad_2[0x62];
};

class SDataGame {
public:
    unsigned int m_money;  // 0x0 (named after its accessors; the name is not the original's)
    // 0x4-0x24: the landmark point, its position and Y rotation (1.0.0's GfFieldManager::setLandmarkPoint stores them,
    // getLandmarkPoint/Pos/RotY read them; the names are not the original's)
    unsigned int m_landmarkPoint;
    unsigned char pad_8[0x8];
    mm::Vec3 m_landmarkPos;
    float m_landmarkRotY;
    // 0x24: GfFieldTime::setupGame stops the time of day when it is not 0 (the name is not the original's)
    unsigned short m_timeStop;
    // 0x26: GfDataUtil::setChapterSave's second argument (stored before m_eventChapterSave, its first; the name
    // is not the original's)
    unsigned short m_chapterSaveValue;
    unsigned short m_eventChapterSave;  // 0x28 (named after its accessors; the name is not the original's)
    unsigned char pad_2A[0x2];
    // by GfDataDriver::getSDataDriver (rows 1-16; the name is not the original's)
    SDataDriver m_drivers[16];
    // by GfDataBlade::getBladeIndex (the name is not the original's; the count is the indexes it hands out)
    SDataBlade m_blades[422];
    SDataParty m_party;  // 0xE9884: GfDataParty::getSDataParty (the name is not the original's)
    unsigned char pad_E98D4[0x4];  // (m_party is 0x50 bytes: m_leader aligns it to 4)
    // 0xE98D8: GfDataItem::getFavoriteItemType returns it; GfItemBox::fn_71002FA0F4 keeps it at +0x308 and clears its
    // 0x122EC bytes (named after its accessor; the type and name are not the original's)
    unsigned char m_favoriteItemType[0x122EC];
    GameFlag m_gameFlag;  // GfGameFlag's (the name is not the original's)
    QuestID m_scenario;  // 0x1097E4 (setScenario stores its halves one by one) (named after its accessors; the name is not the original's)
    QuestID m_select;  // 0x1097E8 (setSelect stores its halves one by one) (named after its accessors; the name is not the original's)
    unsigned char pad_1097EC[0x4];
    // 0x1097F0-0x1098B0: the saved positions and rotations, three each (GfDataParty::getSavePos/getSaveRot pick the
    // first array of each for a true flag, the second for false; the names are not the original's)
    mm::Vec3 m_savePos[3];
    mm::Vec3 m_savePos2[3];
    mm::Vec3 m_saveRot[3];
    mm::Vec3 m_saveRot2[3];
    unsigned int m_skipTravelID;  // 0x1098B0 (named after its accessors; the name is not the original's)
    unsigned char pad_1098B4[0xC];
    // 0x1098C0: the time of day (GfFieldTime::clear stores it, setupGame reads it; the name is not the original's)
    GameTime m_gameTime;
    // 0x1098C4: the play time (GfFieldTime::setupGame reads it; the name is not the original's)
    ElapseTime m_playTime;
    // 0x1098C8: the mercenary teams (GfDataMercenaries' team functions search them; getTeamByIndex asserts in
    // fixed_vector.h's operator[]; the capacity is the room before the count at 0x109940; the name is not the original's)
    mm::mtl::FixedVector<GfDataMercenaries::Team, 3> m_teams;
    // 0x109948: the mercenary team presets (GfDataMercenaries::getPreset; the count is the room up to
    // m_playerCameraDistance; the name is not the original's)
    GfDataMercenaries::Preset m_mercenaryPresets[40];
    float m_playerCameraDistance;  // 0x109B28 (named after its accessors; the name is not the original's)
    // 0x109B2C: how many times the game was cleared (GfGameUtil::incGameClearCount counts it up to 9999; the name is
    // not the original's)
    unsigned int m_gameClearCount;
    // 0x109B30: the task achievements (GfDataQuest::getTaskAchieve returns them; fn_71002E9D10 copies them, its end
    // is begin + count * 12; the count sits at 0x10A130, room for 128; ~SDataSave clears it after none other than
    // m_teams; the name is not the original's)
    mm::mtl::FixedVector<TaskAchieve, 128> m_taskAchieve;
    unsigned char pad_10A138[0xC04];
    unsigned int m_ether;  // 0x10AD3C (named after its accessors; the name is not the original's)
    // 0x10AD40: GfDataUtil::getMoveDistance/setMoveDistance, [0] for AMOVE 0, [1] for 1 (the name is not the
    // original's)
    float m_moveDistance[2];
    unsigned int m_assurePoint;  // 0x10AD48 (named after its accessors; the name is not the original's)
    unsigned int m_assureCount;  // 0x10AD4C (named after its accessors; the name is not the original's)
    unsigned short m_rareBladeAppearType;  // 0x10AD50 (named after its accessors; the name is not the original's)
    unsigned char pad_10AD52[0x2];
    unsigned int m_coin;  // 0x10AD54 (named after its accessors; the name is not the original's)
    // 0x10AD58: saved enemy HP (GfDataEnemy::getSavedHp reads [type - 4], setSavedHp writes [type - 1]; the name is
    // not the original's)
    unsigned int m_enemySavedHp[6];
    float m_cameraHeight;  // 0x10AD70 (named after its accessors; the name is not the original's)
    unsigned char pad_10AD74[0x100];
    float m_cameraYaw;  // 0x10AE74 (named after its accessors; the name is not the original's)
    float m_cameraPitch;  // 0x10AE78 (named after its accessors; the name is not the original's)
    unsigned char m_cameraFreeMode;  // 0x10AE7C (named after its accessors; the name is not the original's)
    unsigned char m_hikariCurrent;  // 0x10AE7D (named after its accessors; the name is not the original's)
    unsigned short m_autoEventAfterLoad;  // 0x10AE7E (named after its accessors; the name is not the original's)
    unsigned char m_collectFlagNewVersion;  // 0x10AE80 (named after its accessors; the name is not the original's)
    unsigned char pad_10AE81[0x1];
    unsigned char m_cameraSide;  // 0x10AE82 (named after its accessors; the name is not the original's)
    // to 0x126D80: SDataGame::SDataGame's last store (a 0x8000-byte clear at 0x11ED80); GfDataStore keeps its
    // SDataOption right after its SDataGame (0x20 + 0x126D80 = getDataOption's 0x126DA0)
    unsigned char pad_10AE83[0x1];
    // 0x10AE84: the saved events and (0x1171D4) their count (GfDataEvent::isSavedEvent searches the first count rows'
    // event ids; the names are not the original's)
    SDataGameSavedEvent m_savedEvents[500];
    unsigned int m_savedEventCount;
    unsigned char pad_1171D8[0x36F4];
    // 0x11A8CC: the challenge battle rule table (TUnk_B535D0::fn_7100291CF4 returns it, fn_7100291D14 a rule of
    // it, fn_7100291CC0 / fn_7100291E40 read and mark its rows; the constructor runs its fn_71001528A0; the name is
    // not the original's)
    TUnk_B535D0::RuleTable m_ruleTable;
    unsigned char pad_11B4CC[0x1770];
    // 0x11CC3C: the count GfDataBlade::fn_7100234998 raises for enemies (arrange ids) 1500 and up, at [enemy - 1500]
    // (below 1500 the count is a 16-bit local flag; GfGameUtil::incEnemySuppress reads it through fn_7100234940). The
    // name is not the original's.
    unsigned short m_enemySuppressCount[800];
    // 0x11D27C: GfDataItem::getItemBox returns it; GfItemBox::fn_71002FA0F4 keeps it at +0x310 and clears its 0x1B04
    // bytes (named after its accessor; the type and name are not the original's)
    unsigned char m_itemBox[0x1B04];
    unsigned char pad_11ED80[0x8000];
};
}  // namespace gf

#endif
