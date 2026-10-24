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
    return m_movieFlags & 1;
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
