#include "classes/fw/EffectCasterBase.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPoint.h"
#include "classes/fw/EffectResData.h"
#include "classes/gf/EffectCaster.h"
#include "classes/gf/GfComEffectCaster.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComEffect.h"
#include "classes/fw/EffectCasterBase.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPoint.h"
#include "classes/fw/Framework.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/EffectResData.h"
#include "classes/gf/EffectCaster.h"
#include "classes/gf/GfComEffectCaster.h"

// the ASM annotation name registerAsmCallbackEffect registers effects under
const char* ASM_CB_NAME_EFFECT = "asm_effect";

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EABD68). setupCaster sets it (and the
// caster's flag at 0xA0) for the first caster of the party leader; the destructor clears it.
static bool s_leaderCasterSet;

GfComEffectCaster::~GfComEffectCaster() {
    s_leaderCasterSet = false;
    cleanup();
}

void GfComEffectCaster::setupCaster(const fw::EffectPoint* point) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    const mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    m_caster = new (fw::Framework::getAllocator(), 16, __FILE__, 669) EffectCaster(point, m_layer);
    if (m_caster) {
        m_caster->pad_8 = frame;
        m_caster->m_pOwner = this;
        if (!s_leaderCasterSet && static_cast<GfObj*>(m_owner)->m_handle == GfGameManager::getPartyLeader()) {
            s_leaderCasterSet = true;
            m_caster->m_isLeader = true;
        }
        if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
            if (model->m_model) {
                EffectCaster* caster = m_caster;
                caster->pad_18 = model->m_model->getInterface();
            }
        }
    }
}

// the names of the parameters are not the original's
void GfComEffectCaster::changeLayer(unsigned int prevLayer, unsigned int layer) {
    if (prevLayer != layer) {
        m_layer = layer;
        if (m_caster) {
            m_caster->changeLayer(prevLayer, layer);
        }
    }
}

void GfComEffectCaster::asmCallback(GfComAsm*, const CallBackCache& cache) { callbackImpl(cache); }

void GfComEffectCaster::evtAnimCallback(GfComEvtAnim*, const CallBackCache& cache) { callbackImpl(cache); }

fw::EffectPoint* GfComEffectCaster::getEffectPoint() { return m_pPoint; }

void GfComEffectCaster::registerAsmCallbackEffect(GF_OBJ_HANDLE*, anm::ResASM* asmRes, fw::EffectResData* resData) {
    if (asmRes && resData) {
        resData->registerAsmAnnotation(asmRes, 3, ASM_CB_NAME_EFFECT);
    }
}

GfComEffectCaster::Param* GfComEffectCaster::findEffectCasterParam(unsigned int id) {
    for (Param* it = m_params.begin(); it != m_params.end(); ++it) {
        if (it->m_id == id) {
            return it;
        }
    }
    return nullptr;
}

// the names of the parameters are not the original's
const char* GfComEffectCaster::getEfpData(const char* name, mm::Mat44& mtx) {
    if (m_caster && m_caster->m_pPoint) {
        const char* parent = m_caster->m_pPoint->getParentName(name);
        mtx = m_caster->m_pPoint->getOffset(name);
        return parent;
    }
    return nullptr;
}

void GfComEffectCaster::setCaster(unsigned int handle) {
    mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(handle, m_caster, 1.0f);
}

bool GfComEffectCaster::setSpeed(unsigned int id, float speed) {
    if (Param* param = findEffectCasterParam(id)) {
        param->m_speed = speed;
        return true;
    }
    return false;
}

bool GfComEffectCaster::startTimer(unsigned int id) {
    if (Param* param = findEffectCasterParam(id)) {
        param->m_timer = 0.0f;
        return true;
    }
    return false;
}

mm::mtl::RTTI GfComEffectCaster::m_rtti("GfComEffectCaster", &GfComEffect::m_rtti, nullptr);

}  // namespace gf
