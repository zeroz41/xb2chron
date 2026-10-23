#include "classes/btl/ButtonChallenge.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/gf/GfMenuObjButtonChallenge2.h"
#include "classes/btl/ButtonChallenge.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/TalkManager.h"
#include "classes/fw/PadManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjButtonChallenge2.h"

namespace btl {

ButtonChallenge::ButtonChallenge()
    : m_context(nullptr), m_prevContext(nullptr), m_nextId(1), m_id(0), m_slowId(0), m_successCount(0),
      m_isOpen(false), m_isDone(true), m_isSkipped(false), m_enemySuccess(false) {}

ButtonChallenge::~ButtonChallenge() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_prevContext != nullptr) {
        m_prevContext->release();
        m_prevContext = nullptr;
    }
}

void ButtonChallenge::fn_710001C6A8(const BUTTON_CHALLENGE_PARAM& param) {
    if (!BattleGlobal::sys()->fn_710000A724() || (param.m_kind != 0 && !BattleGlobal::sys()->fn_71000068F8())) {
        if (m_context != nullptr) {
            m_context->reset();
        } else {
            m_context = gf::GfMenuCallContext::create();
        }
        if (param.m_menuType == 0xF9) {
            gf::GfMenuObjButtonChallenge2::openSequence(m_context, param.m_menuId, false, true);
        } else {
            gf::GfMenuObjButtonChallenge2::open(m_context, param.m_menuId, false, true);
        }
    } else {
        if (m_context != nullptr) {
            m_context->release();
            m_context = nullptr;
        }
        m_isSkipped = true;
    }
    m_isOpen = true;
    m_isDone = false;
}

int ButtonChallenge::Start(const BUTTON_CHALLENGE_PARAM& param) {
    if (m_isOpen) {
        if (param.m_priority < m_param.m_priority) {
            return 0;
        }
        if (!m_isDone && m_param.m_kind == 0) {
            fn_710001C990(3, false);
        }
        CancelProc();
    } else if (m_id != 0) {
        CancelProc();
    }
    m_param = param;
    fn_710001C6A8(param);
    if (m_slowId != 0) {
        BattleGlobal::sys()->DeleteSlow(m_slowId);
        m_slowId = 0;
    }
    BattleGlobal::sys()->SetPause(4, false);
    if (param.m_kind == 2) {
        BattleGlobal::sys()->SetPause(4, true);
    }
    int id = m_nextId;
    m_nextId = id == -1 ? 1 : id + 1;
    m_id = id;
    return id;
}

void ButtonChallenge::Cancel(unsigned int id) {
    if (m_id == id && !m_isDone) {
        CancelProc();
    }
}

void ButtonChallenge::ProgressSeparately() {
    if (m_context != nullptr) {
        gf::GfMenuObjButtonChallenge2::resume(m_context);
    }
}

bool ButtonChallenge::IsProc() const {
    return m_isOpen || m_param.m_kind != 4;
}

void ButtonChallenge::fn_710001D2F0(unsigned int id) {
    if (m_id == id && m_isSkipped && !m_isDone) {
        fn_710001C990(2, false);
        m_isOpen = false;
        m_isSkipped = false;
        if (m_context != nullptr) {
            m_context->release();
            m_context = nullptr;
        }
        m_param = BUTTON_CHALLENGE_PARAM();
        m_id = 0;
        if (m_slowId != 0) {
            BattleGlobal::sys()->DeleteSlow(m_slowId);
            m_slowId = 0;
        }
        BattleGlobal::sys()->SetPause(4, false);
    }
}

bool ButtonChallenge::IsEnemyChallengeSuccess() {
    bool success = m_enemySuccess;
    m_enemySuccess = false;
    return success;
}

}  // namespace btl
