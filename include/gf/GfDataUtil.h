#ifndef GF_GFDATAUTIL_H
#define GF_GFDATAUTIL_H

namespace gf {
class SDataGame;
class DataParamAcc;
// a kind of move (only its symbols' spelling is known: the functions taking it tell 0 and 1 apart)
enum AMOVE : int;
// the game data's helpers (functions, by its symbols)
class GfDataUtil {
public:
    static unsigned int getMoney();  // unsigned: canBuyItem and canSellItem compare it unsigned
    static int getObjTypeByCharaId(unsigned int chara);  // the object type of a character
    static void setScenarioFlag(unsigned short flag);
    static void setRandomInn();  // picks one of 16 inns at random (the comment is not the original's)
    static void setMoney(unsigned int value);
    static unsigned int getEventChapterSave();
    // GfPlayComMenuChapterSave::start passes its id and GfDataUtil::getScenarioFlag()
    static void setChapterSave(unsigned int id, unsigned short value);
    static unsigned int getSkipTravelID();
    static float getPlayerCameraDistance();
    static void setPlayerCameraDistance(float value);
    static unsigned int getCoin();
    static void setCoin(unsigned int value);
    static float getCameraHeight();
    static void setCameraHeight(float value);
    static float getCameraYaw();
    static void setCameraYaw(float value);
    static float getCameraPitch();
    static void setCameraPitch(float value);
    static bool isCameraFreeMode();
    static void setCameraFreeMode(bool value);
    static unsigned int getAutoEventAfterLoad();
    static bool isCollectFlagNewVersion();
    static unsigned char getCameraSide();
    static void setCameraSide(unsigned char value);
    static void convertNewCollectFlagPatch();
    static const char* getAttributeFileName(unsigned int attribute);
    static float getMoveDistance(AMOVE move);
    static void setMoveDistance(AMOVE move, float distance);
    // 2.0.0's symbols name it. What it does: whether getDataGame()'s m_chapterSaveValue (+0x26) equals
    // GfDataUtil::getScenarioFlag and m_eventChapterSave (+0x28) is not 0.
    static bool isStartChapterSave();
    // 2.0.0's symbols name it. What it does: GfGameFlag::getLocal of the game data's flags (GfDataManager::getDataGame
    // + 0xFBBC4), width 16, index 1; GfMenuObjUtil::isCustomEnableBlade compares it with 2000.
    static unsigned short getScenarioFlag();
    // 2.0.0's symbols name it. What it does: local flag 1 (type 16) of game's GameFlag (+0xFBBC4).
    static unsigned short getScenarioFlag(const SDataGame& game);
    // 2.0.0's symbols name it. What it does: GfDataUtil::isClearGame's test on GfDataManager::getDataGame()'s flags;
    // GfGameManager:: isClearGame tail-calls it.
    static bool isClearGame();
    // 2.0.0's symbols name it. What it does: true when local flag 0xBDCD (type 1) of game's flags (+0xFBBC4) is set,
    // else whether flag 0xD880 is; GfGameManager::isClearGame passes the title's save buffer's game data.
    static bool isClearGame(const SDataGame& game);
    // 2.0.0's symbols name it. What it does: sets local game flag 0xBDCD (width 1) of the game data's GameFlag (game +
    // 0xFBBC4) to flag; GfGameUtil::incGameClearCount passes getDataGame() and true.
    static void setClearGame(SDataGame& game, bool flag);
    // 2.0.0's symbols name it. What it does: true when local flag 0xD793 (type 1) of game's GameFlag is set, else
    // whether flag 0xD882 is.
    static bool isClearTwiceGame(const SDataGame& game);
    // 2.0.0's symbols name it. What it does: GfDataUtil::isClearGameCheck's test on GfDataManager::getDataGame()'s
    // flags.
    static bool isClearGameCheck();
    // 2.0.0's symbols name it. What it does: true when local flag 0xD77E (type 1) of game's GameFlag is set, else
    // whether flag 0xD87E is.
    static bool isClearGameCheck(const SDataGame& game);
    // 2.0.0's symbols name it. What it does: sets local flags 0xD77E and 0xD87E (type 1) to flag (the two
    // GfDataUtil::isClearGameCheck tests).
    static void setClearGameCheck(bool flag);
    // 2.0.0's symbols name it. What it does: whether GfDataUtil::getScenarioFlag (local flag 1, type 16) is above
    // 0xBE7.
    static bool isVandammeDead();
    // 2.0.0's symbols name it. What it does: whether local flag 0xD791 (type 1) of game's GameFlag is set.
    static bool isAdvanceSaved(const SDataGame& game);
    // 2.0.0's symbols name it. What it does: sets local flag 0xD791 (type 1) of game's GameFlag to flag
    // (GfDataUtil::isAdvanceSaved reads it).
    static void setAdvanceSaved(SDataGame& game, bool flag);
    // 2.0.0's symbols name it. What it does: whether local flag 0xD795 (type 1) of GfDataManager::getDataGame()'s
    // GameFlag is set.
    static bool isAdvanceContinue();
    // 2.0.0's symbols name it. What it does: sets local flag 0xD795 (type 1) of game's GameFlag to flag
    // (GfDataUtil::isAdvanceContinue reads it).
    static void setAdvanceContinue(SDataGame& game, bool flag);
    // 2.0.0's symbols name it. What it does: whether local flag 0xD860 (type 1) of GfDataManager::getDataGame()'s
    // GameFlag is set (GfDataUtil::setIra sets it).
    static bool isIra();
    // 2.0.0's symbols name it. What it does: sets local game flag 0xD860 (width 1) of game's GameFlag (+0xFBBC4) to
    // flag; GfGameAoc::setupGame passes getDataGame() and (mode == 1).
    static void setIra(SDataGame& game, bool flag);
    // 2.0.0's symbols name it. What it does: stores GfDataAoc::getContentVersion(n) + 1 into the game's
    // SDataGame::m_aocIds[n] for n 0 to 4 (GfGameUtilSaveData::setupGameSaveData calls it).
    static void saveAocVersion(SDataGame& game);
    // 2.0.0's symbols name it. What it does: true when GfDataAoc::getContentVersion(n) is below the game's m_aocIds[n]
    // minus 1, for any n of 1 to 4 (title_main's TitleMain::isValidAocVersion calls it on the save buffer's game).
    static bool isInvalidVersionAoc(const SDataGame& game);
    // 2.0.0's symbols name it. What it does: returns entry index of a 9-entry unsigned int table in the unit's .rodata
    // ({300, 4, 3, 1, 2, 0, 0, 0, 0}, no bounds check); GfObjFactory::createComponent and GfObjUtil::replaceColisionPrio call it.
    static unsigned int getPlayerColiPriority(unsigned int index);
    // 2.0.0's symbols name it. What it does: true for the enemy of BDAT ID 0x3F1 (object type 4) or the blade of BDAT
    // ID 0x18 (object type 3), read through acc; SCOM_OBJ_VFADE's constructor then uses effect 16.
    static bool isEffectKagutsuchi(const DataParamAcc& acc);
    // GfBdatBtl::getGrowLevelExp2(id) while GfDataUtil::isIra's flag (1, 0xD860) is set, else getGrowLevelExp(id)
    static unsigned int getGrowLevelExp(unsigned int id);
    // 2.0.0's symbols name it. What it does: true when local flag 0xD788 (type 1) is set, else when the pointer at
    // 0x7100C294C0 is set and gf::GfDataAoc::getContentVersion(3) is above 0 (GfGameManager::isEnableNamedRecord).
    static bool isVersion150();
    // the symbols name them: refreshBdatParam re-runs GfDataBlade::setupSDataBlade on every listed blade and
    // GfDataDriver::calcDriverBaseParamByLevel on drivers 1-25
    static void refreshBdatParam();
    static void refreshBladeSaveData();
    static void setupUi1868ForSDataGame(SDataGame& game);
};
}  // namespace gf

#endif
