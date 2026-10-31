#include "btl/challenge_battle_manager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/GfReqSmallCom.h"
#include "btl/challenge_battle_manager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfReqSmallCom.h"
#include "plugin/Bdat.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"

namespace btl {

void fn_71000254E4() {
#line 98
    new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B3A9C8;
}

void fn_7100025588() {
    delete TUnk_B3A9C8::get();
}

bool TUnk_B3A9C8::fn_710002567C() const {
    return pad_26 != 0;
}

void TUnk_B3A9C8::fn_710002575C() {
    TalkManager::get()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(0x30), 0, 0);
    pad_1c = 2.75f;
}

void fn_7100025908(const fw::UpdateInfo& info) {
    TUnk_B3A9C8::get()->fn_7100025920(info);
}

bool TUnk_B3A9C8::fn_7100026A48() const {
    return pad_26 > 149;
}

bool TUnk_B3A9C8::fn_7100026A58() const {
    return pad_26 > 199;
}

void TUnk_B3A9C8::fn_7100026C18(unsigned short value) {
    if (pad_26 != 0) {
        pad_24 = value;
    }
}

void TUnk_B3A9C8::fn_7100026CF0(int value) {
    if (value != 0 && pad_26 != 0) {
        gf::fn_7100558BAC(value);
    }
}

float fn_7100026D08() {
    return BattleGlobal::get()->pad_5c50;
}

float TUnk_B3A9C8::fn_7100026D20(bool* flag) const {
    if (pad_26 != 160) {
        *flag = false;
        return -1.0f;
    }
    float limit = BtlSystemBalanceAccess::get()->pad_120;
    float rest = limit - pad_18;
    bool low;
    if (rest <= 0.0f) {
        rest = 0.0f;
        low = true;
    } else if (rest >= limit) {
        rest = limit;
        low = false;
    } else {
        low = rest / limit < 0.3f;
    }
    *flag = rest <= 5.0f || low;
    return rest;
}

bool TUnk_B3A9C8::fn_7100026DAC() const {
    if (pad_26 == 201 && gf::GfGameManager::isFadeout()) {
        return true;
    }
    return false;
}

bool TUnk_B3A9C8::fn_7100026DDC() const {
    return pad_26 >= 100 && pad_26 < 150;
}

bool TUnk_B3A9C8::fn_7100026DF0() const {
    if (pad_26 == 0) {
        return false;
    }
    if (pad_29 == 3) {
        return !CharacterManager::get()->IsExistBattleEnemy(nullptr, reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1), false);
    }
    return fn_7100026DDC();
}

bool TUnk_B3A9C8::fn_7100026E4C() const {
    return pad_26 >= 157 && pad_26 < 162;
}

bool TUnk_B3A9C8::fn_7100026E64() const {
    if (pad_26 == 0) {
        return true;
    }
    return pad_2b != 0;
}

bool TUnk_B3A9C8::fn_7100026EB0() const {
    if (pad_26 == 0) {
        return true;
    }
    return pad_29 == 3;
}

bool TUnk_B3A9C8::fn_7100026ED0() const {
    return gf::GfGameManager::fn_71002AC5D8()->m_value4 - pad_10 <= 300.0f;
}

}  // namespace btl
