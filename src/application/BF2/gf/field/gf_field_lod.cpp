#include "mm/mtl/Algorithm.h"
#include "classes/gf/GfFieldLodColiAnim.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfFieldLodColiAnim.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfManager.h"
#include "classes/fw/EffectManager.h"
#include "ml/ScnObjAccSeamPos.h"
#include "ml/ScnObjAccPartsPos.h"
#include "plugin/Bdat.h"
#include <string.h>
#include "mm/mtl/Vector.h"

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
