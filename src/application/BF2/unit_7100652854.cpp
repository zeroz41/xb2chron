// The aiData script class: the methods an AI script calls on its object (ai::AiData), its constructor function
// (aiData(id, index) hands the script the AiManager's data, or a default one) and its registration with the VM
// (ocAiDataRegist, which pluginRegist calls). The method names are the table's strings; the functions are file
// statics the symbols leave unnamed (fn_ placeholders).
#include "gf/FileStaticVec3.h"
#include "vm/yvm2.h"
#include "btl/Misc.h"
#include "btl/Utility.h"
#include "classes/ai/AiData.h"
#include "classes/ai/AiManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfObjAcc.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"

using namespace btl;

// the handle the AI's getters give for no object
#define INVALID_HANDLE reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)

// Helpers for the methods' arguments and return values (the names are not the original's).
static inline int argInt(VMThread* th, int no) {
    return vmArgIntGet(no, vmArgPtrGet(th, no));
}
static inline float argFixed(VMThread* th, int no) {
    return vmArgFixedGet(no, vmArgPtrGet(th, no));
}
static inline void retBool(VMThread* th, bool value) {
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
}
static inline void retInt(VMThread* th, int value) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(th, &ret);
}
static inline void retFixed(VMThread* th, float value) {
    VMData ret;
    ret.type = VMDATA_FIXED;
    ret.v.f = value;
    vmRetValSet(th, &ret);
}

// aiData.IsValid
static int fn_7100652854(VMThread* th, ai::AiData* data) {
    retBool(th, data->isValid());
    return 1;
}

// aiData.GetParam
static int fn_71006528A0(VMThread* th, ai::AiData* data) {
    retInt(th, data->getParam(argInt(th, 1)));
    return 1;
}

// aiData.SetParam
static int fn_7100652904(VMThread* th, ai::AiData* data) {
    int index = argInt(th, 1);
    int value = argInt(th, 2);
    data->setParam(index, value);
    return 0;
}

// aiData.setFrameCount
static int fn_7100652970(VMThread* th, ai::AiData* data) {
    data->setFrameCount(argInt(th, 1));
    return 0;
}

// aiData.setBladeArtsPower
static int fn_71006529B0(VMThread* th, ai::AiData* data) {
    int power = argInt(th, 1);
    Utility::AI_AddBladeArtsRecast(data->getHandle(), power, false);
    return 0;
}

// aiData.setSuperArmor
static int fn_71006529FC(VMThread* th, ai::AiData* data) {
    float time = argFixed(th, 1);
    Utility::AI_SetSuperArmor(data->getHandle(), time);
    return 0;
}

// aiData.getTargetMeId
static int fn_7100652A4C(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetTargetedCharacterID(data->getHandle()));
    return 1;
}

// aiData.getLinkEnemyId
static int fn_7100652A98(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetLinkCharacterID(data->getHandle()));
    return 1;
}

// aiData.getDiffHeightTarget
static int fn_7100652AE4(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retFixed(th, target != INVALID_HANDLE ? Utility::AI_GetVertDiff(data->getHandle(), target) : 0.0f);
    return 1;
}

// aiData.getEatEnemyId
static int fn_7100652B5C(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetEatTargetCharacterID(data->getHandle(), 20.0f));
    return 1;
}

// aiData.getTargetMeNum
static int fn_7100652BAC(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetAimCharacterNum(data->getHandle()));
    return 1;
}

// aiData.getFightComboTarget
static int fn_7100652BF8(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retInt(th, target != INVALID_HANDLE ? Utility::AI_GetFightComboID(target) : -1);
    return 1;
}

// aiData.getElemComboTarget
static int fn_7100652C54(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retInt(th, target != INVALID_HANDLE ? Utility::AI_GetElementalComboID(target) : -1);
    return 1;
}

// aiData.getStampTarget
static int fn_7100652CB0(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retInt(th, target != INVALID_HANDLE ? Utility::AI_GetStamp(target) : -1);
    return 1;
}

// aiData.getFightCombo
static int fn_7100652D0C(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetFightComboID(data->getHandle()));
    return 1;
}

// aiData.getElemCombo
static int fn_7100652D58(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetElementalComboID(data->getHandle()));
    return 1;
}

// aiData.getId
static int fn_7100652DA4(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetCharacterAIID(data->getHandle()));
    return 1;
}

// aiData.getIdTarget
static int fn_7100652DF0(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetTargetCharacterID(data->getHandle()));
    return 1;
}

// aiData.getIdVoiceCode
static int fn_7100652E3C(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_SearchVoiceCodeCharacter(argInt(th, 1)));
    return 1;
}

// aiData.getRescueTargetId
static int fn_7100652E94(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetRescueTargetCharacterID(data->getHandle()));
    return 1;
}

// aiData.getCounterBackTargetId
static int fn_7100652EE0(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetBackAttackerCharacterID(data->getHandle()));
    return 1;
}

// aiData.getDistanceTargetRadiusSub
static int fn_7100652F2C(VMThread* th, ai::AiData* data) {
    float radius = data->getRadius();
    float radiusTarget = data->getRadiusTarget();
    mm::Vec3 pos = data->getPosition();
    mm::Vec3 posTarget = data->getPositionTarget();
    float distance = (posTarget - pos).length();
    float value = distance - (radius + radiusTarget);
    VMData ret;
    ret.type = VMDATA_FIXED;
    ret.v.f = value;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.getRadius
static int fn_7100652FF8(VMThread* th, ai::AiData* data) {
    retFixed(th, data->getRadius());
    return 1;
}

// aiData.getRadiusTarget
static int fn_7100653040(VMThread* th, ai::AiData* data) {
    retFixed(th, data->getRadiusTarget());
    return 1;
}

// aiData.getTargetDirection
static int fn_7100653088(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retInt(th, target != INVALID_HANDLE ? Utility::AI_GetTargetDirection(target, data->getHandle()) : 0);
    return 1;
}

// aiData.getTargetDirectionCount: not identical yet (wip/unit_7100652854.scratch_all90.cpp)
static int fn_7100653104(VMThread* th, ai::AiData* data);

// aiData.getDirectionCount
static int fn_7100653204(VMThread* th, ai::AiData* data) {
    int num = argInt(th, 1);
    int mode = 1;
    if (!vmArgOmitChk(th, 2)) {
        mode = argInt(th, 2);
    }
    retInt(th, Utility::AI_CheckCharacterNum(data->getHandle(), num, static_cast<Utility::CHECK_CHR_NUM_MODE>(mode)));
    return 1;
}

// aiData.getDirectionTarget
static int fn_71006532AC(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retInt(th, target != INVALID_HANDLE ? Utility::AI_GetTargetDirection(data->getHandle(), target) : 0);
    return 1;
}

// aiData.getPartyId
static int fn_7100653324(VMThread* th, ai::AiData* data) {
    gf::GfObjAcc acc(data->getHandle());
    int partyId = acc.getPartyID();
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = partyId;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.getKizuna
static int fn_7100653380(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetKizunaStage(data->getHandle()));
    return 1;
}

// aiData.getWeaponType
static int fn_71006533CC(VMThread* th, ai::AiData* data) {
    gf::DataParamAcc acc(data->getHandle());
    int weaponType = acc.getWeaponType(-1, false);
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = weaponType;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.getBladeArtsLevel
static int fn_7100653438(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetSpAttackLevel(data->getHandle()));
    return 1;
}

// aiData.getArtsId
static int fn_7100653484(VMThread* th, ai::AiData* data) {
    int index = argInt(th, 1);
    gf::DataParamAcc acc(data->getHandle());
    int arts = acc.fn_71002208A4(acc.getWeaponType(-1, false), index, 0);
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = arts;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.getTargetReaction
static int fn_7100653528(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retInt(th, target != INVALID_HANDLE ? Utility::AI_GetReactionID(target) : -1);
    return 1;
}

// aiData.getNumPartyByHpRate
static int fn_7100653584(VMThread* th, ai::AiData* data) {
    int rate = argInt(th, 1);
    gf::GfObjAcc acc(data->getHandle());
    int value = Utility::AI_CheckHpRateCharacterNum(data->getHandle(), rate, static_cast<Utility::CHECK_CHR_NUM_MODE>(1));
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.getTargetAiId
static int fn_7100653610(VMThread* th, ai::AiData* data) {
    gf::GfObjAcc acc(data->getHandle());
    ai::AiData* target = ai::AiManager::getPtr()->getDataFromHandle(data->getHandleTarget());
    int value = target != NULL ? target->getId() : -1;
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.getTargetDriverId
static int fn_7100653728(VMThread* th, ai::AiData* data) {
    int id = Utility::AI_GetBdatID(data->getHandleTarget());
    retInt(th, id != 0 ? id : -1);
    return 1;
}

// aiData.getTargetBladeId
static int fn_710065377C(VMThread* th, ai::AiData* data) {
    int id = Utility::fn_7100014DC0(data->getHandleTarget());
    retInt(th, id != 0 ? id : -1);
    return 1;
}

// aiData.getDistancePoint
static int fn_71006537D0(VMThread* th, ai::AiData* data) {
    int pointId = -1;
    if (!vmArgOmitChk(th, 1)) {
        pointId = argInt(th, 1);
    }
    int toTarget = 0;
    if (!vmArgOmitChk(th, 2)) {
        toTarget = vmArgBoolGet(2, vmArgPtrGet(th, 2));
    }
    mm::Vec3 point = mm::Vec3::zero;
    bool found;
    if (pointId >= 0) {
        found = Utility::AI_GetGimmickPoint(point, pointId);
    } else {
        found = Utility::AI_GetCharacterGimmickPoint(data->getHandle(), point);
    }
    float distance = -1.0f;
    if (found) {
        mm::Vec3 pos;
        bool valid = true;
        if (toTarget > 0) {
            int targetId = Utility::AI_GetTargetCharacterID(data->getHandle());
            valid = Utility::AI_GetObjectPosition(Utility::AI_GetCharacterHandle(targetId), pos);
        } else {
            pos = data->getPosition();
        }
        if (valid) {
            distance = (point - pos).length();
        }
    }
    retFixed(th, distance);
    return 1;
}

// aiData.getEatTargetId
static int fn_710065396C(VMThread* th, ai::AiData* data) {
    float range = 20.0f;
    if (!vmArgOmitChk(th, 1)) {
        range = argFixed(th, 1);
    }
    retInt(th, Utility::AI_GetEatTargetCharacterID(data->getHandle(), range));
    return 1;
}

// aiData.getIdByBuffId: not identical yet (wip/unit_7100652854.scratch_all90.cpp)
static int fn_71006539F8(VMThread* th, ai::AiData* data);

// aiData.getScoutStartHp
static int fn_7100653BF8(VMThread* th, ai::AiData* data) {
    retInt(th, data->getScoutStartHp());
    return 1;
}

// aiData.getAutoAttackState
static int fn_7100653C40(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetAutoAttackState(data->getHandle()));
    return 1;
}

// aiData.getElemBall
static int fn_7100653C8C(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::fn_71000126C0(data->getHandle()));
    return 1;
}

// aiData.actionRescue
static int fn_7100653CD8(VMThread* th, ai::AiData* data) {
    int arg = argInt(th, 1);
    retBool(th, Utility::AI_StartActionRescue(data->getHandle(), arg));
    return 1;
}

// aiData.actionHoming
static int fn_7100653D50(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_StartActionEscape(data->getHandle()));
    return 1;
}

// aiData.actionArts
static int fn_7100653DA0(VMThread* th, ai::AiData* data) {
    int arts = argInt(th, 1);
    int arg = -1;
    if (!vmArgOmitChk(th, 2)) {
        arg = argInt(th, 2);
    }
    retBool(th, Utility::AI_StartActionArts(data->getHandle(), arts, arg));
    return 1;
}

// aiData.actionNormalAttack
static int fn_7100653E58(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_StartActionAttack(data->getHandle()));
    return 1;
}

// aiData.actionTalentArts
static int fn_7100653EA8(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::fn_7100012DEC(data->getHandle()));
    return 1;
}

// aiData.actionAngry
static int fn_7100653EF8(VMThread* th, ai::AiData* data) {
    int time = argInt(th, 1);
    retBool(th, Utility::AI_SetAngry(data->getHandle(), time));
    return 1;
}

// aiData.actionBladeChange
static int fn_7100653F70(VMThread* th, ai::AiData* data) {
    int arg = argInt(th, 1);
    retBool(th, Utility::AI_StartActionBladeChange(data->getHandle(), arg));
    return 1;
}

// aiData.actionBladeArts
static int fn_7100653FE8(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_StartSpAttack(data->getHandle()));
    return 1;
}

// aiData.actionDriverArts
static int fn_7100654038(VMThread* th, ai::AiData* data) {
    int id = argInt(th, 1);
    int arg = -1;
    if (!vmArgOmitChk(th, 2)) {
        arg = argInt(th, 2);
    }
    retBool(th, Utility::AI_StartActionArtsByID(data->getHandle(), id, arg));
    return 1;
}

// aiData.moveSideTarget
static int fn_71006540F0(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    bool result = false;
    if (target != INVALID_HANDLE) {
        int targetId = Utility::AI_GetCharacterAIID(target);
        result = Utility::AI_StartMoveSide(data->getHandle(), targetId, 2.0f, 10.0f);
    }
    retBool(th, result);
    return 1;
}

// aiData.moveBackTarget
static int fn_7100654178(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    bool result = false;
    if (target != INVALID_HANDLE) {
        int targetId = Utility::AI_GetCharacterAIID(target);
        result = Utility::AI_StartMoveBack(data->getHandle(), targetId, 2.0f, 10.0f);
    }
    retBool(th, result);
    return 1;
}

// aiData.moveBackFriend
static int fn_7100654200(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_StartMoveFriendBack(data->getHandle(), 2.0f, 10.0f));
    return 1;
}

// aiData.moveChaseTarget
static int fn_7100654258(VMThread* th, ai::AiData* data) {
    float distance = 0.0f;
    if (!vmArgOmitChk(th, 1)) {
        distance = argInt(th, 1);
    }
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    bool result = false;
    if (target != INVALID_HANDLE) {
        if (distance <= 0.0f) {
            distance = data->getRadius() + data->getRadiusTarget();
        }
        int targetId = Utility::AI_GetCharacterAIID(target);
        result = Utility::AI_StartMoveTarget(data->getHandle(), targetId, distance, 10.0f);
    }
    bool value = result;
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.moveChaseTargetById
static int fn_7100654340(VMThread* th, ai::AiData* data) {
    int targetId = argInt(th, 1);
    float distance = 0.0f;
    if (!vmArgOmitChk(th, 2)) {
        distance = argInt(th, 2);
    }
    gf::GF_OBJ_HANDLE* target = Utility::AI_GetCharacterHandle(targetId);
    bool result = false;
    if (target != INVALID_HANDLE) {
        if (distance <= 0.0f) {
            distance = data->getRadius() + data->getRadius(target);
        }
        result = Utility::AI_StartMoveTarget(data->getHandle(), targetId, distance, 10.0f);
    }
    bool value = result;
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.moveDirectionTarget
static int fn_710065443C(VMThread* th, ai::AiData* data) {
    int direction = argInt(th, 1);
    int distance = argInt(th, 2);
    int frames = argInt(th, 3);
    gf::GF_OBJ_HANDLE* handle = data->getHandle();
    int targetId = Utility::AI_GetTargetCharacterID(handle);
    bool result = false;
    if (targetId >= 0) {
        float time = frames / 30.0f;
        switch (direction) {
        case 1:
            result = Utility::AI_StartMoveFront(handle, targetId, distance, time);
            break;
        case 2:
            result = Utility::AI_StartMoveLeft(handle, targetId, distance, time);
            break;
        case 3:
            result = Utility::AI_StartMoveRight(handle, targetId, distance, time);
            break;
        case 4:
            result = Utility::AI_StartMoveBack(handle, targetId, distance, time);
            break;
        }
    }
    retBool(th, result);
    return 1;
}

// aiData.moveStepBack
static int fn_7100654584(VMThread* th, ai::AiData* data) {
    float time = argInt(th, 1) / 30.0f;
    retBool(th, Utility::AI_StartMoveBackward(data->getHandle(), 1000.0f, time));
    return 1;
}

// aiData.moveSatellite
static int fn_7100654614(VMThread* th, ai::AiData* data) {
    int mode = argInt(th, 1);
    int distance = argInt(th, 2);
    retBool(th, Utility::AI_StartMoveSatellite(data->getHandle(), mode == 3, distance));
    return 1;
}

// aiData.moveStop
static int fn_71006546B8(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_MoveStop(data->getHandle(), false));
    return 1;
}

// aiData.movePointScout
static int fn_710065470C(VMThread* th, ai::AiData* data) {
    float frames = 300.0f;
    if (!vmArgOmitChk(th, 1)) {
        frames = argInt(th, 1);
    }
    mm::Vec3 pos = mm::Vec3::zero;
    bool result = false;
    if (Utility::AI_GetCharacterGimmickPoint(data->getHandle(), pos)) {
        float time = frames / 30.0f;
        if (time <= 0.0f) {
            time = 300.0f;
        }
        if (Utility::AI_StartMovePosition(data->getHandle(), pos, time)) {
            Utility::AI_SetScout(data->getHandle(), true);
            result = true;
        }
    }
    bool value = result;
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.movePointFront
static int fn_7100654808(VMThread* th, ai::AiData* data) {
    int point = argInt(th, 1);
    mm::Vec3 pos = mm::Vec3::zero;
    bool result = false;
    if (point >= 0 && Utility::AI_GetGimmickPoint(pos, point)) {
        Utility::AI_SetUseNavi(data->getHandle(), false);
        result = Utility::AI_StartMovePosition(data->getHandle(), pos, 10.0f);
    }
    bool value = result;
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.movePointBack
static int fn_71006548C8(VMThread* th, ai::AiData* data) {
    int point = argInt(th, 1);
    bool result = false;
    if (point >= 0) {
        mm::Vec3 pos = mm::Vec3::zero;
        if (Utility::AI_GetGimmickPoint(pos, point)) {
            mm::Vec3 dir;
            if (Misc::CalcDirectionXZ(pos, data->getPosition(), dir)) {
                Utility::AI_TurnDirection(data->getHandle(), dir);
                Utility::AI_SetUseNavi(data->getHandle(), false);
                pos.y = data->getPosition().y;
                result = Utility::AI_StartMovePosBackward(data->getHandle(), pos, 10.0f);
            }
        }
    }
    retBool(th, result);
    return 1;
}

// aiData.turnTarget
static int fn_71006549CC(VMThread* th, ai::AiData* data) {
    Utility::AI_TurnTarget(data->getHandle());
    return 0;
}

// aiData.isFlightTarget
static int fn_71006549EC(VMThread* th, ai::AiData* data) {
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    retBool(th, target != INVALID_HANDLE && Utility::AI_IsFly(target));
    return 1;
}

// aiData.isStartBattle
static int fn_7100654A4C(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::IsBattleStart(data->getHandle()));
    return 1;
}

// aiData.isBladeChangeRequest
static int fn_7100654A9C(VMThread* th, ai::AiData* data) {
    retInt(th, -1);
    return 1;
}

// aiData.isDestruct
static int fn_7100654AD0(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_IsDestruct(data->getHandle()));
    return 1;
}

// aiData.isFrameCountEnd
static int fn_7100654B20(VMThread* th, ai::AiData* data) {
    retBool(th, data->isFrameCountEnd());
    return 1;
}

// aiData.isMove
static int fn_7100654B6C(VMThread* th, ai::AiData* data) {
    bool a = Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(11), 0);
    bool b = Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(10), 0);
    retInt(th, b ? (a ? 1 : 2) : 0);
    return 1;
}

// aiData.isTurn
static int fn_7100654BF8(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(9), 0));
    return 1;
}

// aiData.isScout
static int fn_7100654C50(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(15), 0));
    return 1;
}

// aiData.isBattleOpenning
static int fn_7100654CA8(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_IsBattleOpening(data->getHandle()));
    return 1;
}

// aiData.isAutoAttack
static int fn_7100654CF8(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_IsInAttackRange(data->getHandle()));
    return 1;
}

// aiData.isArts
static int fn_7100654D48(VMThread* th, ai::AiData* data) {
    int arts = argInt(th, 1);
    retBool(th, Utility::AI_IsEnableArts(data->getHandle(), arts, -1));
    return 1;
}

// aiData.isTalentArts
static int fn_7100654DC4(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::fn_7100014958(data->getHandle(), -1));
    return 1;
}

// aiData.isDriverArts
static int fn_7100654E18(VMThread* th, ai::AiData* data) {
    int id = argInt(th, 1);
    retBool(th, Utility::AI_IsEnableArtsByID(data->getHandle(), id, -1));
    return 1;
}

// aiData.isTargetArts: not identical yet (wip/unit_7100652854.scratch_all90.cpp)
static int fn_7100654E94(VMThread* th, ai::AiData* data);

// aiData.isWater
static int fn_7100654F14(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(12), 0));
    return 1;
}

// aiData.isTargetDriverID
static int fn_7100654F6C(VMThread* th, ai::AiData* data) {
    int id = argInt(th, 1);
    gf::GF_OBJ_HANDLE* target = data->getHandleTarget();
    gf::GfObjAcc acc(target);
    bool result = false;
    if (acc.m_obj != NULL && acc.getType() == 3) {
        result = Utility::AI_GetBdatID(target) == id;
    }
    bool value = result;
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
    return 1;
}

// aiData.isBladeArts
static int fn_7100655014(VMThread* th, ai::AiData* data) {
    int arg = 0;
    if (!vmArgOmitChk(th, 1)) {
        arg = argInt(th, 1);
    }
    retBool(th, Utility::AI_IsEnableSpAttack(data->getHandle(), arg));
    return 1;
}

// aiData.isChainTime
static int fn_71006550A4(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(13), 0));
    return 1;
}

// aiData.isValidAI
static int fn_71006550FC(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(14), 0));
    return 1;
}

// aiData.isDead
static int fn_7100655154(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(3), 0));
    return 1;
}

// aiData.isAwaking
static int fn_71006551AC(VMThread* th, ai::AiData* data) {
    retBool(th, Utility::AI_CheckState(data->getHandle(), static_cast<Utility::CHECK_STATE>(16), 0));
    return 1;
}

// aiData.playVoice
static int fn_7100655204(VMThread* th, ai::AiData* data) {
    int voice = argInt(th, 1);
    retBool(th, Utility::AI_PlayVoice(data->getHandle(), voice) != 0);
    return 1;
}

// aiData.getPlayVoice
static int fn_710065527C(VMThread* th, ai::AiData* data) {
    retInt(th, Utility::AI_GetPlayVoiceID(data->getHandle()));
    return 1;
}

// aiData.addKizuna
static int fn_71006552C8(VMThread* th, ai::AiData* data) {
    int value = argInt(th, 1);
    Utility::AI_AddKizuna(data->getHandle(), value);
    return 0;
}

// The data the constructor function hands a script when the AiManager has none for the id (the name is not the
// original's).
static ai::AiData s_defaultData;

// aiData(id, index): the AiManager's index-th data of that id (the parameter names are not the original's)
// the third argument is 64 bits wide (the value keeps its low 16 bits); the second is unused (the types are not
// known)
static int fn_7100655310(VMThread* th, void* unused, unsigned long ocId) {
    int id = argInt(th, 1);
    int index = argInt(th, 2);
    ai::AiData* data = ai::AiManager::getPtr()->getDataFromId(id, index);
    if (data == NULL) {
        data = &s_defaultData;
    }
    VMData ret;
    ret.type = VMDATA_OC;
    ret.hi = ocId;
    ret.v.obj = data;
    vmRetValSet(th, &ret);
    return 1;
}

// The aiData script class's properties: none. Proposed name, not the original's: the symbols leave it unnamed
// (lbl_7100EC16F0).
static VMOCProperty s_aiDataProperties[1];

// The aiData script class's methods. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B720C0).
static VMOCMethod s_aiDataMethods[] = {
    {"IsValid", reinterpret_cast<void*>(&fn_7100652854), 0},
    {"GetParam", reinterpret_cast<void*>(&fn_71006528A0), 0},
    {"SetParam", reinterpret_cast<void*>(&fn_7100652904), 0},
    {"setFrameCount", reinterpret_cast<void*>(&fn_7100652970), 0},
    {"setBladeArtsPower", reinterpret_cast<void*>(&fn_71006529B0), 0},
    {"setSuperArmor", reinterpret_cast<void*>(&fn_71006529FC), 0},
    {"getTargetMeId", reinterpret_cast<void*>(&fn_7100652A4C), 0},
    {"getLinkEnemyId", reinterpret_cast<void*>(&fn_7100652A98), 0},
    {"getDiffHeightTarget", reinterpret_cast<void*>(&fn_7100652AE4), 0},
    {"getEatEnemyId", reinterpret_cast<void*>(&fn_7100652B5C), 0},
    {"getTargetMeNum", reinterpret_cast<void*>(&fn_7100652BAC), 0},
    {"getFightComboTarget", reinterpret_cast<void*>(&fn_7100652BF8), 0},
    {"getElemComboTarget", reinterpret_cast<void*>(&fn_7100652C54), 0},
    {"getStampTarget", reinterpret_cast<void*>(&fn_7100652CB0), 0},
    {"getFightCombo", reinterpret_cast<void*>(&fn_7100652D0C), 0},
    {"getElemCombo", reinterpret_cast<void*>(&fn_7100652D58), 0},
    {"getId", reinterpret_cast<void*>(&fn_7100652DA4), 0},
    {"getIdTarget", reinterpret_cast<void*>(&fn_7100652DF0), 0},
    {"getIdVoiceCode", reinterpret_cast<void*>(&fn_7100652E3C), 0},
    {"getRescueTargetId", reinterpret_cast<void*>(&fn_7100652E94), 0},
    {"getCounterBackTargetId", reinterpret_cast<void*>(&fn_7100652EE0), 0},
    {"getDistanceTargetRadiusSub", reinterpret_cast<void*>(&fn_7100652F2C), 0},
    {"getRadius", reinterpret_cast<void*>(&fn_7100652FF8), 0},
    {"getRadiusTarget", reinterpret_cast<void*>(&fn_7100653040), 0},
    {"getTargetDirection", reinterpret_cast<void*>(&fn_7100653088), 0},
    {"getTargetDirectionCount", reinterpret_cast<void*>(&fn_7100653104), 0},
    {"getDirectionCount", reinterpret_cast<void*>(&fn_7100653204), 0},
    {"getDirectionTarget", reinterpret_cast<void*>(&fn_71006532AC), 0},
    {"getPartyId", reinterpret_cast<void*>(&fn_7100653324), 0},
    {"getKizuna", reinterpret_cast<void*>(&fn_7100653380), 0},
    {"getWeaponType", reinterpret_cast<void*>(&fn_71006533CC), 0},
    {"getBladeArtsLevel", reinterpret_cast<void*>(&fn_7100653438), 0},
    {"getArtsId", reinterpret_cast<void*>(&fn_7100653484), 0},
    {"getTargetReaction", reinterpret_cast<void*>(&fn_7100653528), 0},
    {"getNumPartyByHpRate", reinterpret_cast<void*>(&fn_7100653584), 0},
    {"getTargetAiId", reinterpret_cast<void*>(&fn_7100653610), 0},
    {"getTargetDriverId", reinterpret_cast<void*>(&fn_7100653728), 0},
    {"getTargetBladeId", reinterpret_cast<void*>(&fn_710065377C), 0},
    {"getDistancePoint", reinterpret_cast<void*>(&fn_71006537D0), 0},
    {"getEatTargetId", reinterpret_cast<void*>(&fn_710065396C), 0},
    {"getIdByBuffId", reinterpret_cast<void*>(&fn_71006539F8), 0},
    {"getScoutStartHp", reinterpret_cast<void*>(&fn_7100653BF8), 0},
    {"getAutoAttackState", reinterpret_cast<void*>(&fn_7100653C40), 0},
    {"getElemBall", reinterpret_cast<void*>(&fn_7100653C8C), 0},
    {"actionRescue", reinterpret_cast<void*>(&fn_7100653CD8), 0},
    {"actionHoming", reinterpret_cast<void*>(&fn_7100653D50), 0},
    {"actionArts", reinterpret_cast<void*>(&fn_7100653DA0), 0},
    {"actionNormalAttack", reinterpret_cast<void*>(&fn_7100653E58), 0},
    {"actionTalentArts", reinterpret_cast<void*>(&fn_7100653EA8), 0},
    {"actionAngry", reinterpret_cast<void*>(&fn_7100653EF8), 0},
    {"actionBladeChange", reinterpret_cast<void*>(&fn_7100653F70), 0},
    {"actionBladeArts", reinterpret_cast<void*>(&fn_7100653FE8), 0},
    {"actionDriverArts", reinterpret_cast<void*>(&fn_7100654038), 0},
    {"moveSideTarget", reinterpret_cast<void*>(&fn_71006540F0), 0},
    {"moveBackTarget", reinterpret_cast<void*>(&fn_7100654178), 0},
    {"moveBackFriend", reinterpret_cast<void*>(&fn_7100654200), 0},
    {"moveChaseTarget", reinterpret_cast<void*>(&fn_7100654258), 0},
    {"moveChaseTargetById", reinterpret_cast<void*>(&fn_7100654340), 0},
    {"moveDirectionTarget", reinterpret_cast<void*>(&fn_710065443C), 0},
    {"moveStepBack", reinterpret_cast<void*>(&fn_7100654584), 0},
    {"moveSatellite", reinterpret_cast<void*>(&fn_7100654614), 0},
    {"moveStop", reinterpret_cast<void*>(&fn_71006546B8), 0},
    {"movePointScout", reinterpret_cast<void*>(&fn_710065470C), 0},
    {"movePointFront", reinterpret_cast<void*>(&fn_7100654808), 0},
    {"movePointBack", reinterpret_cast<void*>(&fn_71006548C8), 0},
    {"turnTarget", reinterpret_cast<void*>(&fn_71006549CC), 0},
    {"isFlightTarget", reinterpret_cast<void*>(&fn_71006549EC), 0},
    {"isStartBattle", reinterpret_cast<void*>(&fn_7100654A4C), 0},
    {"isBladeChangeRequest", reinterpret_cast<void*>(&fn_7100654A9C), 0},
    {"isDestruct", reinterpret_cast<void*>(&fn_7100654AD0), 0},
    {"isFrameCountEnd", reinterpret_cast<void*>(&fn_7100654B20), 0},
    {"isMove", reinterpret_cast<void*>(&fn_7100654B6C), 0},
    {"isTurn", reinterpret_cast<void*>(&fn_7100654BF8), 0},
    {"isScout", reinterpret_cast<void*>(&fn_7100654C50), 0},
    {"isBattleOpenning", reinterpret_cast<void*>(&fn_7100654CA8), 0},
    {"isAutoAttack", reinterpret_cast<void*>(&fn_7100654CF8), 0},
    {"isArts", reinterpret_cast<void*>(&fn_7100654D48), 0},
    {"isTalentArts", reinterpret_cast<void*>(&fn_7100654DC4), 0},
    {"isDriverArts", reinterpret_cast<void*>(&fn_7100654E18), 0},
    {"isTargetArts", reinterpret_cast<void*>(&fn_7100654E94), 0},
    {"isWater", reinterpret_cast<void*>(&fn_7100654F14), 0},
    {"isTargetDriverID", reinterpret_cast<void*>(&fn_7100654F6C), 0},
    {"isBladeArts", reinterpret_cast<void*>(&fn_7100655014), 0},
    {"isChainTime", reinterpret_cast<void*>(&fn_71006550A4), 0},
    {"isValidAI", reinterpret_cast<void*>(&fn_71006550FC), 0},
    {"isDead", reinterpret_cast<void*>(&fn_7100655154), 0},
    {"isAwaking", reinterpret_cast<void*>(&fn_71006551AC), 0},
    {"playVoice", reinterpret_cast<void*>(&fn_7100655204), 0},
    {"getPlayVoice", reinterpret_cast<void*>(&fn_710065527C), 0},
    {"addKizuna", reinterpret_cast<void*>(&fn_71006552C8), 0},
    {NULL, NULL, 0},
};

VMOC aiData = {"aiData", reinterpret_cast<void*>(&fn_7100655310), s_aiDataProperties, s_aiDataMethods};

void ocAiDataRegist() {
    vmOCRegist(&aiData);
}
