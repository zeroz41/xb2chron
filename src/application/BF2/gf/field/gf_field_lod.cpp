#include "mm/mtl/Algorithm.h"
#include "classes/gf/GfFieldLodColiAnim.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfFieldLodColiAnim.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMapManager.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/EffectManager.h"
#include "ml/ScnObjAccSeamPos.h"
#include "ml/ScnObjAccPartsPos.h"
#include "classes/ml/DevGraph.h"
#include "plugin/Bdat.h"
#include <string.h>
#include "mm/mtl/Vector.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComTransform.h"
#include "gf/GfObjUtil.h"
#include "effect/SendParam.h"
#include "mm/mtl/FixStr.h"
#include "idcoli/IDColiParms.h"

namespace gf {

GfFieldLodEffect::GfFieldLodEffect() : m_hasAsset(false), m_handle(0), m_state(LOD_STATE_NONE) {
    for (int i = 0; i < LOD_STATE_NONE; i++) {
        m_assets[i] = nullptr;
    }
}

void* GfFieldLodEffect::getAsset(GfFieldLodState state) const {
    if (state >= LOD_STATE_ANIM && state < LOD_STATE_NONE) {
        return m_assets[state];
    }
    return nullptr;
}

void GfFieldLodEffect::createAsset(int bdatId) {
    disposeAsset();
    m_hasAsset = true;
    fw::EffectPack* pack = GfFieldManager::getEffectPack();
    if (pack == nullptr) {
        return;
    }
    unsigned char* fp = GfDataBdat::getFP(0x72);
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "effect_anime_normal", bdatId, 7));
    if (name != nullptr && *name != '\0') {
        if (void* asset = fw::EffectManager::get()->search(name, pack)) {
            m_assets[LOD_STATE_ANIM] = asset;
        }
    }
    name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "effect_anime_reverse", bdatId, 7));
    if (name != nullptr && *name != '\0') {
        if (void* asset = fw::EffectManager::get()->search(name, pack)) {
            m_assets[LOD_STATE_ANIM_REVERSE] = asset;
        }
    }
    name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "effect_visibleON", bdatId, 7));
    if (name != nullptr && *name != '\0') {
        if (void* asset = fw::EffectManager::get()->search(name, pack)) {
            m_assets[LOD_STATE_POP] = asset;
        }
    }
    name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "effect_visibleOFF", bdatId, 7));
    if (name != nullptr && *name != '\0') {
        if (void* asset = fw::EffectManager::get()->search(name, pack)) {
            m_assets[LOD_STATE_DEPOP] = asset;
        }
    }
    name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "effect_fadeOUT", bdatId, 7));
    if (name != nullptr && *name != '\0') {
        if (void* asset = fw::EffectManager::get()->search(name, pack)) {
            m_assets[LOD_STATE_DEPOP_FADE] = asset;
        }
    }
    m_skipFrame = Bdat::getValCheck(fp, "effect_skipframe", bdatId, 2);
}

void GfFieldLodEffect::disposeAsset() {
    if (m_handle != 0) {
        fw::EffectManager::get()->remove(m_handle);
        m_handle = 0;
    }
    m_hasAsset = false;
    for (int i = 0; i < LOD_STATE_NONE; i++) {
        m_assets[i] = nullptr;
    }
}

void GfFieldLodEffect::createInst(GfFieldLodState state, ml::ScnObjAccPartsPos& pos, bool flag) {
    void* current = getAsset(m_state);
    if (current != nullptr && fw::EffectManager::get()->isLoop(current)) {
        if (m_handle != 0) {
            fw::EffectManager::get()->dead(m_handle);
            m_handle = 0;
        }
    } else {
        m_handle = 0;
    }
    m_state = state;
    if (getAsset(state) == nullptr) {
        return;
    }
    if (flag && !fw::EffectManager::get()->isLoop(getAsset(state))) {
        return;
    }
    unsigned int handle = fw::EffectManager::get()->create(getAsset(state), true);
    if (handle == 0) {
        return;
    }
    fw::EffectManager::get()->setCategory(handle, static_cast<fw::EF_CATEGORY>(1));
    effect::SendParam param;
    pos.getMatrix(param.m_mtx);
    param.m_valueA = m_skipFrame;
    fw::EffectManager::get()->setParam(handle, &param);
    m_handle = handle;
}

void GfFieldLodColiAnim::PosInfo::updateAnim(ml::ScnObjAccPartsPos& pos, float frame) {
    if (!m_playing) {
        return;
    }
    bool loop = pos.isLoop();
    float posFrame = pos.getPosFrame();
    float nodeFrame = pos.getNodeFrame();
    if (m_reverse) {
        posFrame -= frame;
        nodeFrame -= frame;
        if (posFrame < 0.0f) {
            posFrame = loop ? pos.getPosMaxFrame() : 0.0f;
        }
        if (nodeFrame < 0.0f) {
            nodeFrame = loop ? pos.getNodeMaxFrame() : 0.0f;
        }
    } else {
        posFrame += frame;
        nodeFrame += frame;
        if (pos.getPosMaxFrame() < posFrame) {
            posFrame = loop ? 0.0f : pos.getPosMaxFrame();
        }
        if (pos.getNodeMaxFrame() < nodeFrame) {
            nodeFrame = loop ? 0.0f : pos.getNodeMaxFrame();
        }
    }
    mm::Mat44 mat;
    if (pos.isPosAnm()) {
        pos.getAnmMatrix(&mat);
    }
    pos.setPosFrame(posFrame);
    pos.setNodeFrame(nodeFrame);
    if (pos.isPosAnm()) {
        pos.setMatrix(mat);
        syncGfTransform(mat);
        pos.getAnmMatrix(&mat);
        if (m_moveObjIdx >= 0 && m_owner->m_info.m_coli != nullptr) {
            idcoli::IDColiParmsGrand parms(m_owner->m_info.m_coli);
            parms.getMoveObj(m_moveObjIdx).setMatrix(mat);
        }
    }
}

void GfFieldLodColiAnim::PosInfo::updatePopDepopEffect(ml::ScnObjAccPartsPos& pos) {
    if (!m_effect.m_hasAsset || !pos.isPosMatrix()) {
        return;
    }
    GfFieldLodState state = m_effect.m_state;
    if (m_effect.getAsset(state) == nullptr || (state != LOD_STATE_POP && state != LOD_STATE_DEPOP)) {
        return;
    }
    GfObj* mover = GfObjUtil::getObj(GfGameManager::getControlMover());
    if (mover == nullptr) {
        return;
    }
    const mm::Vec3& moverPos = mover->getComponent<GfComTransform>(0)->getPosition();
    mm::Mat44 mat;
    pos.getMatrix(mat);
    mm::Vec3 diff = moverPos - mat.getTrans();
    if (diff.dot(diff) <= m_popDistSq) {
        if (m_effect.m_handle == 0) {
            m_effect.createInst(state, pos, true);
        }
    } else if (m_effect.m_handle != 0) {
        fw::EffectManager::get()->dead(m_effect.m_handle);
        m_effect.m_handle = 0;
    }
}

GfFieldLodColiAnim::GfFieldLodColiAnim(const CreateInfo* info) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfFieldLodColiAnim::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    createPosInfos(info.m_flag);
}

void GfFieldLodColiAnim::dispose() {
    disposePosInfos();
    m_info = CreateInfo();
}

void GfFieldLodColiAnim::update(fw::UpdateInfo const& info) {
    if (m_info.m_model == nullptr || m_info.m_lod == nullptr || GfManager::isDestroyNow() || m_posInfos.size() == 0) {
        return;
    }
    for (PosInfo& posInfo : m_posInfos) {
        if (posInfo.m_objHandle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            posInfo.update(info);
        }
    }
}

int GfFieldLod::findBdatIdByLodId(unsigned short lodId) const {
    for (size_t i = 0; i < 0x400; i++) {
        if (m_lodIds[i] == lodId) {
            return m_idTop + i;
        }
    }
    return m_idTop - 1;
}

bool GfFieldLodColiAnim::play(unsigned short lodId, bool reverse, bool immediate) {
    ml::ScnObjAccSeamPos seam(m_info.m_model);
    int max = seam.getMax();
    bool played = false;
    for (int i = 0; i < max; i++) {
        ml::ScnObjAccPartsPos pos = seam.getObj(i);
        if (lodId != pos.getID() || (!pos.isPosAnm() && !pos.isNodeAnm())) {
            continue;
        }
        PosInfo& posInfo = m_posInfos[i];
        posInfo.m_playing = true;
        posInfo.m_reverse = reverse;
        if (immediate) {
            pos.setPosFrame(reverse ? 0.0f : pos.getPosMaxFrame());
            pos.setNodeFrame(reverse ? 0.0f : pos.getNodeMaxFrame());
        }
        if (posInfo.m_effect.m_hasAsset) {
            GfFieldLodState state = reverse ? LOD_STATE_ANIM_REVERSE : LOD_STATE_ANIM;
            void* asset = posInfo.m_effect.getAsset(state);
            bool loop = asset != nullptr && fw::EffectManager::get()->isLoop(asset);
            if (!immediate || loop) {
                posInfo.m_effect.createInst(state, pos, immediate && loop);
            }
        }
        played = true;
    }
    return played;
}

bool GfFieldLodColiAnim::isPlayEnd(unsigned short lodId) const {
    ml::ScnObjAccSeamPos seam(m_info.m_model);
    size_t count = m_posInfos.size();
    for (size_t i = 0; i < count; i++) {
        const PosInfo& posInfo = m_posInfos[i];
        ml::ScnObjAccPartsPos pos = seam.getObj(posInfo.m_index);
        if (lodId != pos.getID() || pos.isLoop()) {
            continue;
        }
        if (pos.isPosAnm() && ((posInfo.m_reverse && pos.getPosFrame() <= 0.0f) ||
                               (!posInfo.m_reverse && pos.getPosMaxFrame() <= pos.getPosFrame()))) {
            return true;
        }
        if (pos.isNodeAnm() && ((posInfo.m_reverse && pos.getNodeFrame() <= 0.0f) ||
                                (!posInfo.m_reverse && pos.getNodeMaxFrame() <= pos.getNodeFrame()))) {
            return true;
        }
    }
    return false;
}

void GfFieldLodColiAnim::setPlaySpeed(unsigned short lodId, float speed) {
    ml::ScnObjAccSeamPos seam(m_info.m_model);
    int max = seam.getMax();
    for (int i = 0; i < max; i++) {
        ml::ScnObjAccPartsPos pos = seam.getObj(i);
        if (lodId == pos.getID()) {
            m_posInfos[i].m_speed = speed;
        }
    }
}

float GfFieldLodColiAnim::getAnimEndTime(unsigned short lodId) const {
    ml::ScnObjAccSeamPos seam(m_info.m_model);
    int max = seam.getMax();
    for (int i = 0; i < max; i++) {
        ml::ScnObjAccPartsPos pos = seam.getObj(i);
        if (lodId != pos.getID()) {
            continue;
        }
        if (pos.isPosAnm()) {
            return pos.getPosMaxFrame() * ml::DevGraph::getFrameSyncSec();
        }
        if (pos.isNodeAnm()) {
            return pos.getNodeMaxFrame() * ml::DevGraph::getFrameSyncSec();
        }
    }
    return 0.0f;
}

void GfFieldLodColiAnim::setFade(unsigned short lodId, bool visible, float time) {
    ml::ScnObjAccSeamPos seam(m_info.m_model);
    int max = seam.getMax();
    for (int i = 0; i < max; i++) {
        ml::ScnObjAccPartsPos pos = seam.getObj(i);
        if (lodId != pos.getID()) {
            continue;
        }
        PosInfo& posInfo = m_posInfos[i];
        if (posInfo.m_visible != visible) {
            posInfo.m_fadeElapsed = 0.0f;
            posInfo.m_fadeTime = time;
            posInfo.m_visible = visible;
        }
        if (posInfo.m_effect.m_hasAsset) {
            GfFieldLodState state = visible ? LOD_STATE_POP : (time <= 0.0f ? LOD_STATE_DEPOP : LOD_STATE_DEPOP_FADE);
            void* asset = posInfo.m_effect.getAsset(state);
            bool loop = asset != nullptr && fw::EffectManager::get()->isLoop(asset);
            if (time > 0.0f || loop) {
                posInfo.m_effect.createInst(state, pos, time == 0.0f && !loop);
            }
        }
    }
}
}  // namespace gf

// instantiated for gf::GfFieldLodColiAnim::createPosInfos (not written yet)
template void mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::push_back(gf::GfFieldLodColiAnim::PosInfo const&);

namespace gf {

bool GfFieldLod::isAnimReverse(int bdatId) const {
    return GfGameFlag::getLocal(1, bdatId + 0x9631 - m_idTop) != 0;
}

void GfFieldLod::BdatInfo::dispose() {
    m_bdatId = 0;
}

void GfFieldLod::BdatInfo::dirtyCache() {
    if (m_bdatId != 0) {
        m_conds[0].m_cached = false;
        m_conds[1].m_cached = false;
        m_conds[2].m_cached = false;
    }
}

void GfFieldLod::BdatInfo::create(unsigned short bdatId) {
    m_bdatId = bdatId;
    unsigned char* fp = GfDataBdat::getFP(0x72);
    m_lodId = Bdat::getValCheck(fp, "LODID", bdatId, 2);
    unsigned int fadeIn = Bdat::getValCheck(fp, "LOD_fadeIN_TIME", bdatId, 8);
    m_fadeInTime = *reinterpret_cast<float*>(&fadeIn);
    unsigned int fadeOut = Bdat::getValCheck(fp, "LOD_fadeOUT_TIME", bdatId, 8);
    m_fadeOutTime = *reinterpret_cast<float*>(&fadeOut);
    mm::mtl::FixStr<32> column;
    for (size_t i = 0; i < 3; i++) {
        CondInfo& cond = m_conds[i];
        cond.m_cached = false;
        column.format("ScenarioFlagMin%d", i + 1);
        unsigned short scenarioMin = Bdat::getValCheckU16(fp, column.m_str, bdatId);
        column.format("ScenarioFlagMax%d", i + 1);
        unsigned short scenarioMax = Bdat::getValCheckU16(fp, column.m_str, bdatId);
        if (scenarioMin <= scenarioMax) {
            cond.m_scenarioFlag = gmk::ScenarioFlagCond(scenarioMin, scenarioMax);
        }
        column.format("QuestFlag%d", i + 1);
        unsigned short quest = Bdat::getValCheck(fp, column.m_str, bdatId, 2);
        column.format("QuestFlagMin%d", i + 1);
        unsigned char questMin = Bdat::getValCheckU8(fp, column.m_str, bdatId);
        column.format("QuestFlagMax%d", i + 1);
        unsigned char questMax = Bdat::getValCheckU8(fp, column.m_str, bdatId);
        if (questMin > questMax) {
            return;
        }
        cond.m_questFlag = gmk::QuestFlagCond(quest, questMin, questMax);
        column.format("Condition%d", i + 1);
        cond.m_gameCond = Bdat::getValCheck(fp, column.m_str, bdatId, 2);
    }
}

bool GfFieldLod::setAnimReverse(int bdatId, bool reverse, bool immediate) {
    GfGameFlag::setLocal(1, bdatId + 0x9631 - m_idTop, reverse);
    if (m_coliAnim.m_info.m_model == nullptr || m_coliAnim.m_info.m_lod == nullptr) {
        return false;
    }
    if (!m_updating) {
        BdatInfo* info = _findBdatInfo(bdatId);
        if (info != nullptr) {
            info->dirtyCache();
        }
    }
    return m_coliAnim.play(m_lodIds[bdatId - m_idTop], reverse, immediate);
}

GfFieldLod::GfFieldLod(const GfSetupParam& param)
    : m_idTop(0), m_initialized(false), m_updateIndex(0), m_updating(false), m_eventPlaying(false) {
    initialize(param);
}

void GfFieldLod::initialize(const GfSetupParam& param) {
    memset(m_lodIds, 0xff, sizeof(m_lodIds));
    unsigned char* fp = GfDataBdat::getFP(0x72);
    m_idTop = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    for (int i = 0; i < count; i++) {
        m_lodIds[i] = Bdat::getValCheck(fp, "LODID", i + m_idTop, 2);
    }
    m_initialized = true;
    validateByInitData();
}

GfFieldLod::~GfFieldLod() {}

GfFieldLod::BdatInfo* GfFieldLod::_findBdatInfo(int bdatId) {
    if (m_bdatInfos.size() != 0) {
        for (BdatInfo* it = m_bdatInfos.begin(); it != m_bdatInfos.end(); ++it) {
            if (it->m_bdatId == bdatId) {
                return it;
            }
        }
    }
    return nullptr;
}

bool GfFieldLod::isFadeOut(int bdatId) const {
    return GfGameFlag::getLocal(1, bdatId - m_idTop + 0x9230) == 0;
}

bool GfFieldLod::isPlayAnimEnd(int bdatId) const {
    unsigned short lodId = m_lodIds[bdatId - m_idTop];
    return m_coliAnim.isPlayEnd(lodId);
}

float GfFieldLod::getAnimEndTime(int bdatId) const {
    unsigned short lodId = m_lodIds[bdatId - m_idTop];
    return m_coliAnim.getAnimEndTime(lodId);
}

void GfFieldLod::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    switch (gev) {
    case GEV(2): {
        size_t size = m_bdatInfos.size();
        for (size_t i = 0; i < size; i++) {
            m_bdatInfos[i].update();
        }
        break;
    }
    case GEV(3):
        disposeBdatInfos();
        disposeColiAnim();
        break;
    case GEV(5): {
        validateBySaveData();
        fw::ModelObject* obj = GfMapManager::getModelObject();
        if (obj != nullptr) {
            ml::ScnObjModel* model = obj->getInterface();
            if (model != nullptr) {
                createColiAnim(model, false);
            }
        }
        validateVeSe();
        break;
    }
    default:
        break;
    }
}

void GfFieldLod::validateBySaveData() {
    unsigned char* fp = GfDataBdat::getFP(0x72);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    for (int i = 0; i < count; i++) {
        int id = top + i;
        unsigned int visible = GfGameFlag::getLocal(1, 0x9230 + i);
        get()->setFade(id, visible != 0, false);
        unsigned int reverse = GfGameFlag::getLocal(1, 0x9631 + i);
        get()->setAnimReverse(id, reverse != 0, true);
    }
}

void GfFieldLod::createColiAnim(ml::ScnObjModel* model, bool flag) {
    if (model == nullptr) {
        return;
    }
    disposeBdatInfos();
    disposeColiAnim();
    GfFieldLodColiAnim::CreateInfo info;
    info.m_model = model;
    fw::ColiObject* coli = GfMapManager::getColiObject();
    info.m_coli = coli != nullptr ? coli->m_coliObj : nullptr;
    info.m_lod = this;
    info.m_flag = flag;
    m_coliAnim.create(info);
    createBdatInfos();
    m_coliAnim.validateVeSe(*this);
}

void GfFieldLod::gevPlayEvent(GEV gev, unsigned int eventId) {
    switch (gev) {
    case GEV(10):
        m_eventPlaying = true;
        break;
    case GEV(11):
        m_eventPlaying = false;
        break;
    default:
        break;
    }
}

bool GfFieldLod::findTransform(mm::Mat44& mat, int bdatId) const {
    if (m_coliAnim.m_info.m_model != nullptr && m_coliAnim.m_info.m_lod != nullptr) {
        ml::ScnObjAccSeamPos seam(m_coliAnim.m_info.m_model);
        int max = seam.getMax();
        if (max > 0) {
            unsigned short lodId = m_lodIds[bdatId - m_idTop];
            for (int i = 0; i < max; i++) {
                ml::ScnObjAccPartsPos parts = seam.getObj(i);
                if (parts.isPosMatrix() && lodId == parts.getID()) {
                    parts.getMatrix(mat);
                    return true;
                }
            }
        }
    }
    return false;
}

const GfFieldLod::BdatInfo* GfFieldLod::findBdatInfo(int bdatId) const {
    if (m_bdatInfos.size() != 0) {
        for (const BdatInfo* it = m_bdatInfos.begin(); it != m_bdatInfos.end(); ++it) {
            if (it->m_bdatId == bdatId) {
                return it;
            }
        }
    }
    return nullptr;
}

void GfFieldLod::setLodSwitchId(int bdatId, unsigned int switchId) {
    if (m_coliAnim.m_info.m_model == nullptr || m_coliAnim.m_info.m_lod == nullptr) {
        return;
    }
    unsigned short lodId = m_lodIds[bdatId - m_idTop];
    ml::ScnObjAccSeamPos seam(m_coliAnim.m_info.m_model);
    int max = seam.getMax();
    for (int i = 0; i < max; i++) {
        ml::ScnObjAccPartsPos parts = seam.getObj(i);
        if (lodId == parts.getID()) {
            parts.setSwitchID(switchId);
        }
    }
}

unsigned int GfFieldLod::getLodSwitchId(int bdatId) const {
    if (m_coliAnim.m_info.m_model == nullptr || m_coliAnim.m_info.m_lod == nullptr) {
        return -1;
    }
    unsigned short lodId = m_lodIds[bdatId - m_idTop];
    ml::ScnObjAccSeamPos seam(m_coliAnim.m_info.m_model);
    int max = seam.getMax();
    unsigned int switchId = -1;
    for (int i = 0; i < max; i++) {
        ml::ScnObjAccPartsPos parts = seam.getObj(i);
        if (lodId == parts.getID() && parts.isSwitch()) {
            switchId = parts.getSwitchID();
        }
    }
    return switchId;
}

void GfFieldLod::validateByInitData() {
    unsigned char* fp = GfDataBdat::getFP(0x72);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    for (int i = 0; i < count; i++) {
        int id = top + i;
        int visible = Bdat::getFlagVal(fp, "flag", id, "Visible");
        get()->setFade(id, visible != 0, true);
        int reverse = Bdat::getFlagVal(fp, "flag", id, "AnimReverse");
        get()->setAnimReverse(id, reverse != 0, true);
    }
}

void GfFieldLod::finalize() {
    disposeBdatInfos();
    disposeColiAnim();
    m_initialized = false;
}

void GfFieldLod::updateBdatInfos() {
    m_updating = true;
    size_t size = m_bdatInfos.size();
    size_t count = size > 4 ? 4 : size;
    for (size_t i = 0; i < count; i++, m_updateIndex++) {
        if (size <= m_updateIndex) {
            m_updateIndex = 0;
        }
        m_bdatInfos[m_updateIndex].update();
    }
    m_updating = false;
}

void GfFieldLod::disposeColiAnim() {
    m_coliAnim.dispose();
}

void GfFieldLod::disposeBdatInfos() {
    m_bdatInfos.destroy();
}

void GfFieldLod::build(const GfSetupParam& param) {
#line 2075
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldLod(param);
}

void GfFieldLod::destroy() {
    GfFieldLod* lod = get();
    lod->finalize();
    delete lod;
}

void GfFieldLod::update(const fw::UpdateInfo& info) {
    GfFieldLod* lod = get();
    if (lod == nullptr || !lod->m_initialized) {
        return;
    }
    if (!lod->m_eventPlaying) {
        lod->updateBdatInfos();
    }
    get()->m_coliAnim.update(info);
}

bool GfFieldLod::isAnimReverseOfInit(int bdatId) {
    return Bdat::getFlagVal(GfDataBdat::getFP(0x72), "flag", bdatId, "AnimReverse") != 0;
}

const mm::mtl::RTTI* GfFieldLodColiAnim::ColiUserData::getRTTI() const {
    return &m_rtti;
}
}  // namespace gf

// instantiated for gf::GfFieldLodColiAnim::createPosInfos, mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::push_back (not written yet)
template void mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::expand(unsigned long, unsigned long);

namespace gf {

mm::mtl::RTTI GfFieldLodColiAnim::ColiUserData::m_rtti("gf::GfFieldLodColiAnim::ColiUserData", &fw::ColiUserData::m_rtti, nullptr);

}  // namespace gf
