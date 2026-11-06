#include "classes/event/ModelObj.h"
#include "classes/event/ScheManager.h"
#include "classes/event/CharaUtil.h"
#include "classes/event/AlphaManager.h"
#include "classes/event/CharaDysUpdater.h"
#include "classes/event/CharaIKUpdater.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "classes/event/TarAxis.h"
#include "classes/event/AttachActorCS.h"
#include "classes/event/ScriptUtil.h"
#include "classes/event/CharaPlayTalk.h"
#include "gf/GfDataBlade.h"
#include "mm/Mat44.h"
#include "classes/event/FrameManager.h"
#include "classes/fw/CameraManager.h"
#include "classes/event/CamManager.h"
#include "classes/event/DebugManager.h"
#include "classes/gf/GfAssetSetup.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/EffectObj.h"
#include "classes/event/CamObj.h"
#include "classes/event/ObjectChara.h"
#include "classes/event/DataManager.h"
#include "classes/event/ObjectEffect.h"
#include "classes/event/ObjectCamera.h"
#include "classes/event/ObjectUtil.h"
#include "classes/ml/DevGraph.h"
#include <math.h>
#include "classes/event/CamFree.h"
#include "classes/event/VolumeManager.h"
#include "classes/event/VolumePlayer.h"
#include "classes/event/VoicePlayer.h"
#include "classes/event/VoiceMaker.h"
#include "classes/event/VoiceOneShoter.h"
#include "classes/event/VoiceManager.h"
#include "fw/LangUtil.h"
#include "classes/event/CsSndManager.h"
#include "classes/fw/SoundManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/event/AgelogManager.h"
#include "classes/event/DebugManager.h"
#include "classes/event/Manager.h"
#include "classes/event/UIManager.h"
#include "classes/event/CharaSetRot.h"
#include "classes/event/CmdVariable.h"
#include "classes/event/CharaSetPos.h"
#include "classes/event/CharaStopAction.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfObj.h"
#include "gf/MsgGameLipAction.h"
#include "gf/MsgGameTalkAction.h"
#include "plugin/Bdat.h"
#include "classes/event/CmdItem.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/CharaEffectPlayer.h"
#include "classes/event/CharaTarPlayer.h"
#include "classes/event/CharaTarPlayerMot.h"
#include "classes/event/CharaWeightItem.h"
#include "classes/event/CharaObj.h"
#include "string.h"
#include "classes/RchaEff.h"
#include "classes/RchaChrEff.h"
#include "classes/RchaCamEff.h"
#include "classes/RchaCam.h"
#include "classes/event/EffectEvaPlayer.h"
#include "classes/event/EffectPlayEva.h"
#include "classes/event/EffectManager.h"
#include "classes/event/ResManager.h"
#include "classes/event/MotstmManager.h"
#include "classes/event/Extend.h"
#include "classes/event/CharaEvaPlayerEff.h"
#include "classes/event/CharaWpnAsm.h"
#include "classes/event/CharaEvaPlayer.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/ml/DrStmReadCheck.h"
#include "classes/event/CamEvaPlayer.h"
#include "classes/event/CamEvaPlayerEff.h"
#include "classes/event/EffectCtrl.h"
#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/CmdItem.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/CharaObj.h"
#include "classes/event/Object.h"
#include "classes/event/ObjectChara.h"
#include "classes/event/ObjectCamera.h"
#include "classes/event/ObjectEffect.h"
#include "classes/event/ObjectList.h"
#include "classes/event/ObjectManager.h"
#include "classes/event/MemoryManager.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/event/LightManager.h"
#include "classes/event/CmdVariable.h"
#include "classes/event/ICmd/Param.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfReqManager.h"
#include "gf/GfReqCommand.h"
#include "gf/GfReqParam.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfComModel.h"
#include "classes/fw/ModelObject.h"
#include "ml/ScnObjAccResMdlInfo.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComEffectCaster.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "classes/fw/EffectManager.h"
#include "mm/Math.h"
#include "classes/event/RandPlayer/Warp.h"
#include "classes/event/RandPlayer/Wait.h"
#include "classes/event/RandUtil.h"
#include "classes/event/CharaStopHead.h"
#include "classes/event/StmPackMemory.h"
#include "classes/event/StmPackData.h"
#include "classes/event/StmPackHeader.h"
#include "classes/fw/RenderResource.h"
#include "ml/EventFileTh.h"
#include "classes/event/SeqManager/start.h"
#include "classes/event/SeqManager/end.h"
#include "classes/event/SeqManager/end_fadein.h"
#include "classes/event/SeqManager/start_streaming1.h"
#include "classes/event/SeqManager/start_capture_wait.h"
#include "classes/event/SeqManager/start_notice.h"
#include "classes/event/SeqManager/end_notice.h"
#include "classes/event/SeqManager/play_start.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "classes/gf/GfScriptManager.h"
#include "gf/FileStaticVec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/Vec2.h"
#include "mm/Col4.h"
#include "classes/event/ParamVariable.h"
#include "classes/event/Param.h"
#include "classes/event/CharaSetTar.h"
#include "classes/event/CharaWinkPlayer.h"
#include "classes/event/CharaWeightPlayer.h"
#include "classes/event/EffectPlayEff.h"
#include "classes/gf/GfMovieManager.h"
#include "ml/MTRand.h"
#include "classes/event/ShakeManager.h"
#include "classes/event/TodoManager.h"
#include "classes/event/ObjectPartyList.h"
#include "classes/event/BouManager.h"
#include "gf/GfObjAcc.h"
#include "classes/event/FrameInfo.h"
#include "classes/event/LipsyncRes.h"
#include "classes/event/MstxtRes.h"
#include "classes/event/EffectRes.h"
#include "classes/fw/EffectPack.h"
#include "classes/fw/BdatManager.h"
#include "classes/gf/GfMenuObjEventSubtitle.h"
#include "event/AgelogUtil.h"
#include "classes/event/AgelogManager.h"
#include "ml/DateName.h"
#include "classes/event/AttachActorGf.h"
#include "classes/event/BlurManager.h"
#include "classes/event/BouRect.h"
#include "classes/event/CamField.h"
#include "classes/event/CamFree.h"
#include "fw/FwDebug.h"
#include "classes/ml/EventView.h"
#include "classes/ml/DevKeyboard.h"
#include "classes/gf/GfPause.h"
#include "classes/ml/Scn.h"
#include "classes/ml/WinView.h"
#include "classes/event/CharaMount.h"
#include "classes/event/CharaPlayAction.h"
#include "classes/event/CharaPlayActionAuto.h"
#include "classes/event/CharaPlayTalkAuto.h"
#include "classes/event/CharaTurnRot.h"
#include "classes/event/CmdVariable.h"
#include "classes/event/CopydataManager.h"
#include "classes/event/FormManager.h"
#include "fw/ColiCheck.h"
#include "gf/GfGameUtil.h"
#include "classes/event/MercenariesManager.h"
#include "classes/event/ObjectCamera.h"
#include "classes/event/ObjectEffect.h"
#include "classes/event/ObjectTree.h"
#include "classes/event/ParamVariable.h"
#include "classes/event/ScriptCharaMotion.h"
#include "classes/event/ScriptCharaMotionABC.h"
#include "classes/event/SkipManager.h"
#include "classes/event/CharaManager.h"

#include "classes/event/EvtxtManager.h"
#include "classes/event/LipsyncManager.h"
#include "classes/event/MdlstmManager.h"
#include "classes/event/MstxtManager.h"
#include "classes/event/OffscrManager.h"

namespace event {

CmdVariable::~CmdVariable() {}

ParamVariable::~ParamVariable() {}

Param::Param() {}

AttachActorCS::~AttachActorCS() {
    while (m_casters.size() != 0) {
        setEffectCaster(false, **m_casters.begin());
    }
    while (m_mounts.size() != 0) {
        setEffectMount(false, (*m_mounts.begin())->m_handle, "", mm::Vec3::zero, false, static_cast<EVT_attachtype>(0));
    }
}

bool AttachActorCS::getMtpMat(mm::Mat44& mat, const char*) const {
    mat = mm::Mat44::identity;
    return false;
}

AttachActorGf::~AttachActorGf() {}

bool AttachActorGf::getMtpMat(mm::Mat44& mat, const char*) const {
    mat = mm::Mat44::identity;
    return false;
}

const char* AttachActorBase::getName() const {
    return m_name;
}

bool AttachActorBase::getMat(mm::Mat44& mat) const {
    mat = m_mat;
    return true;
}

bool AttachActorBase::getMtpMatGlobal(mm::Mat44& mat, const char* name) const {
    mm::Mat44 m;
    if (!getMtpMat(m, name)) {
        mat = m_mat;
        return false;
    }
    mat.mulCopy(m, m_mat);
    return true;
}

bool AttachActorBase::hasMtp(const char* name) const {
    mm::Mat44 mat;
    return getMtpMat(mat, name);
}

bool AttachActorBase::getEfpMatGlobal(mm::Mat44& mat, const char* name) const {
    mm::Mat44 m;
    if (!getEfpMat(m, name)) {
        mat = m_mat;
        return false;
    }
    mat.mulCopy(m, m_mat);
    return true;
}

bool AttachActorBase::hasEfp(const char* name) const {
    mm::Mat44 mat;
    return getEfpMat(mat, name);
}

bool AttachActorBase::getBoneMatGlobal(mm::Mat44& mat, const char* name) const {
    mm::Mat44 m;
    if (!getBoneMat(m, name)) {
        mat = m_mat;
        return false;
    }
    mat.mulCopy(m, m_mat);
    return true;
}

bool AttachActorBase::hasBone(const char* name) const {
    mm::Mat44 mat;
    return getBoneMat(mat, name);
}

CamFree::~CamFree() {
    if (m_flags & 1) {
        mm::mtl::PtrSingleton<Manager>::sys()->m_scn->getView(-1)->detachWorkEvent(this);
    }
}

void CamFree::update(const event::FrameInfo&) {}

bool CamFree::OnMouseButtonDown(ml::EventView* view) {
    if (view->pad_28 & 1) {
        pad_4c |= 8;
    } else {
        pad_4c &= ~8u;
    }
    if (view->m_buttons & 4) {
        pad_4c |= 1;
    }
    if (view->m_buttons & 2) {
        pad_4c |= 2;
    }
    if (view->m_buttons & 1) {
        pad_4c |= 4;
    }
    pad_50 = 0;
    if (!(pad_4c & 8)) {
        return false;
    }
    if (pad_4c & 1) {
        pad_50 = 1;
    } else if (pad_4c & 2) {
        pad_50 = 2;
    } else if (pad_4c & 4) {
        pad_50 = 3;
    } else {
        return false;
    }
    return true;
}

bool CamFree::OnMouseButtonUp(ml::EventView* view) {
    if (view->m_buttons & 4) {
        pad_4c &= ~1u;
    }
    if (view->m_buttons & 2) {
        pad_4c &= ~2u;
    }
    if (view->m_buttons & 1) {
        pad_4c &= ~4u;
    }
    pad_50 = 0;
    if (!(pad_4c & 8)) {
        return false;
    }
    if (pad_4c & 1) {
        pad_50 = 1;
    } else if (pad_4c & 2) {
        pad_50 = 2;
    } else if (pad_4c & 4) {
        pad_50 = 3;
    } else {
        return false;
    }
    return true;
}

bool CamFree::OnKeyUp(ml::EventView* view) {
    if (!(view->pad_28 & 1)) {
        return false;
    }
    pad_4c &= ~8u;
    pad_50 = 0.0f;
    return true;
}

bool CamFree::OnKeyDown(ml::EventView* view) {
    if (view->pad_28 & 1) {
        pad_4c |= 8;
    }
    if (view->pad_2c & 1) {
        switch (view->pad_33) {
        case 0x25: {
            float fov = pad_30 - 0.5f;
            if (fov < 5.0f) {
                fov = 5.0f;
            } else if (fov > 120.0f) {
                fov = 120.0f;
            }
            pad_30 = fov;
            break;
        }
        case 0x26:
            ctrlDolly(mm::Pnt<int>(0, 8));
            break;
        case 0x27: {
            float fov = pad_30 + 0.5f;
            if (fov < 5.0f) {
                fov = 5.0f;
            } else if (fov > 120.0f) {
                fov = 120.0f;
            }
            pad_30 = fov;
            break;
        }
        case 0x28:
            ctrlDolly(mm::Pnt<int>(0, -8));
            break;
        case 0x81:
            pad_34 += -0.017453292f;
            break;
        case 0x82:
            moveScreen(mm::Pnt<int>(0, -8));
            break;
        case 0x83:
            pad_34 += 0.017453292f;
            break;
        case 0x84:
            moveScreen(mm::Pnt<int>(8, 0));
            break;
        case 0x86:
            moveScreen(mm::Pnt<int>(-8, 0));
            break;
        case 0x88:
            moveScreen(mm::Pnt<int>(0, 8));
            break;
        }
    }
    return false;
}

void CamField::update(const event::FrameInfo&) {}

void CharaTurnRot::init() {}

int CharaLinerPos::update(const ICmd::Param& param) {
    if (m_ik == nullptr || m_dys == nullptr) {
        return 2;
    }
    CharaObj* chara = static_cast<CharaObj*>(param.m_param.val(0).getUserdata());
    float step = chara->m_frameInfo.m_step;
    if (param.m_frame == 0) {
        mm::Vec3 pos(param.m_param.val(1).getF32(), param.m_param.val(2).getF32(), param.m_param.val(3).getF32());
        m_anm.clear();
        m_anm.append(0.0f, chara->m_pos, static_cast<CV_TYPE>(0));
        m_anm.append(param.m_param.val(4).getF32(), pos, static_cast<CV_TYPE>(param.m_param.val(5).getS32()));
        if (m_gravity == 0) {
            CharaUtil::setGravity(chara->m_gfHandle, false);
        }
        m_ik->setFootIK(false, static_cast<CharaIKUpdater::FOOT_TYPE>(0));
        m_dys->resetMovement(0);
    }
    m_anm.update(step);
    chara->setPos(m_anm.m_value);
    if (m_anm.isPlaying()) {
        return 2;
    }
    m_anm.clear();
    return 1;
}

int CharaLinerRot::update(const ICmd::Param& param) {
    if (m_dys == nullptr) {
        return 2;
    }
    CharaObj* chara = static_cast<CharaObj*>(param.m_param.val(0).getUserdata());
    float step = chara->m_frameInfo.m_step;
    if (param.m_frame == 0) {
        mm::Vec3 from = chara->m_rot;
        mm::Vec3 rot(param.m_param.val(1).getF32(), param.m_param.val(2).getF32(), param.m_param.val(3).getF32());
        m_anm.clear();
        m_anm.append(0.0f, from, static_cast<CV_TYPE>(0));
        m_anm.append(param.m_param.val(4).getF32(), rot, static_cast<CV_TYPE>(param.m_param.val(5).getS32()));
        m_dys->resetMovement(0);
    }
    m_anm.update(step);
    chara->setRot(m_anm.m_value);
    if (m_anm.isPlaying()) {
        return 2;
    }
    m_anm.clear();
    return 1;
}

CharaPlayActionAuto::~CharaPlayActionAuto() {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj != nullptr && (m_flags & 4)) {
        if (!(m_flags & 1)) {
            const char* cmd = reinterpret_cast<const char*>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), "cmd2", 1, 7));
            const char* stat = reinterpret_cast<const char*>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), "stat2", 1, 7));
            gf::GfComEvtAnim* anim = obj->getComponent<gf::GfComEvtAnim>(2);
            if (anim != nullptr) {
                anim->execCmd(cmd);
                if (strcmp(anim->getStateName() ? anim->getStateName() : "", stat) != 0) {
                    anim->setState(stat);
                }
            }
        } else {
            gf::MsgGameTalkAction msg;
            msg.m_action = 2;
            msg.m_setState = false;
            msg.m_result = false;
            static_cast<fw::MessageObject*>(obj)->recieveMessage(obj, msg);
        }
    }
}

void CharaPlayActionAuto::init() {}

int CharaPlayActionAuto::update(const ICmd::Param& param) {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj != nullptr) {
        float step = static_cast<CharaObj*>(param.m_param.val(0).getUserdata())->m_frameInfo.m_cmdStep;
        if (param.m_frame <= 0) {
            m_time = param.m_param.val(1).getF32();
            m_flags |= 2;
        }
        if (!(m_flags & 4) && !CharaUtil::isActionBusy(obj) &&
            !mm::mtl::Singleton<ScheManager>::getPtr()->isTurnBusy(m_handle)) {
            play(obj);
            m_flags |= 4;
        }
        m_time -= step;
        if (!(m_time < 0.0f)) {
            return 0;
        }
        idle();
    }
    return 1;
}

void CharaPlayActionAuto::term() {}

void CharaPlayAction::init() {}

void CharaPlayAction::term() {
    if (m_flags & 2) {
        m_flags &= ~2;
    } else {
        idle();
    }
}

CharaPlayTalkAuto::~CharaPlayTalkAuto() {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj != nullptr && (m_flags & 5) == 5) {
        gf::MsgGameLipAction msg;
        msg.m_action = 1;
        static_cast<fw::MessageObject*>(obj)->recieveMessage(obj, msg);
    }
}

void CharaPlayTalkAuto::init() {}

void CharaPlayTalkAuto::term() {}

void CharaPlayTalk::init() {
    m_flags = 0;
    pad_68 = 1.0f;
    pad_6c = 1.0f;
    pad_70 = 0.0f;
    pad_74 = 0.0f;
}

void CharaPlayTalk::term() {
    idle();
}

int CharaPlayEvaEff::update(const ICmd::Param& param) {
    if (m_model != nullptr && gf::GfObjUtil::getObj(m_model->m_handle) != nullptr) {
        float step = static_cast<CharaObj*>(param.m_param.val(0).getUserdata())->m_frameInfo.m_step;
        if (param.m_frame <= 0) {
            const char* name =
                mm::mtl::Singleton<Extend>::getPtr()->replaceString(param.m_param.val(1).getStr(), "event", "effect");
            void* data;
            unsigned long size;
            if (!mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
                ResManager::Item* item = mm::mtl::Singleton<ResManager>::getPtr()->search(
                    mm::mtl::Singleton<Extend>::getPtr()->effeva(name));
                if (item == nullptr || item->m_data == nullptr || item->m_size == 0) {
                    return 1;
                }
                data = item->m_data;
                size = item->m_size;
            } else {
                data = mm::mtl::Singleton<MotstmManager>::getPtr()->adr(
                    mm::mtl::Singleton<Extend>::getPtr()->effeva(name), &size);
                if (data == nullptr) {
                    return 1;
                }
            }
            m_player.play(m_model, m_effectPlayer, data);
            m_time = param.m_param.val(2).getF32();
            m_data = data;
            m_flags |= 1;
            if (m_time <= 0.0f) {
                m_flags |= 2;
            } else {
                m_flags &= ~2;
            }
        }
        m_player.update(step * param.m_param.val(3).getF32());
        if (m_flags & 2) {
            return 2;
        }
        m_time -= step;
        if (!(m_time < 0.0f)) {
            return 2;
        }
        m_player.stop();
    }
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && m_data != nullptr) {
        mm::mtl::Singleton<MotstmManager>::getPtr()->free(m_data);
    }
    m_data = nullptr;
    m_flags &= ~1;
    return 1;
}

void CharaPlayEvaEff::term() {
    if (m_flags & 1) {
        if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && m_data != nullptr) {
            mm::mtl::Singleton<MotstmManager>::getPtr()->free(m_data);
        }
        m_data = nullptr;
        m_flags &= ~1;
    }
}

void CharaHideWpn::term() {
    if (m_flags & 4) {
        ObjectList* scene = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
        if (scene != nullptr && scene->m_categories[0] != nullptr) {
            unsigned int id = m_id;
            for (Object* obj = scene->m_categories[0]->m_child; obj != nullptr; obj = obj->m_next) {
                if (obj->m_type == 2) {
                    gf::GfObjAcc acc(static_cast<ObjectChara*>(obj)->m_chara->m_gfHandle);
                    if (acc.getType() == 3 && acc.getBdatId() == id) {
                        static_cast<ObjectChara*>(obj)->m_chara->setHideWeapon(static_cast<WPNHIDEID>(2), false,
                                                                                m_flags & 2);
                        break;
                    }
                }
            }
        }
        m_flags &= ~4u;
    }
}

void CharaWinkPlayer::idle_start() {
    m_count = ml::mtRand(60) + 90;
    m_state = &CharaWinkPlayer::idle_waiting;
}

void CharaWinkPlayer::idle_waiting() {
    if (m_flags & 1) {
        return;
    }
    if (m_count-- > 0) {
        return;
    }
    m_weightPlayer->easeIn(static_cast<gf::AnimLayer>(3), "S_eye_close", 4.0f, 1.0f, 1.0f, static_cast<CV_TYPE>(1),
                           static_cast<WeightLayer>(1));
    m_stateName = "close";
    m_state = &CharaWinkPlayer::idle_wink;
    m_count = 7;
}

void CharaMount::init() {}

// undoes the mount: the model leaves its parent and gets its saved transform back
void CharaMount::term() {
    if (m_model && m_parent) {
        gf::GfComTransform* transform = gf::GfObjUtil::getObj(m_model->m_handle)->getComponent<gf::GfComTransform>(0);
        m_model->resetMount(m_parent);
        transform->setPosition(m_pos);
        transform->setRotation(m_rot);
        m_parent = nullptr;
    }
}

int CharaFade::update(const ICmd::Param& param) {
    float step = static_cast<CharaObj*>(param.m_param.val(0).getUserdata())->m_frameInfo.m_step;
    if (param.m_frame == 0) {
        float from = 1.0f;
        if (m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_handle);
            from = acc.getAlphaEvent();
        }
        float to = param.m_param.val(1).getBool() ? 0.0f : 1.0f;
        float time = param.m_param.val(2).getF32();
        m_anm.clear();
        m_anm.append(0.0f, from, static_cast<CV_TYPE>(0));
        m_anm.append(time, to, static_cast<CV_TYPE>(1));
    }
    m_anm.update(step);
    if (m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(m_handle, static_cast<ALPHA_ATTR>(1), m_anm.m_value, 1.0f);
    }
    if (m_anm.isPlaying()) {
        return 2;
    }
    m_anm.clear();
    if (m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(m_handle, static_cast<ALPHA_ATTR>(1),
                                                             param.m_param.val(1).getBool() ? 0.0f : 1.0f, 1.0f);
    }
    return 1;
}

void BlurManager::OnEventProc(event::MSG_TYPE) {}

EffectEvaPlayer::~EffectEvaPlayer() {
    if (m_rcha) {
        delete m_rcha;
        m_rcha = nullptr;
    }
    m_ctrl = nullptr;
}

void EffectPlayEff::term() {
    pad_20 = -1.0f;
}

void AnmVec::update(float step) {
    AnmBase::update(step);
    if (pad_8 & 2) {
        mm::Vec3& value = m_value;
        mm::Vec3 result = calcEvalute(pad_68, pad_70);
        if (&value != &result) {
            value = result;
        }
    }
}

void AnmF32::update(float step) {
    AnmBase::update(step);
    if (pad_8 & 2) {
        m_value = calcEvalute(pad_68, pad_70);
    }
}

void AnmCol::update(float step) {
    AnmBase::update(step);
    if (pad_8 & 2) {
        m_value = calcEvalute(pad_68, pad_70);
    }
}

mm::Vec3 DataManager::axis2rot(unsigned int type, float x, float y, float z, const mm::Vec3& pos) {
    if (type < 4) {
        return mm::Vec3(x, getRotOfsY(type, pos) + y, z);
    }
    ObjectList* list;
    if (type < ((list = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current) ? list->m_counts[0] + 4ul : 4)) {
        return mm::Vec3(x, getRotOfsY(type, pos) + y, z);
    }
    return mm::Vec3(x, y, z);
}

int EffectLinearCol::update(const ICmd::Param& param) {
    if (m_ctrl == nullptr) {
        return 1;
    }
    EffectObj* obj = static_cast<EffectObj*>(param.m_param.val(0).getUserdata());
    float step = obj->m_step;
    if (param.m_frame == 0) {
        mm::Col4 color(param.m_param.val(1).getF32(), param.m_param.val(2).getF32(), param.m_param.val(3).getF32(),
                       param.m_param.val(4).getF32());
        m_anm.clear();
        m_anm.append(0.0f, obj->m_ctrl.m_color, static_cast<CV_TYPE>(0));
        m_anm.append(param.m_param.val(5).getF32(), color, static_cast<CV_TYPE>(param.m_param.val(6).getS32()));
    }
    m_anm.update(step);
    m_ctrl->m_color = m_anm.m_value;
    if (m_anm.isPlaying()) {
        return 2;
    }
    m_anm.clear();
    return 1;
}

int EffectPlayEva::update(const ICmd::Param& param) {
    if (m_ctrl != nullptr) {
        float step = static_cast<EffectObj*>(param.m_param.val(0).getUserdata())->m_step;
        if (param.m_frame <= 0) {
            const char* name = param.m_param.val(1).getStr();
            void* data;
            unsigned long size;
            if (!(mm::mtl::Singleton<EffectManager>::getPtr()->m_flags & 1)) {
                ResManager::Item* item = mm::mtl::Singleton<ResManager>::getPtr()->search(
                    mm::mtl::Singleton<Extend>::getPtr()->eva(name));
                if (item == nullptr || item->m_data == nullptr || item->m_size == 0) {
                    return 1;
                }
                data = item->m_data;
                size = item->m_size;
            } else {
                data = mm::mtl::Singleton<MotstmManager>::getPtr()->adr(
                    mm::mtl::Singleton<Extend>::getPtr()->eva(name), &size);
                if (data == nullptr) {
                    return 1;
                }
            }
            m_player.play(m_ctrl, data);
            m_time = param.m_param.val(2).getF32();
            m_data = data;
        }
        m_player.update(step);
        m_time -= step;
        if (!(m_time < 0.0f)) {
            return 2;
        }
    }
    m_player.stop();
    if ((mm::mtl::Singleton<EffectManager>::getPtr()->m_flags & 1) && m_data != nullptr) {
        mm::mtl::Singleton<MotstmManager>::getPtr()->free(m_data);
    }
    m_data = nullptr;
    return 1;
}

void EffectPlayEva::term() {
    if ((mm::mtl::Singleton<EffectManager>::getPtr()->m_flags & 1) && m_data != nullptr) {
        mm::mtl::Singleton<MotstmManager>::getPtr()->free(m_data);
    }
    m_data = nullptr;
}

int EffectLinearRot::update(const ICmd::Param& param) {
    if (m_ctrl == nullptr) {
        return 1;
    }
    EffectObj* obj = static_cast<EffectObj*>(param.m_param.val(0).getUserdata());
    float step = obj->m_step;
    if (param.m_frame == 0) {
        mm::Vec3 rot(param.m_param.val(1).getF32(), param.m_param.val(2).getF32(), param.m_param.val(3).getF32());
        m_anm.clear();
        m_anm.append(0.0f, obj->m_ctrl.m_rot, static_cast<CV_TYPE>(0));
        m_anm.append(param.m_param.val(4).getF32(), rot, static_cast<CV_TYPE>(param.m_param.val(5).getS32()));
    }
    m_anm.update(step);
    m_ctrl->m_rot = m_anm.m_value;
    if (m_anm.isPlaying()) {
        return 2;
    }
    m_anm.clear();
    return 1;
}

int EffectLinearPos::update(const ICmd::Param& param) {
    if (m_ctrl == nullptr) {
        return 1;
    }
    EffectObj* obj = static_cast<EffectObj*>(param.m_param.val(0).getUserdata());
    float step = obj->m_step;
    if (param.m_frame == 0) {
        mm::Vec3 pos(param.m_param.val(1).getF32(), param.m_param.val(2).getF32(), param.m_param.val(3).getF32());
        m_anm.clear();
        m_anm.append(0.0f, obj->m_ctrl.m_pos, static_cast<CV_TYPE>(0));
        m_anm.append(param.m_param.val(4).getF32(), pos, static_cast<CV_TYPE>(param.m_param.val(5).getS32()));
    }
    m_anm.update(step);
    m_ctrl->m_pos = m_anm.m_value;
    if (m_anm.isPlaying()) {
        return 2;
    }
    m_anm.clear();
    return 1;
}

void FormManager::OnEventProc(event::MSG_TYPE) {}

void MercenariesManager::OnEventProc(event::MSG_TYPE) {}

BouRect::~BouRect() {}

void ObjectCamera::start() {}

void ObjectEffect::start() {}

void CopydataManager::OnEventProc(event::MSG_TYPE) {}

void ScriptCharaMotion::undo(const event::Param&) {}

void ScriptCharaMotionABC::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->playMotionABC(param.val(0).getStr(), param.val(1).getStr(), param.val(2).getStr(),
                                    param.val(3).getF32(), param.val(4).getF32(), param.val(5).getF32(),
                                    param.val(6).getF32(), param.val(7).getF32(), param.val(8).getF32());
    }
}

void ScriptCharaMotionABC::undo(const event::Param&) {}

void FrameManager::setSkipAbleFrame(float frame) {
    m_skipAbleFrame = frame;
    pad_15c = pad_160 + frame;
}

SkipManager::~SkipManager() {}

const char* AgelogManager::LOG_DIR = "C:/MonolithSoft/BF2/agelog";

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void AgelogManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 7:
        if (m_flags.test(0) && !m_flags.test(1)) {
            m_flags.set(1, true);
            if (m_path.m_str[0] == '\0') {
                char date[0x40];
                mlGetDateName(date, sizeof(date));
                m_path.format("%s/%s/agelog_%s.txt", LOG_DIR, "nx", date);
            }
        }
        break;
    case 10:
        if (m_flags.test(1)) {
            m_flags.set(1, false);
        }
        break;
    case 12:
        m_flags.set(1, false);
        break;
    case 17:
        render();
        break;
    }
}

mm::mtl::FixStr<256> AgelogUtil::s_path;

const mm::Vec2 CharaSetTar::LENS_LIMIT(10.0f * (3.14f / 180.0f), 30.0f * (3.14f / 180.0f));
const mm::Vec2 CharaSetTar::JOY_LIMIT(10.0f * (3.14f / 180.0f), 15.0f * (3.14f / 180.0f));

// the colour FadeManager::playEventSkip and FadeCtrl::fadeoutEventSkip/fadeinEventSkip fade through
static const mm::Col4 s_skipFadeColor(0.0f, 0.0f, 0.0f, 1.0f);

const mm::mtl::FixStr<32> ShakeManager::s_names[4] = {mm::mtl::FixStr<32>("TYPE_SS"), mm::mtl::FixStr<32>("TYPE_S"), mm::mtl::FixStr<32>("TYPE_M"),
                                                 mm::mtl::FixStr<32>("TYPE_L")};

Param TodoManager::s_zero;

mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> ObjectPartyList::s_drlist;
mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> ObjectPartyList::s_bllist;


// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void OffscrManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 12) {
        clear();
    }
}

}  // namespace event

#include "classes/event/StmManager.h"
#include "classes/event/MdlstmObj.h"
#include "classes/event/IStmMemory.h"
#include "classes/event/MdlstmManager.h"
#include "classes/event/AlphaManager.h"
#include "classes/event/Extend.h"
#include "classes/event/ModelManager.h"

namespace event {

StmManager::~StmManager() {
    if (m_stm != nullptr) {
        delete m_stm;
        m_stm = nullptr;
    }
}

// the table store stays: the body is not empty
MdlstmObj::~MdlstmObj() {
    ;
}

// fades the built model out, destroys both models, releases the reader and clears the object
void MdlstmObj::finishFree() {
    if (m_buildModel != nullptr) {
        mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(m_buildModel->m_handle, ALPHA_ATTR(2), 0.0f, 1.0f);
        if (m_buildModel != nullptr) {
            mm::mtl::Singleton<ModelManager>::getPtr()->destroyModel(m_buildModel, m_user);
            m_buildModel = nullptr;
        }
    }
    if (m_model != nullptr) {
        mm::mtl::Singleton<ModelManager>::getPtr()->destroyModel(m_model, m_user);
        m_model = nullptr;
    }
    pad_b0 = 0;
    pad_b8 = 0;
    pad_c0 = 0;
    pad_c8 = 0;
    if (m_reader != nullptr) {
        m_reader->release();
        m_reader = nullptr;
    }
    pad_e8 = 0;
    m_id = 0;
    m_flags.reset();
    m_state = 0;
    m_frame = 0.0f;
    m_name.clear();
    m_type = MODEL_TYPE();
    pad_9c = 0;
    m_option.bladeId = 0;
    m_option.left = false;
    m_option.bladeFlag = false;
}

// 1.0.0's ModelObj::isBusy: pad_8's bits 2-3, a running wait, or the game model still loading
inline bool ModelObj::isBusy() const {
    if (pad_8 & 0xc) {
        return true;
    }
    if (m_busyWait >= 0) {
        return true;
    }
    if (m_model != nullptr && m_model->isBusy(nullptr)) {
        return true;
    }
    return false;
}

// steps the object through its states: load at its frame, model once both files are in, delay, busy, free
void MdlstmObj::exec(float frame, float loadFrame) {
    if (m_state == 2) {
        if (m_type != 0) {
            if (m_frame <= loadFrame) {
                finishLoad();
            }
        } else if (m_name.m_str[0] != '\0') {
            finishLoad();
        }
    }
    if (m_state == 3) {
        if ((m_model != nullptr && !m_model->isBusy()) || (m_flags.test(3) && m_flags.test(4))) {
            finishLoaded();
        }
    }
    if (m_state == 4) {
        if (m_frame <= frame) {
            finishModel();
        }
    }
    if (m_state == 5) {
        if (pad_e8-- <= 0) {
            finishDelay();
        }
    }
    if (m_state == 6) {
        if (!m_buildModel->isBusy()) {
            finishBusy();
        }
    }
    if (m_state == 9) {
        if (pad_e8-- <= 0) {
            finishFree();
        }
    }
    if (m_buildModel != nullptr && m_state < 7 && !m_buildModel->isBusy()) {
        mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(m_buildModel->m_handle, ALPHA_ATTR(2), 0.0f, 1.0f);
    }
}

void MdlstmObj::init(float frame, const char* name, unsigned int id, bool flag, int user) {
    m_flags.set(0);
    m_frame = frame;
    m_name = name;
    m_option.bladeFlag = flag;
    m_type = MODEL_TYPE();
    pad_9c = 0;
    m_option.bladeId = 0;
    m_option.left = false;
    m_id = id;
    pad_b0 = 0;
    pad_c0 = 0;
    m_buildModel = nullptr;
    pad_e8 = 0;
    m_user = user;
    m_state = 1;
    MdlstmData::Info info;
    if (mm::mtl::Singleton<MdlstmData>::getPtr()->getReplaceInfo(info, m_name.m_str)) {
        m_type = info.m_type;
        pad_9c = info.m_id;
        m_option.bladeId = info.m_bladeId;
        m_option.left = info.m_left;
    }
}

ModelObj* MdlstmObj::build() {
    if (m_state == 2) {
        finishLoad();
    }
    if (m_state == 3) {
        finishLoaded();
    }
    if (m_state == 4) {
        finishModel();
    }
    if (m_state == 5) {
        finishDelay();
    }
    if (m_state == 6) {
        finishBusy();
    }
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(m_buildModel->m_handle, ALPHA_ATTR(2), 1.0f, 1.0f);
    if (mm::mtl::Singleton<MdlstmManager>::getPtr()->pad_14 & 1) {
        mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(m_buildModel->m_handle, ALPHA_ATTR(1), 1.0f, 1.0f);
    }
    m_state = 8;
    return m_buildModel;
}

// mdo and arc: a loaded file named as the model's mdo sets bit 3, as its arc bit 4
void MdlstmObj::OnResEvent(const IResEvent::PARAM& param) {
    if (strcmp(param.m_name, mm::mtl::Singleton<Extend>::getPtr()->mdo(m_name.m_str)) == 0) {
        m_flags.set(3);
        m_flags.reset(1);
    } else if (strcmp(param.m_name, mm::mtl::Singleton<Extend>::getPtr()->arc(m_name.m_str)) == 0) {
        m_flags.set(4);
        m_flags.reset(2);
    }
}

void MdlstmManager::clear() {
    mm::mtl::Singleton<MdlstmData>::getPtr()->clear();
    for (unsigned int i = 0; i < m_active.size(); i++) {
        m_active[i]->dispose();
    }
    for (unsigned int i = 0; i < m_active.size(); i++) {
        m_active[i]->finishFree();
    }
    m_active.clear();
    pad_3c018 = 0;
    pad_3e028 = 0;
    pad_3e02c = 0;
    pad_3e030 = 0;
    pad_10 = 0;
    pad_14 = 0;
}

// bit 2 of m_flags enables it (2.0.0's setSkipFastEnable); the debug flags 5 and 6 can turn it off
bool SkipManager::isSkipFast() const {
    if ((m_flags & 4) &&
        (!mm::mtl::Singleton<DebugManager>::getPtr()->testFlag(5) ||
         mm::mtl::Singleton<DebugManager>::getPtr()->testFlag(6)) &&
        isSkip()) {
        return true;
    }
    return false;
}

// the next object's frame after `frame` (the last loaded one's when none is earlier)
float MdlstmManager::getNextCutFrame(float frame) {
    if (pad_3c018 == 0) {
        return frame;
    }
    float next = m_objs[pad_3c018 - 1].m_frame;
    for (unsigned int i = 0; i < pad_3c018; i++) {
        if (m_active[i]->m_frame > frame && m_active[i]->m_frame < next) {
            next = m_active[i]->m_frame;
        }
    }
    return next;
}

// m_active stays sorted by frame: the new object goes in front of the first later one
void MdlstmManager::load(float frame, const char* name, unsigned int id, bool flag) {
    if (!(pad_10 & 1)) {
        return;
    }
    MdlstmObj* obj = &m_objs[pad_3c018++];
    obj->init(frame, name, id, flag, pad_3e030);
    for (unsigned int i = 0; i < m_active.size(); i++) {
        if (m_active[i]->m_frame <= obj->m_frame) {
            continue;
        }
        for (; i < m_active.size(); i++) {
            MdlstmObj* next = m_active[i];
            m_active[i] = obj;
            obj = next;
        }
    }
    m_active.push_back(obj);
}

ModelObj* MdlstmManager::build(const char* name, unsigned int id) {
    for (unsigned int i = 0; i < pad_3e028; i++) {
        if (m_active[i]->isBuildable(name, id)) {
            return m_active[i]->build();
        }
    }
    return nullptr;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void MdlstmManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 14) {
        update();
    } else if (msg == 12) {
        clear();
    }
}

}  // namespace event

#include "classes/event/MotstmManager.h"
#include "classes/event/FrameManager.h"

namespace event {

// 1.0.0's StmManager::destroy
inline void StmManager::destroy() {
    if (m_stm != nullptr) {
        delete m_stm;
        m_stm = nullptr;
    }
    pad_8 = 0;
}

// 1.0.0's MotstmManager::clear
inline void MotstmManager::clear() {
    m_stmManager.destroy();
    m_flags.reset();
}

// 1.0.0's MotstmManager::render: only the FrameManager lookup is left of it (what used it is compiled out)
inline void MotstmManager::render() {
    if (m_flags.test(0) && (m_dispFlags & 1)) {
        mm::mtl::Singleton<FrameManager>::getPtr();
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void MotstmManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 14) {
        update();
    } else if (msg == 12) {
        clear();
    } else if (msg == 16) {
        render();
    }
}

MotstmManager::~MotstmManager() {}

MstxtRes::MstxtRes(const char* name) : m_flags(0), m_name(name) {
    m_fileName = mm::mtl::Singleton<Extend>::getPtr()->filename(name);
    m_fileName += "_ms";
    mm::mtl::FixStr<64> path;
    path.format("bdat/%s/%s.bdat", fw::LangUtil::getLangFolder().m_str, m_fileName.m_str);
    mm::mtl::Singleton<ResManager>::getPtr()->load(path.m_str, this, false);
    m_flags |= 1;
}

MstxtRes::~MstxtRes() {
    if (m_flags & 4) {
        gf::GfMenuObjEventSubtitle::endText();
        fw::BdatManager::unregistBdat(2);
        m_flags &= ~4;
    }
}

void MstxtRes::OnResEvent(const IResEvent::PARAM& param) {
    if (param.m_type == 3) {
        m_flags |= 2;
    } else if (param.m_type == 4) {
        mm::mtl::PtrSingleton<Manager>::sys()->failureSkip();
    }
    m_flags &= ~1;
}

void Manager::failureSkip() {
    mm::mtl::Singleton<DebugManager>::getPtr()->setFlag(8);
    mm::mtl::Singleton<DebugManager>::getPtr()->setFlag(0);
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("failure skip!! [%s.sb]", m_eventName.m_str);
}

void MstxtManager::load(const char* name) {
    MstxtRes* found = nullptr;
    for (unsigned long i = 0; i < m_res.size(); i++) {
        if (strcmp(name, m_res[i]->m_name.m_str) == 0) {
            found = m_res[i];
            break;
        }
    }
    if (found != nullptr) {
        return;
    }
    m_res.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) MstxtRes(name));
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void MstxtManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 12) {
        clear();
    }
}

void LipsyncRes::OnResEvent(const IResEvent::PARAM& param) {
    if (param.m_type == 3) {
        m_arc.setData(param.m_data);
        m_flags |= 2;
    } else {
        m_flags &= ~2;
    }
    m_flags &= ~1;
}

void LipsyncManager::load(const char* name) {
    LipsyncRes* found = nullptr;
    for (unsigned long i = 0; i < m_res.size(); i++) {
        if (strcmp(name, m_res[i]->m_name.m_str) == 0) {
            found = m_res[i];
            break;
        }
    }
    if (found != nullptr) {
        return;
    }
    m_res.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) LipsyncRes(name));
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void LipsyncManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 4) {
        clear();
    } else if (msg == 12) {
        clear();
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void EvtxtManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 17) {
        render();
    }
}

}  // namespace event

// the MstxtRes constructor's (not written yet) and the other 27 callers' text formatting
template mm::mtl::FixStr<64>& mm::mtl::FixStr<64>::format(const char* format, ...);

#include "classes/event/Extend.h"

namespace event {

const char* Extend::mdo(const char* pszName) {
    m_path = pszName;
    m_path += ".wimdo";
    return m_path.m_str;
}

const char* Extend::arc(const char* pszName) {
    m_path = pszName;
    m_path += ".arc";
    return m_path.m_str;
}

const char* Extend::anm(const char* pszName) {
    m_path = pszName;
    m_path += ".anm";
    return m_path.m_str;
}

const char* Extend::eva(const char* pszName) {
    m_path = pszName;
    m_path += ".eva";
    return m_path.m_str;
}

const char* Extend::effeva(const char* pszName) {
    m_path = pszName;
    m_path += "_eff.eva";
    return m_path.m_str;
}

const char* Extend::lgt(const char* pszName) {
    m_path = pszName;
    m_path += ".wilgt";
    return m_path.m_str;
}

const char* Extend::wav(const char* pszName) {
    m_path = pszName;
    m_path += ".nop";
    return m_path.m_str;
}

const char* Extend::evpa(const char* pszName) {
    m_path = pszName;
    m_path += ".evpa";
    return m_path.m_str;
}

const char* Extend::webm(const char* pszName) {
    m_path = pszName;
    m_path += ".webm";
    return m_path.m_str;
}

const char* Extend::filename(const char* pszPath) {
    const char* p = strrchr(pszPath, '\\');
    if (p != nullptr) {
        return p + 1;
    }
    p = strrchr(pszPath, '/');
    if (p != nullptr) {
        return p + 1;
    }
    return pszPath;
}

const char* Extend::replaceString(const char* str, const char* from, const char* to) {
    // the buffer's name is not the original's
    static char s_buf[256];
    memset(s_buf, 0, sizeof(s_buf));
    char* dst = s_buf;
    while (*str != '\0') {
        if (memcmp(str, from, strlen(from)) == 0) {
            memcpy(dst, to, strlen(to));
            str += strlen(from);
            dst += strlen(to);
        } else {
            *dst++ = *str++;
        }
    }
    return s_buf;
}

PosAxis::PosAxis() : m_type(1), m_value(mm::Vec3::zero) {}

RotAxis::RotAxis() : m_type(1), m_value(mm::Vec3::zero) {}

TarAxis::TarAxis() : m_type(1), m_value(mm::Vec3::zero) {}

void ParamVariable::setS32(int value) {
    m_type = 1;
    m_value.intValue = value;
}

void ParamVariable::setF32(float value) {
    m_type = 2;
    m_value.floatValue = value;
}

void ParamVariable::setBool(bool value) {
    m_type = 3;
    m_value.boolValue = value;
}

void ParamVariable::setStr(const char* value) {
    m_type = 4;
    m_value.strValue = value;
}

void ParamVariable::setUserdata(void* value) {
    m_type = 5;
    m_value.userdata = value;
}

ParamVariable& Param::val(unsigned int i) {
    return m_vals[i];
}

void Param::createString(mm::mtl::FixStr<256>& str) {
    str = "";
    for (int i = 0; i < 10; i++) {
        mm::mtl::FixStr<256> s;
        m_vals[i].createString(s);
        str += s.m_str;
        str += " ";
    }
}

}  // namespace event

#include "classes/event/HideManager.h"
#include "classes/event/SelectManager.h"
#include "classes/event/FrameManager.h"
#include "classes/event/SkipManager.h"
#include "classes/event/DebugManager.h"
#include "classes/event/CharaSetIdle.h"
#include "classes/event/CharaPlayHead.h"
#include "classes/event/CharaPlayFacial.h"
#include "classes/event/CharaPlayWink.h"
#include "classes/event/Object.h"
#include "classes/event/LightObj.h"
#include "classes/event/LightEvt.h"
#include "classes/event/ObjectLight.h"
#include "classes/event/ObjectCamera.h"

namespace event {

void HideManager::defineGroup(GRP_TYPE group) {
    m_group = group;
}

HideManager::GRP_TYPE HideManager::getGroup() const {
    return m_group;
}

LightEvt::~LightEvt() {
    if (m_lgt) {
        mm::mtl::PtrSingleton<Manager>::sys()->m_scn->releaseItem(m_lgt);
        m_lgt = nullptr;
    }
    m_name.clear();
    m_lgtParam = 0;
}

LightObj::~LightObj() {
    clear();
}

SelectManager::~SelectManager() {}

int SelectManager::getResult() const {
    return m_result;
}

float FrameManager::getFrame() const {
    return m_frame;
}

float FrameManager::getMaxFrame() const {
    return m_maxFrame;
}

bool SkipManager::isSkip() const {
    return m_flags & 1;
}

void DebugManager::playMessage(const char* format, ...) {
    char buffer[512];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    m_message = buffer;
    m_messageTime = 90;
    m_flags |= 2;
}

bool DebugManager::isMovieDebug() const {
    return (m_flags >> 16) & 1;
}

void CharaSetTar::term() {
    if (m_flags & 1) {
        idle();
        m_flags &= ~1;
    }
}

void CharaSetIdle::init() {
    m_step = 0;
}

void CharaPlayHead::init() {
    m_step = 0;
}

void CharaPlayHead::term() {
    idle();
}

void CharaPlayFacial::init() {
    m_step = 0;
}

void CharaPlayFacial::term() {
    idle();
}

void CharaPlayWink::init() {
    m_step = 0;
}

ObjectChara* ObjectManager::getChara(unsigned int id) {
    updateCurrent();
    Object* category = m_current->m_categories[0];
    if (category) {
        for (Object* obj = category->m_child; obj; obj = obj->m_next) {
            if (id-- == 0) {
                return static_cast<ObjectChara*>(obj);
            }
        }
    }
    return nullptr;
}

void CharaPlayWink::term() {
    idle();
}

ObjectLight::~ObjectLight() {
    if (m_light) {
        delete m_light;
        m_light = nullptr;
    }
}

void ObjectLight::play(const char* name, float frame) {
    m_light->play(name, frame);
}

ObjectCamera::ObjectCamera(const char* name, unsigned int id)
    : Object(static_cast<OBJTYPE>(3), name), m_cam(nullptr), pad_70(id), pad_4e0(0), pad_4e4(0) {
    CamObj* cam = mm::mtl::Singleton<CamManager>::getPtr()->createCam(id);
    m_cam = cam;
    mm::Vec3 pos = cam->m_pos;
    m_pos.m_type = 1;
    m_pos.m_value = pos;
    mm::Vec3 tar = cam->m_tar;
    m_tar.m_type = 1;
    m_tar.m_value = tar;
}

// the camera is removed from CamManager's list (the current one cleared while its pad_64 is 0) and deleted
ObjectCamera::~ObjectCamera() {
    CamManager* mgr = mm::mtl::Singleton<CamManager>::getPtr();
    CamObj* cam = m_cam;
    for (CamObj** it = mgr->m_list.m_cams.begin(); it != mgr->m_list.m_cams.end(); ++it) {
        if (*it == cam) {
            if (cam->pad_64 == 0) {
                mgr->m_cur = nullptr;
            }
            delete cam;
            mgr->m_list.m_cams.erase(it);
            break;
        }
    }
    m_cam = nullptr;
}

void ObjectCamera::end() {
    if (m_cam) {
        m_cam->end();
    }
}

void ObjectCamera::render(const mm::Col4&) {
    SeqManager::getPtr();
}

void ObjectCamera::tail() {
    m_cam->tail();
}

bool ObjectCamera::OnBouRectSelect(const IBouCallback::SelectParam&) {
    return false;
}

void ObjectCamera::OnBouRender(const IBouCallback::RenderParam&) {
    if (SeqManager::getPtr()->pad_276c < 3 && pad_70 == 0) {
        int x = ml::DevGraph::getRootWidth() - 415;
        CamObj* cam = m_cam;
        const mm::Vec3& pos = cam->m_pos;
        const mm::Vec3& tar = cam->m_tar;
        float dx = tar.x - pos.x;
        float dy = tar.y - pos.y;
        float dz = tar.z - pos.z;
        mm::Vec3 rot;
        rot.y = -atan2f(dx, -dz);
        rot.x = atan2f(dy, sqrtf(dx * dx + dz * dz));
        rot.z = cam->m_rotZ;
        ObjectUtil::drawCameraInfo(x, 120, pos, tar, rot, m_cam->m_fov, m_cam->pad_8);
    }
}

void ObjectCamera::OnManiRender(IManiCallback::RenderParam&) {
    SeqManager::getPtr();
}

// the party leader's driver row: 1 while the event has no party (or the leader slot is empty)
unsigned int ObjectPartyList::getLeaderDriverId() const {
    if (s_drlist.empty()) {
        return 1;
    }
    gf::GF_OBJ_HANDLE* leader = s_drlist[0];
    if (leader == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return 1;
    }
    return gf::GfObjAcc(leader).getBdatId();
}

Object::~Object() {
    Object* child = m_child;
    while (child) {
        Object* next = child->m_next;
        delete child;
        child = next;
    }
}

ObjectTree::~ObjectTree() {}

Object* Object::searchByPath(const char* path) {
    unsigned long len = strlen(m_name.m_str);
    if (len <= strlen(path) && memcmp(path, m_name.m_str, len) == 0) {
        if (strcmp(path, m_name.m_str) == 0) {
            return this;
        }
        char buf[512];
        char* rest = nullptr;
        strcpy(buf, path);
        strtok_r(buf, "/", &rest);
        for (Object* child = m_child; child; child = child->m_next) {
            Object* found = child->searchByPath(rest);
            if (found) {
                return found;
            }
        }
    }
    return nullptr;
}

void CamHands::update(const FrameInfo& info) {
    float step = info.m_step;
    if (m_flags & 1) {
        calcFollowPos();
    }
    if (m_anmPos.pad_8 & 2) {
        m_anmPos.update(step);
        pad_10 = m_anmPos.m_value;
    }
    if (m_flags & 6) {
        calcFollowTar();
    }
    if (m_anmTar.pad_8 & 2) {
        m_anmTar.update(step);
        pad_20 = m_anmTar.m_value;
    }
    if (m_anmFov.pad_8 & 2) {
        m_anmFov.update(step);
        pad_30 = m_anmFov.m_value;
    }
    if (m_anmRotZ.pad_8 & 2) {
        m_anmRotZ.update(step);
        pad_34 = m_anmRotZ.m_value;
    }
}

void CamHands::setPos(PosAxis const& pos, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(pos.m_type, pos.m_value.x, pos.m_value.y,
                                                                           pos.m_value.z);
    pad_10 = value;
    m_anmPos.clear();
    m_anmPos.append(0.0f, value, static_cast<CV_TYPE>(0));
    m_anmPos.pad_58 = type;
    m_posKeys.clear();
    m_posKeys.push_back(pos);
}

void CamHands::addAnmPos(float time, PosAxis const& pos, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(pos.m_type, pos.m_value.x, pos.m_value.y,
                                                                           pos.m_value.z);
    m_anmPos.append(time, value, type);
    m_posKeys.push_back(pos);
}

void CamHands::insertAnmPos(unsigned long index, PosAxis const& pos) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(pos.m_type, pos.m_value.x, pos.m_value.y,
                                                                           pos.m_value.z);
    if (index < m_anmPos.m_values.size()) {
        m_anmPos.m_values.begin()[index] = value;
    }
    if (index < m_posKeys.size()) {
        m_posKeys.begin()[index] = pos;
    }
}

void CamHands::setTar(TarAxis const& tar, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    const mm::Vec3& pos = pad_10;
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2tar(tar.m_type, tar.m_value.x, tar.m_value.y,
                                                                           tar.m_value.z, pos);
    pad_20 = value;
    m_anmTar.clear();
    m_anmTar.append(0.0f, value, static_cast<CV_TYPE>(0));
    m_anmTar.pad_58 = type;
    m_tarKeys.clear();
    m_tarKeys.push_back(tar);
    bool follow = tar.m_type == 4 || tar.m_type == 5;
    if (follow) {
        m_flags |= 4;
    } else {
        m_flags &= ~4;
    }
}

void CamHands::addAnmTar(float time, TarAxis const& tar, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    const mm::Vec3& pos = pad_10;
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2tar(tar.m_type, tar.m_value.x, tar.m_value.y,
                                                                           tar.m_value.z, pos);
    m_anmTar.append(time, value, type);
    m_tarKeys.push_back(tar);
    bool follow = tar.m_type == 4 || tar.m_type == 5;
    if (follow) {
        m_flags |= 4;
    } else {
        m_flags &= ~4;
    }
}

void CamHands::insertAnmTar(unsigned long index, TarAxis const& tar) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    const mm::Vec3& pos = pad_10;
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2tar(tar.m_type, tar.m_value.x, tar.m_value.y,
                                                                           tar.m_value.z, pos);
    if (index < m_anmTar.m_values.size()) {
        m_anmTar.m_values.begin()[index] = value;
    }
    if (index < m_tarKeys.size()) {
        m_tarKeys.begin()[index] = tar;
    }
    bool follow = tar.m_type == 4 || tar.m_type == 5;
    if (follow) {
        m_flags |= 4;
    } else {
        m_flags &= ~4;
    }
}

void CamHands::setFov(float fov, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    pad_30 = fov;
    m_anmFov.clear();
    m_anmFov.append(0.0f, fov, static_cast<CV_TYPE>(0));
    m_anmFov.pad_58 = type;
    pad_a70.clear();
    pad_a70.push_back(fov);
}

void CamHands::addAnmFov(float time, float fov, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_anmFov.append(time, fov, type);
    pad_a70.push_back(fov);
}

void CamHands::setRotZ(float rotZ, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    pad_34 = rotZ;
    m_anmRotZ.clear();
    m_anmRotZ.append(0.0f, rotZ, static_cast<CV_TYPE>(0));
    m_anmRotZ.pad_58 = type;
    pad_ab8.clear();
    pad_ab8.push_back(rotZ);
}

void CamHands::addAnmRotZ(float time, float rotZ, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_anmRotZ.append(time, rotZ, type);
    pad_ab8.push_back(rotZ);
}

CamMotion::~CamMotion() {
    stop();
}

void CamMotion::update(const FrameInfo& info) {
    if (pad_40 & 2) {
        m_player.update(info.m_step);
    }
    if (pad_40 & 4) {
        m_playerEff.update(info.m_step);
    }
}

// the interface is pushed onto its camera layer when enabled, popped when disabled (only on a change)
int CamObj::SetEnable::update(const ICmd::Param& param) {
    unsigned int index = param.m_param.val(0).getS32();
    bool enable = param.m_param.val(1).getBool();
    CamInterface* cam = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[index];
    if (enable) {
        if (!cam->pad_ac) {
            (fw::CameraManager::get()->m_layers + static_cast<unsigned int>(cam->m_type))->push(cam->m_self, 0.0f);
        }
        cam->pad_ac = true;
    } else {
        if (cam->pad_ac) {
            (fw::CameraManager::get()->m_layers + static_cast<unsigned int>(cam->m_type))->pop(cam->m_self, 0.0f);
        }
        cam->pad_ac = false;
    }
    return 1;
}

int CamObj::SetTargetPos::update(const ICmd::Param& param) {
    unsigned int index = param.m_param.val(0).getS32();
    mm::Vec3 pos(param.m_param.val(1).getF32(), param.m_param.val(2).getF32(), param.m_param.val(3).getF32());
    mm::Vec3 tar(param.m_param.val(4).getF32(), param.m_param.val(5).getF32(), param.m_param.val(6).getF32());
    float roll = param.m_param.val(7).getF32();
    CamInterface* cam = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[index];
    cam->pad_b0 = roll;
    cam->setLookAt(pos, tar, roll);
    return 1;
}

// the angle is converted from a focal length (mm, 25.39 mm film) when the third value is set; at least 5 degrees
int CamObj::SetFov::update(const ICmd::Param& param) {
    unsigned int index = param.m_param.val(0).getS32();
    float fov = param.m_param.val(1).getF32();
    if (param.m_param.val(2).getBool()) {
        fov = atanf(25.39f / (fov + fov));
        fov = (fov + fov) * 180.0f / 3.1415f;
    }
    CamInterface* cam = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[index];
    cam->m_fov = fmaxf(fov, 5.0f);
    return 1;
}

int CamObj::SetNearfar::update(const ICmd::Param& param) {
    unsigned int index = param.m_param.val(0).getS32();
    float nearClip = param.m_param.val(1).getF32();
    float farClip = param.m_param.val(2).getF32();
    CamInterface* cam = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[index];
    cam->m_nearClip = nearClip;
    cam->m_farClip = farClip;
    return 1;
}

CamObj::~CamObj() {
    changeActive(nullptr);
    m_cmdQueue.update();
    m_cmdQueue.update();
}

// the camera that leaves gets a SetEnable(false), the one that comes a SetEnable(true); m_field's needs none
void CamObj::changeActive(CamBase* cam) {
    if (m_activeCam != cam) {
        if (m_activeCam != nullptr && m_activeCam != &m_field) {
            CmdParam param;
            param.val(0).setS32(pad_64);
            param.val(1).setBool(false);
            m_cmdQueue.push_back(&m_setEnable, param);
        }
        m_activeCam = cam;
        if (cam != nullptr && cam != &m_field) {
            CmdParam param;
            param.val(0).setS32(pad_64);
            param.val(1).setBool(true);
            m_cmdQueue.push_back(&m_setEnable, param);
        }
    }
}

// the active camera's view is copied in and, unless it is m_field or CamManager's free camera runs, queued to the
// interface as SetTargetPos, SetFov and SetNearfar commands
void CamObj::update(const FrameInfo& info) {
    if (m_activeCam && info.m_step > 0.0f) {
        m_activeCam->update(info);
        CamBase* cam = m_activeCam;
        float px = cam->pad_10.x;
        float py = cam->pad_10.y;
        float pz = cam->pad_10.z;
        float tx = cam->pad_20.x;
        float ty = cam->pad_20.y;
        float tz = cam->pad_20.z;
        float fov = cam->pad_30;
        float roll = cam->pad_34;
        float nearClip = cam->m_near;
        float farClip = cam->m_far;
        m_pos.x = px;
        m_pos.y = py;
        m_pos.z = pz;
        m_tar.x = tx;
        m_tar.y = ty;
        m_tar.z = tz;
        m_fov = fov;
        m_rotZ = roll;
        m_near = nearClip;
        m_far = farClip;
        if (cam != &m_field && !(mm::mtl::Singleton<CamManager>::getPtr()->m_list.pad_14 & 2)) {
            CmdParam param;
            param.val(0).setS32(pad_64);
            param.val(1).setF32(px);
            param.val(2).setF32(py);
            param.val(3).setF32(pz);
            param.val(4).setF32(tx);
            param.val(5).setF32(ty);
            param.val(6).setF32(tz);
            param.val(7).setF32(roll);
            m_cmdQueue.push_back(&m_setTargetPos, param);
            param.val(0).setS32(pad_64);
            param.val(1).setF32(fov);
            param.val(2).setBool(pad_8);
            m_cmdQueue.push_back(&m_setFov, param);
            param.val(0).setS32(pad_64);
            param.val(1).setF32(nearClip);
            param.val(2).setF32(farClip);
            m_cmdQueue.push_back(&m_setNearfar, param);
        }
    }
}

void CamObj::render(const mm::Col4& col) {
    if (m_activeCam) {
        m_activeCam->render(col);
    }
}

void CamObj::tail() {
    if (m_activeCam) {
        m_cmdQueue.update();
    }
}

void CamManager::loadResource(const char* name) {
    if (m_list.pad_10 & 1) {
        return;
    }
    mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr, false);
}

// the camera of id 0 becomes the current one
CamObj* CamManager::createCam(unsigned int id) {
    CamObj* cam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
        CamObj(id, (m_list.pad_10 >> 2) & 1, m_list.pad_10 & 1);
    m_list.m_cams.push_back(cam);
    if (id == 0) {
        m_cur = cam;
    }
    return cam;
}

void CamManager::setFocal(bool focal) {
    if (focal) {
        m_list.pad_10 |= 4;
    } else {
        m_list.pad_10 &= ~4;
    }
}

}  // namespace event

#include "classes/event/ModelManager.h"

namespace event {

void CharaObj::createGhost() {
    if (!mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
        m_ghost = mm::mtl::Singleton<ModelManager>::getPtr()->createModel(m_modelId);
    }
    m_state = 6;
}

void CharaObj::playWink(int a, float b, bool c, float d, float e, int f, bool g, bool h) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue1.erase(&m_playWink);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setS32(a);
    param.val(2).setF32(b);
    param.val(3).setBool(c);
    param.val(4).setF32(d);
    param.val(5).setF32(e);
    param.val(6).setS32(f);
    param.val(7).setBool(g);
    param.val(8).setBool(h);
    m_cmdQueue1.push_back(&m_playWink, param);
}

// run by CharaObj::tail (not written yet); the table is built by the CharaObj constructor (not written yet)
template void CmdQueue<5, 0>::update();
template CmdQueue<5, 0>::~CmdQueue();

void CharaObj::setPos(const mm::Vec3& pos) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_pos = pos;
    m_cmdQueue2.erase(&m_setPos);
    CmdParam param;
    param.val(0).setF32(pos.x);
    param.val(1).setF32(pos.y);
    param.val(2).setF32(pos.z);
    m_cmdQueue2.push_back(&m_setPos, param);
}

void CharaObj::setRot(const mm::Vec3& rot) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_rot = rot;
    m_cmdQueue2.erase(&m_setRot);
    CmdParam param;
    param.val(0).setF32(rot.x);
    param.val(1).setF32(rot.y);
    param.val(2).setF32(rot.z);
    m_cmdQueue2.push_back(&m_setRot, param);
}

void CharaObj::turnRot(const mm::Vec3& rot, EVT_rotcvtype type, float time) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_rot = rot;
    m_rotGoal = rot;
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(rot.x);
    param.val(2).setF32(rot.y);
    param.val(3).setF32(rot.z);
    param.val(4).setS32(type);
    param.val(5).setF32(time);
    CmdQueue<8, 0>* queue = &m_cmdQueue0;
    if (type == 0) {
        if (m_cmdQueue0.contains(&m_turnRot)) {
            m_cmdQueue0.erase(&m_turnRot);
        }
        queue = &m_cmdQueue1;
    }
    queue->push_back(&m_turnRot, param);
}

void CharaObj::linerRot(const mm::Vec3& rot, float time, CV_TYPE cvType) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (time == 0.0f) {
        m_rot = rot;
        m_rotGoal = rot;
        m_cmdQueue1.erase(&m_linerRot);
    } else {
        m_rotGoal = rot;
    }
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(rot.x);
    param.val(2).setF32(rot.y);
    param.val(3).setF32(rot.z);
    param.val(4).setF32(time);
    param.val(5).setS32(cvType);
    m_cmdQueue1.push_back(&m_linerRot, param);
}

}  // namespace event

#include "classes/event/CharaFacialUtil.h"

namespace event {

void CharaObj::setTar(const TarAxis& tar, float time, EVT_tarcvtype cvType, EVT_aimtype aimType, float a, float b) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (mm::mtl::Singleton<CharaManager>::getPtr()->getModeFlags() & 0x10) {
        gf::GF_OBJ_HANDLE* handle = m_gfHandle;
        if (gf::GfObj* obj = gf::GfObjUtil::getObj(handle)) {
            gf::GfObjAcc acc(handle);
            unsigned int type = obj->m_type;
            if (CharaFacialUtil::transferGroup(acc.getBdatId(), type) == 3 && acc.getBdatId() == 2) {
                // a queued action 6 or 11 keeps its own target
                for (unsigned int i = 0; i < m_cmdQueue0.m_items.size(); i++) {
                    if (m_cmdQueue0.m_items[i].m_cmd == &m_playAction) {
                        if (m_playAction.m_id == 6) {
                            return;
                        }
                        if (m_playAction.m_id == 11) {
                            return;
                        }
                        break;
                    }
                }
            }
        }
    }
    m_cmdQueue2.erase(&m_setTar);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setS32(tar.m_type);
    param.val(2).setF32(tar.m_value.x);
    param.val(3).setF32(tar.m_value.y);
    param.val(4).setF32(tar.m_value.z);
    param.val(5).setF32(time);
    param.val(6).setS32(cvType);
    param.val(7).setS32(aimType);
    param.val(8).setF32(a);
    param.val(9).setF32(b);
    m_cmdQueue2.push_back(&m_setTar, param);
}

void CharaObj::setIdle(int id) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue0.erase(&m_setIdle);
    m_cmdQueue0.erase(&m_playActionAuto);
    m_cmdQueue0.erase(&m_playAction);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setS32(id);
    m_cmdQueue0.push_back(&m_setIdle, param);
}

void CharaObj::playAutoAction(float a) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (!(mm::mtl::Singleton<CharaManager>::getPtr()->isAutoTalkMode())) {
        return;
    }
    m_cmdQueue0.erase(&m_setIdle);
    m_cmdQueue0.erase(&m_playActionAuto);
    m_cmdQueue0.erase(&m_playAction);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(a);
    m_cmdQueue0.push_back(&m_playActionAuto, param);
}

void CharaObj::playMotionABC(const char* a, const char* b, const char* c, float d, float e, float f, float g, float h, float i) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue1.erase(&m_playMotion);
    m_cmdQueue1.erase(&m_playMotionABC);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setStr(a);
    param.val(2).setStr(b);
    param.val(3).setStr(c);
    param.val(4).setF32(d);
    param.val(5).setF32(e);
    param.val(6).setF32(f);
    param.val(7).setF32(g);
    param.val(8).setF32(h);
    param.val(9).setF32(i);
    m_cmdQueue1.push_back(&m_playMotionABC, param);
}

void CharaObj::playAction(int id, float time, bool a, bool b) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    // bit 3 of the mode flags: 1.0.0 names it seamless action
    if (mm::mtl::Singleton<CharaManager>::getPtr()->getModeFlags() & 8) {
        for (unsigned int i = 0; i < m_cmdQueue0.m_items.size(); i++) {
            if (m_cmdQueue0.m_items[i].m_cmd == &m_playAction) {
                if (m_playAction.m_id == id) {
                    m_playAction.m_flags |= 2;
                    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("action seamless");
                }
                break;
            }
        }
    }
    if (mm::mtl::Singleton<CharaManager>::getPtr()->getModeFlags() & 0x10) {
        gf::GF_OBJ_HANDLE* handle = m_gfHandle;
        if (gf::GfObj* obj = gf::GfObjUtil::getObj(handle)) {
            gf::GfObjAcc acc(handle);
            unsigned int type = obj->m_type;
            if (CharaFacialUtil::transferGroup(acc.getBdatId(), type) == 3 && acc.getBdatId() == 2 &&
                (id == 11 || id == 6)) {
                m_cmdQueue2.erase(&m_setTar);
            }
        }
    }
    m_cmdQueue0.erase(&m_setIdle);
    m_cmdQueue0.erase(&m_playActionAuto);
    m_cmdQueue0.erase(&m_playAction);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setS32(id);
    param.val(2).setF32(time);
    param.val(3).setBool(a);
    param.val(4).setBool(b);
    m_cmdQueue0.push_back(&m_playAction, param);
}

void CharaObj::stopAction() {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (m_cmdQueue0.contains(&m_playAction)) {
        m_cmdQueue0.erase(&m_playAction);
        CmdParam param;
        m_cmdQueue0.push_back(&m_stopAction, param);
    }
}

void CharaObj::playMotion(const char* name, float a, float b, float c) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (mm::mtl::Singleton<DebugManager>::getPtr()->testFlag(8)) {
        return;
    }
    if (m_state == 4 || m_state == 5) {
        initModelStream();
        m_flags |= 0x40;
        m_motionParam = a;
    }
    m_cmdQueue1.erase(&m_playMotion);
    m_cmdQueue1.erase(&m_playMotionABC);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setStr(name);
    param.val(2).setF32(a);
    param.val(3).setF32(b);
    param.val(4).setF32(c);
    m_cmdQueue1.push_back(&m_playMotion, param);
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
        m_cmdQueue1.erase(&m_playEva);
        m_cmdQueue1.erase(&m_playEvaEff);
        m_cmdQueue1.erase(&m_hideWpn);
        param.val(0).setUserdata(this);
        param.val(1).setStr(name);
        param.val(2).setF32(a);
        param.val(3).setF32(b);
        m_cmdQueue1.push_back(&m_playEva, param);
        param.val(0).setUserdata(this);
        param.val(1).setStr(name);
        param.val(2).setF32(a);
        param.val(3).setF32(b);
        m_cmdQueue1.push_back(&m_playEvaEff, param);
        param.val(0).setUserdata(this);
        param.val(1).setF32(a);
        m_cmdQueue1.push_back(&m_hideWpn, param);
    }
}

void CharaObj::playHead(int id, float time, bool a, bool b, float c, float d) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue1.erase(&m_playHead);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setS32(id);
    param.val(2).setF32(time);
    param.val(3).setBool(a);
    param.val(4).setBool(b);
    param.val(5).setF32(c);
    param.val(6).setF32(d);
    m_cmdQueue1.push_back(&m_playHead, param);
}

void CharaObj::stopHead() {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (m_cmdQueue1.contains(&m_playHead)) {
        m_cmdQueue1.erase(&m_playHead);
        CmdParam param;
        m_cmdQueue1.push_back(&m_stopHead, param);
    }
}

void CharaObj::playFacial(int a, float b, int c, float d, int e, float f, int g, float h, float i, float j) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue1.erase(&m_playFacial);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setS32(a);
    param.val(2).setF32(b);
    param.val(3).setS32(c);
    param.val(4).setF32(d);
    param.val(5).setS32(e);
    param.val(6).setF32(f);
    param.val(7).setS32(g);
    param.val(8).setF32(h);
    param.val(9).setF32(i);
    param.val(10).setF32(j);
    m_cmdQueue1.push_back(&m_playFacial, param);
}

void CharaObj::playAutoTalk(float a) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    if (!(mm::mtl::Singleton<CharaManager>::getPtr()->isAutoTalkMode())) {
        return;
    }
    m_cmdQueue1.erase(&m_playTalkAuto);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(a);
    m_cmdQueue1.push_back(&m_playTalkAuto, param);
}

void CharaObj::playTalk(bool a, float b, bool c, bool d, float e, float f, float g, float h) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    ICmd* cmd = &m_playTalk;
    if (!a) {
        // a talk still queued with flag 8 keeps running
        for (unsigned int i = 0; i < m_cmdQueue1.m_items.size(); i++) {
            if (m_cmdQueue1.m_items[i].m_cmd == cmd) {
                if (m_playTalk.m_flags & 8) {
                    return;
                }
                break;
            }
        }
    }
    m_cmdQueue1.erase(cmd);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setBool(a);
    param.val(2).setF32(b);
    param.val(3).setBool(c);
    param.val(4).setBool(d);
    param.val(5).setF32(e);
    param.val(6).setF32(f);
    param.val(7).setF32(g);
    param.val(8).setF32(h);
    m_cmdQueue1.push_back(cmd, param);
}

void CharaObj::mount(CharaObj* parent, const char* name, const mm::Vec3& pos, const mm::Vec3& rot) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue1.erase(&m_mount);
    if (parent != nullptr) {
        CmdParam param;
        param.val(0).setUserdata(parent->m_model);
        param.val(1).setStr(name);
        param.val(2).setF32(pos.x);
        param.val(3).setF32(pos.y);
        param.val(4).setF32(pos.z);
        param.val(5).setF32(rot.x);
        param.val(6).setF32(rot.y);
        param.val(7).setF32(rot.z);
        m_cmdQueue1.push_back(&m_mount, param);
        m_flags |= 0x10;
    } else {
        CmdParam param;
        param.val(0).setUserdata(nullptr);
        param.val(1).setStr("");
        param.val(2).setF32(0.0f);
        param.val(3).setF32(0.0f);
        param.val(4).setF32(0.0f);
        param.val(5).setF32(0.0f);
        param.val(6).setF32(0.0f);
        param.val(7).setF32(0.0f);
        m_cmdQueue1.push_back(&m_mount, param);
        m_flags &= ~0x10;
    }
}

void CharaObj::resetDynamics(int type) {
    m_dysUpdater.resetDynamics(type);
}

void CharaObj::playFade(bool a, float b) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_cmdQueue1.erase(&m_fade);
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setBool(a);
    param.val(2).setF32(b);
    m_cmdQueue1.push_back(&m_fade, param);
    if (a) {
        m_flags |= 0x20;
    } else {
        m_flags &= ~0x20;
    }
}

void CharaEffectPlayer::stopAfterImage() {
    if (m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && (m_flags & 8)) {
        gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
        if (obj != nullptr) {
            if (gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1)) {
                ml::ScnObjAccResMdlInfo info(model->m_model->getInterface());
                info.releaseAfterImage();
            }
        }
        m_flags &= ~8;
    }
}

void CharaEffectPlayer::stopRimBloom() {
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) || !(m_flags & 4)) {
        return;
    }
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    gf::GfComProperty* property = obj != nullptr ? obj->getComponent<gf::GfComProperty>(5) : nullptr;
    gf::GfComEffectCaster* caster = obj != nullptr ? obj->getComponent<gf::GfComEffectCaster>(7) : nullptr;
    fw::Message msg(0x1000057, 0x80);
    if (property != nullptr && caster != nullptr) {
        gf::GfObj* owner = static_cast<gf::GfObj*>(property->m_owner);
        caster->recieveMessage(owner, msg);
    }
    m_rimBloom = 0;
    m_flags &= ~4;
}

void CharaEffectPlayer::stopVolumeFade(VF_TYPE type) {
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    unsigned int bit = type == 1 ? 2 : 1;
    if (m_flags & bit) {
        gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
        if (obj != nullptr) {
            if (gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1)) {
                ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
                fade.setRatio(0.0f, m_fadeIndices[type]);
            }
        }
        m_flags &= ~bit;
    }
    m_anm[type].clear();
    m_flags &= ~(type == 1 ? 0x20 : 0x10);
}

void CharaEffectPlayer::updateVolumeFadeAnim(VF_TYPE type, float step) {
    AnmF32& anm = m_anm[type];
    anm.update(step);
    m_fadeRatios[type] = anm.m_value;
    if (!anm.isPlaying()) {
        m_flags &= ~(type == 1 ? 0x20 : 0x10);
    }
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1);
    ml::VolumeFadeParams params;
    if (fw::EffectManager::sys()->getVolumeFadeParam(m_fadeIds[type], params)) {
        params.m_color0 = m_fadeColors0[type];
        params.m_color1 = m_fadeColors1[type];
        params.m_value0 = m_fadeValues0[type];
        params.m_value1 = m_fadeValues1[type];
        if (model != nullptr) {
            ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
            fade.setParams(params, m_fadeIndices[type]);
            fade.setRatio(m_fadeRatios[type], m_fadeIndices[type]);
        }
    }
}

void CharaEffectPlayer::playVolumeFade(VF_TYPE type, int id, const mm::Vec3& color0, const mm::Vec3& color1,
                                       float value0, float value1, int index, float ratio) {
    unsigned int bit = type == 1 ? 2 : 1;
    if ((m_flags & bit) && m_fadeIds[type] == id && m_fadeColors0[type].isEqual(color0) &&
        m_fadeColors1[type].isEqual(color1) && m_fadeValues0[type] == value0 && m_fadeValues1[type] == value1 &&
        m_fadeIndices[type] == index && m_fadeRatios[type] == ratio) {
        return;
    }
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (!(mm::mtl::Singleton<CharaManager>::getPtr()->getModeFlags() & 1)) {
        gf::GfObjAcc acc(m_handle);
        mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("volumeFade %s %d", acc.getDebugName(), id);
    }
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1);
    ml::VolumeFadeParams params;
    if (fw::EffectManager::sys()->getVolumeFadeParam(id, params)) {
        mm::clampSelf(value1, 0.0f, 1.0f);
        params.m_color0 = color0;
        params.m_color1 = color1;
        params.m_value0 = value0;
        params.m_value1 = value1;
        if (model != nullptr) {
            ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
            int max = fade.getMax();
            mm::clampSelf(index, -1, fade.getMax() - 1);
            mm::clampSelf(ratio, 0.0f, 1.0f);
            fade.setParams(params, index);
            fade.setRatio(ratio, index);
        }
        m_fadeIds[type] = id;
        m_fadeColors0[type] = color0;
        m_fadeColors1[type] = color1;
        m_fadeValues0[type] = value0;
        m_fadeValues1[type] = value1;
        m_fadeIndices[type] = index;
        m_fadeRatios[type] = ratio;
        m_flags |= bit;
    }
}

void CharaEffectPlayer::playVolumeFadeAnim(VF_TYPE type, float ratio, float frame) {
    unsigned int bit = type == 1 ? 2 : 1;
    if ((m_flags & bit) && m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        AnmF32& anm = m_anm[type];
        anm.clear();
        anm.append(0.0f, m_fadeRatios[type], CV_TYPE(1));
        anm.append(frame, ratio, CV_TYPE(1));
        m_flags |= type == 1 ? 0x20 : 0x10;
    }
}

void CharaEffectPlayer::playRimBloom(int type) {
    if ((m_flags & 4) && m_rimBloom == type) {
        return;
    }
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    gf::GfObjAcc acc(m_handle);
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("rimBloom %s %d", acc.getDebugName(), type);
    stopRimBloom();
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    gf::GfComProperty* property = obj != nullptr ? obj->getComponent<gf::GfComProperty>(5) : nullptr;
    gf::GfComEffectCaster* caster = obj != nullptr ? obj->getComponent<gf::GfComEffectCaster>(7) : nullptr;
    RimBloomMessage msg;
    msg.m_type = type;
    if (property != nullptr && caster != nullptr) {
        gf::GfObj* owner = static_cast<gf::GfObj*>(property->m_owner);
        caster->recieveMessage(owner, msg);
    }
    m_rimBloom = type;
    m_flags |= 4;
}

void CharaEffectPlayer::playAfterImage(int src, int dst, float param0, float param1, float param2) {
    if ((m_flags & 8) && m_afterImageSrc == src && m_afterImageDst == dst && m_afterImageParams[0] == param0 &&
        m_afterImageParams[1] == param1 && m_afterImageParams[2] == param2) {
        return;
    }
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    gf::GfObjAcc acc(m_handle);
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("afterImage %s %d %d", acc.getDebugName(), src, dst);
    stopAfterImage();
    // the defaults getAfterImageParams starts from (orange trails)
    ml::DrMdlAfterImageParams params;
    params.m_params0[0] = 4.0f;
    params.m_params0[1] = 12.0f;
    params.m_params0[2] = 0.95f;
    params.m_color0 = mm::Col3::orange;
    params.m_params1[2] = 0.0f;
    params.m_params1[0] = 0.3f;
    params.m_params1[1] = 0.0f;
    params.m_color1 = mm::Col3::orange;
    params.m_params2[2] = 0.0f;
    params.m_params2[0] = 0.3f;
    params.m_params2[1] = 0.0f;
    fw::EffectManager::sys()->getAfterImageParams(src, dst, params);
    params.m_params0[0] = param0;
    params.m_params0[1] = param1;
    params.m_params0[2] = param2;
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj != nullptr) {
        if (gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1)) {
            ml::ScnObjAccResMdlInfo info(model->m_model->getInterface());
            info.createAfterImage(params);
        }
    }
    m_afterImageSrc = src;
    m_afterImageDst = dst;
    m_afterImageParams[0] = param0;
    m_afterImageParams[1] = param1;
    m_afterImageParams[2] = param2;
    m_flags |= 8;
}

CharaEffectPlayer::~CharaEffectPlayer() {}

CharaTarPlayerMot::~CharaTarPlayerMot() {}

CharaTarPlayer::~CharaTarPlayer() {}

CharaWeightItem::~CharaWeightItem() {}

void CharaObj::playVolumeFade(CharaEffectPlayer::VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d,
                              float e, int f, float g) {
    m_effectPlayer.playVolumeFade(type, a, b, c, d, e, f, g);
}
}  // namespace event

template mm::mtl::PtrSingleton<event::Manager>::~PtrSingleton();

namespace event {

void CharaObj::playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, float time, float delay) {
    m_effectPlayer.playVolumeFadeAnim(type, time, delay);
}

void CharaObj::stopVolumeFade(CharaEffectPlayer::VF_TYPE type) {
    m_effectPlayer.stopVolumeFade(type);
}

void CharaObj::playRimBloom(int type) {
    m_effectPlayer.playRimBloom(type);
}

void CharaObj::stopRimBloom() {
    m_effectPlayer.stopRimBloom();
}

void CharaObj::setExtDisp(const char* name, bool disp) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_partUpdater.setExtDisp(name, disp);
}

void CharaObj::setExtParam(const char* name, float value) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_partUpdater.setExtParam(name, value);
}
}  // namespace event

#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfEvtModelWeapon.h"

namespace event {

void CharaObj::setScaleWeapon(float scale) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    m_weaponScale = scale;
    if (m_model != nullptr && m_model->m_modelType == 2) {
        static_cast<gf::GfEvtModelWeapon*>(m_model)->setScale(scale);
    }
}

CharaWpnAsm::~CharaWpnAsm() {}

void CharaEvaPlayer::setBattleWeapon(int weapon) {
    CharaWpnAsm::CMD cmd = static_cast<CharaWpnAsm::CMD>(weapon - 1);
    switch (m_model->m_modelType) {
    // the cases in this order (the two-weapon ones apart): the original tests 0, 1, then 2
    case 2:
        m_wpnRight.execCmd(m_model, cmd, false, nullptr);
        break;
    case 1:
        m_wpnRight.execCmd(m_model, cmd, false, nullptr);
        m_wpnLeft.execCmd(m_model, cmd, true, nullptr);
        break;
    case 0:
        m_wpnRight.execCmd(m_model, cmd, false, nullptr);
        m_wpnLeft.execCmd(m_model, cmd, true, nullptr);
        break;
    }
    m_battleWeapon = weapon;
}

CharaEvaPlayerEff::~CharaEvaPlayerEff() {
    if (m_rcha) {
        delete m_rcha;
        m_rcha = nullptr;
    }
    m_model = nullptr;
    m_player = nullptr;
}

void CharaEvaPlayerEff::stop() {
    if (m_rcha) {
        delete m_rcha;
        m_rcha = nullptr;
    }
    m_model = nullptr;
    m_player = nullptr;
}

int CharaSetPos::update(const ICmd::Param& param) {
    if (m_handle == (gf::GF_OBJ_HANDLE*)-1) {
        return true;
    }
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj == nullptr) {
        return false;
    }
    gf::GfComTransform* transform = obj->getComponent<gf::GfComTransform>(0);
    transform->setPosition(mm::Vec3(param.m_param.val(0).getF32(), param.m_param.val(1).getF32(), param.m_param.val(2).getF32()));
    return true;
}

int CharaStopAction::update(const ICmd::Param&) {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj != nullptr) {
        gf::GfComEvtAnim* anim = obj->getComponent<gf::GfComEvtAnim>(2);
        if (anim != nullptr) {
            anim->execCmd("C_idle");
            if (strcmp(anim->getStateName() ? anim->getStateName() : "", "S_idle") != 0) {
                anim->setState("S_idle");
            }
        }
    }
    return true;
}

ObjectChara::ObjectChara(const char* name)
    : Object(static_cast<OBJTYPE>(2), name), m_flags(0), m_chara(nullptr) {}

ObjectChara::~ObjectChara() {
    if (m_chara) {
        delete m_chara;
        m_chara = nullptr;
    }
}

void ObjectChara::createGfObj(gf::GF_OBJ_HANDLE* handle) {
    m_chara = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) CharaObj(m_name.m_str);
    m_chara->createGfObj(handle);
    m_flags |= 1;
}

void ObjectChara::createGfObj(CHARA_TYPE type, unsigned int id, unsigned int a, unsigned int b) {
    m_chara = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) CharaObj(m_name.m_str);
    m_chara->createGfObj(type, id, a, b);
    m_flags |= 1;
}

void ObjectChara::createModel(const char* name, unsigned int a, unsigned int b) {
    m_chara = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) CharaObj(m_name.m_str);
    m_chara->createModel(name, a, b);
    m_flags &= ~1u;
}

void ObjectChara::createGhost() {
    m_chara = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) CharaObj(m_name.m_str);
    m_chara->createGhost();
    m_flags |= 1;
}

void ObjectChara::clear() {
    if (m_chara) {
        m_chara->clear();
    }
}

void Object::clear() {}

void ObjectChara::start() {
    if (m_chara) {
        m_chara->start();
    }
}

void Object::start() {}

void ObjectChara::end() {
    if (m_chara) {
        m_chara->end();
    }
}

void Object::end() {}

void ObjectChara::update() {
    const FrameInfo& info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
    if (m_chara) {
        m_chara->update(info);
    }
}

void Object::update() {}

void Object::render(const mm::Col4&) {}

void ObjectChara::tail() {
    const FrameInfo& info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
    if (m_chara) {
        m_chara->tail(info);
    }
}

void Object::tail() {}

bool ObjectChara::isLoading() const {
    return !(m_chara->m_flags & 8);
}

void ObjectChara::turnRotAxis(const RotAxis& rot, EVT_rotcvtype type, float time) {
    m_rot = rot;
    CharaObj* chara = m_chara;
    const mm::Vec3& pos = (chara->m_cmdQueue0.contains(&chara->m_walkPos) ||
                           chara->m_cmdQueue1.contains(&chara->m_walkPos) ||
                           chara->m_cmdQueue1.contains(&chara->m_linerPos))
                              ? chara->m_posGoal
                              : chara->m_pos;
    chara->turnRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(rot.m_type, rot.m_value.x, rot.m_value.y,
                                                                        rot.m_value.z, pos),
                   type, time);
    m_chara->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::linerRotAxis(const RotAxis& rot, float time, CV_TYPE type) {
    m_rot = rot;
    CharaObj* chara = m_chara;
    const mm::Vec3& pos = (chara->m_cmdQueue0.contains(&chara->m_walkPos) ||
                           chara->m_cmdQueue1.contains(&chara->m_walkPos) ||
                           chara->m_cmdQueue1.contains(&chara->m_linerPos))
                              ? chara->m_posGoal
                              : chara->m_pos;
    chara->linerRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(rot.m_type, rot.m_value.x, rot.m_value.y,
                                                                         rot.m_value.z, pos),
                    time, type);
    m_chara->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::OnManiSetPos(IManiCallback::SetParam& param) {
    mm::Vec3 trans = param.m_mtx.getTrans();
    PosAxis pos = m_pos;
    mm::Mat44 inv = pos.calcOrigMatInv();
    pos.m_value = mm::Vec3(trans.x * inv.m[0][0] + trans.y * inv.m[1][0] + trans.z * inv.m[2][0] + inv.m[3][0],
                           trans.x * inv.m[0][1] + trans.y * inv.m[1][1] + trans.z * inv.m[2][1] + inv.m[3][1],
                           trans.x * inv.m[0][2] + trans.y * inv.m[1][2] + trans.z * inv.m[2][2] + inv.m[3][2]);
    setPosAxis(pos);
}

void ObjectChara::OnManiSetRot(IManiCallback::SetParam& param) {
    const mm::Mat44& mtx = param.m_mtx;
    mm::Vec3 r;
    r.x = mm::asin(-mtx.m[2][1]);
    if (r.x < 1.57079637f) {
        if (r.x > -1.57079637f) {
            r.z = ::atan2f(mtx.m[0][1], mtx.m[1][1]);
            r.y = ::atan2f(mtx.m[2][0], mtx.m[2][2]);
        } else {
            r.z = ::atan2f(mtx.m[0][2], mtx.m[0][0]);
            r.y = 0.0f;
        }
    } else {
        r.z = ::atan2f(mtx.m[0][2], mtx.m[0][0]);
        r.y = 0.0f;
    }
    RotAxis rot = m_rot;
    mm::Vec3 pos = m_chara->m_pos;
    rot.m_value = mm::Vec3(0.0f, r.y - mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(rot.m_type, pos), 0.0f);
    setRotAxis(rot);
}

ObjectEffect::ObjectEffect(const char* name)
    : Object(static_cast<OBJTYPE>(4), name), pad_150(false), pad_190(0) {
    m_effect = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) EffectObj(name);
    m_caster = 0;
    m_mountActor = 0;
    m_mountName = "";
    m_mountPos = mm::Vec3::zero;
    m_mountFlag = false;
    m_mountType = (EVT_attachtype)0;
    m_mountMtx = mm::Mat44::identity;
    pad_150 = false;
    pad_190 = 0;
}

ObjectEffect::~ObjectEffect() {
    if (m_effect) {
        delete m_effect;
        m_effect = nullptr;
    }
}

void ObjectEffect::end() {
    if (m_effect) {
        m_effect->end();
    }
}

// run by ObjectEffect::update and queued by EffectObj::play, moveTo, turnTo, colorTo, playAnim (not written yet);
// the table is built by the EffectObj constructor (not written yet)
template void CmdQueue<6, 0>::update();
template void CmdQueue<6, 0>::erase(const ICmd* cmd);
template void CmdQueue<6, 0>::push_back(ICmd* cmd, const CmdParam& param);
template CmdQueue<6, 0>::~CmdQueue();

void ObjectEffect::tail() {
    m_effect->m_ctrl.update();
}

void ObjectEffect::OnManiSetPos(IManiCallback::SetParam& param) {
    mm::Vec3 trans = param.m_mtx.getTrans();
    PosAxis pos = m_pos;
    mm::Mat44 inv = pos.calcOrigMatInv();
    pos.m_value = mm::Vec3(trans.x * inv.m[0][0] + trans.y * inv.m[1][0] + trans.z * inv.m[2][0] + inv.m[3][0],
                           trans.x * inv.m[0][1] + trans.y * inv.m[1][1] + trans.z * inv.m[2][1] + inv.m[3][1],
                           trans.x * inv.m[0][2] + trans.y * inv.m[1][2] + trans.z * inv.m[2][2] + inv.m[3][2]);
    setPosAxis(pos);
}

void ObjectEffect::setPosAxis(const PosAxis& pos) {
    m_pos = pos;
    EffectObj* effect = m_effect;
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(pos.m_type, pos.m_value.x, pos.m_value.y,
                                                                          pos.m_value.z);
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        effect->m_ctrl.m_pos = value;
    }
}

void ObjectEffect::OnManiSetRot(IManiCallback::SetParam& param) {
    const mm::Mat44& mtx = param.m_mtx;
    mm::Vec3 r;
    r.x = mm::asin(-mtx.m[2][1]);
    if (r.x < 1.57079637f) {
        if (r.x > -1.57079637f) {
            r.z = ::atan2f(mtx.m[0][1], mtx.m[1][1]);
            r.y = ::atan2f(mtx.m[2][0], mtx.m[2][2]);
        } else {
            r.z = -::atan2f(mtx.m[0][2], mtx.m[0][0]);
            r.y = 0.0f;
        }
    } else {
        r.z = ::atan2f(mtx.m[0][2], mtx.m[0][0]);
        r.y = 0.0f;
    }
    RotAxis rot = m_rot;
    mm::Vec3 pos = m_effect->m_ctrl.m_pos;
    rot.m_value = mm::Vec3(r.x, r.y - mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(rot.m_type, pos), r.z);
    setRotAxis(rot);
}

void ObjectEffect::setRotAxis(const RotAxis& rot) {
    m_rot = rot;
    EffectObj* effect = m_effect;
    const mm::Vec3& pos = effect->m_ctrl.m_pos;
    mm::Vec3 value = mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(rot.m_type, rot.m_value.x, rot.m_value.y,
                                                                          rot.m_value.z, pos);
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        effect->m_ctrl.m_rot = value;
    }
}

void ObjectEffect::linerPosAxis(const PosAxis& pos, float time, CV_TYPE type) {
    m_pos = pos;
    m_effect->moveTo(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(pos.m_type, pos.m_value.x, pos.m_value.y,
                                                                          pos.m_value.z),
                     time, type);
}

void ObjectEffect::linerRotAxis(const RotAxis& rot, float time, CV_TYPE type) {
    m_rot = rot;
    EffectObj* effect = m_effect;
    const mm::Vec3& pos = effect->m_ctrl.m_pos;
    effect->turnTo(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(rot.m_type, rot.m_value.x, rot.m_value.y,
                                                                        rot.m_value.z, pos),
                   time, type);
}

void ObjectEffect::setMount(IAttachActor* actor, const char* name, const mm::Vec3& pos, bool flag,
                            EVT_attachtype type) {
    EffectObj* effect = m_effect;
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        effect->m_ctrl.setMount(actor, name, pos, flag, type);
    }
    m_caster = 0;
    m_mountActor = actor;
    m_mountName = name;
    m_mountPos = pos;
    m_mountFlag = flag;
    m_mountType = type;
}

// the walks to the end of the first three categories come first and use nothing (as in startPage)
ObjectList::~ObjectList() {
    for (Object* last = m_categories[0]->m_child; last; last = last->m_next) {
    }
    for (Object* last = m_categories[1]->m_child; last; last = last->m_next) {
    }
    for (Object* last = m_categories[2]->m_child; last; last = last->m_next) {
    }
    if (m_root) {
        clearSub(m_root);
    }
    if (Object* parent = m_categories[2]) {
        Object* child = parent->m_child;
        while (child) {
            Object* next = child->m_next;
            delete child;
            child = next;
        }
        parent->m_child = nullptr;
    }
    m_counts[2] = 0;
    if (Object* parent = m_categories[0]) {
        Object* child = parent->m_child;
        while (child) {
            Object* next = child->m_next;
            delete child;
            child = next;
        }
        parent->m_child = nullptr;
    }
    m_counts[0] = 0;
    if (Object* parent = m_categories[1]) {
        Object* child = parent->m_child;
        while (child) {
            Object* next = child->m_next;
            delete child;
            child = next;
        }
        parent->m_child = nullptr;
    }
    m_counts[1] = 0;
    if (Object* parent = m_categories[3]) {
        Object* child = parent->m_child;
        while (child) {
            Object* next = child->m_next;
            delete child;
            child = next;
        }
        parent->m_child = nullptr;
    }
    m_counts[3] = 0;
    if (m_root) {
        m_root->m_child = nullptr;
    }
    for (int i = 3; i >= 0; --i) {
        if (m_categories[i]) {
            delete m_categories[i];
            m_categories[i] = nullptr;
        }
    }
    if (m_root) {
        delete m_root;
        m_root = nullptr;
    }
    m_flags = 0;
    m_active = nullptr;
    pad_80 = nullptr;
}

void ObjectList::clearSub(Object* obj) {
    obj->clear();
    for (Object* child = obj->m_child; child; child = child->m_next) {
        clearSub(child);
    }
}

void ObjectList::startSceneSub(Object* obj) {
    obj->start();
    for (Object* child = obj->m_child; child; child = child->m_next) {
        startSceneSub(child);
    }
}

// empties the effect category: each effect leaves BouManager's list, then the objects are deleted
void ObjectList::startPage() {
    for (Object* obj = m_categories[2]->m_child; obj; obj = obj->m_next) {
        BouManager* bou = mm::mtl::Singleton<BouManager>::getPtr();
        for (IBouCallback** it = bou->m_callbacks.begin(); it != bou->m_callbacks.end(); ++it) {
            if (*it == obj) {
                bou->m_callbacks.erase(it);
                break;
            }
        }
    }
    Object* parent = m_categories[2];
    Object* last = parent->m_child;
    while (last) {
        last = last->m_next;
    }
    if (parent) {
        Object* child = parent->m_child;
        while (child) {
            Object* next = child->m_next;
            delete child;
            child = next;
        }
        parent->m_child = nullptr;
    }
    m_counts[2] = 0;
    m_active = nullptr;
}

void ObjectList::endSceneSub(Object* obj) {
    obj->end();
    for (Object* child = obj->m_child; child; child = child->m_next) {
        endSceneSub(child);
    }
}

void ObjectList::updateSub(Object* obj) {
    obj->update();
    for (Object* child = obj->m_child; child; child = child->m_next) {
        updateSub(child);
    }
}

void ObjectList::renderSub(Object* obj) {
    if (obj->isLoading()) {
        obj->render(mm::Col4(0.5f, 0.5f, 0.5f, 0.5f));
    } else {
        obj->render(mm::Col4(1.0f, 1.0f, 1.0f, 0.5f));
    }
    for (Object* child = obj->m_child; child; child = child->m_next) {
        renderSub(child);
    }
}

void ObjectList::tailSub(Object* obj) {
    obj->tail();
    for (Object* child = obj->m_child; child; child = child->m_next) {
        tailSub(child);
    }
}

bool ObjectList::isLoadingSub(Object* obj) const {
    if (obj->isLoading()) {
        return true;
    }
    for (Object* child = obj->m_child; child; child = child->m_next) {
        if (isLoadingSub(child)) {
            return true;
        }
    }
    return false;
}

Object* ObjectList::createGfObj(const char* name, gf::GF_OBJ_HANDLE* handle) {
    ObjectChara* obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
        ObjectChara(name);
    obj->createGfObj(handle);
    Object* parent = m_categories[0];
    if (parent->m_child == nullptr) {
        parent->m_child = obj;
    } else {
        Object* last = parent->m_child;
        while (last->m_next) {
            last = last->m_next;
        }
        last->m_next = obj;
    }
    m_counts[0]++;
    mm::mtl::Singleton<BouManager>::getPtr()->m_callbacks.push_back(obj);
    m_active = obj;
    if (pad_80 == nullptr) {
        pad_80 = obj;
    }
    return obj;
}

gf::GF_OBJ_HANDLE* ObjectList::getDriverByBlade(unsigned int bladeId) {
    for (unsigned int id = 1; id <= 3; id++) {
        gf::GF_OBJ_HANDLE* driver = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getDriver(id);
        gf::GF_OBJ_HANDLE* blade = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getBlade(id);
        if (gf::GfObjAcc(blade).getBdatId() == bladeId) {
            return driver;
        }
    }
    return gf::GfGameManager::getPartyLeaderDriver();
}

gf::GF_OBJ_HANDLE* ObjectList::getBladeByDriver(unsigned int driverId) {
    for (unsigned int id = 1; id <= 3; id++) {
        gf::GF_OBJ_HANDLE* driver = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getDriver(id);
        gf::GF_OBJ_HANDLE* blade = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getBlade(id);
        if (gf::GfObjAcc(driver).getBdatId() == driverId) {
            return blade;
        }
    }
    return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

Object* ObjectList::createCamera(const char* name, unsigned int id) {
    Object* result = nullptr;
    if (id < m_counts[1]) {
        for (Object* obj = m_categories[1]->m_child; obj; obj = obj->m_next) {
            if (id-- == 0) {
                result = obj;
                break;
            }
        }
    } else {
        ObjectCamera* obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
            ObjectCamera(name, id);
        Object* parent = m_categories[1];
        if (parent->m_child == nullptr) {
            parent->m_child = obj;
        } else {
            Object* last = parent->m_child;
            while (last->m_next) {
                last = last->m_next;
            }
            last->m_next = obj;
        }
        m_counts[1]++;
        mm::mtl::Singleton<BouManager>::getPtr()->m_callbacks.push_back(obj);
        m_active = obj;
        result = obj;
    }
    return result;
}

Object* ObjectList::createEffect(const char* name) {
    ObjectEffect* obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
        ObjectEffect(name);
    Object* parent = m_categories[2];
    if (parent->m_child == nullptr) {
        parent->m_child = obj;
    } else {
        Object* last = parent->m_child;
        while (last->m_next) {
            last = last->m_next;
        }
        last->m_next = obj;
    }
    m_counts[2]++;
    mm::mtl::Singleton<BouManager>::getPtr()->m_callbacks.push_back(obj);
    m_active = obj;
    return obj;
}

Object* ObjectList::createLight(const char* name, unsigned int id) {
    Object* result = nullptr;
    if (id < m_counts[3]) {
        for (Object* obj = m_categories[3]->m_child; obj; obj = obj->m_next) {
            if (id-- == 0) {
                result = obj;
                break;
            }
        }
    } else {
        ObjectLight* obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
            ObjectLight(name, id);
        Object* parent = m_categories[3];
        if (parent->m_child == nullptr) {
            parent->m_child = obj;
        } else {
            Object* last = parent->m_child;
            while (last->m_next) {
                last = last->m_next;
            }
            last->m_next = obj;
        }
        m_counts[3]++;
        m_active = obj;
        result = obj;
    }
    return result;
}

void ObjectList::setActivePath(const char* path) {
    Object* root = m_root;
    if (root == nullptr) {
        return;
    }
    if (*path == '\0') {
        m_active = nullptr;
        return;
    }
    Object* found = nullptr;
    {
        char buf[512];
        char* rest = nullptr;
        strcpy(buf, path);
        strtok_r(buf, "/", &rest);
        for (Object* child = root->m_child; child; child = child->m_next) {
            if (strcmp(buf, child->m_name.m_str) == 0) {
                found = child->searchByPath(path);
                break;
            }
        }
    }
    m_active = found;
    if (found == nullptr || found == m_root || found == m_categories[0] || found == m_categories[1] ||
        found == m_categories[2] || found == m_categories[3]) {
        m_active = nullptr;
    }
}

Object* ObjectList::searchByNameSub(Object* obj, const char* name) {
    if (strcmp(name, obj->m_name.m_str) == 0) {
        return obj;
    }
    for (Object* child = obj->m_child; child; child = child->m_next) {
        Object* found = searchByNameSub(child, name);
        if (found) {
            return found;
        }
    }
    return nullptr;
}

void ObjectList::listupObject(mm::mtl::FixedVector<unsigned int, 256>& list, unsigned int type, bool append) {
    if (!append) {
        list.clear();
    }
    if (m_categories[0] == nullptr) {
        return;
    }
    for (Object* obj = m_categories[0]->m_child; obj && list.size() < 256; obj = obj->m_next) {
        if (obj->m_type == 2 && static_cast<ObjectChara*>(obj)->m_chara->m_gfHandle !=
                                    reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(static_cast<ObjectChara*>(obj)->m_chara->m_gfHandle);
            if (acc.getType() == type) {
                list.push_back(acc.getBdatId());
            }
        }
    }
}

void ObjectManager::updateCurrent() {
    if (strcmp(m_sceneName.m_str, m_currentName.m_str) == 0) {
        return;
    }
    m_current = searchScene(m_sceneName.m_str);
    if (!m_current) {
        m_current = createScene(m_sceneName.m_str);
    }
    if (m_current) {
        m_currentName = m_sceneName;
    }
}

void ObjectManager::render() {
    if (isDisp() || mm::mtl::Singleton<CharaManager>::getPtr()->isCharaDisp() ||
        mm::mtl::Singleton<CharaManager>::getPtr()->isFacialDisp() ||
        mm::mtl::Singleton<CharaManager>::getPtr()->isBoneDisp() ||
        mm::mtl::Singleton<EffectManager>::getPtr()->isEffectDisp() ||
        mm::mtl::Singleton<LightManager>::getPtr()->isLightDisp()) {
        if (m_current) {
            m_current->render();
        }
    }
}

Object* ObjectManager::createGfObjPcByWalkID(const char* name, unsigned int walkId, unsigned int a) {
    bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
    updateCurrent();
    if (skip) {
        return m_current->createGhost(name);
    }
    return m_current->createGfObjPcByWalkID(name, walkId, a);
}

// 1.0.0's ObjectList::createGfObjPcByBladeID: the driver of that blade, or (bit 0 of m_flags) a new driver of
// the blade's creator (3 when it has none)
inline Object* ObjectList::createGfObjPcByBladeID(const char* name, unsigned int bladeId, unsigned int a) {
    if (!(m_flags & 1)) {
        return createGfObj(name, getDriverByBlade(bladeId));
    }
    int creator = gf::GfDataBlade::getCreator(bladeId);
    return createGfObj(name, static_cast<CHARA_TYPE>(1), creator == 0 ? 3 : creator, a, 0);
}

Object* ObjectManager::createGfObjPcByBladeID(const char* name, unsigned int bladeId, unsigned int a) {
    bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
    updateCurrent();
    if (skip) {
        return m_current->createGhost(name);
    }
    return m_current->createGfObjPcByBladeID(name, bladeId, a);
}

Object* ObjectManager::createGfObjBlByWalkID(const char* name, unsigned int walkId, unsigned int a) {
    bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
    updateCurrent();
    if (skip) {
        return m_current->createGhost(name);
    }
    return m_current->createGfObjBlByWalkID(name, walkId, a);
}

Object* ObjectManager::createGfObjBladeByPcID(const char* name, unsigned int pcId, unsigned int a) {
    bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
    updateCurrent();
    if (skip) {
        return m_current->createGhost(name);
    }
    return m_current->createGfObjBladeByPcID(name, pcId, a);
}

Object* ObjectManager::createGfObjPartyIn(const char* name, CHARA_TYPE type, unsigned int id, unsigned int a, unsigned int b) {
    bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
    updateCurrent();
    if (skip) {
        return m_current->createGhost(name);
    }
    return m_current->createGfObjPartyIn(name, type, id, a, b);
}

Object* ObjectManager::createGfObj(const char* name, CHARA_TYPE type, unsigned int id, unsigned int a, unsigned int b) {
    bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
    updateCurrent();
    if (skip) {
        return m_current->createGhost(name);
    }
    return m_current->createGfObj(name, type, id, a, b);
}

Object* ObjectManager::createModel(const char* name, const char* model, unsigned int a, unsigned int b) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        updateCurrent();
        return m_current->createGhost(name);
    }
    mm::mtl::FixStr<128> path(model);
    gf::GfGameEvent::replaceEquipModel(path);
    updateCurrent();
    return m_current->createModel(name, path.m_str, a, b);
}

Object* ObjectManager::createCamera(const char* name, unsigned int id) {
    updateCurrent();
    return m_current->createCamera(name, id);
}

Object* ObjectManager::createEffect(const char* name) {
    updateCurrent();
    return m_current->createEffect(name);
}

Object* ObjectManager::createLight(const char* name, unsigned int id) {
    updateCurrent();
    return m_current->createLight(name, id);
}

// 1.0.0's createScene (same signature): a new scene list, added to m_scenes
ObjectList* ObjectManager::createScene(const char* name) {
    ObjectList* list = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
        ObjectList(name, m_flags & 1);
    m_scenes.push_back(list);
    return list;
}

inline void ObjectManager::init() {
    m_flags = 0;
    m_sceneName = "default";
    m_currentName = "";
    m_current = nullptr;
    mm::mtl::Singleton<ObjectPartyList>::getPtr()->init();
}

inline void ObjectManager::clear() {
    for (unsigned long i = 0; i < m_scenes.size(); i++) {
        if (m_scenes[i]) {
            delete m_scenes[i];
            m_scenes[i] = nullptr;
        }
    }
    m_scenes.clear();
    m_flags = 0;
    m_sceneName = "default";
    m_currentName = "";
    m_current = nullptr;
}

inline void ObjectManager::setupScene() {
    m_sceneName = mm::mtl::PtrSingleton<Manager>::sys()->m_sceneName.m_str;
    updateCurrent();
}

inline void ObjectManager::startScene() {
    m_sceneName = mm::mtl::PtrSingleton<Manager>::sys()->m_sceneName.m_str;
    updateCurrent();
    if (m_current) {
        m_current->startScene();
    }
}

inline void ObjectManager::startPage() {
    if (m_current) {
        m_current->startPage();
    }
}

inline void ObjectManager::endScene() {
    if (m_current) {
        m_current->endScene();
    }
}

inline void ObjectManager::update() {
    if (m_current) {
        m_current->update();
    }
}

inline void ObjectManager::tail() {
    if (m_current) {
        m_current->tail();
    }
}

void ObjectManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        init();
        break;
    case 5:
        setupScene();
        break;
    case 7:
        startScene();
        break;
    case 8:
        startPage();
        break;
    case 10:
        endScene();
        break;
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    case 18:
        tail();
        break;
    default:
        break;
    }
}

Object* ObjectManager::searchByName(const char* name) {
    ObjectList* list = m_current;
    if (list) {
        Object* root = list->m_root;
        if (root) {
            Object* obj = ObjectList::searchByNameSub(root, name);
            if (!obj || obj == root) {
                return nullptr;
            }
            for (int i = 0; i < 4; ++i) {
                if (obj == list->m_categories[i]) {
                    return nullptr;
                }
            }
            return obj;
        }
    }
    return nullptr;
}

}  // namespace event

#include "classes/event/CharaManager.h"
#include "classes/event/QuestManager.h"
#include "classes/event/StatusManager.h"
#include "classes/gf/GfGameEvent.h"

namespace event {

CharaManager::CharaManager() : m_modeFlags(0), m_dispFlags(0), m_offscrID(0), m_reuseFlag(0) {}

void CharaManager::loadResource(const char* name) {
    if (isStreamMode()) {
        return;
    }
    mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->anm(name), nullptr, false);
}

CharaManager::~CharaManager() {}

void CharaManager::clear() {
    m_offscrID = 0;
    m_reuseFlag = 0;
    m_modeFlags = 0;
}

void CharaManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 4) {
        clear();
    }
}

void QuestManager::clear() {
    m_flags = 0;
}

void QuestManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        clear();
        break;
    case 12:
        clear();
        break;
    default:
        break;
    }
}

StatusManager::StatusManager() : m_flags(0) {}

StatusManager::~StatusManager() {}

void StatusManager::init() {
    clear();
    gf::GfGameEvent::setCancelFlag(false);
}

void StatusManager::clear() {
    m_list.clear();
    m_flags = 0;
}

void StatusManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        init();
        break;
    case 12:
        clear();
        break;
    default:
        break;
    }
}

}  // namespace event


#include "classes/event/DofManager.h"
#include "classes/event/FadeManager.h"
#include "classes/event/TextManager.h"
#include "fw/FwDebug.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/event/SkipManager.h"
#include "classes/gf/GfGameManager.h"

namespace event {

DofManager::DofManager()
    : pad_10(0), pad_14(0), pad_18(1), pad_1c(0.0f), pad_20(0.0f), pad_24(5.0f), pad_28(false), pad_2c(0),
      pad_30(0.1f), pad_34(5.0f), pad_38(0.6f), pad_3c(4.0f), pad_40(1.0f), pad_44(0), pad_48(false), pad_50("") {}

DofManager::~DofManager() {}

void DofManager::update() {
    if (!(pad_14 & 1)) return;
    if (pad_28) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setDOF(true);
        acc.setDOFOverride(true);
        acc.setDoFDistance(0.0f);
        acc.setDoFRange(0.0f);
        acc.setDOFAutoFocus(true);
        acc.setDOFFocusNum(pad_2c);
        acc.setDOFFocusMin(pad_30);
        acc.setDoFPixlRatio(pad_34);
        acc.setDoFLens(pad_38);
        acc.setDoFStrength(pad_3c);
        acc.setDoFBlend(pad_40);
        acc.setDofPixlLv(pad_44);
        acc.setDofHLvMode(pad_48);
        pad_14 &= ~2;
    } else {
        if (pad_18 == 0) return;
        if (pad_14 & 2) pad_20 = calcDist(pad_18, pad_1c);
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setDOF(true);
        acc.setDOFOverride(true);
        acc.setDoFDistance(pad_20);
        acc.setDoFRange(pad_24);
        acc.setDOFAutoFocus(false);
        acc.setDOFFocusNum(0);
        acc.setDOFFocusMin(0.0f);
        acc.setDoFPixlRatio(pad_34);
        acc.setDoFLens(pad_38);
        acc.setDoFStrength(pad_3c);
        acc.setDoFBlend(pad_40);
        acc.setDofPixlLv(pad_44);
        acc.setDofHLvMode(pad_48);
        pad_14 &= ~2;
    }
}

float DofManager::calcDist(int type, float dist) {
    if (type < 3) {
        if (type == 2) {
            CharaObj* chara = mm::mtl::Singleton<TextManager>::getPtr()->pad_5d0;
            if (chara != nullptr) return calcDistSub(chara, dist);
        }
        return dist;
    }
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    unsigned int num = cur != nullptr ? cur->m_counts[0] + 3 : 3;
    if (num < (unsigned int)type) return dist;
    ObjectManager* mgr = mm::mtl::Singleton<ObjectManager>::getPtr();
    mgr->updateCurrent();
    Object* cat = mgr->m_current->m_categories[0];
    if (cat == nullptr || cat->m_child == nullptr) return dist;
    int index = type - 3;
    for (Object* obj = cat->m_child; obj != nullptr; obj = obj->m_next) {
        if (index == 0) return calcDistSub(static_cast<ObjectChara*>(obj)->m_chara, dist);
        index--;
    }
    return dist;
}

void DofManager::render() {
    if (!(pad_10 & 1)) return;
    ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
    int x = ml::DevGraph::getRootWidth() - 200;
    int y = ml::DevGraph::getRootHeight() - 275;
    fw::debug::drawSquare2D(mm::Rect<int>(x, y, 180, 210), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 180, 210), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(x + 5, y + 5, "DOF");
    if (acc.isDOFAutoFocus()) {
        fw::debug::drawFont(x + 5, y + 5, "         [simple]");
    } else {
        fw::debug::drawFont(x + 5, y + 5, "         [distance]");
    }
    if (acc.isDOF()) {
        int px = x + 10;
        int py = y + 22;
        if (acc.isDOFAutoFocus()) {
            if (!(acc.getDOFFocusNum() > 0)) {
                fw::debug::drawFont(px, py, "foNo:     AUTO");
            } else {
                fw::debug::drawFont(px, py, "foNo:     %d", acc.getDOFFocusNum());
            }
            fw::debug::drawFont(px, py + 17, "foMin:    %.2f", acc.getDOFFocusMin());
        } else {
            fw::debug::drawFont(px, py, "axis:     %s", getAxisName(pad_18));
            fw::debug::drawFont(px, py + 17, "dist:     %.2f", acc.getDoFDistance());
            fw::debug::drawFont(px, py + 34, "range:    %.2f", acc.getDoFRange());
        }
        fw::debug::drawFont(x + 5, y + 85, "DETAIL");
        if (pad_50[0] != '\0') fw::debug::drawFont(x + 5, y + 85, "         [%s]", pad_50);
        fw::debug::drawFont(x + 10, y + 102, "pixel:    %.2f", acc.getDoFPixlRatio());
        fw::debug::drawFont(x + 10, y + 119, "lens:     %.2f", acc.getDoFLens());
        fw::debug::drawFont(x + 10, y + 136, "strength: %.2f", acc.getDoFStrength());
        fw::debug::drawFont(x + 10, y + 153, "blend:    %.2f", acc.getDoFBlend());
        fw::debug::drawFont(x + 10, y + 170, "pixelLv:  %d", acc.getDofPixlLv());
        fw::debug::drawFont(x + 10, y + 187, "hlv:  %s", acc.isDofHLvMode() ? "ON" : "OFF");
    }
}

const char* DofManager::getAxisName(int axis) {
    if (axis < 3) {
        if (axis == 1) return "CAM";
        if (axis == 2) return "SAY";
        return "NONE";
    }
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    unsigned int num = cur != nullptr ? cur->m_counts[0] + 3 : 3;
    if (num < (unsigned int)axis) return "NONE";
    ObjectManager* mgr = mm::mtl::Singleton<ObjectManager>::getPtr();
    mgr->updateCurrent();
    Object* cat = mgr->m_current->m_categories[0];
    if (cat == nullptr || cat->m_child == nullptr) return "ERR";
    int index = axis - 3;
    for (Object* obj = cat->m_child; obj != nullptr; obj = obj->m_next) {
        if (index == 0) return obj->m_name.m_str;
        index--;
    }
    return "ERR";
}

float DofManager::calcDistSub(CharaObj* chara, float) {
    mm::Vec3 eye = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[0]->m_eye;
    mm::Vec3 tar = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[0]->m_target;
    mm::Vec3 vec = chara->m_pos + mm::Vec3(0.0f, chara->pad_1730, 0.0f) - eye;
    float dist = vec.length();
    vec.normalize();
    mm::Vec3 dir = mm::Vec3(tar) - mm::Vec3(eye);  // the copies give the original's operand order (zkit sweep)
    dir.normalize();
    return dist * vec.dot(dir);
}

void DofManager::play(int type, int id) {
    unsigned char* fp = Bdat::getFP("EVT_dof");
    Bdat::uVal dist, range, pixel, lens, strength, blend;
    dist.ulong = Bdat::getValCheck(fp, "dist", id, 8);
    range.ulong = Bdat::getValCheck(fp, "range", id, 8);
    pixel.ulong = Bdat::getValCheck(fp, "pixel", id, 8);
    lens.ulong = Bdat::getValCheck(fp, "lens", id, 8);
    strength.ulong = Bdat::getValCheck(fp, "strength", id, 8);
    blend.ulong = Bdat::getValCheck(fp, "blend", id, 8);
    int pixelLv = (short)Bdat::getValCheck(fp, "pixelLv", id, 5);
    bool hlv = (short)Bdat::getValCheck(fp, "hlv", id, 5) > 0;
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "name", id, 7));
    play(type, dist.real, range.real, pixel.real, lens.real, strength.real, blend.real, pixelLv, hlv, name);
}

void DofManager::playSimple(int type, int id) {
    unsigned char* fp = Bdat::getFP("EVT_dof");
    Bdat::uVal foMin, pixel, lens, strength, blend;
    foMin.ulong = Bdat::getValCheck(fp, "foMin", id, 8);
    pixel.ulong = Bdat::getValCheck(fp, "pixel", id, 8);
    lens.ulong = Bdat::getValCheck(fp, "lens", id, 8);
    strength.ulong = Bdat::getValCheck(fp, "strength", id, 8);
    blend.ulong = Bdat::getValCheck(fp, "blend", id, 8);
    int pixelLv = (short)Bdat::getValCheck(fp, "pixelLv", id, 5);
    bool hlv = (short)Bdat::getValCheck(fp, "hlv", id, 5) > 0;
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "name", id, 7));
    pad_14 |= 3;
    pad_28 = true;
    pad_2c = type;
    pad_30 = foMin.real;
    pad_34 = pixel.real;
    pad_38 = lens.real;
    pad_3c = strength.real;
    pad_40 = blend.real;
    pad_44 = pixelLv;
    pad_48 = hlv;
    pad_50 = name;
}

FadeManager::~FadeManager() {}

FadeCtrl::~FadeCtrl() {}

void FadeCtrl::clear() {
    for (int i = 0; i < 3; i++) {
        pad_8[i].update();
        pad_8[i].pad_4 = false;
        pad_8[i].pad_c = false;
    }
    pad_68 = 0;
}

void FadeCtrl::update() {
    for (int i = 0; i < 3; i++) pad_8[i].update();
}

void DofManager::clear() {
    stop();
}

void DofManager::OnEventProc(event::MSG_TYPE msg) {
    // the cases' order keeps the two stop() tails apart (as the original's jump table has them)
    switch (msg) {
    case 4:
        clear();
        break;
    case 14:
        update();
        break;
    case 12:
        stop();
        break;
    case 17:
        render();
        break;
    default:
        break;
    }
}

void FadePlanner::update(float step) {
    for (int i = 0; i < 4; i++) {
        Entry& entry = pad_c[i];
        if (entry.pad_0 & 4) {
            entry.pad_20 -= step;
            if (entry.pad_20 < 0.0f) {
                play(static_cast<TYPE>(i));
                entry.pad_0 &= ~4;
            }
        }
    }
}

void FadePlanner::play(TYPE type) {
    Entry& entry = pad_c[type];
    unsigned int frame = entry.pad_4;
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) frame = 0;
    // odd types fade every layer in, even ones fade entry's layer out (inferred from the stores)
    bool in = type & 1;
    FadeCtrl* ctrl = mm::mtl::Singleton<FadeCtrl>::getPtr();
    if (!in) {
        FadeCtrl::Layer& layer = ctrl->pad_8[entry.pad_c];
        layer.pad_4 = true;
        layer.pad_5 = true;
        layer.pad_8 = frame;
        layer.pad_c = true;
        layer.pad_10 = entry.pad_10;
    } else {
        ctrl->pad_8[0].pad_4 = true;
        ctrl->pad_8[0].pad_5 = false;
        ctrl->pad_8[0].pad_8 = frame;
        ctrl->pad_8[0].pad_c = false;
        ctrl->pad_8[1].pad_4 = true;
        ctrl->pad_8[1].pad_5 = false;
        ctrl->pad_8[1].pad_8 = frame;
        ctrl->pad_8[1].pad_c = false;
        if (!(ctrl->pad_68 & 1)) {
            ctrl->pad_8[2].pad_4 = true;
            ctrl->pad_8[2].pad_5 = false;
            ctrl->pad_8[2].pad_8 = frame;
            ctrl->pad_8[2].pad_c = false;
        }
    }
}

FadeManager::FadeManager() : pad_10(0), pad_14(0) {}

void FadeManager::update() {
    const FrameInfo& info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
    pad_18.update(info.pad_4);
    mm::mtl::Singleton<FadeCtrl>::getPtr()->update();
}

bool FadeManager::isFading() const {
    FadeCtrl* ctrl = mm::mtl::Singleton<FadeCtrl>::getPtr();
    for (int i = 0; i < 3; i++) {
        if (ctrl->pad_8[i].pad_4 || gf::GfGameManager::isFading(ctrl->pad_8[i].pad_0)) return true;
    }
    return false;
}

void FadeManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 1:
        // 1.0.0's FadeManager::clear (out of line there at 0x71000E00B8)
        pad_18.clear();
        mm::mtl::Singleton<FadeCtrl>::getPtr()->clear();
        pad_14 = 0;
        break;
    case 15:
        update();
        break;
    default:
        break;
    }
}

// puts the current scene's characters at the EVT_formation rows from id on (ofsX/ofsZ in mtx's frame, snapped to
// the ground; rot in degrees added to mtx's yaw); a named row after the first starts the next formation
bool FormManager::replace(unsigned int id, const mm::Mat44& mtx) {
    unsigned char* fp = Bdat::getFP("EVT_formation");
    unsigned int end = Bdat::getIdTop(fp) + Bdat::getIdCount(fp);
    ObjectManager* objects = mm::mtl::Singleton<ObjectManager>::getPtr();
    if (objects->m_current) {
        unsigned int num = objects->m_current->m_counts[0];
        unsigned int row = id;
        for (unsigned int i = 0; i < num; i++, row++) {
            if (row >= end) {
                break;
            }
            Bdat::uVal ofsX, ofsZ, rot;
            ofsX.ulong = Bdat::getVal(fp, "ofsX", row);
            ofsZ.ulong = Bdat::getVal(fp, "ofsZ", row);
            rot.ulong = Bdat::getVal(fp, "rot", row);
            const char* name = reinterpret_cast<const char*>(Bdat::getVal(fp, "name", row));
            float rotY = rot.real * 0.017453292f;
            if (row > id && name[0] != '\0') {
                break;
            }
            mm::Vec3 ofs(ofsX.real, 0.0f, ofsZ.real);
            mm::Vec3 pos(ofs.x * mtx.m[0][0] + ofs.y * mtx.m[1][0] + ofs.z * mtx.m[2][0] + mtx.m[3][0],
                         ofs.x * mtx.m[0][1] + ofs.y * mtx.m[1][1] + ofs.z * mtx.m[2][1] + mtx.m[3][1],
                         ofs.x * mtx.m[0][2] + ofs.y * mtx.m[1][2] + ofs.z * mtx.m[2][2] + mtx.m[3][2]);
            {
                mm::Vec3 snap = pos;
                if (fw::ColiCheck::getSnapPos(snap, mm::Vec3(pos.x, pos.y + 1.0f, pos.z), 6.0f, 0xFFFFFFFF)) {
                    pos = snap;
                }
            }
            mm::Vec3 front(0.0f, 0.0f, 1.0f);
            rotY += atan2f(front.x * mtx.m[0][0] + front.y * mtx.m[1][0] + front.z * mtx.m[2][0],
                           front.x * mtx.m[0][2] + front.y * mtx.m[1][2] + front.z * mtx.m[2][2]);
            ObjectChara* chara = mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(i);
            chara->setPosAxis(PosAxis(1, pos.x, pos.y, pos.z));
            chara->setRotAxis(RotAxis(1, 0.0f, rotY, 0.0f));
        }
    }
    return true;
}

void ObjectChara::setRotAxis(const RotAxis& rot) {
    m_rot = rot;
    CharaObj* chara = m_chara;
    const mm::Vec3& pos = (chara->m_cmdQueue0.contains(&chara->m_walkPos) ||
                           chara->m_cmdQueue1.contains(&chara->m_walkPos) ||
                           chara->m_cmdQueue1.contains(&chara->m_linerPos))
                              ? chara->m_posGoal
                              : chara->m_pos;
    chara->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(rot.m_type, rot.m_value.x, rot.m_value.y,
                                                                       rot.m_value.z, pos));
    m_chara->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

inline bool FormManager::replace(unsigned int id, int npc) {
    mm::Mat44 mtx = mm::Mat44::identity;
    if (!gf::GfGameUtil::findNpcMat44(mtx, npc)) {
        return false;
    }
    return replace(id, mtx);
}

inline bool FormManager::replace(unsigned int id, const mm::Vec3& pos, float rotY) {
    mm::Mat44 mtx;
    mtx.setRotY(rotY);
    mtx.addTrans(pos);
    return replace(id, mtx);
}

}  // namespace event

#include "classes/event/MovieManager.h"

namespace event {

void MovieManager::OnEventProc(event::MSG_TYPE msg) {
    // the cases' order keeps the two clear() tails apart (as the original's jump table has them)
    switch (msg) {
    case 4:
        clear();
        break;
    case 15:
        update();
        break;
    case 12:
        clear();
        break;
    case 17:
        render();
        break;
    default:
        break;
    }
}

}  // namespace event

#include "classes/event/CamManager.h"

namespace event {

CamManager::CamManager() : m_cur(nullptr) {}

void CamManager::init() {
    m_list.pad_10 = 0;
    for (unsigned long i = 0; i < 4; i++) {
        CamInterface* cam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
            CamInterface(static_cast<fw::CAMERA_TYPE>(i));
        cam->addRef();
        m_interfaces.push_back(cam);
    }
}

// while the free camera runs (pad_14 bit 1) its view drives the first interface
void CamManager::update() {
    if (m_list.pad_14 & 2) {
        m_free.update(mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo());
        mm::Vec3 pos;
        pos.x = m_free.pad_10.x;
        pos.y = m_free.pad_10.y;
        pos.z = m_free.pad_10.z;
        mm::Vec3 tar;
        tar.x = m_free.pad_20.x;
        tar.y = m_free.pad_20.y;
        tar.z = m_free.pad_20.z;
        float fov = m_free.pad_30;
        float roll = m_free.pad_34;
        if (m_free.pad_8) {
            fov = atanf(25.39f / (fov + fov));
            fov = (fov + fov) * 180.0f / 3.1415f;
        }
        CamInterface* cam = mm::mtl::Singleton<CamManager>::getPtr()->m_interfaces[0];
        cam->pad_b0 = roll;
        cam->setLookAt(pos, tar, roll);
        cam->m_fov = fmaxf(fov, 5.0f);
    }
}

void CamManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        init();
        break;
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    default:
        break;
    }
}

}  // namespace event

#include "classes/event/ResManager.h"
#include "classes/event/ResPack.h"

namespace event {

ResPack::~ResPack() {
    if (m_res != nullptr) {
        m_res->release();
        m_res = nullptr;
    }
    m_handle.m_handle = 0;
    m_func = nullptr;
    m_event = nullptr;
}

// inline here: the original's out-of-line copy (0x71000B8D70, called from another unit) stores in an order no source
// form gives yet, while the copies Singleton<ResManager>::getPtr inlines (EffectPlayEva::update) match this one
ResManager::ResManager() : pad_0x18(0), pad_0x10b8(0), pad_0x10bc(0) {}

void ResManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        clear();
        break;
    case 14:
        update();
        break;
    case 12:
        clear();
        break;
    case 16:
        render();
        break;
    default:
        break;
    }
}

}  // namespace event

#include "classes/event/ShakeManager.h"

namespace event {

ShakerRes::~ShakerRes() {
    clear();
}

void Shaker::stop() {
    m_flags = 0;
}

void Shaker::tail() {
    m_cmdQueue.update();
}

void ShakeManager::clear() {
    m_shaker.stop();
    m_flags = 0;
}

ShakeManager::ShakeManager() : m_flags(0) {}

void ShakeManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        clear();
        break;
    case 14:
        update();
        break;
    case 12:
        clear();
        break;
    case 18:
        m_shaker.tail();
        break;
    default:
        break;
    }
}

}  // namespace event

#include "classes/event/CaptureManager.h"

namespace event {

void CaptureManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        if (m_flags & 1) {
            ready();
        }
        break;
    case 8:
        if ((m_flags & 3) == 1) {
            start();
        }
        break;
    case 10:
        if (m_flags & 2) {
            stop();
        }
        break;
    case 12:
        if (m_flags & 2) {
            stop();
        }
        break;
    case 14:
        update();
        break;
    case 17:
        render();
        break;
    default:
        break;
    }
}

}  // namespace event

#include "classes/event/ScheManager.h"

namespace event {

ScheManager::~ScheManager() {}

CaptureManager::~CaptureManager() {}

}  // namespace event

// ---- script commands (session 19) ----
#include "classes/event/ObjectManager.h"

event::ObjectManager::ObjectManager() : m_flags(0), m_dispFlags(0), m_sceneName("default") {}

event::ObjectManager::~ObjectManager() {}
#include "classes/event/ObjectChara.h"
#include "classes/event/ObjectEffect.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "classes/event/ScriptCharaWalkPos.h"
#include "classes/event/ScriptCharaTurnRot.h"
#include "classes/event/ScriptCharaTgt.h"
#include "classes/event/ScriptCharaAction.h"
#include "classes/event/ScriptCharaHead.h"
#include "classes/event/ScriptCharaFacial.h"
#include "classes/event/ScriptCharaMount.h"
#include "classes/event/ScriptEffectPlay.h"
#include "classes/event/ScriptEffectMount.h"
#include "classes/event/ScriptCharaSetIdle.h"
#include "classes/event/ScriptCharaLinerPos.h"
#include "classes/event/ScriptCharaLinerRot.h"
#include "classes/event/ScriptEffectMove.h"
#include "classes/event/ScriptEffectTurn.h"
#include "classes/event/ScriptEffectScale.h"
#include "classes/event/ScriptEffectCast.h"
#include "classes/event/ScriptEffectColor.h"

namespace event {

void ScriptCharaWalkPos::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        m_prevPos = obj->m_pos;
        obj->walkPosAxis(axis, static_cast<EVT_poscvtype>(param.val(4).getS32()), param.val(5).getBool());
    }
}

void ScriptCharaWalkPos::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        PosAxis pos(m_prevPos);
        obj->setPosAxis(pos);
    }
}

void ScriptCharaWalkPos::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setPosAxis(PosAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptCharaTurnRot::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        RotAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        m_prevRot = obj->m_rot;
        mm::mtl::Singleton<ScheManager>::getPtr()->cancelTurn(obj->m_chara->m_gfHandle);
        EVT_rotcvtype cvType = static_cast<EVT_rotcvtype>(param.val(4).getS32());
        float time = param.val(5).getF32();
        obj->turnRotAxis(axis, cvType, time);
    }
}

void ScriptCharaTurnRot::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        RotAxis rot(m_prevRot);
        obj->setRotAxis(rot);
    }
}

void ScriptCharaTurnRot::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setRotAxis(RotAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptCharaTgt::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        float time = param.val(4).getF32();
        m_wasQueued = obj->m_chara->m_cmdQueue2.contains(&obj->m_chara->m_setTar);
        m_prevTar = obj->m_tar;
        mm::mtl::Singleton<ScheManager>::getPtr()->cancelLook(obj->m_chara->m_gfHandle);
        EVT_tarcvtype cvType = static_cast<EVT_tarcvtype>(param.val(5).getS32());
        EVT_aimtype aimType = static_cast<EVT_aimtype>(param.val(6).getS32());
        float a = param.val(7).getF32();
        float b = param.val(8).getF32();
        obj->m_tar = axis;
        obj->m_chara->setTar(axis, time, cvType, aimType, a, b);
    }
}

void ScriptCharaTgt::undo(const event::Param&) {
    // nothing to restore: the active object is looked up and left as is
    mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2);
}

void ScriptCharaTgt::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        float time = param.val(4).getF32();
        obj->m_tar = axis;
        obj->m_chara->setTar(axis, time, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
    }
}

void ScriptCharaLinerPos::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        m_prevPos = obj->m_pos;
        obj->linerPosAxis(axis, param.val(4).getBool(), param.val(5).getF32(), static_cast<CV_TYPE>(param.val(6).getS32()));
    }
}

void ScriptCharaLinerPos::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setPosAxis(m_prevPos);
    }
}

void ScriptCharaLinerPos::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setPosAxis(PosAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptCharaLinerRot::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setRotAxis(m_prevRot);
    }
}

void ScriptCharaLinerRot::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setRotAxis(RotAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptCharaSetIdle::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        pad_8 = obj->m_chara->getIdle();
        obj->m_chara->setIdle(param.val(0).getS32());
    }
}

void ScriptCharaSetIdle::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->setIdle(pad_8);
    }
}

void ScriptCharaAction::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        int id = param.val(0).getS32();
        float time = param.val(1).getF32();
        bool a = param.val(2).getBool();
        bool b = param.val(3).getBool();
        CharaObj* chara = obj->m_chara;
        pad_8 = chara->m_cmdQueue0.contains(&chara->m_playAction) ? chara->m_playAction.m_id : 0;
        mm::mtl::Singleton<ScheManager>::getPtr()->cancelTurn(obj->m_chara->m_gfHandle);
        obj->m_chara->playAction(id, time, a, b);
    }
}

void ScriptCharaAction::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        if (pad_8 > 0) {
            obj->m_chara->playAction(pad_8, 30.0f, true, true);
        } else {
            obj->m_chara->stopAction();
        }
    }
}

void ScriptCharaAction::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        int id = param.val(0).getS32();
        float time = param.val(1).getF32();
        obj->m_chara->playAction(id, time, true, true);
    }
}

void ScriptCharaHead::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        int id = param.val(0).getS32();
        float time = param.val(1).getF32();
        bool a = param.val(2).getBool();
        bool b = param.val(3).getBool();
        float c = param.val(4).getF32();
        float d = param.val(5).getF32();
        CharaObj* chara = obj->m_chara;
        pad_8 = chara->m_cmdQueue1.contains(&chara->m_playHead) ? chara->m_playHead.m_id : 0;
        obj->m_chara->playHead(id, time, a, b, c, d);
    }
}

void ScriptCharaHead::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        if (pad_8 > 0) {
            obj->m_chara->playHead(pad_8, 30.0f, true, true, -1.0f, -1.0f);
        } else {
            obj->m_chara->stopHead();
        }
    }
}

void ScriptCharaHead::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        int id = param.val(0).getS32();
        float time = param.val(1).getF32();
        obj->m_chara->playHead(id, time, true, true, -1.0f, -1.0f);
    }
}

void ScriptCharaFacial::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        int a = param.val(0).getS32();
        float b = param.val(1).getF32();
        int c = param.val(2).getS32();
        float d = param.val(3).getF32();
        int e = param.val(4).getS32();
        float f = param.val(5).getF32();
        int g = param.val(6).getS32();
        float h = param.val(7).getF32();
        float i = param.val(8).getF32();
        float j = param.val(9).getF32();
        CharaObj* chara = obj->m_chara;
        pad_8 = chara->m_cmdQueue1.contains(&chara->m_playFacial) ? chara->m_playFacial.m_id : 0;
        obj->m_chara->playFacial(a, b, c, d, e, f, g, h, i, j);
    }
}

void ScriptCharaFacial::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->playFacial(pad_8, 30.0f, -1, -1.0f, -1, -1.0f, -1, -1.0f, -1.0f, -1.0f);
    }
}

// mounts the active character on the scene's character val 0 (when the scene has that many) at the val 1 joint,
// val 2..4 its position and val 5..7 its rotation
void ScriptCharaMount::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        unsigned int id = param.val(0).getS32();
        const char* name = param.val(1).getStr();
        mm::Vec3 pos(param.val(2).getF32(), param.val(3).getF32(), param.val(4).getF32());
        mm::Vec3 rot(param.val(5).getF32(), param.val(6).getF32(), param.val(7).getF32());
        ObjectList* scene = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
        if (scene != 0 && scene->m_counts[0] > id) {
            ObjectChara* parent = mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(id);
            if (obj != parent) {
                obj->m_chara->mount(parent->m_chara, name, pos, rot);
            }
        }
    }
}

void ScriptCharaMount::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
    }
}

void ScriptEffectPlay::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        const char* name = param.val(0).getStr();
        float a = param.val(1).getF32();
        float b = param.val(2).getF32();
        float c = param.val(3).getF32();
        int d = param.val(4).getS32();
        int e = param.val(5).getS32();
        obj->play(name, a, b, c, d, e);
    }
}

void ScriptEffectPlay::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->m_effect->stop();
    }
}

void ScriptEffectPlay::redo(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        const char* name = param.val(0).getStr();
        float a = param.val(1).getF32();
        float b = param.val(2).getF32();
        float c = param.val(3).getF32();
        int d = param.val(4).getS32();
        obj->play(name, a, b, c, d, 0);
    }
}

void ScriptEffectCast::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        ObjectChara* chara = static_cast<ObjectChara*>(param.val(0).getUserdata());
        AttachActorBase* caster = chara->m_chara->m_attach;
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_ctrl.setCaster(caster);
        }
        obj->m_caster = caster;
        obj->m_mountActor = 0;
    }
}

void ScriptEffectMount::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        ObjectChara* chara = static_cast<ObjectChara*>(param.val(0).getUserdata());
        EVT_attachtype type = static_cast<EVT_attachtype>(param.val(1).getS32());
        const char* name = param.val(2).getStr();
        mm::Vec3 pos(param.val(3).getF32(), param.val(4).getF32(), param.val(5).getF32());
        obj->setMount(chara->m_chara->m_attach, name, pos, param.val(6).getBool(), type);
    }
}

void ScriptEffectMount::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->setMount(nullptr, "", mm::Vec3::zero, false, static_cast<EVT_attachtype>(0));
    }
}

void ScriptEffectMove::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->setPosAxis(m_prevPos);
    }
}

void ScriptEffectMove::redo(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->setPosAxis(PosAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptEffectTurn::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->setRotAxis(m_prevRot);
    }
}

void ScriptEffectTurn::redo(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->setRotAxis(RotAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptEffectScale::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        mm::Vec3 scalePrev = obj->m_effect->m_ctrl.m_scale;
        m_prevScale = scalePrev;
        float scale = param.val(0).getF32();
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_ctrl.m_scale.x = scale;
            effect->m_ctrl.m_scale.y = scale;
            effect->m_ctrl.m_scale.z = scale;
        }
    }
}

void ScriptEffectScale::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_ctrl.m_scale.x = m_prevScale.x;
            effect->m_ctrl.m_scale.y = m_prevScale.y;
            effect->m_ctrl.m_scale.z = m_prevScale.z;
        }
    }
}

void ScriptEffectScale::redo(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        float scale = param.val(0).getF32();
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_ctrl.m_scale.x = scale;
            effect->m_ctrl.m_scale.y = scale;
            effect->m_ctrl.m_scale.z = scale;
        }
    }
}

void ScriptEffectColor::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        mm::Col4 color(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        const mm::Col4& cur = obj->m_effect->m_ctrl.m_color;
        m_prevColor = mm::Col4(cur.r, cur.g, cur.b, cur.a);
        float time = param.val(4).getF32();
        CV_TYPE type = static_cast<CV_TYPE>(param.val(5).getS32());
        obj->m_effect->colorTo(color, time, type);
    }
}

void ScriptEffectColor::undo(const event::Param&) {
    const mm::Col4& prev = m_prevColor;
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_ctrl.m_color = prev;
        }
    }
}

void ScriptEffectColor::redo(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        mm::Col4 color(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        float time = param.val(4).getF32();
        CV_TYPE type = static_cast<CV_TYPE>(param.val(5).getS32());
        obj->m_effect->colorTo(color, time, type);
    }
}

PosAxis::PosAxis(unsigned int type, float x, float y, float z) : m_type(type), m_value(x, y, z) {}

RotAxis::RotAxis(unsigned int type, float x, float y, float z) : m_type(type), m_value(x, y, z) {}

}  // namespace event

#include "classes/event/ObjectCamera.h"
#include "classes/event/CamObj.h"
#include "classes/event/ScriptEffectKill.h"
#include "classes/event/ScriptEffectAnim.h"
#include "classes/event/ScriptCharaMotion.h"
#include "classes/event/ScriptCharaFade.h"
#include "classes/event/TextManager.h"
#include "classes/event/ScriptPlayText.h"
#include "classes/event/ScriptCamPos.h"
#include "classes/event/ScriptCamTar.h"
#include "classes/event/ScriptCamMovePos.h"
#include "classes/event/ScriptCamMoveTar.h"
#include "classes/event/ScriptCamFov.h"
#include "classes/event/ScriptCamRotZ.h"
#include "classes/event/ScriptCamMoveFov.h"
#include "classes/event/ScriptCamMoveRotZ.h"
#include "classes/event/ScriptCamFollowPos.h"
#include "classes/event/ScriptCamFollowTar.h"
#include "classes/event/ScriptCharaWink.h"
#include "classes/event/ScriptCharaTalk.h"

namespace event {

void ScriptCharaLinerRot::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        RotAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        m_prevRot = obj->m_rot;
        obj->linerRotAxis(axis, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
    }
}

void ScriptEffectMove::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        m_prevPos = obj->m_pos;
        obj->linerPosAxis(axis, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
    }
}

void ScriptEffectTurn::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        RotAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        m_prevRot = obj->m_rot;
        obj->linerRotAxis(axis, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
    }
}

void ScriptEffectKill::doit(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->m_effect->m_ctrl.kill();
    }
}

void ScriptEffectKill::redo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->m_effect->m_ctrl.kill();
    }
}

void ScriptEffectAnim::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->m_effect->playAnim(param.val(0).getStr(), param.val(1).getF32());
    }
}

// takes the text down: the subtitle while bit 0 is set, else the window (its strings emptied)
void ScriptPlayText::doit(const event::Param& param) {
    const char* name = param.val(0).getStr();
    int index = param.val(1).getS32();
    float a = param.val(2).getF32();
    float b = param.val(3).getF32();
    float c = param.val(4).getF32();
    int d = param.val(5).getS32();
    CharaObj* chara;
    if (index < 0) {
        ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
        chara = obj != 0 ? obj->m_chara : 0;
    } else {
        ObjectManager* mgr = mm::mtl::Singleton<ObjectManager>::getPtr();
        mgr->updateCurrent();
        Object* obj = mgr->m_current->m_categories[0]->m_child;
        for (int i = 0; i != index; i++) {
            obj = obj->m_next;
        }
        chara = static_cast<ObjectChara*>(obj)->m_chara;
    }
    mm::mtl::Singleton<TextManager>::getPtr()->play(name, chara, a, b, c, d);
}

void ScriptPlayText::undo(const event::Param&) {
    TextManager* text = mm::mtl::Singleton<TextManager>::getPtr();
    if (!(text->m_flags & 1)) {
        text->m_window.erase();
        text->m_window.pad_218 = -1;
        text->m_window.pad_110 = "";
        text->m_window.pad_c = "";
        text->m_window.pad_8 &= ~3;
    } else {
        gf::GfMenuObjEventSubtitle::hideText();
        text->m_caption.pad_c = "";
        text->m_caption.pad_8 &= ~1;
    }
    text->m_flags &= ~0x3c0;
}

void ScriptCharaMotion::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->playMotion(param.val(0).getStr(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    }
}

void ScriptCharaFade::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        float time = param.val(1).getF32();
        bool fade = param.val(0).getBool();
        m_prevFade = (obj->m_chara->m_flags & 0x20) != 0;
        obj->m_chara->playFade(fade, time);
    }
}

void ScriptCharaFade::undo(const event::Param&) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->playFade(m_prevFade, 0.0f);
    }
}

void ScriptCharaFade::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->m_chara->playFade(param.val(0).getBool(), 0.0f);
    }
}

void ScriptCamPos::doit(const event::Param& param) {
    // the active camera read in place (not through ObjectManager::getActive): the original's typed pointer
    // addresses the inlined FixedVector::clear's elements from the object (ldr [obj + i * 32 + 0xa0]!)
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        unsigned int axisType = param.val(0).getS32();
        mm::Vec3 value(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        PosAxis axis(axisType, value.x, value.y, value.z);
        CV_TYPE type = static_cast<CV_TYPE>(param.val(4).getS32());
        m_prevPos = obj->m_pos;
        obj->m_pos = axis;
        obj->m_posQueue.clear();
        obj->m_posQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setPos(axis, type);
        if (m_prevPos.m_type != axisType || !(value - m_prevPos.m_value).isZero()) {
            mm::mtl::Singleton<TextManager>::getPtr()->m_flags |= 0x20;
        }
    }
}

void ScriptCamPos::undo(const event::Param&) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        PosAxis axis(m_prevPos);
        obj->m_pos = axis;
        obj->m_posQueue.clear();
        obj->m_posQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setPos(axis, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamMovePos::doit(const event::Param& param) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        float time = param.val(4).getF32();
        CV_TYPE type = static_cast<CV_TYPE>(param.val(5).getS32());
        obj->m_posQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmPos(time, axis, type);
    }
}

void ScriptCamMovePos::redo(const event::Param& param) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        CV_TYPE type = static_cast<CV_TYPE>(param.val(5).getS32());
        obj->m_posQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmPos(0.0f, axis, type);
    }
}

void ScriptCamTar::doit(const event::Param& param) {
    // the active camera read in place, as ScriptCamPos::doit
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        unsigned int axisType = param.val(0).getS32();
        mm::Vec3 value(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        TarAxis axis(axisType, value.x, value.y, value.z);
        CV_TYPE type = static_cast<CV_TYPE>(param.val(4).getS32());
        m_prevTar = obj->m_tar;
        obj->m_tar = axis;
        obj->m_tarQueue.clear();
        obj->m_tarQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setTar(axis, type);
        if (m_prevTar.m_type != axisType || !(value - m_prevTar.m_value).isZero()) {
            mm::mtl::Singleton<TextManager>::getPtr()->m_flags |= 0x20;
        }
    }
}

void ScriptCamTar::undo(const event::Param&) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        TarAxis axis(m_prevTar);
        obj->m_tar = axis;
        obj->m_tarQueue.clear();
        obj->m_tarQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setTar(axis, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamMoveTar::doit(const event::Param& param) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        float time = param.val(4).getF32();
        CV_TYPE type = static_cast<CV_TYPE>(param.val(5).getS32());
        obj->m_tarQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmTar(time, axis, type);
    }
}

void ScriptCamMoveTar::redo(const event::Param& param) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        CV_TYPE type = static_cast<CV_TYPE>(param.val(5).getS32());
        obj->m_tarQueue.push_back(axis);
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmTar(0.0f, axis, type);
    }
}

void ScriptCamFov::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = param.val(0).getF32();
        CV_TYPE type = static_cast<CV_TYPE>(param.val(1).getS32());
        m_prevFov = obj->m_cam->m_fov;
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setFov(value, type);
    }
}

void ScriptCamFov::undo(const event::Param&) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = m_prevFov;
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setFov(value, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamRotZ::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = param.val(0).getF32() * 0.0174532924f;
        CV_TYPE type = static_cast<CV_TYPE>(param.val(1).getS32());
        m_prevRotZ = obj->m_cam->m_rotZ;
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setRotZ(value, type);
    }
}

void ScriptCamRotZ::undo(const event::Param&) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = m_prevRotZ;
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.setRotZ(value, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamMoveFov::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = param.val(0).getF32();
        float time = param.val(1).getF32();
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmFov(time, value, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamMoveFov::redo(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = param.val(0).getF32();
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmFov(0.0f, value, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamMoveRotZ::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = param.val(0).getF32() * 0.0174532924f;
        float time = param.val(1).getF32();
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmRotZ(time, value, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamMoveRotZ::redo(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float value = param.val(0).getF32() * 0.0174532924f;
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        cam->m_hands.addAnmRotZ(0.0f, value, static_cast<CV_TYPE>(1));
    }
}

void ScriptCamFollowPos::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        m_prevFollow = (cam->m_hands.m_flags & 1) != 0;
        bool follow = param.val(0).getBool();
        cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        if (follow) {
            cam->m_hands.m_flags |= 1;
        } else {
            cam->m_hands.m_flags &= ~1;
        }
    }
}

void ScriptCamFollowTar::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        m_prevFollow = (cam->m_hands.m_flags & 1) != 0; // bit 0 (the position flag) here too, as the original reads it
        bool follow = param.val(0).getBool();
        cam = obj->m_cam;
        cam->changeActive(&cam->m_hands);
        if (follow) {
            cam->m_hands.m_flags |= 2;
        } else {
            cam->m_hands.m_flags &= ~2;
        }
    }
}

}  // namespace event

#include "plugin/Bdat.h"
#include "classes/event/ScriptSetActive.h"
#include "classes/event/ScriptCamCut.h"
#include "classes/event/ScriptCamMotion.h"
#include "classes/event/ScriptCamNearfar.h"
#include "classes/event/ScriptCharaWink.h"
#include "classes/event/ScriptCharaTalk.h"
#include "classes/event/ScriptCamFollowPos.h"
#include "classes/event/ScriptCamFollowTar.h"
#include "classes/event/ObjectList.h"
#include "classes/event/GroupManager.h"
#include "classes/event/TextManager.h"
#include "mm/Vec3.h"

namespace event {

void ScriptSetActive::doit(const event::Param& param) {
    const char* path = param.val(0).getStr();
    ObjectList* scene = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    m_prevActive = scene != 0 ? scene->m_active : 0;
    ObjectManager* mgr = mm::mtl::Singleton<ObjectManager>::getPtr();
    mgr->updateCurrent();
    mgr->m_current->setActivePath(path);
}

int ScriptUtil::getObjType(Object* obj) {
    if (obj == nullptr) {
        return 0;
    }
    return obj->m_type;
}

void ScriptSetActive::undo(const event::Param&) {
    Object* prev = m_prevActive;
    ObjectManager* mgr = mm::mtl::Singleton<ObjectManager>::getPtr();
    mgr->updateCurrent();
    mgr->m_current->m_active = prev;
}

void ScriptCamMotion::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        const char* name = param.val(0).getStr();
        mm::Vec3 pos(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_motion);
        cam->m_motion.play(name, pos);
    }
}

void ScriptCamMotion::undo(const event::Param&) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        CamObj* cam = obj->m_cam;
        cam->changeActive(&cam->m_motion);
        cam->m_motion.stop();
    }
}

void ScriptCamNearfar::doit(const event::Param& param) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        int id = param.val(0).getS32();
        m_prevNear = obj->m_cam->m_hands.m_near;
        m_prevFar = obj->m_cam->m_hands.m_far;
        CamObj* cam = obj->m_cam;
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } nearVal, farVal;
        nearVal.bits = (unsigned int)Bdat::getValCheck(Bdat::getFP("EVT_nearfar"), "near", id, 8);
        farVal.bits = (unsigned int)Bdat::getValCheck(Bdat::getFP("EVT_nearfar"), "far", id, 8);
        cam->m_hands.m_near = nearVal.value;
        cam->m_hands.m_far = farVal.value;
    }
}

void ScriptCamNearfar::undo(const event::Param&) {
    ObjectCamera* obj = static_cast<ObjectCamera*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(3));
    if (obj != 0) {
        float nearClip = m_prevNear;
        float farClip = m_prevFar;
        CamObj* cam = obj->m_cam;
        cam->m_hands.m_near = nearClip;
        cam->m_hands.m_far = farClip;
    }
}

void ScriptCamCut::doit(const event::Param& param) {
    // the active camera read in place, as ScriptCamPos::doit
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        const char* name = param.val(0).getStr();
        m_prevCut = obj->m_cutName;
        obj->m_cutName = name;
    }
}

void ScriptCamCut::undo(const event::Param&) {
    ObjectList* cur = mm::mtl::Singleton<ObjectManager>::getPtr()->m_current;
    ObjectCamera* obj = cur != 0 ? static_cast<ObjectCamera*>(cur->m_active) : 0;
    if (obj != 0 && obj->m_type == 3) {
        obj->m_cutName = m_prevCut;
    }
}

void ScriptCharaWink::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        int a = param.val(0).getS32();
        float b = param.val(1).getF32();
        bool c = param.val(2).getBool();
        float d = param.val(3).getF32();
        float e = param.val(4).getF32();
        int f = param.val(5).getS32();
        bool g = param.val(6).getBool();
        bool h = param.val(7).getBool();
        obj->m_chara->playWink(a, b, c, d, e, f, g, h);
    }
}

void ScriptCharaTalk::doit(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        float b = param.val(0).getF32();
        bool c = param.val(1).getBool();
        bool d = param.val(2).getBool();
        float e = param.val(3).getF32();
        float f = param.val(4).getF32();
        float g = param.val(5).getF32();
        float h = param.val(6).getF32();
        obj->m_chara->playTalk(true, b, c, d, e, f, g, h);
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void GroupManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    }
}

GroupManager::~GroupManager() {}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
bool VoiceManager::playAuto(const char* name, float frame, IVoiceEvent* event) {
    if (!(pad_10 & 1)) {
        return false;
    }
    const char* path = m_maker.makePath(name);
    if (path == nullptr) {
        return false;
    }
    bool found = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(path);
    if (found) {
        pad_10 |= 2;
    } else {
        pad_10 &= ~2;
    }
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        return found;
    }
    return m_player.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path), frame, event);
}

void TextManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        init();
        break;
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    case 18:
        m_flags &= ~0x20;
        break;
    }
}

}  // namespace event
#include "classes/event/UIManager.h"
#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/gf/GfMenuObjChapterTelop.h"
#include "classes/gf/GfMenuObjZoneTelop.h"
#include "classes/event/SeManager.h"
#include "classes/gf/GfMenuObjStaffroll.h"
#include "classes/gf/GfMenuObjOpeningTelop.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuObjEventSkip.h"
#include "classes/gf/GfMenuObjBalloon.h"
#include "classes/gf/GfMenuObjShop.h"
#include "classes/minigame/tora/MinigameUpdatableObject.h"
#include "classes/event/ModelManager.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfInitParamNpc.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/gf/GfAssetSetupEventObj.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfEvtModelNpc.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "classes/gf/GfEvtModelWeapon.h"
#include "classes/gf/GfEvtModelEvent.h"
#include "classes/event/DebugManager.h"
#include "classes/event/FrameManager.h"
#include "classes/event/CpuManager.h"

namespace event {

FrameManager::FrameManager()
    : pad_18(0), pad_d0(), m_frame(0.0f), pad_15c(0.0f), pad_160(0.0f), pad_164(0.0f), pad_16c(0),
      m_maxFrame(1000.0f), pad_184(1), m_keyFrames(), m_frameInfo() {
    pad_10.reset();
    pad_14 = 2;
    for (int i = 0; i < 22; i++) {
        pad_20[i] = reinterpret_cast<gf::GF_PAUSE_HANDLE*>(-1);
    }
}

void FrameManager::initPage() {
    resetPage();
    pad_160 = pad_15c;
    pad_10.set(8);
    CpuManager* cpu = mm::mtl::Singleton<CpuManager>::getPtr();
    cpu->m_frame = 0.0f;
    cpu->m_cpuFrame = 0.0f;
    cpu->m_startFrame = cpu->calcCpuFrame();
    cpu->m_flags |= 1;
}

void FrameManager::tail() {
    if (pad_14 & 0x20) {
        frameInfo();
    }
    if ((pad_14 & 2) && (pad_10.test(8) || m_frame != pad_164) && pad_d0.m_str[0] != '\0') {
        // what it was sent is compiled out
        mm::mtl::Singleton<CopydataManager>::getPtr();
    }
    if (pad_14 & 4) {
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && pad_11ac++ >= 10) {
            pad_14 &= ~4;
        }
    }
    pad_10.reset(6);
    pad_10.reset(8);
}

void FrameManager::pauseClearAll() {
    for (unsigned int i = 0; i < 22; i++) {
        pause(static_cast<PAUSE_TYPE>(i), false);
    }
}

void FrameManager::addKeyFrame(float frame, bool flag) {
    KeyFrame key = {frame, flag};
    if (!m_keyFrames.empty() && !(key.frame > m_keyFrames.back().frame)) {
        for (unsigned long i = 0; i < m_keyFrames.size(); i++) {
            KeyFrame& entry = m_keyFrames[i];
            if (key.frame == entry.frame) {
                if (flag) {
                    entry.flag = true;
                }
                return;
            }
            if (key.frame < entry.frame) {
                float entryFrame = entry.frame;
                bool entryFlag = entry.flag;
                entry.frame = key.frame;
                entry.flag = key.flag;
                key.frame = entryFrame;
                key.flag = entryFlag;
            }
        }
    }
    m_keyFrames.push_back(key);
}

FrameManager::~FrameManager() {}

void SeManager::load(const char* name) {
    gf::GfGameEvent::createSe(name);
    m_loadCount++;
}

void SeManager::changeVolume(int id, float volume, float frame) {
    if (m_objs[id].m_flags & 1) {
        m_objs[id].changeVolume(volume, frame);
    }
}

void SeManager::pan(int id, float pan, float frame, CV_TYPE type) {
    if (m_objs[id].m_flags & 1) {
        m_objs[id].pan(pan, frame, type);
    }
}

SeManager::~SeManager() {}

bool UIManager::openSkip(bool& result) {
    if (!(m_openFlags & 1)) {
        m_openFlags |= 1;
        pad_2b4 = 14;
    } else {
        if (pad_2b4 == 11) {
            m_skipContext = gf::GfMenuCallContext::create();
            gf::GfMenuObjEventSkip::open(m_skipContext);
        }
        if (!(pad_2b4 >= 0 && pad_2b4-- != 0) && m_skipContext->isTerm()) {
            gf::GfMenuCallContext::GfMenuResult res = {};
            m_skipContext->popResult(res);
            mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(1), false);
            m_openFlags &= ~1;
            if (m_skipContext != nullptr) {
                m_skipContext->release();
                m_skipContext = nullptr;
            }
            pad_2b4 = -1;
            result = res.m_id == 0;
            return true;
        }
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(1), true);
    return false;
}

// the windows 73..153 open after a fade out and a wait
bool UIManager::openCommonUI(unsigned int id) {
    bool fade = id >= 73 && id <= 153;
    if (!(m_openFlags & 4)) {
        bool skip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip();
        if (fade) {
            mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 40, static_cast<FadeCtrl::PRIO>(0), nullptr);
        }
        pad_2b0 = skip ? 0 : 30;
        m_openFlags |= 4;
    }
    bool wait = fade && (mm::mtl::Singleton<FadeManager>::getPtr()->isFading() || pad_2b0-- > 0);
    if (!wait) {
        if (!(m_openFlags & 2)) {
            gf::GfMenuManager::openCommonWindow(id);
            m_openFlags |= 2;
        }
        wait = gf::GfMenuManager::isOpenCommonWindow();
    }
    if (wait) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(4), true);
        return false;
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(4), false);
    m_openFlags &= ~6;
    return true;
}

void SkipManager::skip(bool skip, float frame) {
    if (skip) {
        if ((m_flags & 1) && m_endFrame == frame) {
            return;
        }
        mm::mtl::Singleton<MovieManager>::getPtr()->stop();
        m_endFrame = frame;
        m_flags |= 1;
    } else if (m_flags & 1) {
        m_flags &= ~1;
    }
}

void SkipManager::setSkipVolume(bool skip) {
    if (skip) {
        if (!(m_flags & 2)) {
            mm::mtl::Singleton<VolumeManager>::get().m_skip.start();
            m_flags |= 2;
        }
    } else {
        if (m_flags & 2) {
            mm::mtl::Singleton<VolumeManager>::get().m_skip.end();
            CsSndManager* snd = mm::mtl::Singleton<CsSndManager>::getPtr();
            FrameManager* frame = mm::mtl::Singleton<FrameManager>::getPtr();
            if (snd->m_flags & 2) {
                float time = (frame->getFrame() + snd->m_bgmFrame1) / 30.0f;
                mm::mtl::PtrSingleton<fw::SoundManager>::sys()->setPlayTime(snd->m_bgmHandle1, time);
            }
            m_flags &= ~2;
        }
    }
}

bool UIManager::execFieldSkill(unsigned int id, bool& result) {
    if (!(m_openFlags & 0x8)) {
        m_fieldSkillResult = gf::GfGameUtil::evalSumFs(id, 0);
        m_openFlags |= 0x8;
    }
    if (gf::GfMenuFieldSkill::isRunning()) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(5), true);
        return false;
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(5), false);
    m_openFlags &= ~0x8;
    result = m_fieldSkillResult;
    return true;
}

bool UIManager::openShopUI(unsigned int id, bool& result) {
    if (!(m_openFlags & 0x10)) {
        m_shopContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjShop::OpenParam param;
        param.m_option = false;
        param.m_shopId = id;
        gf::GfMenuObjShop::open(m_shopContext, param);
        m_openFlags |= 0x10;
    }
    if (!m_shopContext->isTerm()) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(6), true);
        return false;
    }
    gf::GfMenuCallContext::GfMenuResult res = {};
    m_shopContext->popResult(res);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(6), false);
    m_openFlags &= ~0x10;
    if (m_shopContext != nullptr) {
        m_shopContext->release();
        m_shopContext = nullptr;
    }
    result = res.m_id == 1;
    return true;
}

UIManager::UIManager()
    : m_openFlags(0), m_flags(0), pad_18(0), m_fieldSkillResult(true), m_skipContext(nullptr),
      m_shopContext(nullptr), pad_30(0), m_payoffResult(0), pad_40(0), m_rewardContext(nullptr),
      m_bladeNameContext(nullptr), m_chapTelopContext(nullptr), pad_68(0), m_avanTitleContext(nullptr),
      m_zoneTelopContext(nullptr), m_minigame(nullptr), pad_2a8(0) {}

int UIManager::getPayoffUI() const {
    return m_payoffResult;
}

int UIManager::getExperienceUI() const {
    return m_exResult;
}

bool UIManager::openRewardUI(unsigned int id) {
    bool opened = true;
    if (!(m_openFlags & 0x80)) {
        m_rewardContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjBalloon::OpenGetItemParam param;
        param.m_id = id;
        opened = gf::GfMenuObjBalloon::openGetItem(m_rewardContext, param);
        m_openFlags |= 0x80;
    }
    if (!opened || m_rewardContext->isTerm()) {
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(9), false);
        m_openFlags &= ~0x80;
        if (m_rewardContext != nullptr) {
            m_rewardContext->release();
            m_rewardContext = nullptr;
        }
        return true;
    }
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(9), true);
    return false;
}

void UIManager::openBladeNameUI() {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        if (m_bladeNameContext != nullptr) {
            m_bladeNameContext->release();
            m_bladeNameContext = nullptr;
        }
        m_bladeNameContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjBladeCreate::openCreatedBladeName(m_bladeNameContext);
        m_openFlags |= 0x100;
    }
}

bool UIManager::openChapTelopUI(unsigned int id) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && !(m_openFlags & 0x200)) {
        m_chapTelopContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjChapterTelop::openEndTelop(m_chapTelopContext, id);
        pad_68 = 1;
        mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 0, static_cast<FadeCtrl::PRIO>(0), nullptr);
        m_openFlags |= 0x200;
    }
    return true;
}

void UIManager::openAvanTitleUI(unsigned int id) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && !(m_openFlags & 0x800)) {
        m_avanTitleContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjChapterTelop::openAvanTitle(m_avanTitleContext, id);
        m_openFlags |= 0x800;
    }
}

void UIManager::closeAvanTitleUI(int frame) {
    if (m_openFlags & 0x800) {
        gf::GfMenuObjChapterTelop::close(frame);
        if (m_avanTitleContext != nullptr) {
            m_avanTitleContext->release();
            m_avanTitleContext = nullptr;
        }
        m_openFlags &= ~0x800;
    }
}

void UIManager::openZoneTelopUI(unsigned int id) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && !(m_openFlags & 0x1000)) {
        m_zoneTelopContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjZoneTelop::open(m_zoneTelopContext, id);
        m_openFlags |= 0x1000;
    }
}

void UIManager::openOpeningTelopUI(OPTELOP_TYPE type, unsigned int id) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        if (!(m_openFlags & 0x2000)) {
            gf::GfMenuManager::openOpeningTelop();
            m_openFlags |= 0x2000;
        }
        switch (type) {
        case OPTELOP_C:
            gf::GfMenuObjOpeningTelop::openCenter(id);
            break;
        case OPTELOP_LB:
            gf::GfMenuObjOpeningTelop::openLeft(id);
            break;
        case OPTELOP_RT:
            gf::GfMenuObjOpeningTelop::openRight(id);
            break;
        case OPTELOP_LH:
            gf::GfMenuObjOpeningTelop::openLeftHalf(id);
            break;
        case OPTELOP_RH:
            gf::GfMenuObjOpeningTelop::openRightHalf(id);
            break;
        }
    }
}

void UIManager::closeOpeningTelopUI(OPTELOP_TYPE type) {
    switch (type) {
    case OPTELOP_C:
        gf::GfMenuObjOpeningTelop::closeCenter();
        break;
    case OPTELOP_LB:
        gf::GfMenuObjOpeningTelop::closeLeft();
        break;
    case OPTELOP_RT:
        gf::GfMenuObjOpeningTelop::closeRight();
        break;
    case OPTELOP_LH:
        gf::GfMenuObjOpeningTelop::closeLeftHalf();
        break;
    case OPTELOP_RH:
        gf::GfMenuObjOpeningTelop::closeRightHalf();
        break;
    }
}

void UIManager::startStaffrollUI(float speed, int type) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        if (!(m_openFlags & 0x4000)) {
            gf::GfMenuManager::openStaffroll();
            m_openFlags |= 0x4000;
        }
        gf::GfMenuObjStaffroll::start(speed / 30.0f, type);
    }
}

void UIManager::endStaffroll() {
    gf::GfMenuObjStaffroll::fadeout();
}

bool UIManager::startNewGameWait() {
    if (!mm::mtl::Singleton<DebugManager>::getPtr()->testFlag(12)) {
        unsigned int flags = m_openFlags;
        if (!(flags & 0x40000)) {
            flags |= 0x40000;
            m_openFlags = flags;
        }
        FrameManager* frame = mm::mtl::Singleton<FrameManager>::getPtr();
        if (!(flags & 0x80000)) {
            frame->pause(static_cast<FrameManager::PAUSE_TYPE>(18), true);
            return false;
        }
        frame->pause(static_cast<FrameManager::PAUSE_TYPE>(18), false);
        m_openFlags &= ~0x40000;
    }
    return true;
}

bool UIManager::openMinigame() {
    if (!(m_openFlags & 0x100000)) {
        m_minigame = minigame::tora::factory::create(nullptr);
        m_openFlags |= 0x100000;
    }
    if (!m_minigame->isTerminate()) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(13), true);
        return false;
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(13), false);
    m_minigame->setTerminate();
    m_minigame = nullptr;
    m_openFlags &= ~0x100000;
    return true;
}

bool UIManager::openCampUI(bool& talk) {
    if (!(m_openFlags & 0x400000)) {
        gf::GfMenuManager::openCampMenu();
        m_openFlags |= 0x400000;
    }
    bool open = gf::GfMenuManager::isOpenCampMenu();
    bool select = gf::GfMenuManager::isCampSelectTalk();
    if (!select && open) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(15), true);
        return false;
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(15), false);
    m_openFlags &= ~0x400000;
    talk = select;
    return true;
}

bool UIManager::openBtlchOrderUI() {
    if (!(m_openFlags & 0x800000)) {
        gf::GfMenuManager::openBtlchOrder();
        m_openFlags |= 0x800000;
    }
    if (gf::GfMenuManager::isOpenBtlchOrder()) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(16), true);
        return false;
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(16), false);
    m_openFlags &= ~0x800000;
    return true;
}

bool UIManager::openNamedUI() {
    if (!(m_openFlags & 0x1000000)) {
        gf::GfMenuManager::openNamedList();
        m_openFlags |= 0x1000000;
    }
    if (gf::GfMenuManager::isOpenNamedList()) {
        mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
        mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(17), true);
        return false;
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(static_cast<FrameManager::PAUSE_TYPE>(17), false);
    m_openFlags &= ~0x1000000;
    return true;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void UIManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 2:
        logout();
        break;
    case 4:
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    }
}

void ModelObj::setupModel(const DESC& desc) {
    gf::GfAssetSetupEventObj setup;
    setup.setRefResource(0, desc.files[0].name.m_str, desc.files[0].data, desc.files[0].size);
    if (desc.files[1].data != nullptr) {
        setup.setRefResource(1, desc.files[1].name.m_str, desc.files[1].data, desc.files[1].size);
    }
    gf::GfInitParamEventObj param;
    param.m_createType = 11;
    param.pad_81 = false;
    param.m_assetSetup = &setup;
    param.pad_24 = pad_5c;
    m_model = gf::GfGameEvent::createEventObj(param);
    m_busyWait = 2;
    m_handle = m_model->m_handle;
}

ModelObj::~ModelObj() {
    if (m_model) {
        m_model->release();
        m_model = nullptr;
    }
    if (m_stmReader) {
        m_stmReader->release();
        m_stmReader = nullptr;
    }
}

ModelObj* ModelManager::createModel(const char* name, bool flag, unsigned int arg, int user) {
    ModelObj* obj;
    if ((mm::mtl::Singleton<MdlstmManager>::getPtr()->pad_14 & 1) &&
        (obj = searchModel(user, name, flag, arg)) != nullptr) {
        obj->setReserve(user, true);
        return obj;
    }
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ModelObj(name, flag, arg);
    obj->setReserve(user, true);
    m_objs.push_back(obj);
    return obj;
}

ModelObj* ModelManager::searchModel(unsigned int user, const char* name, bool flag, unsigned int arg) {
    for (unsigned long i = 0; i < m_objs.size(); i++) {
        if (!m_objs[i]->isReserve(user)) {
            ModelObj* obj = m_objs[i];
            if (obj->isSame(name, flag, arg)) {
                return m_objs[i];
            }
        }
    }
    return nullptr;
}

ModelObj* ModelManager::createModel(const char* name, const ModelObj::DESC& desc, bool flag, unsigned int arg,
                                    int user) {
    ModelObj* obj;
    if ((mm::mtl::Singleton<MdlstmManager>::getPtr()->pad_14 & 1) &&
        (obj = searchModel(user, name, desc, flag, arg)) != nullptr) {
        obj->setReserve(user, true);
        return obj;
    }
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
        ModelObj(name, desc, flag, arg);
    obj->setReserve(user, true);
    m_objs.push_back(obj);
    return obj;
}

ModelObj* ModelManager::searchModel(unsigned int user, const char* name, const ModelObj::DESC& desc, bool flag,
                                    unsigned int arg) {
    for (unsigned long i = 0; i < m_objs.size(); i++) {
        if (!m_objs[i]->isReserve(user)) {
            ModelObj* obj = m_objs[i];
            if (obj->isSame(name, desc, flag, arg)) {
                return m_objs[i];
            }
        }
    }
    return nullptr;
}

ModelObj* ModelManager::searchModel(unsigned int user, MODEL_TYPE type, unsigned int id,
                                    const ModelObj::OPTION& option, bool flag, unsigned int arg) {
    for (unsigned long i = 0; i < m_objs.size(); i++) {
        if (!m_objs[i]->isReserve(user)) {
            ModelObj* obj = m_objs[i];
            if (obj->isSame(type, id, option, flag, arg)) {
                return m_objs[i];
            }
        }
    }
    return nullptr;
}

void ModelManager::destroyModel(ModelObj* obj, int user) {
    if (obj == nullptr) {
        return;
    }
    if (mm::mtl::Singleton<MdlstmManager>::getPtr()->pad_14 & 1) {
        obj->setReserve(user, false);
        if (obj->isReserve(-1)) {
            return;
        }
    }
    // the original's lookup tests the entries against null after the delete: it erases the first non-null entry,
    // not necessarily the model's
    delete obj;
    for (mm::mtl::FixedVector<ModelObj*, 1024>::iterator it = m_objs.begin(); it != m_objs.end(); ++it) {
        if (*it != nullptr) {
            m_objs.erase(it);
            break;
        }
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void ModelManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 14) {
        update();
    }
}

ModelManager::~ModelManager() {}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void DebugManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        m_flags &= ~0x150;
        break;
    case 15:
        update();
        break;
    case 17:
        render();
        break;
    case 19:
        if (m_flags & 0x4000) {
            m_flags &= ~0x6000;
        }
        break;
    }
}

}  // namespace event
#include "classes/event/EffectManager.h"
#include "classes/event/LightManager.h"
#include "classes/event/SeamlessManager.h"
#include "classes/event/SkipManager.h"
#include "classes/event/BgmManager.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/event/HideManager.h"
#include "classes/event/DebugManager.h"
#include "classes/event/MovieManager.h"
#include "classes/event/TodoManager.h"
#include "classes/event/DataManager.h"
#include "classes/event/SeqManager.h"
#include "classes/ml/DevSetting.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/event/MemoryManager.h"
#include "classes/event/ResManager.h"

namespace event {

void EffectObj::moveTo(const mm::Vec3& pos, float time, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(pos.x);
    param.val(2).setF32(pos.y);
    param.val(3).setF32(pos.z);
    param.val(4).setF32(time);
    param.val(5).setS32(type);
    m_cmdQueue.push_back(&m_linearPos, param);
}

void EffectObj::turnTo(const mm::Vec3& rot, float time, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(rot.x);
    param.val(2).setF32(rot.y);
    param.val(3).setF32(rot.z);
    param.val(4).setF32(time);
    param.val(5).setS32(type);
    m_cmdQueue.push_back(&m_linearRot, param);
}

void EffectObj::colorTo(const mm::Col4& color, float time, CV_TYPE type) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
        return;
    }
    CmdParam param;
    param.val(0).setUserdata(this);
    param.val(1).setF32(color.r);
    param.val(2).setF32(color.g);
    param.val(3).setF32(color.b);
    param.val(4).setF32(color.a);
    param.val(5).setF32(time);
    param.val(6).setS32(type);
    m_cmdQueue.push_back(&m_linearCol, param);
}

EffectRes::~EffectRes() {
    if (m_pack != nullptr) {
        m_pack->release();
        m_pack = nullptr;
    }
}

void EffectRes::OnResEvent(const IResEvent::PARAM& param) {
    if (param.m_type == 3) {
        m_pack = fw::EffectPack::createFromMemory(param.m_data, param.m_size, param.m_name, false);
        m_flags &= ~1;
        return;
    }
    m_pack = nullptr;
    m_flags &= ~1;
}

EffectManager::EffectManager() : m_flags(0), m_dispFlags(0), pad_a0(0), m_offscrID(0), pad_ac(0) {}

void EffectManager::load(const char* name) {
    EffectRes* found = nullptr;
    for (unsigned long i = 0; i < m_entries.size(); i++) {
        if (strcmp(name, m_entries[i]->m_name.m_str) == 0) {
            found = m_entries[i];
            break;
        }
    }
    if (found != nullptr) {
        return;
    }
    m_entries.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) EffectRes(name));
}

void EffectManager::loadResource(const char* name) {
    if (m_flags & 1) {
        return;
    }
    mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr, false);
}

LightManager::LightManager() : m_flags(0), m_modeFlags(0), m_offScrLights(), m_evtLight(nullptr) {}

void LightManager::render() {
    if (!(m_flags & 1)) {
        return;
    }
    int x = ml::DevGraph::getRootWidth() - 250;
    if (m_evtLight && m_evtLight->isPlaying()) {
        m_evtLight->render(x, 280);
    }
    for (int i = 1; i < 4; i++) {
        LightEvt* light = m_offScrLights[i];
        if (light && light->isPlaying()) {
            light->render(x, 280 + i * 50);
        }
    }
}

LightManager::~LightManager() {}

void LightManager::loadResource(const char* name) {
    if (m_modeFlags & 1) {
        return;
    }
    mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->lgt(name), nullptr, true);
}

SeamlessManager::SeamlessManager() : m_flags(0), m_dispFlags(0), m_firstKeys(), m_keys() {}

void SeamlessManager::update() {
    if (m_keys.empty()) {
        return;
    }
    const FrameInfo& info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
    if (m_keys.empty()) {
        return;
    }
    while (m_keys.begin()->m_frame + 5.0f <= info.pad_0) {
        m_keys.erase(m_keys.begin());
        m_flags &= ~2;
        if (m_keys.empty()) {
            return;
        }
    }
    m_pos = m_keys.begin()->m_pos;
    m_flags = (m_flags & ~3) | 2;
    ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
    acc.setSeamMapAddPosMode(true);
    acc.setSeamMapReadPos(m_pos);
    m_flags |= 4;
}

void SeamlessManager::render() {
    if (!(m_dispFlags & 1) || !(m_flags & 3)) {
        return;
    }
    int x = ml::DevGraph::getRootWidth() - 415;
    fw::debug::drawSquare2D(mm::Rect<int>(x, 120, 225, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<int>(x, 120, 225, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    if (m_flags & 1) {
        fw::debug::drawFont(x + 5, 125, "SEAMLESS(FIRST)");
    } else {
        fw::debug::drawFont(x + 5, 125, "SEAMLESS");
    }
    fw::debug::drawFont(x + 10, 140, "pos:");
    if (m_flags & 1) {
        fw::debug::drawFont(x + 50, 140, "%.2f %.2f %.2f", m_firstPos.x, m_firstPos.y, m_firstPos.z);
    } else {
        fw::debug::drawFont(x + 50, 140, "%.2f %.2f %.2f", m_pos.x, m_pos.y, m_pos.z);
    }
}

SeamlessManager::FirstKey::FirstKey(const char* name, const PosAxis& pos, const mm::Vec3& value) {
    m_name = name;
    m_pos = pos;
    m_value = value;
}

void SeamlessManager::addSeamPoint(float frame, const PosAxis& pos) {
    if (!m_keys.empty()) {
        if (frame <= m_keys.begin()->m_frame) {
            m_keys.clear();
        } else if (m_keys.size() >= m_keys.capacity()) {
            m_keys.erase(m_keys.begin());
        }
    }
    Key key;
    key.m_frame = frame;
    key.m_pos =
        mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(pos.m_type, pos.m_value.x, pos.m_value.y, pos.m_value.z);
    m_keys.push_back(key);
}

// 1.0.0 has it out of line (event::SeamlessManager::clear); 3.0.1 keeps only OnEventProc's inlined copy
inline void SeamlessManager::clear() {
    if (m_flags & 4) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setSeamMapAddPosMode(false);
        m_flags &= ~4;
    }
    m_keys.clear();
    m_firstKeys.clear();
    m_flags = 0;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void SeamlessManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    }
}

SeamlessManager::~SeamlessManager() {}

SkipManager::SkipManager() : m_flags(0), pad_14(0), m_endFrame(-1.0f) {}

BgmManager::BgmManager() : pad_10(0), pad_14(0), pad_7c(0) {}

// 1.0.0 has it out of line (event::BgmManager::clear); 3.0.1 keeps only OnEventProc's inlined copies
inline void BgmManager::clear() {
    if (pad_10 & 0x22) {
        gf::EventBgmSetup setup;
        float fade = mm::mtl::Singleton<FrameManager>::getPtr()->pad_18 != 0 ? 0.0f : (1.0f / 3.0f);
        bool flag = pad_10 & 1;
        setup.pad_4c = fade;
        setup.pad_62 = true;
        setup.pad_63 = false;
        setup.pad_61 = flag;
        gf::GfGameEvent::stopBgm(setup);
        pad_10 &= ~0x22;
    }
    pad_18 = "";
    pad_7c = 0;
    pad_10 = 0;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void BgmManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 1:
        clear();
        break;
    case 2:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    }
}

HideManager::HideManager() : pad_10(0), m_group(), m_firstList(), m_secondList(), m_objs() {}

HideManager::~HideManager() {}

}  // namespace event

#include "classes/event/LodManager.h"

namespace event {

LodManager::~LodManager() {}

DebugManager::DebugManager() : m_flags(0), pad_224(0) {}

// out of line: Singleton<DebugManager>::getPtr registers it with __cxa_atexit (D2 0x7100149758, a bare ret)
DebugManager::~DebugManager() {}

MovieManager::MovieManager() : pad_10(0), pad_118(false), pad_220(-1) {}

// out of line: Singleton<MovieManager>::getPtr registers it with __cxa_atexit (D2 0x710014B038, a bare ret)
MovieManager::~MovieManager() {}

TodoManager::TodoManager() : pad_10(0), pad_14(0), pad_8c20(0) {}

// makes the command, queues it with a copy of the parameters and runs the next queued one (pad_8c20 counts them)
void TodoManager::add(ITodo* (*exec)(), const Param& param) {
    float frame = FrameManager::getPtr()->getFrame();
    updateAdd();
    m_items.push_back(TodoItem(frame, exec, exec(), param));
    long next = pad_8c20;
    m_items[next].m_todo->doit(m_items[next].m_param);
    pad_8c20++;
}

// 1.0.0's SeqManager::login
inline void SeqManager::login() {
    pad_2860 = 1;
    ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(1));
    m_flags &= ~8;
}

// 1.0.0's SeqManager::logout
inline void SeqManager::logout() {
    ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(0));
    ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
    if (acc.isGlassBr()) {
        acc.setGlassBr(false, 0);
    }
}

// 1.0.0's SeqManager::clear
inline void SeqManager::clear() {
    m_flags = 0;
    m_seqName = "";
    m_cmdQueue.clear();
}

// the key function: emits SeqManager's table (its destructor is inline)
SeqManager::SeqManager()
    : m_flags(0), m_dispFlags(0), pad_2718(0), pad_2760(0), pad_2764(0), pad_2768(0), pad_276c(0), pad_2770(""),
      pad_2778(0), pad_277c(0), pad_2780(""), pad_2788(0), pad_278c(0), pad_2790(0), pad_2794(0), pad_2798(0),
      pad_279c(0), pad_27a0(0), pad_27a8(0), pad_27b0(0), pad_27b4(0), pad_27b8(0), pad_27bc(0), pad_27c0(0),
      pad_27c8(0), pad_27d0(0), pad_27d8(1), pad_27d9(0), pad_27da(0), pad_27db(0), pad_27dc(0), pad_27dd(0),
      pad_27e4(0), pad_27e8(0), pad_27f0(0), pad_27f8(0), pad_2800(0), pad_2808(0), pad_280c(0), pad_2810(0),
      pad_2814(0), pad_2818(0), pad_2820(""), pad_2830(0), pad_2838(0), pad_2840(0), pad_2848(0) {}

// queued by SeqManager::init, setupScene, startScene, end and play (not written yet)
template void CmdQueue<32, 0>::push_back(ICmd* cmd, const CmdParam& param);

void SeqManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 1:
        login();
        break;
    case 2:
        logout();
        clear();
        break;
    case 4:
        init();
        break;
    case 5:
        setupScene();
        break;
    case 6:
        m_startLoading.pad_8 = 1;
        break;
    case 7:
        startScene();
        break;
    case 9:
        m_exec.pad_8 = 1;
        break;
    case 11:
        end();
        break;
    case 12:
        m_endWait.pad_8 = 1;
        break;
    case 15:
        m_cmdQueue.update();
        break;
    case 17:
        render();
        break;
    default:
        break;
    }
}

// the fixed target axes 4 and 5 are the radian ones; any other id names an object (looked up, never radian)
DataManager::DataManager() : m_flags(0), m_sceneName("default"), m_current(0) {}


MemoryManager::MemoryManager() : pad_10(0), pad_18(0), pad_24(), pad_28(0), pad_30(0), pad_38(0), m_txtbufs(), pad_1048(0), pad_1050(0), pad_1058(0) {}

MemoryManager::~MemoryManager() {}

}  // namespace event

#include "classes/event/AlphaManager.h"

namespace event {

AlphaManager::~AlphaManager() {}

EffectManager::~EffectManager() {}

}  // namespace event
#include "classes/event/BouManager.h"
#include "classes/event/CpuManager.h"
#include "classes/event/Manager.h"
#include "classes/event/EnvManager.h"
#include "classes/gf/GfFieldGimmick.h"
#include "effect/SendParam.h"
#include "classes/event/SelectManager.h"
#include "classes/event/RandManager.h"
#include "classes/ml/Scn.h"
#include "classes/ml/WinView.h"

namespace event {

// 1.0.0's BouManager::clear: detaches from the view first when attached
inline void BouManager::clear() {
    endActive();
    if (m_flags.test(1)) {
        mm::mtl::PtrSingleton<Manager>::sys()->m_scn->getView(-1)->detachWorkEvent(this);
        m_flags.set(1, false);
    }
    m_actives.clear();
    m_callbacks.clear();
    m_flags.reset();
}

bool BouManager::OnMouseMove(ml::EventView* view) {
    if (!m_flags.test(0)) {
        return false;
    }
    if (m_debugFlags.test(0) && m_flags.test(2) && !m_flags.test(3)) {
        m_rect.w = view->m_pos.x - m_rect.x;
        m_rect.h = view->m_pos.y - m_rect.y;
        updateActive(view->m_pos);
    }
    return false;
}

bool BouManager::OnMouseButtonUp(ml::EventView*) {
    if (!m_flags.test(0)) {
        return false;
    }
    if (m_debugFlags.test(0) && m_flags.test(2) && !m_flags.test(3)) {
        m_flags.set(2, false);
    }
    return false;
}

bool BouManager::OnKeyDown(ml::EventView*) {
    if (m_flags.test(0) && m_debugFlags.test(0)) {
        m_flags.set(3, true);
    }
    return false;
}

bool BouManager::OnKeyUp(ml::EventView*) {
    if (m_flags.test(0) && m_debugFlags.test(0)) {
        m_flags.set(3, false);
    }
    return false;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void BouManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 16:
        render();
        break;
    case 12:
        clear();
        break;
    }
}

BouManager::~BouManager() {}

}  // namespace event

#include "classes/event/ManiManager.h"

namespace event {

bool ManiManager::OnMouseButtonDown(ml::EventView*) { return false; }


// the transfer's cloud sea 1 turns EnvManager's on (type true), 0 turns it on with type false
void EnvTransfer::load() {
    if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
        time->setTime(m_hour, m_min);
        gf::GfGameEvent::setMapWeather(m_weatherID);
        switch (m_cloudSea) {
        case 0: {
            EnvManager* env = mm::mtl::Singleton<EnvManager>::getPtr();
            if (env->m_cloudSea != 2) {
                gf::GfGameEvent::setCloudSea(true, false);
            }
            env->m_cloudSea = 2;
            break;
        }
        case 1: {
            EnvManager* env = mm::mtl::Singleton<EnvManager>::getPtr();
            if (env->m_cloudSea != 1) {
                gf::GfGameEvent::setCloudSea(true, true);
            }
            env->m_cloudSea = 1;
            break;
        }
        }
    }
}

EnvManager::EnvManager()
    : m_flags(0), m_debugFlags(0), m_hour(-1), m_min(-1), m_cloudSea(0), m_colorFilter(0), m_filterNum(-1),
      m_filterFarNum(-1), m_filterTime(0.0f), m_filterCount(0), m_effect(0) {}

void EnvManager::clear() {
    if (m_flags & 4) {
        gf::GfGameEvent::resetWeaType();
        m_flags &= ~4;
    }
    if (m_flags & 2) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setAutoResetScene(false);
        m_flags &= ~2;
    }
    if (m_flags & 8) {
        mm::mtl::PtrSingleton<gf::GfFieldGimmick>::sys()->m_eventFade.m_active = false;
        m_flags &= ~8;
    }
    if (m_flags & 1) {
        if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
            time->setTimeStop(false);
        }
        m_flags &= ~1;
    }
    if (m_cloudSea) {
        gf::GfGameEvent::setCloudSea(false, false);
    }
    if (m_colorFilter) {
        gf::GfGameEvent::setColorFilter(false, -1, -1, 0.0f);
    }
    if (m_effect) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effect);
    }
    if (m_flags & 0x10) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setMotBlurOverride(true);
        acc.setMotBlur(true);
        m_flags &= ~0x10;
    }
    if (m_flags & 0x20) {
        m_flags &= ~0x20;
        m_toneMap = 0.0f;
    }
    m_hour = -1;
    m_min = -1;
    m_cloudSea = 0;
    m_colorFilter = 0;
    m_filterNum = -1;
    m_filterFarNum = -1;
    m_filterTime = 0.0f;
    m_filterCount = 0;
    m_effect = 0;
}

void EnvManager::update() {
    if (m_colorFilter == 2) {
        if ((int)m_filterTime <= m_filterCount++) {
            gf::GfGameEvent::setColorFilter(false, -1, -1, 0.0f);
            m_colorFilter = 0;
            m_filterTime = 0.0f;
            if (m_effect) {
                mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_effect);
            }
            m_effect = 0;
        }
    }
    if (m_flags & 0x10) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setMotBlurOverride(true);
        acc.setMotBlur(false);
    }
    if (m_flags & 0x20) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setOverrideToneMap(m_toneMap);
    }
}

void EnvManager::render() {
    if (!(m_debugFlags & 1)) {
        return;
    }
    gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys();
    if (time == nullptr) {
        return;
    }
    int x = ml::DevGraph::getRootWidth() - 150;
    fw::debug::drawSquare2D(mm::Rect<int>(x, 160, 140, 70), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<int>(x, 160, 140, 70), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(x + 5, 165, "ENV");
    int lx = x + 10;
    unsigned int hour, min;
    time->getTime(hour, min);
    fw::debug::drawFont(lx, 180, "clock:");
    fw::debug::drawFont(lx + 80, 180, "%02d:%02d", hour, min);
    int weather = gf::GfFieldWeather::getCurrentMapWeatherID(false);
    fw::debug::drawFont(lx, 195, "weather:");
    fw::debug::drawFont(lx + 80, 195, "%d", weather);
    int sea = gf::GfFieldWeather::getCurrentCloudSea();
    fw::debug::drawFont(lx, 210, "sea:");
    fw::debug::drawFont(lx + 80, 210, "%d", sea);
}

// the clock is "HHMM": the digits a shorter string lacks count as 0, the hour wraps at 24 and the minute at 60
void EnvManager::setClock(const char* clock) {
    size_t len = strlen(clock);
    int min1 = 0;
    int min10 = 0;
    int hour10 = 0;
    int hour1 = 0;
    if (len > 0) {
        hour10 = (clock[0] - '0') * 10;
        if (len > 1) {
            hour1 = clock[1] - '0';
            if (len > 2) {
                min10 = (clock[2] - '0') * 10;
                if (len > 3) {
                    min1 = clock[3] - '0';
                }
            }
        }
    }
    int hour = hour10 + hour1;
    int min = min10 + min1;
    while (hour >= 24) {
        hour -= 24;
    }
    while (min >= 60) {
        min -= 60;
    }
    if (m_hour != hour || m_min != min) {
        if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
            time->setTime(hour, min);
        }
        m_hour = hour;
        m_min = min;
    }
}

void EnvManager::setColorFilter(COLORFILTER_TYPE type, int no, int frame, float rate) {
    switch (type) {
    case 0:
        if (m_colorFilter != 0) {
            gf::GfGameEvent::setColorFilter(false, -1, -1, rate / 30.0f);
            m_colorFilter = 0;
            m_filterTime = rate;
            if (m_effect) {
                mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_effect);
            }
            m_effect = 0;
        }
        break;
    case 1:
        if (m_colorFilter == 1 && m_filterNum == no && m_filterFarNum == frame && m_filterTime == rate) {
            break;
        }
        gf::GfGameEvent::setColorFilter(true, no, frame, rate / 30.0f);
        m_colorFilter = 1;
        m_filterNum = no;
        m_filterFarNum = frame;
        m_filterTime = rate;
        playVignette(no, frame);
        break;
    case 2:
        if (m_colorFilter == 1) {
            gf::GfGameEvent::setColorFilter(true, -1, -1, rate / 30.0f);
            m_colorFilter = 2;
            m_filterTime = rate;
            m_filterCount = 0;
            if (m_effect) {
                mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_effect);
            }
            m_effect = 0;
        }
        m_filterTime = rate;
        break;
    }
}

void EnvManager::playVignette(int num, int farNum) {
    if (m_effect) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_effect);
    }
    m_effect = 0;
    if (num == 5000 || farNum == 5000) {
        m_effect = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create("cmn_205_000", nullptr, true);
    } else if (num == 5001 || farNum == 5001) {
        m_effect = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create("cmn_205_001", nullptr, true);
    } else {
        return;
    }
    if (m_effect) {
        // the matrix, scale, colour, first range and first flag set again, as GfGameScene's vignette does: the
        // original stores them after the matrix copy
        effect::SendParam param;
        param.m_mtx = mm::Mat44::identity;
        param.m_scale.x = 1.0f;
        param.m_scale.y = 1.0f;
        param.m_scale.z = 1.0f;
        param.m_color[0] = 1.0f;
        param.m_color[1] = 1.0f;
        param.m_color[2] = 1.0f;
        param.m_color[3] = 1.0f;
        param.m_rangeA = 1.0f;
        param.m_valueA = 0.0f;
        param.m_flagA = false;
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setViewnum(m_effect, 0);
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(m_effect, &param);
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void EnvManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
    case 12:
        clear();
        break;
    case 1:
        login();
        break;
    case 14:
        update();
        break;
    case 17:
        render();
        break;
    }
}

CamEvaPlayer::~CamEvaPlayer() {
    if (m_rcha) {
        m_rcha->clear();
        if (m_rcha) {
            delete m_rcha;
            m_rcha = nullptr;
        }
    }
    m_cam = nullptr;
}

CamEvaPlayerEff::~CamEvaPlayerEff() {
    if (m_rcha) {
        m_rcha->clear();
        if (m_rcha) {
            delete m_rcha;
            m_rcha = nullptr;
        }
    }
}

void DofManager::play(int type, float p0, float p1, float p2, float p3, float p4, float p5, int frame, bool flag,
                      const char* name) {
    pad_14 |= 3;
    pad_18 = type;
    pad_1c = p0;
    pad_20 = p0;
    pad_24 = p1;
    pad_28 = false;
    pad_34 = p2;
    pad_38 = p3;
    pad_3c = p4;
    pad_40 = p5;
    pad_44 = frame;
    pad_48 = flag;
    pad_50 = name;
}

void DofManager::stop() {
    unsigned char* fp = Bdat::getFP("EVT_dof");
    pad_14 = 0;
    pad_18 = 1;
    Bdat::uVal val;
    val.ulong = Bdat::getValCheck(fp, "dist", Bdat::getIdTop(fp), 8);
    pad_1c = val.real;
    val.ulong = Bdat::getValCheck(fp, "dist", Bdat::getIdTop(fp), 8);
    pad_20 = val.real;
    val.ulong = Bdat::getValCheck(fp, "range", Bdat::getIdTop(fp), 8);
    pad_24 = val.real;
    pad_28 = false;
    pad_2c = 0;
    pad_30 = 0.1f;
    val.ulong = Bdat::getValCheck(fp, "pixel", Bdat::getIdTop(fp), 8);
    pad_34 = val.real;
    val.ulong = Bdat::getValCheck(fp, "lens", Bdat::getIdTop(fp), 8);
    pad_38 = val.real;
    val.ulong = Bdat::getValCheck(fp, "strength", Bdat::getIdTop(fp), 8);
    pad_3c = val.real;
    val.ulong = Bdat::getValCheck(fp, "blend", Bdat::getIdTop(fp), 8);
    pad_40 = val.real;
    pad_44 = (short)Bdat::getValCheck(fp, "pixelLv", Bdat::getIdTop(fp), 5);
    pad_48 = (short)Bdat::getValCheck(fp, "hlv", Bdat::getIdTop(fp), 5) > 0;
    pad_50 = "";
    if (Manager::get()->m_scn != nullptr) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setDOF(false);
        acc.setDOFOverride(true);
        acc.setDoFDistance(pad_20);
        acc.setDoFRange(pad_24);
        acc.setDOFAutoFocus(pad_28);
        acc.setDOFFocusNum(pad_2c);
        acc.setDOFFocusMin(pad_30);
        acc.setDoFPixlRatio(pad_34);
        acc.setDoFLens(pad_38);
        acc.setDoFStrength(pad_3c);
        acc.setDoFBlend(pad_40);
        acc.setDofPixlLv(pad_44);
        acc.setDofHLvMode(pad_48);
    }
}

SelectManager::SelectManager() : pad_10(0), pad_14(0), pad_38(0), m_result(0) {}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void SelectManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        clear();
        break;
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    }
}

RandManager::RandManager() : m_flags(0) {}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void RandManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        clear();
        break;
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    }
}

void FrameManager::pause(PAUSE_TYPE type, bool enable) {
    unsigned int bit = 1 << type;
    if (((pad_18 & bit) != 0) == enable) {
        return;
    }
    gf::GF_PAUSE_HANDLE*& handle = pad_20[type];
    if (handle != reinterpret_cast<gf::GF_PAUSE_HANDLE*>(-1)) {
        gf::GfPause::destroyHandle(handle);
        handle = reinterpret_cast<gf::GF_PAUSE_HANDLE*>(-1);
    }
    if (enable) {
        switch (type) {
        case 1:
            handle = gf::GfPause::reqPause(0x28d);
            break;
        case 3:
            handle = gf::GfPause::reqPause(0x81);
            break;
        case 12:
        case 21:
            handle = gf::GfPause::reqPause(0x8d);
            break;
        case 19:
        case 20:
            if (pad_14 & 0x10) {
                handle = gf::GfPause::reqPause(0x8d);
            }
            break;
        default:
            break;
        }
        pad_18 |= bit;
    } else {
        pad_18 &= ~bit;
    }
    mm::mtl::Singleton<CsSndManager>::getPtr()->pause((pad_18 & 0x3c1002) != 0);
    VoiceManager* voice = mm::mtl::Singleton<VoiceManager>::getPtr();
    bool voicePause = (pad_18 & 0x3c100a) != 0;
    if (voicePause) {
        voice->pad_10 |= 4;
    } else {
        voice->pad_10 &= ~4u;
    }
    voice->m_player.pause(voicePause);
    if (voicePause != (voice->m_oneShoter.pad_8 & 1)) {
        for (unsigned int i = 0; i < voice->m_oneShoter.m_handles.size(); i++) {
            mm::mtl::PtrSingleton<fw::SoundManager>::sys()->pause(*voice->m_oneShoter.m_handles.at(i), voicePause, 0.0f);
        }
        if (voicePause) {
            voice->m_oneShoter.pad_8 |= 1;
        } else {
            voice->m_oneShoter.pad_8 &= ~1u;
        }
    }
    if (mm::mtl::Singleton<MovieManager>::getPtr()->pad_10 & 4) {
        bool moviePause = (pad_18 & 0x38300a) != 0;
        gf::GfMovieManager* movie = mm::mtl::PtrSingleton<gf::GfMovieManager>::sys();
        bool paused = movie->ispause();
        if (moviePause) {
            if (!paused) {
                mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->pause();
            }
        } else if (paused) {
            mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->play();
        }
    }
    // CpuManager's pause bit 1 follows whether any type is set; leaving it moves the start on by the paused time
    CpuManager* cpu = mm::mtl::Singleton<CpuManager>::getPtr();
    bool on = pad_18 != 0;
    if (cpu->m_flags & 1) {
        bool paused = (cpu->m_flags & 6) != 0;
        cpu->m_flags = !on ? cpu->m_flags & ~2u : cpu->m_flags | 2;
        bool now = (cpu->m_flags & 6) != 0;
        if (paused != now) {
            float frame = cpu->calcCpuFrame();
            if (now) {
                cpu->m_pauseFrame = frame;
            } else {
                cpu->m_startFrame = fmaxf(cpu->m_startFrame + (frame - cpu->m_pauseFrame), 0.0f);
            }
        }
    }
    if (type == 1) {
        if (enable) {
            pad_10.set(10);
        } else {
            pad_10.set(11);
        }
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void CpuManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        init();
        break;
    case 12:
        end();
        break;
    case 14:
        update();
        break;
    case 19:
        tailAlways();
        break;
    }
}

}  // namespace event
#include "classes/event/LightManager.h"
#include "classes/event/LightEvt.h"
#include "classes/event/OutsiderManager.h"
#include "classes/event/CsSndManager.h"
#include "classes/fw/SoundManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/event/VolumeManager.h"
#include "classes/event/VolumePlayer.h"
#include "classes/event/SkipManager.h"
#include "classes/event/FrameManager.h"
#include "classes/event/RandManager.h"
#include "classes/event/RandPlayer.h"
#include "classes/ml/Scn.h"
#include "classes/ml/WinView.h"

namespace event {

// RandManager's table is emitted by OnEventProc; its D2 inlines the RandPlayer's (0x710014B070)
RandManager::~RandManager() {}

RandPlayer::~RandPlayer() {}

// 1.0.0's LightManager::clearEvtLight
inline void LightManager::clearEvtLight() {
    if (m_evtLight) {
        delete m_evtLight;
        m_evtLight = nullptr;
    }
}

// 1.0.0's LightManager::clearOffScrLight
inline void LightManager::clearOffScrLight() {
    for (int i = 0; i < 4; i++) {
        if (m_offScrLights[i]) {
            delete m_offScrLights[i];
            m_offScrLights[i] = nullptr;
        }
    }
}

// 1.0.0's LightManager::clear
inline void LightManager::clear() {
    clearEvtLight();
    clearOffScrLight();
    m_modeFlags = 0;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void LightManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
    case 12:
        clear();
        break;
    case 16:
        render();
        break;
    case 18:
        update();
        break;
    }
}

// 1.0.0's OutsiderField::clear
inline void OutsiderField::clear() {
    m_type = static_cast<TYPE>(1);
    m_pos = mm::Vec3::zero;
    m_size = 0.0f;
    m_hitPos = mm::Vec3::zero;
    m_hitRate = 0.0f;
}

// 1.0.0's OutsiderManager::clear
inline void OutsiderManager::clear() {
    if (m_flags & 1) {
        update(false);
    }
    m_field.clear();
    m_flags = 0;
    m_tgtType = static_cast<OBJ_TYPE>(0);
}

// 1.0.0's OutsiderManager::update()
inline void OutsiderManager::update() {
    if (m_flags & 1) {
        m_field.update();
        if (m_field.m_hitRate > 0.0f) {
            update(true);
        }
    }
}

void MovieManager::clear() {
    close();
    captureScreen(false);
    pad_10 = 0;
}

// bit 7: the scene render is in capture mode
void MovieManager::captureScreen(bool enable) {
    if (enable) {
        if (!(pad_10 & 0x80)) {
            ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
            acc.setCaptureMode(true);
            pad_10 |= 0x80;
        }
    } else {
        if (pad_10 & 0x80) {
            ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
            acc.setCaptureMode(false);
            pad_10 &= ~0x80;
        }
    }
}

void MovieManager::update() {
    if ((pad_10 & 0x14) == 0x14) {
        if (!mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->isplaying()) {
            stop();
        }
    }
    if (pad_10 & 0x20) {
        if (pad_228-- <= 0) {
            pad_10 &= ~0x20;
        }
    }
    if (pad_10 & 0x40) {
        if (pad_22c-- <= 0) {
            close();
        }
    }
}

// the debug overlay: the preloading movie's file (pad_14) or the playing one's (pad_11c) and its length in frames
void MovieManager::render() {
    int x = (ml::DevGraph::getRootWidth() - 210) >> 1;
    if (pad_10 & 2) {
        fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 1.0f, 1.0f));
        fw::debug::drawFont(x + 25, 105, "MOVIE PRELOADING");
        fw::debug::drawFont(x + 150, 105, pad_118 ? "(OBJ)" : "");
        fw::debug::drawFont(x + 25, 120, mm::mtl::Singleton<Extend>::getPtr()->filename(pad_14.m_str));
    } else if (pad_10 & 4) {
        fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
        fw::debug::drawFont(x + 25, 105, "MOVIE PLAYING");
        fw::debug::drawFont(x + 150, 105, pad_118 ? "(OBJ)" : "");
        fw::debug::drawFont(x + 25, 120, mm::mtl::Singleton<Extend>::getPtr()->filename(pad_11c.m_str));
        float frame = mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->get_length() * 30.0f;
        fw::debug::drawFont(x + 190, 120, "FR:%.2f", frame);
    }
}

// "/stream/movie/mv" + the name without its "bf", "qst", "fev" and "deb" parts; bf10480100 gets "_h" or "_s" by
// StatusManager's homuri flag, and "_us" in region 1
bool MovieManager::makePath(mm::mtl::FixStr<256>& path, const char* name) {
    mm::mtl::FixStr<256> work(name);
    auto cut = [&work](const char* part, int len) {
        const char* found = strstr(work.m_str, part);
        if (found != nullptr) {
            int index = found - work.m_str;
            if (work.m_nLen > index) {
                int end = index + len;
                if (!(end < work.m_nLen)) {
                    end = work.m_nLen;
                }
                strcpy(work.m_str + index, work.m_str + end);
                work.m_nLen = strlen(work.m_str);
            }
        }
    };
    cut("bf", 2);
    cut("qst", 3);
    cut("fev", 3);
    cut("deb", 3);
    path.format("/stream/movie/mv%s", work.m_str);
    if (strcmp(name, "bf10480100") == 0) {
        if (mm::mtl::Singleton<StatusManager>::getPtr()->getHomuriFlag() == 0) {
            path += "_h";
            mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("call HOMURA movie");
        } else {
            path += "_s";
            mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("call HIKARI movie");
        }
        if (gf::GfMenuManager::getRegion() == 1) {
            path += "_us";
        }
    }
    return true;
}

// opens the movie (1280x720 for an object movie) and sets its file, unless it is the one already preloading;
// closes everything while the scene is skipped
void MovieManager::preload(const char* name, bool obj) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        close();
        return;
    }
    if ((pad_10 & 2) && isSame(pad_14.m_str, name) && pad_118 == obj) {
        return;
    }
    mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->stop();
    mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->close();
    if (obj) {
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->open(gf::getAllocator(gf::ALLOCATOR(10)), 1280, 720);
    } else {
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->open(gf::getAllocator(gf::ALLOCATOR(10)));
    }
    if (!mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->set_file(mm::mtl::Singleton<Extend>::getPtr()->webm(name))) {
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->close();
        return;
    }
    pad_10 = (pad_10 & ~0x43) | 3;
    pad_14 = name;
    pad_118 = obj;
}

bool MovieManager::isSame(const char* a, const char* b) {
    mm::mtl::FixStr<256> pathA;
    if (a[0] != '\0' && a[0] != '/') {
        pathA = "/";
        pathA += a;
        a = pathA.m_str;
    }
    mm::mtl::FixStr<256> pathB;
    if (b[0] != '\0' && b[0] != '/') {
        pathB = "/";
        pathB += b;
        b = pathB.m_str;
    }
    return strcmp(a, b) == 0;
}

bool MovieManager::isLoading() const {
    if (pad_10 & 2) {
        if (mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->isstandby() == false) {
            return true;
        }
    }
    return false;
}

// plays the preloaded movie when it is this one, else opens and plays it; everything is cleared while the scene is
// skipped
void MovieManager::play(const char* name, bool obj, bool arg) {
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        clear();
        return;
    }
    if ((pad_10 & 2) && isSame(pad_14.m_str, name) && pad_118 == obj) {
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->play();
        pad_11c = name;
        pad_10 &= ~2;
        pad_14 = "";
        pad_118 = false;
    } else {
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->stop();
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->close();
        if (obj) {
            mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->open(gf::getAllocator(gf::ALLOCATOR(10)), 1280, 720);
        } else {
            mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->open(gf::getAllocator(gf::ALLOCATOR(10)));
        }
        if (!mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->set_file(mm::mtl::Singleton<Extend>::getPtr()->webm(name))) {
            mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->close();
            return;
        }
        mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->play();
        pad_11c = name;
    }
    pad_10 |= 5;
    if (arg) {
        pad_10 |= 0x10;
    } else {
        pad_10 &= ~0x10;
    }
    pad_10 &= ~0x60;
    // an object movie has no countdown (the original stores the flags again on this path)
    if (obj) {
        pad_10 &= ~0x20;
    } else {
        pad_228 = 1;
        pad_10 |= 0x28;
    }
}

void MovieManager::setScriptFlag(bool enable) {
    if (enable) {
        pad_10 |= 0x100;
    } else {
        pad_10 &= ~0x100;
    }
}

bool MovieManager::isLoadedAuto(const char* name, bool obj) const {
    mm::mtl::FixStr<256> path;
    makePath(path, name);
    if (pad_10 & 2) {
        if (strcmp(pad_14.m_str, path.m_str) == 0 && pad_118 == obj) {
            return mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->isstandby();
        }
        return false;
    }
    return false;
}

// 1.0.0's OutsiderManager::render
inline void OutsiderManager::render() {
    if (m_dispFlags.test(0) && (m_flags & 1)) {
        m_field.draw();
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void OutsiderManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
    case 10:
    case 12:
        clear();
        break;
    case 14:
        update();
        break;
    case 16:
        render();
        break;
    default:
        break;
    }
}

unsigned int StatusManager::getDriverByBladeId(unsigned int bladeId) const {
    return gf::GfDataBlade::getCreator(bladeId);
}

void VoicePlayer::preload(float time, const char* name) {
    while (static_cast<int>(m_keys.size()) >= 8) {
        m_keys.erase(m_keys.begin());
    }
    m_keys.push_back(Key(time, name));
}

void VoiceMaker::create(bool use, const char* dir, const char* name) {
    m_flags = 0;
    m_path.clear();
    if (use) {
        unsigned long len = strlen(name);
        if (len > 2 && (memcmp(name, "bf", 2) == 0 ||
                        (len > 3 && (memcmp(name, "qst", 3) == 0 || memcmp(name, "fev", 3) == 0 ||
                                     memcmp(name, "deb", 3) == 0 || (len > 6 && memcmp(name, "kizuna", 6) == 0))))) {
            m_path.format("/stream/%s/%s/%s/", dir, fw::LangUtil::getVoiceFolder(), name);
            m_flags |= 1;
        }
    }
}

const char* VoiceMaker::makePath(const char* name) {
    if (!(m_flags & 1)) {
        return nullptr;
    }
    m_voicePath = m_path.m_str;
    m_voicePath += name;
    return m_voicePath.m_str;
}

VoicePlayer::~VoicePlayer() {}

VoiceOneShoter::~VoiceOneShoter() {}

VoiceManager::VoiceManager() : pad_10(0), pad_14(0) {}

VoiceManager::~VoiceManager() {}

void VoiceManager::preloadAuto(float frame, const char* name) {
    if (pad_10 & 1) {
        const char* path = m_maker.makePath(name);
        if (path != nullptr) {
            m_player.preload(frame, mm::mtl::Singleton<Extend>::getPtr()->wav(path));
        }
    }
}

void VoiceManager::preload(float frame, const char* name) {
    const char* wav = mm::mtl::Singleton<Extend>::getPtr()->wav(name);
    m_player.preload(frame, wav);
}

bool VoiceManager::playOneshot(const char* name, float volume) {
    mm::mtl::FixStr<64> path("/stream/");
    path += name;
    if (fw::LangUtil::getVoiceType() != 0) {
        path = mm::mtl::Singleton<Extend>::getPtr()->replaceString(name, "jp", fw::LangUtil::getVoiceFolder());
    }
    return m_oneShoter.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path.m_str), volume);
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void VoiceManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        m_player.clear();
        for (unsigned int i = 0; i < m_oneShoter.m_handles.size(); i++) {
            mm::mtl::PtrSingleton<fw::SoundManager>::sys()->pause(*m_oneShoter.m_handles.at(i), false, 0.0f);
            mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopVoice(m_oneShoter.m_handles[i], 1.0f / 3.0f);
        }
        m_oneShoter.m_handles.clear();
        m_oneShoter.pad_8 = 0;
        pad_10 = 0;
        break;
    case 7:
    case 8:
        if (m_player.m_nextHandle != 0) {
            mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopVoice(m_player.m_nextHandle, 0.0f);
            m_player.m_nextHandle = 0;
        }
        m_player.m_nextName = "";
        m_player.m_keys.clear();
        break;
    case 12:
        m_player.clear();
        for (unsigned int i = 0; i < m_oneShoter.m_handles.size(); i++) {
            mm::mtl::PtrSingleton<fw::SoundManager>::sys()->pause(*m_oneShoter.m_handles.at(i), false, 0.0f);
            mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopVoice(m_oneShoter.m_handles[i], 1.0f / 3.0f);
        }
        m_oneShoter.m_handles.clear();
        m_oneShoter.pad_8 = 0;
        pad_10 = 0;
        break;
    case 14:
        m_player.update();
        m_oneShoter.update();
        break;
    case 16:
        if (pad_14 & 1) {
            m_player.draw();
        }
        break;
    default:
        break;
    }
}

VolumeManager::VolumeManager() : pad_10(0), pad_14(0) {}

inline void VolumeSeamless::update() {
    if (m_flags & 6) {
        if (m_timer >= 0.0f) {
            m_timer -= 1.0f;
        }
        if ((m_flags & 4) && m_timer < 0.0f) {
            m_flags &= ~4;
        }
    }
}

inline void VolumeManager::update() {
    m_seamless.update();
    mm::mtl::Singleton<VolumePlayer>::getPtr()->update();
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void VolumeManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 1:
        init();
        break;
    case 2:
        clear();
        break;
    case 14:
        update();
        break;
    case 17:
        render();
        break;
    default:
        break;
    }
}

inline void CsSndManager::stop0() {
    mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopBgm(m_bgmHandle0, 1.0f);
    m_bgmHandle0 = 0;
    m_bgmName0 = "";
    m_flags &= ~1;
}

inline void CsSndManager::stop1() {
    mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopBgm(m_bgmHandle1, 1.0f);
    m_bgmHandle1 = 0;
    m_bgmName1 = "";
    m_flags &= ~0xe;
}

inline void CsSndManager::clear() {
    if (m_flags & 1) {
        stop0();
    }
    if (m_flags & 2) {
        stop1();
    }
    m_flags = 0;
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void CsSndManager::OnEventProc(event::MSG_TYPE msg) {
    switch (msg) {
    case 4:
        clear();
        break;
    case 14:
        update();
        break;
    case 12:
        clear();
        break;
    case 16:
        render();
        break;
    default:
        break;
    }
}

}  // namespace event

#include "classes/event/Manager.h"
#include "classes/ml/ProcDesktop.h"
#include "classes/gf/GfGameEvent.h"
#include "fw/LangUtil.h"
#include "mtl/MemManager.h"
#include "classes/event/EnvManager.h"
#include "classes/ml/Scn.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/event/SeqManager.h"
#include "classes/event/FrameManager.h"
#include "classes/event/DebugManager.h"
#include "classes/event/ResManager.h"
#include "classes/event/CpuManager.h"
#include "classes/event/ScheManager.h"
#include "classes/event/ShakeManager.h"
#include "classes/event/MemoryManager.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/WinView.h"

namespace event {

void Manager::render() {
    ml::ProcDesktop::isDispInfo();
}

bool Manager::OnKeyDown(ml::EventView*) {
    return false;
}

void Manager::update() {
    if (m_flags & 1) {
        sendMessage(static_cast<MSG_TYPE>(14));
    }
    sendMessage(static_cast<MSG_TYPE>(15));
    if (m_flags & 1) {
        SeqManager* seq = mm::mtl::Singleton<SeqManager>::getPtr();
        if (!seq->m_cmdQueue.empty() && seq->m_cmdQueue.m_items[0].m_cmd == &seq->m_endWait &&
            mm::mtl::Singleton<ResManager>::getPtr()->pad_0x10b8 <= 0) {
            sendMessage(static_cast<MSG_TYPE>(12));
            sendMessage(static_cast<MSG_TYPE>(13));
            clearPlay();
        }
    }
    if (isPlaying()) {
        if (mm::mtl::Singleton<SeqManager>::getPtr()->m_flags & 1) {
            sendMessage(static_cast<MSG_TYPE>(2));
            clearPlay();
            if (m_state.test(10)) {
                m_state.reset(10);
            }
            m_state.reset(0);
            m_state.set(1);
        }
        if (mm::mtl::Singleton<SeqManager>::getPtr()->m_flags & 2) {
            sendMessage(static_cast<MSG_TYPE>(2));
            if (m_state.test(10)) {
                m_state.reset(10);
            }
            m_state.reset(0);
        }
    }
}

void Manager::tail() {
    if (m_flags & 1) {
        sendMessage(static_cast<MSG_TYPE>(18));
    }
    sendMessage(static_cast<MSG_TYPE>(19));
}

void Manager::post() {}

bool Manager::end() {
    if (isPlaying()) {
        if (!(m_flags & 0x20)) {
            sendMessage(static_cast<MSG_TYPE>(11));
            m_flags |= 0x20;
        }
        if (m_flags & 1) {
            return false;
        }
        m_flags &= ~0x20;
    }
    return true;
}

void Manager::finishNewGameWait() {
    mm::mtl::Singleton<UIManager>::getPtr()->m_openFlags |= 0x80000;
}

void Manager::play(const char* name, gf::GF_OBJ_HANDLE* handle, unsigned int word0, unsigned int word1,
                   unsigned int word2, unsigned int word3, const mm::Vec3& pos, float value) {
    m_playHandle = handle;
    pad_288 = word0;
    pad_28c = word1;
    pad_290 = word2;
    pad_294 = word3;
    m_languageMode = LANGUAGE_MODE_NONE;
    m_playPos = mm::Vec3::zero;
    pad_2b0 = 0.0f;
    if (gf::GfGameManager::isGameTypeIra()) {
        m_playPos = pos;
        pad_2b0 = value;
    }
    if (!isPlaying()) {
        mm::mtl::Singleton<SeqManager>::getPtr()->play(name);
    }
    m_state.set(0);
    m_state.reset(1);
}

void Manager::stop() {
    if (isPlaying()) {
        mm::mtl::Singleton<DebugManager>::getPtr()->setFlag(4);
        end();
    }
}

bool Manager::init(const char* name) {
    if (!(m_flags & 1)) {
        m_flags = 0;
        m_eventName = name;
        m_sceneName = name;
        gf::GfEvent::callEventPlay(static_cast<gf::GEV>(9), gf::GfDataEvent::getEventID(name));
        SeqManager* seq = mm::mtl::Singleton<SeqManager>::getPtr();
        if (seq->m_cmdQueue.empty() || seq->m_cmdQueue.m_items[0].m_cmd != &seq->m_playNext) {
            if (!ml::ProcDesktop::isDispInfo()) {
                m_state.set(10);
            }
            sendMessage(static_cast<MSG_TYPE>(1));
        }
        sendMessage(static_cast<MSG_TYPE>(3));
        sendMessage(static_cast<MSG_TYPE>(4));
        m_state.set(0);
        m_flags |= 1;
    }
    SeqManager* seq = mm::mtl::Singleton<SeqManager>::getPtr();
    return !seq->m_cmdQueue.contains(&seq->m_startAreajump);
}

bool Manager::setupScene(const char* name) {
    m_sceneName = name;
    sendMessage(static_cast<MSG_TYPE>(5));
    return true;
}

bool Manager::setupSceneEnd() {
    if (!(m_flags & 2)) {
        sendMessage(static_cast<MSG_TYPE>(6));
        m_flags |= 2;
    }
    if (mm::mtl::Singleton<SeqManager>::getPtr()->isSetupSceneEnd()) {
        m_flags &= ~2;
        return true;
    }
    return false;
}

bool Manager::startScene(const char* name, int no) {
    if (!(m_flags & 4)) {
        m_sceneName = name;
        m_sceneNo = no;
        sendMessage(static_cast<MSG_TYPE>(7));
        m_flags |= 4;
    }
    SeqManager* seq = mm::mtl::Singleton<SeqManager>::getPtr();
    if (seq->m_cmdQueue.contains(&seq->m_startForm) || seq->m_cmdQueue.contains(&seq->m_startChange) ||
        seq->m_cmdQueue.contains(&seq->m_startEnvSeam) || seq->m_cmdQueue.contains(&seq->m_startWeather) ||
        seq->m_cmdQueue.contains(&seq->m_startStreaming0) || seq->m_cmdQueue.contains(&seq->m_startCaptureWait)) {
        return false;
    }
    m_flags &= ~4;
    return true;
}

void FrameManager::startPage(const char* name, int no, float frame) {
    bool b = pad_10.test(4);
    pad_d0 = name;
    m_pageNo = no;
    m_maxFrame = fmaxf(frame, 0.0f);
    if (b && Manager::get()->m_sceneNo <= no) {
        pad_10.set(5);
        pad_178 = m_maxFrame - 1.0f;
    }
}

bool Manager::startPage(const char* name, int no, float frame) {
    if (!(m_flags & 8)) {
        sendMessage(static_cast<MSG_TYPE>(8));
        mm::mtl::Singleton<FrameManager>::getPtr()->startPage(name, no, frame);
        m_flags |= 8;
    }
    SeqManager* seq = mm::mtl::Singleton<SeqManager>::getPtr();
    if (seq->m_cmdQueue.contains(&seq->m_startStreaming1)) {
        return false;
    }
    m_flags &= ~8;
    return true;
}

bool Manager::endScene() {
    if (!(m_flags & 0x10)) {
        sendMessage(static_cast<MSG_TYPE>(9));
        m_flags |= 0x10;
    }
    SeqManager* seq = mm::mtl::Singleton<SeqManager>::getPtr();
    if (seq->m_cmdQueue.contains(&seq->m_exec) || seq->m_cmdQueue.contains(&seq->m_execFadeout) ||
        seq->m_cmdQueue.contains(&seq->m_execGrass) || seq->m_cmdQueue.contains(&seq->m_endChange)) {
        return false;
    }
    sendMessage(static_cast<MSG_TYPE>(10));
    m_flags &= ~0x10;
    return true;
}

void Manager::setLanguageMode(bool enable, LANGUAGE_MODE mode) {
    m_languageMode = enable ? mode : LANGUAGE_MODE_NONE;
}

bool Manager::checkLanguageMode() const {
    switch (m_languageMode) {
    case LANGUAGE_MODE_JP:
        return fw::LangUtil::getVoiceType() == 0;
    case LANGUAGE_MODE_US:
        return fw::LangUtil::getVoiceType() == 1;
    default:
        return true;
    }
}

bool Manager::isDebugPlayOnetime() const {
    return mm::mtl::Singleton<DebugManager>::getPtr()->testFlag(3);
}

void Manager::bkgHomeMenu(bool enable) {
    mm::mtl::Singleton<CpuManager>::getPtr()->setPause(4, true);
    if (!enable) {
        mm::mtl::Singleton<CpuManager>::getPtr()->setPause(4, false);
    }
}

Manager* Manager::create(ml::Scn* scn) {
    if (get()) {
        delete get();
    }
    mtl::ALLOC_HANDLE mem = gf::GfGameEvent::getEventMem();
    return new (mem, nullptr, 0, 4, false) Manager(scn);
}

void Manager::destroy() {
    if (get()) {
        delete get();
    }
}

void EnvManager::setMotBlur(bool enable) {
    if (((m_flags >> 4) & 1) == enable) {
        ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
        acc.setMotBlurOverride(true);
        acc.setMotBlur(enable);
        m_flags = enable ? (m_flags & ~0x10) : (m_flags | 0x10);
    }
}

void EnvManager::setToneMap(bool enable, float value) {
    if (((m_flags >> 5) & 1) != enable) {
        if (enable) {
            ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
            acc.setOverrideToneMap(value);
            m_flags |= 0x20;
        } else {
            m_flags &= ~0x20;
        }
        m_toneMap = value;
    }
}

void EnvManager::setClockStop(bool stop) {
    if (((m_flags & 1) != 0) != stop) {
        if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
            time->setTimeStop(stop);
        }
        if (stop) {
            m_flags |= 1;
        } else {
            m_flags &= ~1;
        }
    }
}

void EnvManager::setMapWeatherID(gf::WEATHERID id, float frame) {
    gf::GfFieldWeather::getCurrentMapWeatherID(false);
    gf::GfGameEvent::setMapWeather(id);
    ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
    acc.setWeatherFrame(frame);
}

void EnvManager::setWeatherType(gf::WEATYPE type) {
    gf::GfGameEvent::setWeaType(type);
    m_flags |= 4;
}

void EnvManager::resetScene() {
    ml::ScnRenderDrSysParmAcc acc(Manager::get()->m_scn->m_renderDrSys, 0);
    acc.resetScene();
}

}  // namespace event

namespace event {

int SeqManager::start::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start";
    }
    return true;
}

int SeqManager::end::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_flags |= 2;
        manager->m_seqName = "end";
    }
    return true;
}

int SeqManager::end_areajump::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        gf::GfMapjumpInfo info(param.m_param.val(1).getS32());
        m_req = gf::GfReqCommand::reqMapjump(info);
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end areajump";
    }
    return !gf::GfReqManager::isValid(m_req);
}

int SeqManager::end_env_seam::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        EnvManager* env = mm::mtl::Singleton<EnvManager>::getPtr();
        if (env->m_event.pad_1c == 1) {
            env->m_event.load();
            env->m_event.pad_18 = 0;
            env->m_event.pad_1c = 0;
        }
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end envseam";
    }
    return true;
}

int SeqManager::end_fadewait::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "exec fadewait";
    }
    return !mm::mtl::Singleton<FadeManager>::getPtr()->isFading();
}

int SeqManager::end_fadein::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end fadein";
    }
    return true;
}

int SeqManager::start_streaming1::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start stream1";
    }
    return true;
}

// val 1 the form's id, val 2 an NPC's id whose matrix places it (0: val 3..5 its position, val 6 its y rotation)
int SeqManager::start_form::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start form";
    }
    unsigned int id = param.m_param.val(1).getS32();
    int npc = param.m_param.val(2).getS32();
    float x = param.m_param.val(3).getF32();
    float y = param.m_param.val(4).getF32();
    float z = param.m_param.val(5).getF32();
    float rotY = param.m_param.val(6).getF32();
    FormManager* form = mm::mtl::Singleton<FormManager>::getPtr();
    if (npc == 0) {
        return form->replace(id, mm::Vec3(x, y, z), rotY);
    }
    return form->replace(id, npc);
}

int SeqManager::start_change::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start change";
    }
    if (param.m_param.val(1).getS32() != 0) {
        if (!mm::mtl::Singleton<StatusManager>::getPtr()->changeFromBdat(param.m_param.val(1).getS32())) {
            return false;
        }
    }
    return true;
}

int SeqManager::start_env_seam::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        unsigned int id = param.m_param.val(1).getS32();
        EnvManager* env = mm::mtl::Singleton<EnvManager>::getPtr();
        if (env->m_event.pad_1c == id) {
            env->m_event.load();
            env->m_event.pad_18 = 0;
            env->m_event.pad_1c = 0;
        }
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start envseam";
    }
    return true;
}

int SeqManager::start_capture_wait::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start capture wait";
    }
    return param.m_frame >= 30;
}

int SeqManager::start_notice::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start notice";
    }
    unsigned int id = param.m_param.val(1).getS32();
    if (id != 0) gf::GfEvent::callEventPlay(static_cast<gf::GEV>(10), id);
    return true;
}

int SeqManager::start_areajump::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        gf::GfMapjumpInfo info(param.m_param.val(1).getS32());
        m_req = gf::GfReqCommand::reqMapjump(info);
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start areajump";
    }
    return !gf::GfReqManager::isValid(m_req);
}

int SeqManager::end_notice::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end notice";
    }
    unsigned int id = param.m_param.val(1).getS32();
    if (id != 0) gf::GfEvent::callEventPlay(static_cast<gf::GEV>(11), id);
    return true;
}

int SeqManager::play_start::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        gf::SCOM_SCRIPT::create(2, param.m_param.val(1).getStr(), false);
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_flags &= ~4;
        manager->m_seqName = "play start";
    }
    if (gf::GfScriptManager::isScriptLoadError(2)) {
        gf::GfScriptManager::destroyScript(2);
        static_cast<SeqManager*>(param.m_param.val(0).getUserdata())->m_flags |= 1;
    }
    return false;
}

int SeqManager::play_next::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        gf::SCOM_SCRIPT::create(2, param.m_param.val(1).getStr(), false);
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        // a 64-bit mask as mm::mtl::Bitflag::set builds it (m_flags may be a Bitflag<32>): the select tests eq
        unsigned long mask = 1UL << 2;
        if (param.m_param.val(2).getBool()) {
            manager->m_flags |= mask;
        } else {
            manager->m_flags &= ~mask;
        }
        UIManager* ui = mm::mtl::Singleton<UIManager>::getPtr();
        if (!(ui->m_flags & 1)) {
            gf::GfMenuObjFade::dispLoading(true, 0);
            ui->m_flags |= 1;
        }
        manager->m_seqName = "play next";
    }
    if (gf::GfScriptManager::isScriptLoadError(2)) {
        gf::GfScriptManager::destroyScript(2);
        static_cast<SeqManager*>(param.m_param.val(0).getUserdata())->m_flags |= 1;
    }
    return false;
}

inline bool ObjectList::isUsingEffect() {
    for (unsigned int i = 0; i < m_counts[2]; i++) {
        Object* obj = m_categories[2]->m_child;
        for (unsigned int j = 0; j < i; j++) {
            obj = obj->m_next;
        }
        if (static_cast<ObjectEffect*>(obj)->m_effect->m_ctrl.pad_110 != nullptr) {
            return true;
        }
    }
    return false;
}

inline void ObjectList::stopEffect() {
    for (unsigned int i = 0; i < m_counts[2]; i++) {
        Object* obj = m_categories[2]->m_child;
        for (unsigned int j = 0; j < i; j++) {
            obj = obj->m_next;
        }
        static_cast<ObjectEffect*>(obj)->m_effect->stop();
    }
}

inline bool ObjectManager::isUsingEffect() {
    if (m_current == nullptr) {
        return false;
    }
    return m_current->isUsingEffect();
}

inline void ObjectManager::stopEffect() {
    for (unsigned long i = 0; i < m_scenes.size(); i++) {
        m_scenes[i]->stopEffect();
    }
}

int SeqManager::end_eff::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end eff";
    }
    bool busy = mm::mtl::Singleton<ObjectManager>::getPtr()->isUsingEffect();
    mm::mtl::Singleton<ObjectManager>::getPtr()->stopEffect();
    return !busy;
}

int RandPlayer::Warp::update(const ICmd::Param& param) {
    if (param.m_frame == 0) {
        gf::GfGameParty::judgeRandomTalkWarp();
    }
    return true;
}

// waits while the character with the id is not yet standing by to talk, at most 60 frames
int RandPlayer::Wait::update(const ICmd::Param& param) {
    Object* obj = RandUtil::searchByID(param.m_param.val(0).getS32());
    if (param.m_frame < 60 && obj->m_type == 2 &&
        !gf::GfObjUtil::isStanbyTalkingPlayer(static_cast<ObjectChara*>(obj)->m_chara->m_gfHandle)) {
        return false;
    }
    return true;
}

// on its first frame: when val 1 is set and the id names a character, aims it at the val 2..4 target (val 5 set) or
// drops its queued target command
int RandPlayer::Reset::update(const ICmd::Param& param) {
    if (param.m_frame == 0) {
        int id = param.m_param.val(0).getS32();
        bool enable = param.m_param.val(1).getBool();
        float x = param.m_param.val(2).getF32();
        float y = param.m_param.val(3).getF32();
        float z = param.m_param.val(4).getF32();
        bool setTar = param.m_param.val(5).getBool();
        Object* obj = RandUtil::searchByID(id);
        if (enable && obj->m_type == 2) {
            CharaObj* chara = static_cast<ObjectChara*>(obj)->m_chara;
            if (setTar) {
                chara->setTar(TarAxis(1, x, y, z), -1.0f, static_cast<EVT_tarcvtype>(1), static_cast<EVT_aimtype>(0),
                              -1.0f, -1.0f);
            } else {
                chara->m_cmdQueue2.erase(&chara->m_setTar);
            }
        }
    }
    return true;
}

// the looked-up character is unused (1.0.0 0x71000D4630 is the same)
int CharaStopHead::update(const ICmd::Param& param) {
    gf::GfObjUtil::getObj(m_handle);
    return true;
}

StmPackHeader::~StmPackHeader() {
    if (m_res) {
        m_res->release();
        m_res = nullptr;
    }
}

void StmPackHeader::create(mtl::ALLOC_HANDLE, const char* name) {
    if (m_res) {
        m_res->release();
        m_res = nullptr;
    }
    m_res = fw::RenderResource::request(mm::mtl::Singleton<MemoryManager>::getPtr()->pad_24, name, 0);
}

StmPackData::~StmPackData() {
    clear();
}

void StmPackData::create(const char* name) {
    clear();
    pad_c = name;
}

bool StmPackData::OnFileEvent(ml::EventFileTh* event) {
    if (event->m_kind == 2) {
        pad_8 &= ~1u;
        return true;
    }
    return false;
}

void StmPackMemory::loadStream(const char* name, const char* header, const char* data) {
    Pack* pack = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) Pack(name);
    pack->m_header.create(mtl::ALLOC_HANDLE(), header);
    pack->m_data.create(data);
    pad_5860.push_back(pack);
}

// not identical yet (4 instructions): ours hoists this+0x5860 into a register, the original indexes [this+i*8, #0x5860]
StmPackMemory::~StmPackMemory() {
    pad_5838 = 0;
    pad_20 = 0;
    pad_28 = 0;
    pad_30.clear();
    mtl::MemManager::deallocate(pad_10, 0, false);
    for (unsigned long i = 0; i < pad_5860.size(); i++) {
        Pack* pack = *pad_5860.at(i);
        pack->m_data.clear();
        pack->m_header.clear();
        delete pack;
    }
    pad_5860.clear();
}

void StmPackMemory::update() {
    if (!(pad_8 & 1)) {
        for (unsigned long i = 0; i < pad_5860.size(); i++) {
            if (pad_5860[i]->m_header.isLoading()) {
                return;
            }
        }
        if (!pad_5860[pad_58f0]->m_data.open()) {
            return;
        }
        pad_18 = (mtl::MemManager::maxAllocSize(pad_c) >> 12) - 2;
        pad_10 = mtl::MemManager::allocate(pad_c, pad_18 * 0x1000, 0x1000, false, "no name", 0);
        pad_8 |= 1;
    }
    if (pad_8 & 1) {
        freeCut();
        if (pad_8 & 2) {
            if (waitCut()) {
                pad_8 &= ~2u;
            }
        } else {
            if (pad_8 & 4) {
                return;
            }
            if (loadCut()) {
                pad_8 |= 2;
            }
        }
    }
}

bool StmPackMemory::loadCut(void* adr, unsigned long size, unsigned long page, unsigned long& next) {
    if (!pad_5860[pad_58e8]->m_data.isSuccess()) {
        return false;
    }
    unsigned long first = pad_5838;
    int prio = pad_5860[pad_58e8]->m_header.getPrio(pad_5838);
    unsigned long dataOfs = pad_5860[pad_58e8]->m_header.getDataOfs(pad_5838);
    unsigned long dataSize = pad_5860[pad_58e8]->m_header.getDataSize(pad_5838);
    pad_5848 = dataSize;
    pad_5850 = size;
    if (dataSize >= size) {
        return false;
    }
    unsigned long count = pad_5860[pad_58e8]->m_header.getCount();
    for (unsigned long i = pad_5838 + 1; i < count; i++) {
        if (prio != pad_5860[pad_58e8]->m_header.getPrio(i)) {
            break;
        }
        unsigned long end = pad_5860[pad_58e8]->m_header.getDataOfs(i) +
                            pad_5860[pad_58e8]->m_header.getDataSize(i) - dataOfs;
        if (end >= size) {
            break;
        }
        pad_5838 = i;
        dataSize = end;
    }
    unsigned long pageEnd = page + (dataSize >> 12) + 1;
    loadCut(adr, dataSize, first, pad_5838, page, pageEnd, prio);
    next = pageEnd;
    pad_5838++;
    return true;
}

void StmPackMemory::loadCut(void* adr, unsigned long size, unsigned long first, unsigned long last,
                            unsigned long pageStart, unsigned long pageEnd, int prio) {
    unsigned long dataOfs = pad_5860[pad_58e8]->m_header.getDataOfs(first);
    pad_5860[pad_58e8]->m_data.read(adr, size, dataOfs);
    StmPackRes res(adr, size, dataOfs, first, last, pageStart, pageEnd, prio, pad_5858, pad_58e8);
    pad_5858++;
    pad_30.push_back(res);
}

void* StmPackMemory::adr(const char* name, unsigned long* size) {
    for (StmPackRes* it = pad_30.begin(); it != pad_30.end(); ++it) {
        if (!it->isLoading() && it->pad_50 == pad_58f0) {
            for (unsigned long i = it->pad_28; i <= it->pad_30; i++) {
                if (strcmp(name, pad_5860[pad_58f0]->m_header.getPath(i)) == 0) {
                    it->pad_0++;
                    if (size != nullptr) {
                        *size = pad_5860[pad_58f0]->m_header.getDataSize(i);
                    }
                    return it->getFileAdr(pad_5860[pad_58f0]->m_header.getDataOfs(i));
                }
            }
        }
    }
    return nullptr;
}

void StmPackMemory::render(const mm::Rect<int>& rect, float alpha) {}

void StmPackMemory::free(void* p, int) {
    for (StmPackRes* it = pad_30.begin(); it != pad_30.end(); ++it) {
        if (!(it->pad_4 & 1) && it->pad_10 <= reinterpret_cast<unsigned long>(p) &&
            reinterpret_cast<unsigned long>(p) < it->pad_10 + it->pad_18) {
            it->pad_4 |= 2;
            it->pad_0--;
            return;
        }
    }
}

bool StmPackMemory::isLoadingPrio(float prio) const {
    if (pad_58e8 <= pad_58f0 && pad_5840 <= prio) {
        return true;
    }
    return false;
}

// the original checks the index twice: a first lookup's value is unused
bool StmPackMemory::isFailure() const {
    pad_5860[pad_58e8];
    return pad_5860[pad_58e8]->m_data.pad_90 == nullptr;
}

}  // namespace event

#include <math.h>
#include <string.h>
#include "classes/event/Scheduler.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfGameParty.h"

namespace event {

void Scheduler::func_stanby(gf::GfObj* obj) {}

void ScheduleItem::func_fadewait(gf::GF_OBJ_HANDLE*) {}

void Scheduler::setup() {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj == nullptr) {
        return;
    }
    if (obj->m_type == 3) {
        m_flags |= 0x30;
    } else if (obj->m_type == 6) {
        if (m_type == 0) {
            m_flags |= 0x3C;
            if (gf::GfObjUtil::getObj(m_item.m_handle) != nullptr &&
                (gf::GfGameUtil::hasBelonging(m_item.m_handle, 2) || gf::GfGameUtil::hasBelonging(m_item.m_handle, 1))) {
                m_flags |= 0xC0;
            }
        } else if (m_type == 1) {
            m_flags |= 0x30;
            m_aimType = static_cast<EVT_aimtype>(1);
        } else if (m_type == 2) {
            m_flags |= 0x3C;
        }
    }
}

Scheduler::~Scheduler() {
    m_item.clear();
}

void Scheduler::func_fld2evt(gf::GfObj* obj) {
    if (m_flags & 0x40) {
        if (gf::GfObjUtil::getObj(m_item.m_handle) != nullptr &&
            (gf::GfGameUtil::hasBelonging(m_item.m_handle, 2) || gf::GfGameUtil::hasBelonging(m_item.m_handle, 1))) {
            m_item.m_alpha = 1.0f;
            m_item.m_func = &ScheduleItem::func_fadeout;
        } else {
            m_item.m_alpha = 0.0f;
            m_item.m_func = nullptr;
        }
    }
    m_turnFunc = obj->m_type == 3 ? nullptr : &Scheduler::func_motionEnd;
}

void Scheduler::func_evt2idle(gf::GfObj* obj) {
    m_state |= 1;
    m_lookFunc = &Scheduler::func_look;
}

void Scheduler::func_evt2fld(gf::GfObj* obj) {
    if (m_flags & 0x20) {
        lookTo(false, obj, nullptr, static_cast<EVT_aimtype>(0), true);
    }
    m_actFunc = &Scheduler::func_return;
}

void Scheduler::func_motionEnd(gf::GfObj* obj) {
    m_turnFunc = &Scheduler::func_motionEnd_loop;
}

void Scheduler::func_motionEnd_loop(gf::GfObj* obj) {
    m_turnFunc = &Scheduler::func_turn;
}

void Scheduler::func_turn(gf::GfObj* obj) {
    if (gf::GfPause::isPause(1)) {
        return;
    }
    if (m_flags & 0x4) {
        float rotY = getRotY(obj, gf::GfGameParty::getLeaderTransformObj());
        gf::GfGameUtil::ExecTurnCmdInfo info;
        info.m_handle = m_handle;
        info.m_rotY = rotY;
        info.m_arg1 = 1.0f;
        info.m_arg2 = 0.7853982f;
        info.m_arg3 = 0.0f;
        gf::GfGameUtil::execTurnCmd(info);
    }
    m_turnFunc = &Scheduler::func_turn_loop;
}

float Scheduler::getRotY(gf::GfObj* obj, gf::GfObj* target) {
    gf::GfComTransform* targetTransform = target->getComponent<gf::GfComTransform>(0);
    gf::GfComTransform* transform = obj->getComponent<gf::GfComTransform>(0);
    const mm::Vec3& pos = transform->getPosition();
    const mm::Vec3& targetPos = targetTransform->getPosition();
    return -atan2f(pos.x - targetPos.x, -(pos.z - targetPos.z));
}

void Scheduler::func_turn_loop(gf::GfObj* obj) {
    if (!(m_flags & 0x4) || gf::GfGameUtil::isTurnEnd(m_handle)) {
        m_turnFunc = nullptr;
    }
}

void Scheduler::func_return(gf::GfObj* obj) {
    if (m_flags & 0x8) {
        m_frame = 360;
    }
    m_actFunc = &Scheduler::func_return_loop;
}

void Scheduler::func_return_loop(gf::GfObj* obj) {
    m_actFunc = &Scheduler::func_motion;
}

void Scheduler::func_motion(gf::GfObj* obj) {
    m_actFunc = &Scheduler::func_motion_loop;
}

void Scheduler::func_motion_loop(gf::GfObj* obj) {
    if (m_flags & 0x80) {
        gf::GfComAsm* com = obj->getComponent<gf::GfComAsm>(2);
        int frame = m_frame--;
        if (com != nullptr && frame > 0) {
            bool loop = com->isLoop(static_cast<gf::AnimLayer>(0));
            const char* state = com->getStateName(static_cast<gf::AnimLayer>(0));
            if (!loop || strcmp(state, "S_idle") == 0) {
                return;
            }
        }
    }
    m_actFunc = &Scheduler::func_item;
}

void Scheduler::func_item(gf::GfObj* obj) {
    if (m_flags & 0x80) {
        if (gf::GfObjUtil::getObj(m_item.m_handle) != nullptr &&
            (gf::GfGameUtil::hasBelonging(m_item.m_handle, 2) || gf::GfGameUtil::hasBelonging(m_item.m_handle, 1))) {
            m_item.m_alpha = 0.0f;
            m_item.m_func = &ScheduleItem::func_fadein;
        } else {
            m_item.m_alpha = 1.0f;
            m_item.m_func = nullptr;
        }
    }
    m_actFunc = &Scheduler::func_item_loop;
}

void Scheduler::func_item_loop(gf::GfObj* obj) {
    if (m_flags & 0x80) {
        if (m_item.m_func == &ScheduleItem::func_fadeout || m_item.m_func == &ScheduleItem::func_fadein) {
            return;
        }
    }
    m_actFunc = nullptr;
}

// a scheduler for handle's object: a running one is replaced by a new one that keeps its flags and ids
void ScheManager::push(gf::GF_OBJ_HANDLE* handle, unsigned int type) {
    for (Scheduler** it = m_schedulers.begin(); it != m_schedulers.end(); ++it) {
        if ((*it)->m_handle == handle) {
            Scheduler* scheduler = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
                Scheduler(**it, type);
            scheduler->setup();
            m_schedulers.push_back(scheduler);
            if (*it) {
                delete *it;
                *it = nullptr;
            }
            m_schedulers.erase(it);
            return;
        }
    }
    Scheduler* scheduler =
        new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) Scheduler(handle, type);
    scheduler->setup();
    m_schedulers.push_back(scheduler);
}

}  // namespace event
template event::VoiceManager* mm::mtl::Singleton<event::VoiceManager>::getPtr();
