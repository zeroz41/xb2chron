#include "classes/event/ICmd/Param.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjUtil.h"
#include "classes/event/RandPlayer/Warp.h"
#include "classes/event/CharaStopHead.h"
#include "classes/event/StmPackMemory.h"
#include "classes/event/SeqManager/start.h"
#include "classes/event/SeqManager/end.h"
#include "classes/event/SeqManager/end_fadein.h"
#include "classes/event/SeqManager/start_streaming1.h"
#include "classes/event/SeqManager/start_capture_wait.h"
#include "classes/event/SeqManager/start_notice.h"
#include "classes/event/SeqManager/end_notice.h"
#include "gf/FileStaticVec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/Vec2.h"
#include "mm/Col4.h"
#include "classes/event/ParamVariable.h"
#include "classes/event/Param.h"
#include "classes/event/CharaSetTar.h"
#include "classes/event/ShakeManager.h"
#include "classes/event/TodoManager.h"
#include "classes/event/ObjectPartyList.h"
#include "event/AgelogUtil.h"
#include "classes/event/AttachActorGf.h"
#include "classes/event/BlurManager.h"
#include "classes/event/BouRect.h"
#include "classes/event/CamField.h"
#include "classes/event/CamFree.h"
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

#include "classes/event/EvtxtManager.h"
#include "classes/event/LipsyncManager.h"
#include "classes/event/MdlstmManager.h"
#include "classes/event/MstxtManager.h"
#include "classes/event/OffscrManager.h"

namespace event {

CmdVariable::~CmdVariable() {}

ParamVariable::~ParamVariable() {}

Param::Param() {}

AttachActorGf::~AttachActorGf() {}

void CamFree::update(const event::FrameInfo&) {}

void CamField::update(const event::FrameInfo&) {}

void CharaTurnRot::init() {}

void CharaPlayActionAuto::init() {}

void CharaPlayActionAuto::term() {}

void CharaPlayAction::init() {}

void CharaPlayTalkAuto::init() {}

void CharaPlayTalkAuto::term() {}

void CharaMount::init() {}

void BlurManager::OnEventProc(event::MSG_TYPE) {}

void FormManager::OnEventProc(event::MSG_TYPE) {}

void MercenariesManager::OnEventProc(event::MSG_TYPE) {}

BouRect::~BouRect() {}

void ObjectCamera::start() {}

void ObjectEffect::start() {}

void CopydataManager::OnEventProc(event::MSG_TYPE) {}

void ScriptCharaMotion::undo(const event::Param&) {}

void ScriptCharaMotionABC::undo(const event::Param&) {}

SkipManager::~SkipManager() {}

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

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void MdlstmManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 14) {
        update();
    } else if (msg == 12) {
        clear();
    }
}

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void MstxtManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 12) {
        clear();
    }
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
#include "classes/event/ObjectLight.h"
#include "classes/event/ObjectCamera.h"

namespace event {

void HideManager::defineGroup(GRP_TYPE group) {
    m_group = group;
}

HideManager::GRP_TYPE HideManager::getGroup() const {
    return m_group;
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

void CharaSetIdle::init() {
    m_step = 0;
}

void CharaPlayHead::init() {
    m_step = 0;
}

void CharaPlayFacial::init() {
    m_step = 0;
}

void CharaPlayWink::init() {
    m_step = 0;
}

void ObjectLight::play(const char* name, float frame) {
    m_light->play(name, frame);
}

void ObjectCamera::tail() {
    m_cam->tail();
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

namespace event {

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

// ---- script commands (session 19) ----
#include "classes/event/ObjectManager.h"

event::ObjectManager::ObjectManager() : m_flags(0), pad_14(0), m_sceneName("default") {}
#include "classes/event/ObjectChara.h"
#include "classes/event/ObjectEffect.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "classes/event/ScriptCharaWalkPos.h"
#include "classes/event/ScriptCharaTurnRot.h"
#include "classes/event/ScriptCharaLinerPos.h"
#include "classes/event/ScriptCharaLinerRot.h"
#include "classes/event/ScriptEffectMove.h"
#include "classes/event/ScriptEffectTurn.h"

namespace event {

void ScriptCharaWalkPos::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setPosAxis(PosAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
    }
}

void ScriptCharaTurnRot::redo(const event::Param& param) {
    ObjectChara* obj = static_cast<ObjectChara*>(mm::mtl::Singleton<ObjectManager>::getPtr()->getActive(2));
    if (obj != 0) {
        obj->setRotAxis(RotAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
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

PosAxis::PosAxis(unsigned int type, float x, float y, float z) : m_type(type), m_value(x, y, z) {}

RotAxis::RotAxis(unsigned int type, float x, float y, float z) : m_type(type), m_value(x, y, z) {}

}  // namespace event

#include "classes/event/ObjectCamera.h"
#include "classes/event/CamObj.h"
#include "classes/event/ScriptEffectKill.h"
#include "classes/event/ScriptEffectAnim.h"
#include "classes/event/ScriptCharaMotion.h"
#include "classes/event/ScriptCharaFade.h"
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
#include "classes/event/ModelManager.h"
#include "classes/event/DebugManager.h"
#include "classes/event/FrameManager.h"

namespace event {

FrameManager::FrameManager()
    : pad_18(0), pad_d0(), m_frame(0.0f), pad_15c(0.0f), pad_160(0.0f), pad_164(0.0f), pad_16c(0),
      m_maxFrame(1000.0f), pad_184(1), pad_1190(0), pad_1198(0), pad_11a0(0), pad_11a8(0) {
    pad_10 = 0;
    pad_14 = 2;
    for (int i = 0; i < 22; i++) {
        pad_20[i] = reinterpret_cast<gf::GF_PAUSE_HANDLE*>(-1);
    }
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

// the message numbers are compared as numbers: no evidence names MSG_TYPE's enumerators yet
void ModelManager::OnEventProc(event::MSG_TYPE msg) {
    if (msg == 14) {
        update();
    }
}

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
#include "classes/event/MemoryManager.h"
#include "classes/event/ResManager.h"

namespace event {

EffectManager::EffectManager() : m_flags(0), m_dispFlags(0), pad_a0(0), m_offscrID(0), pad_ac(0) {}

LightManager::LightManager() : m_flags(0), m_modeFlags(0), m_offScrLights(), m_evtLight(nullptr) {}

LightManager::~LightManager() {}

SeamlessManager::SeamlessManager() : pad_10(0), pad_520(0), pad_2540(0) {}

SkipManager::SkipManager() : m_flags(0), pad_14(0), m_endFrame(-1.0f) {}

BgmManager::BgmManager() : pad_10(0), pad_14(0), pad_7c(0) {}

HideManager::HideManager() : pad_10(0), m_group(), pad_1018(0), pad_2020(0), pad_2228(0) {}

DebugManager::DebugManager() : m_flags(0), pad_224(0) {}

// out of line: Singleton<DebugManager>::getPtr registers it with __cxa_atexit (D2 0x7100149758, a bare ret)
DebugManager::~DebugManager() {}

MovieManager::MovieManager() : pad_10(0), pad_118(false), pad_220(-1) {}

// out of line: Singleton<MovieManager>::getPtr registers it with __cxa_atexit (D2 0x710014B038, a bare ret)
MovieManager::~MovieManager() {}

TodoManager::TodoManager() : pad_10(0), pad_8c18(0), pad_8c20(0), pad_10e28(0) {}

DataManager::DataManager() : m_flags(0), m_sceneName("default"), m_current(0) {}

MemoryManager::MemoryManager() : pad_10(0), pad_18(0), pad_24(0), pad_28(0), pad_30(0), pad_38(0), pad_1040(0), pad_1048(0), pad_1050(0), pad_1058(0) {}

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
    if (m_flags & 2) {
        mm::mtl::PtrSingleton<Manager>::sys()->m_scn->getView(-1)->detachWorkEvent(this);
        m_flags &= ~2;
    }
    m_actives.clear();
    m_callbacks.clear();
    m_flags = 0;
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

}  // namespace event

namespace event {

bool SeqManager::start::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start";
    }
    return true;
}

bool SeqManager::end::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_flags |= 2;
        manager->m_seqName = "end";
    }
    return true;
}

bool SeqManager::end_fadein::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end fadein";
    }
    return true;
}

bool SeqManager::start_streaming1::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start stream1";
    }
    return true;
}

bool SeqManager::start_capture_wait::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start capture wait";
    }
    return param.m_frame >= 30;
}

bool SeqManager::start_notice::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "start notice";
    }
    unsigned int id = param.m_param.val(1).getS32();
    if (id != 0) gf::GfEvent::callEventPlay(static_cast<gf::GEV>(10), id);
    return true;
}

bool SeqManager::end_notice::update(const ICmd::Param& param) {
    if (param.m_frame <= 0) {
        SeqManager* manager = static_cast<SeqManager*>(param.m_param.val(0).getUserdata());
        manager->m_seqName = "end notice";
    }
    unsigned int id = param.m_param.val(1).getS32();
    if (id != 0) gf::GfEvent::callEventPlay(static_cast<gf::GEV>(11), id);
    return true;
}

bool RandPlayer::Warp::update(const ICmd::Param& param) {
    if (param.m_frame == 0) {
        gf::GfGameParty::judgeRandomTalkWarp();
    }
    return true;
}

// the looked-up character is unused (1.0.0 0x71000D4630 is the same)
bool CharaStopHead::update(const ICmd::Param& param) {
    gf::GfObjUtil::getObj(m_handle);
    return true;
}

void StmPackMemory::render(const mm::Rect<int>& rect, float alpha) {}

}  // namespace event
