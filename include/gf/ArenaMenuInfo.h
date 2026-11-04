#ifndef GF_ARENAMENUINFO_H
#define GF_ARENAMENUINFO_H

#include "gf/ArenaChanged.h"
#include "gf/ChBtlInfo.h"

namespace gf {

// 2.0.0's symbols name it (GfGameManager::getBattleArenaMenuInfo, GfGameArena::getMenuInfo, GfArenaUtil's
// setupMenuInfoFor* take one); the field names are not the original's. One battle challenge's data
// (GfArenaUtil::setupMenuInfoForChBtl clears it the way the constructor does, then fills it from GfBdatBtl's row).
// GfMenuBattleAdapter's callbacks read its short at 0x1C, ints at 0x28/0x2C and floats at 0xAD0; gf_menu_obj_btl_time
// reads m_kind; gf_menu_btlch_adapter's callbacks (GfMenuBtlchAdapter) read most of the rest. 0xAF0 bytes: the
// 0xAF0-byte frames of those callbacks hold one.
struct ArenaMenuInfo {
    ArenaMenuInfo() {
        clear();
        m_ratios[0] = 0.0f;
        m_ratios[1] = 0.0f;
        m_ratios[2] = 0.0f;
        m_rule = ChBtlInfo::ChBtlDiff();
        m_valueAE8 = 1;
        m_flagAEC = false;
    }
    // what the constructor and GfArenaUtil::setupMenuInfoForChBtl zero first
    void clear() {
        m_id = 0;
        m_value4 = 0;
        m_kind = 0;
        m_value8 = 0;
        m_valueA = 0;
        m_valueC = 0;
        m_valueE = 0;
        m_value10 = 0;
        m_flag12 = false;
        m_text14.m_message = 0;
        m_flag1A = false;
        m_value1C = 0;
        m_values1E[0] = 0;
        m_values1E[1] = 0;
        m_values1E[2] = 0;
        m_value24 = 0;
        m_value28 = 0;
        m_value2C = 0;
        m_value30 = 0;
    }
    unsigned int m_id;
    unsigned short m_value4;  // seconds
    unsigned short m_kind;  // gf_menu_obj_btl_time's openFromChallengeBattle opens LAY_score with 0 for 1, with 1 for 3
    unsigned short m_value8;
    unsigned short m_valueA;
    unsigned short m_valueC;
    unsigned short m_valueE;
    unsigned short m_value10;  // with m_flag12: 0x10..0x1B hold three {message, flag} pairs
    bool m_flag12;
    unsigned char pad_13[0x1];
    // a message of GfDataBdat 0x1A1 and its flag (the names are not the original's)
    struct Text {
        unsigned short m_message;
        unsigned char m_flag;
    };
    Text m_text14;  // the constructor sets only the message
    Text getText14() const { return m_text14; }
    unsigned short m_value18;  // not set by the constructor
    bool m_flag1A;
    unsigned char pad_1B[0x1];
    unsigned short m_value1C;
    unsigned short m_values1E[3];
    unsigned int m_value24;
    unsigned int m_value28;
    unsigned int m_value2C;
    unsigned int m_value30;  // seconds
    unsigned char pad_34[0x4];
    ArenaChanged m_lists;
    float m_ratios[3];
    ChBtlInfo::ChBtlDiff m_rule;
    ChBtlInfo::ChBtlDiff getRule() const { return m_rule; }
    int m_valueAE8;
    bool m_flagAEC;
};

}  // namespace gf

#endif
