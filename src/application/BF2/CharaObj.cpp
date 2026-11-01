#include "classes/event/ModelObj.h"
#include "classes/event/ScheManager.h"
#include "classes/event/CharaUtil.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "classes/event/TarAxis.h"
#include "classes/event/AttachActorCS.h"
#include "classes/event/ScriptUtil.h"
#include "classes/event/CharaPlayTalk.h"
#include "gf/GfDataBlade.h"
#include "mm/Mat44.h"
#include "classes/event/FrameManager.h"
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
#include "classes/event/CharaObj.h"
#include "string.h"
#include "classes/RchaEff.h"
#include "classes/RchaChrEff.h"
#include "classes/RchaCamEff.h"
#include "classes/RchaCam.h"
#include "classes/event/EffectEvaPlayer.h"
#include "classes/event/CharaEvaPlayerEff.h"
#include "classes/event/CharaWpnAsm.h"
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
#include "classes/event/CmdVariable.h"
#include "classes/event/ICmd/Param.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfReqManager.h"
#include "gf/GfReqCommand.h"
#include "gf/GfReqParam.h"
#include "gf/GfObjUtil.h"
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
#include "classes/ml/EventView.h"
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
#include "classes/event/MercenariesManager.h"
#include "classes/event/ObjectCamera.h"
#include "classes/event/ObjectEffect.h"
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
        setEffectMount(false, (*m_mounts.begin())->m_handle, "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
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

bool AttachActorBase::hasMtp(const char* name) const {
    mm::Mat44 mat;
    return getMtpMat(mat, name);
}

bool AttachActorBase::hasEfp(const char* name) const {
    mm::Mat44 mat;
    return getEfpMat(mat, name);
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

bool CamFree::OnKeyUp(ml::EventView* view) {
    if (!(view->pad_28 & 1)) {
        return false;
    }
    pad_4c &= ~8u;
    pad_50 = 0.0f;
    return true;
}

void CamField::update(const event::FrameInfo&) {}

void CharaTurnRot::init() {}

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

void CamManager::setFocal(bool focal) {
    if (focal) {
        pad_10 |= 4;
    } else {
        pad_10 &= ~4;
    }
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

void CharaObj::playVolumeFade(CharaEffectPlayer::VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d,
                              float e, int f, float g) {
    m_effectPlayer.playVolumeFade(type, a, b, c, d, e, f, g);
}

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

CharaWpnAsm::~CharaWpnAsm() {}

CharaEvaPlayerEff::~CharaEvaPlayerEff() {
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

ObjectChara::~ObjectChara() {
    if (m_chara) {
        delete m_chara;
        m_chara = nullptr;
    }
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

void Object::update() {}

void Object::render(const mm::Col4&) {}

void Object::tail() {}

bool ObjectChara::isLoading() const {
    return !(m_chara->m_flags & 8);
}

ObjectEffect::~ObjectEffect() {
    if (m_effect) {
        delete m_effect;
        m_effect = nullptr;
    }
}

void ObjectEffect::tail() {
    m_effect->m_ctrl.update();
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

namespace event {

DofManager::~DofManager() {}

FadeManager::~FadeManager() {}

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

CamManager::CamManager() : pad_10(0), pad_14(0), m_cur(nullptr) {}

void CamManager::init() {
    pad_10 = 0;
    for (unsigned long i = 0; i < 4; i++) {
        CamInterface* cam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false)
            CamInterface(static_cast<fw::CAMERA_TYPE>(i));
        cam->addRef();
        m_interfaces.push_back(cam);
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

event::ObjectManager::ObjectManager() : m_flags(0), pad_14(0), m_sceneName("default") {}

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
        ATTACH_TYPE type = static_cast<ATTACH_TYPE>(param.val(1).getS32());
        const char* name = param.val(2).getStr();
        mm::Vec3 pos(param.val(3).getF32(), param.val(4).getF32(), param.val(5).getF32());
        obj->setMount(chara->m_chara->m_attach, name, pos, param.val(6).getBool(), type);
    }
}

void ScriptEffectMount::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        obj->setMount(nullptr, "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
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
        mm::Vec3 scalePrev = obj->m_effect->m_scale;
        m_prevScale = scalePrev;
        float scale = param.val(0).getF32();
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_scale.x = scale;
            effect->m_scale.y = scale;
            effect->m_scale.z = scale;
        }
    }
}

void ScriptEffectScale::undo(const event::Param&) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_scale.x = m_prevScale.x;
            effect->m_scale.y = m_prevScale.y;
            effect->m_scale.z = m_prevScale.z;
        }
    }
}

void ScriptEffectScale::redo(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        float scale = param.val(0).getF32();
        EffectObj* effect = obj->m_effect;
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
            effect->m_scale.x = scale;
            effect->m_scale.y = scale;
            effect->m_scale.z = scale;
        }
    }
}

void ScriptEffectColor::doit(const event::Param& param) {
    ObjectEffect* obj = static_cast<ObjectEffect*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(4));
    if (obj != 0) {
        mm::Col4 color(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
        const mm::Col4& cur = obj->m_effect->m_color;
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
            effect->m_color = prev;
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

namespace event {

FrameManager::FrameManager()
    : pad_18(0), pad_d0(), m_frame(0.0f), pad_15c(0.0f), pad_160(0.0f), pad_164(0.0f), pad_16c(0),
      m_maxFrame(1000.0f), pad_184(1), m_keyFrames(), pad_1198(0), pad_11a0(0), pad_11a8(0) {
    pad_10 = 0;
    pad_14 = 2;
    for (int i = 0; i < 22; i++) {
        pad_20[i] = reinterpret_cast<gf::GF_PAUSE_HANDLE*>(-1);
    }
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

int UIManager::getPayoffUI() const {
    return m_payoffResult;
}

int UIManager::fn_7100104AE8() {
    return m_exResult;
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

void UIManager::openAvanTitleUI(unsigned int id) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && !(m_openFlags & 0x800)) {
        m_avanTitleContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjChapterTelop::openAvanTitle(m_avanTitleContext, id);
        m_openFlags |= 0x800;
    }
}

void UIManager::openZoneTelopUI(unsigned int id) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && !(m_openFlags & 0x1000)) {
        m_zoneTelopContext = gf::GfMenuCallContext::create();
        gf::GfMenuObjZoneTelop::open(m_zoneTelopContext, id);
        m_openFlags |= 0x1000;
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
        gf::GfMenuObjOpeningTelop::fn_710044AC84();
        break;
    case OPTELOP_RH:
        gf::GfMenuObjOpeningTelop::fn_710044AB90();
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

LightManager::LightManager() : m_flags(0), m_modeFlags(0), m_offScrLights(), m_evtLight(nullptr) {}

LightManager::~LightManager() {}

SeamlessManager::SeamlessManager() : pad_10(0), m_firstKeys(), m_keys() {}

SeamlessManager::~SeamlessManager() {}

SkipManager::SkipManager() : m_flags(0), pad_14(0), m_endFrame(-1.0f) {}

BgmManager::BgmManager() : pad_10(0), pad_14(0), pad_7c(0) {}

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
        m_dragOfs.x = view->m_pos.x - m_downPos.x;
        m_dragOfs.y = view->m_pos.y - m_downPos.y;
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
    : m_flags(0), pad_14(0), pad_18(-1), pad_1c(-1), m_cloudSea(0), m_colorFilter(0), pad_28(-1), pad_2c(-1),
      pad_30(0), pad_34(0), m_effect(0) {}

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

bool MovieManager::isLoading() const {
    if (pad_10 & 2) {
        if (mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->isstandby() == false) {
            return true;
        }
    }
    return false;
}

void MovieManager::setScriptFlag(bool enable) {
    if (enable) {
        pad_10 |= 0x100;
    } else {
        pad_10 &= ~0x100;
    }
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

namespace event {

void Manager::render() {
    ml::ProcDesktop::isDispInfo();
}

bool Manager::OnKeyDown(ml::EventView*) {
    return false;
}

void Manager::tail() {
    if (m_flags & 1) {
        sendMessage(static_cast<MSG_TYPE>(18));
    }
    sendMessage(static_cast<MSG_TYPE>(19));
}

void Manager::post() {}

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

void StmPackMemory::render(const mm::Rect<int>& rect, float alpha) {}

void StmPackMemory::free(void* p, int) {
    for (Block* it = pad_30.begin(); it != pad_30.end(); ++it) {
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

}  // namespace event
