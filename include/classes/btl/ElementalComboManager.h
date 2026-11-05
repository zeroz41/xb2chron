#ifndef CLASSES_BTL_ELEMENTALCOMBOMANAGER_H
#define CLASSES_BTL_ELEMENTALCOMBOMANAGER_H

#include <stddef.h>
#include <string.h>
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace btl { class BattleCharacter; }

namespace btl {
// table 0x7100B3BAD8
class ElementalComboManager {
public:
    // one per element (ResetElement, UpdateElement; 1.0.0 names the type)
    struct ELEMENTAL_DATA {
        ELEMENTAL_DATA()
            : m_value(0.0f), m_ratio(0.0f), pad_8(0), m_state(0), pad_10(0), pad_14(), pad_b4(0), pad_b8(0xFF),
              pad_b9(0), pad_ba(3), m_element(0) {}
        // ResetElement's loop: the element's own index is set last, as part of the clear (the base register its
        // inlined copy keeps shows the store is the clear's own)
        void Clear(int element) {
            pad_b4 = 0;
            m_value = 0.0f;
            m_ratio = 0.0f;
            pad_8 = 0;
            m_state = 0;
            pad_b8 = 0xFF;
            pad_b9 = 0;
            pad_ba = 3;
            memset(pad_14, 0, sizeof(pad_14));
            m_element = element;
        }
        // GetElementalValue answers it, SetElementalValue caps it at the manager's m_valueMax (1.0.0; the name is
        // not the original's)
        float m_value;
        // m_value over m_valueMax: IsFullElementalValue tests it for 1 (the name is not the original's)
        float m_ratio;
        unsigned int pad_8;
        // IsDirecting (1.0.0) tests it for 3 and up (the name is not the original's)
        int m_state;
        unsigned int pad_10;  // the constructor clears it, ResetElement does not
        // Burst adds an id to the first 20 when they lack it (meaning unknown)
        int pad_14[40];
        unsigned int pad_b4;
        unsigned char pad_b8;
        unsigned char pad_b9;
        unsigned char pad_ba;
        // the element's index, set by ResetElement (the name is not the original's)
        unsigned char m_element;
    };

    // one per combo stage (ElementalComboDamage, CalcRestTimeRatio; 1.0.0 names the type)
    struct ELEMENTAL_COMBO_DATA {
        ELEMENTAL_COMBO_DATA()
            : pad_0(0), pad_4(0), pad_8(0), m_time(0.0f), m_restTime(0.0f), pad_14(0.0f), pad_18(0), pad_1c(0.0f),
              pad_20(0.0f), pad_24(1.0f), pad_28(0), pad_2c(0), pad_70(0), m_restTimeSpeed(2000), m_comboID(0),
              m_source{0, 0xFF}, pad_79(0), pad_7a(), pad_86(0), pad_88_0(0), pad_88_1(0) {}
        void Clear() {
            // the fields up to pad_24 as one block (the original's store order follows a memset)
            memset(this, 0, offsetof(ELEMENTAL_COMBO_DATA, pad_24));
            pad_24 = 1.0f;
            pad_28 = 0;
            pad_2c = 0;
            pad_70 = 0;
            m_restTimeSpeed = 2000;
            m_comboID = 0;
            Source source = {0, 0xFF};
            m_source = source;
            pad_79 = 0;
            pad_86 = 0;
            pad_88_0 = 0;
            pad_88_1 = 0;
            pad_7a = CharaBits();
        }
        unsigned int pad_0;
        unsigned int pad_4;
        unsigned int pad_8;
        // CalcRestTimeRatio (1.0.0) answers m_restTime over m_time (the names are not the original's)
        float m_time;
        float m_restTime;
        float pad_14;  // GetRestTimeRatio answers it while pad_88_0 is set
        unsigned int pad_18;
        // Rub: the combo's "DD" and "Dot" (player: "DDEn", "DotEn") of BDAT 0x23 in hundredths (meaning unknown)
        float pad_1c;
        float pad_20;
        float pad_24;
        unsigned int pad_28;
        unsigned int pad_2c;
        unsigned char pad_30[0x40];
        unsigned int pad_70;
        // the rest time's speed in 2000ths (SetRestTimeSpeed, MulRestTimeSpeed; the name is not the original's)
        unsigned short m_restTimeSpeed;
        // non-zero while the stage runs (GetElementalComboID answers it; the name is not the original's)
        unsigned char m_comboID;
        // its own type: Clear stores both as one 16-bit constant from a local (the names are not the original's)
        struct Source {
            unsigned char rimBloomID;  // Rub hands it to BattleCharacter::SetRimBloom
            // the character the stage came from, 0xFF for none (Rub sets the other manager's m_charaID; Update hands
            // it to CharacterParameter::SetElementalComboID)
            unsigned char charaID;
        };
        Source m_source;
        unsigned char pad_79;
        // a bit per character index (Rub sets its character's; meaning unknown). Its own type: Clear zeroes the 12
        // bytes as one 8-byte and one 4-byte store apart from its neighbours (a memset merges them)
        struct CharaBits {  // the name is not the original's
            unsigned char bits[0xC];
        };
        CharaBits pad_7a;
        unsigned short pad_86;
        unsigned char pad_88_0 : 1;
        unsigned char pad_88_1 : 1;
    };

    // one per element (CreateBallEffect, MoveBallEffect, DeleteBallEffect; the name is not the original's)
    struct BALL_DATA {
        BALL_DATA() : m_effect(0) {}
        // where the ball is (CreateBreakEffect places its effect there; the name is not the original's)
        mm::Vec3 m_pos;
        unsigned char pad_10[0x24];
        // the fw::EffectManager combo ball (DeleteBallEffect destroys it; the name is not the original's)
        unsigned int m_effect;
        unsigned int m_element : 31;  // the name is not the original's
        unsigned int pad_38_31 : 1;
        unsigned char pad_3c[0x4];
    };

    ElementalComboManager();
    virtual ~ElementalComboManager();  // slot 0
    void Reset(bool once);
    void DeleteBallEffect(int element);
    void Initialize(gf::GF_OBJ_HANDLE* handle);
    void CheckCharacterID();
    void ResetElement(int element);
    void ResetElementalComboData();
    void Rub(const ElementalComboManager& other, float rate);
    int GetResistantAttrBreakDamage(int attr) const;
    void ResistantAttrBreakDamage(int attr, BattleCharacter* chr, bool flag);
    unsigned char GetResistantAttrBreakTotalDamage(int attr) const;
    void AddElement(int, int, int, unsigned int, int);
    bool IsEnableElementalCombo(int, int, bool, bool) const;
    void Burst(int, int, unsigned int, bool);
    int GetNextElementalComboID(int, bool, bool) const;
    bool IsFullElementalValue(int element) const;
    bool IsDirecting(int element) const;
    bool IsEnableStartElementalCombo() const;
    unsigned int GetElementalComboID(bool check) const;
    void CreateBallEffect(int element);
    void MoveBallEffect(int element, float);
    void CreateBreakEffect(int element);
    void Update(float);
    void UpdateElement(ELEMENTAL_DATA& data, float);
    void UpdateElementalComboEffect(float);
    void ElementalEffectProc();
    void ElementalComboDamage(ELEMENTAL_COMBO_DATA& data, float, float, int, bool, bool);
    float CalcRestTimeRatio(const ELEMENTAL_COMBO_DATA& data) const;
    void SetElementalValue(int element, float value);
    float GetElementalValue(int element) const;
    void SetRestTimeSpeed(float speed);
    // 2.0.0's symbols name it. What it does: answers pad_aaf[stage - 1] for a stage up to m_comboStage, 0 above it.
    unsigned char GetStageElementalComboID(int stage) const;
    void MulRestTimeSpeed(float rate);
    float GetRestTimeRatio(bool& fixed) const;
    void ApplyElementalComboBonus(int, int, int);

    gf::GF_OBJ_HANDLE* m_handle;  // Initialize stores it (the name is not the original's)
    // the character's index CharacterManager::GetCharacterConst takes (CheckCharacterID; the name is not the
    // original's)
    int m_charaID;
    // CheckCharacterID's clamped rate from the character's parameter (meaning unknown)
    float pad_14;
    // IsEnableStartElementalCombo holds while it is 0 or less (meaning unknown)
    float pad_18;
    ELEMENTAL_DATA m_elements[9];       // the name is not the original's
    ELEMENTAL_COMBO_DATA m_combos[3];   // the name is not the original's
    unsigned char pad_85c[0x4];
    BALL_DATA m_balls[9];               // the name is not the original's
    // counts down 0x8888 per Update; at the end Update hands DataManager::SetElementalEffect the entry pad_aa0_28
    // picks (meaning unknown)
    // its own 32-bit unit (Update loads and stores the word)
    struct {
        unsigned int pad_aa0 : 28;
        unsigned int pad_aa0_28 : 4;
    };
    // the running combo stage, 0 for none (GetElementalComboID, GetRestTimeRatio; the name is not the original's)
    unsigned char m_comboStage : 4;
    unsigned char pad_aa4_4 : 4;
    // the elemental value cap (CheckCharacterID, SetElementalValue; the name is not the original's)
    unsigned char m_valueMax;
    // GetElementalComboID answers it while set (meaning unknown)
    unsigned char pad_aa6;
    // GetResistantAttrBreakTotalDamage answers an entry per attribute 1-8 (the name is not the original's)
    unsigned char m_resistantAttrBreakTotalDamage[8];
    unsigned char pad_aaf[3];  // GetStageElementalComboID answers an entry per stage
    // a player character's manager (CheckCharacterID; the name is not the original's)
    unsigned char m_isPlayer : 1;
    // Reset(true) runs once until it is cleared (the name is not the original's)
    unsigned char m_isReset : 1;
    unsigned char pad_ab2_2 : 1;
    unsigned char pad_ab2_3 : 5;
    unsigned char pad_ab3[0x5];
};
}  // namespace btl

#endif
