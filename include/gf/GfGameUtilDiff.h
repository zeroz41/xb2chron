#ifndef GF_GFGAMEUTILDIFF_H
#define GF_GFGAMEUTILDIFF_H

namespace gf { class SDataOption; enum GFDIFF : int; }

namespace gf {

// the game's difficulty helpers (functions; 2.0.0's symbols name the class)
class GfGameUtilDiff {
public:
    // 2.0.0's symbols name it. What they do: GfGameUtilDiff::getBtlDifficult: its byte 0x6F (as unsigned int);
    // GfGameUtilDiff::isEnableAutoSave: byte 0x82 is set; GfGameUtilDiff::isEnableSpecialBgm: byte 0x84 is 0;
    // GfGameUtilDiff::isEnableAutoBattle / GfGameUtilDiff::isEnableAutoButtonChallenge /
    // GfGameUtilDiff::isEnableEnemyAgg: byte 0x7F / 0x80 / 0x81 is set; GfGameUtilDiff::getBtlDifParam: passes value to
    // GfDataBtlDif::getBtlDifParam on the SSoundUiOption at +0x4C. GfGameManager's statics getBtlDifficult,
    // reqestEventAutoSave, isEnableSpecialBgm, isEnableAutoBattle/9A0/9A4 and getBtlDifParam call them.
    static unsigned int getBtlDifficult();
    static bool isEnableAutoSave();
    static void* getUseSoundUiOption();
    // the value (btl::BattleGlobal::SetupDifficultyData scales it)
    static unsigned int getBtlDifParam(unsigned int value);
    // 2.0.0's symbols name it. What it does: calls GfDataBtlDif::setOptionGameDifficult with type on the same
    // SSoundUiOption GfGameUtilDiff::getUseSoundUiOption returns (GfArenaBattle::execBattleSequence calls it).
    static void setOptionGameDifficult(GFDIFF type);
    static bool isEnableSpecialBgm();
    static bool isEnableAutoBattle();
    static bool isEnableAutoButtonChallenge();
    static bool isEnableEnemyAgg();
    // 2.0.0's symbols name it. What it does: whether byte 0x83 of the option data (as
    // GfGameUtilDiff::isEnableAutoBattle reads it) is set; GfMenuManager::gevPlayerControl tests it.
    static bool isEnableHitonowaSkip();
    // 2.0.0's symbols name it. What it does: calls GfDataBtlDif::setCustomFollow on the option's m_soundUi;
    // GfMenuObjOption::MainListener calls it on the option it saves.
    static void setCustomFollow(SDataOption& option);
};

}  // namespace gf

#endif
