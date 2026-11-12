#ifndef GF_GFGAMEUTILQUESTARTS_H
#define GF_GFGAMEUTILQUESTARTS_H


namespace gf {

// the quest arts helpers (functions; 2.0.0's symbols name the class)
class GfGameUtilQuestArts {
public:
    // 2.0.0's symbols name it. What it does: for each of the 8 rows of GfWeapon.cpp's s_questArtsRows (lbl_71009BBDC4)
    // whose arts match the blade's (DataParamAcc(3, blade) getBladeArts(slot)) at a high enough getBladeArtsLevel (and
    // whose quest, if any, is ordered), raises local flag 8 (row + 0xF9E) by one while below the row's count and sets
    // the row's local flag 1 once the count is reached. Caller:
    // SCOM_ACHIEV_INC::createBladeArts with the blade's bdat id and the arts slot (0..2).
    static void calcQuestArtsCount(unsigned int blade, unsigned int slot);
};

}  // namespace gf

#endif
