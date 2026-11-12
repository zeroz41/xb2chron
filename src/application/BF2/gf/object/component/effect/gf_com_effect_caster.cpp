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
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetResource.h"
#include "gf/GfObjAcc.h"
#include "gf/MsgFxBuff.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfExtendPacking.h"
#include "gf/MsgFxWeapon.h"
#include "classes/gf/GfComAsm.h"
#include "gf/GfObjUtil.h"
#include "gf/GfDataWeapon.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/fw/EffectPack.h"
#include "effect/SendParam.h"
#include "gf/GfEffectGround.h"
#include "gf/GfEnvProperty.h"
#include "classes/gf/GfComProperty.h"
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include "classes/fw/EffectResData.h"
#include "classes/gf/EffectCaster.h"
#include "classes/gf/GfComEffectCaster.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/EffectMountSetupEv.h"

// the ASM annotation name registerAsmCallbackEffect registers effects under
const char* ASM_CB_NAME_EFFECT = "asm_effect";

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EABD68). setupCaster sets it (and the
// caster's flag at 0xA0) for the first caster of the party leader; the destructor clears it.
static bool s_leaderCasterSet;

void GfComEffectCaster::procMsgFxForceCancel(fw::MessageObject*, MsgFxForceCancel&) {
    if (m_resData) {
        for (fw::EffectAnnotationData* it = m_resData->m_annotations.begin(); it != m_resData->m_annotations.end();
             ++it) {
            if (it->pad_f8 && it->pad_10c) {
                effectEnd(it->pad_10c);
                it->pad_10c = 0;
            }
        }
    }
}

void GfComEffectCaster::procMsgFxBuff(fw::MessageObject*, MsgFxBuff& msg) {
    GfComAsm* com = m_owner->getComponent<GfComAsm>(2);
    if (m_resData != nullptr && com != nullptr) {
        GfObjAcc acc(static_cast<GfObj*>(m_owner));
        for (fw::EffectAnnotationData* it = m_resData->m_annotations.begin(); it != m_resData->m_annotations.end();
             ++it) {
            if (it->m_type == 9 && strstr(it->m_stateName.m_str, com->getStateName(AnimLayer(0))) != nullptr) {
                EffectSetUp setup;
                setup.m_name = it->pad_54.m_str;
                setup.pad_44 = it->pad_108;
                setup.m_scale = pad_117b8 * it->pad_c4;
                setup.pad_48 = it->pad_f5;
                setup.pad_49 = it->pad_f4;
                setup.pad_20 = msg.pad_10;
                setup.m_pos = it->m_position;
                setup.m_rot = it->m_rotation;
                setup.pad_4b = it->pad_f9;
                setup.pad_4c = it->pad_fa;
                setup.pad_4d = it->pad_fb;
                if (it->pad_fb) {
                    setup.m_scale = it->pad_c4;
                }
                it->pad_10c = effectStart(setup, it->pad_78.m_str);
            }
        }
    }
}

void GfComEffectCaster::procMsgFxWeapon(fw::MessageObject*, MsgFxWeapon& msg) {
    if (m_resData != nullptr) {
        for (fw::EffectAnnotationData* it = m_resData->m_annotations.begin(); it != m_resData->m_annotations.end();
             ++it) {
            if (it->m_type == 2) {
                switch (msg.m_type) {
                case 0: {
                    EffectSetUp setup;
                    setup.m_name = it->pad_54.m_str;
                    setup.pad_44 = it->pad_108;
                    setup.m_scale = pad_117b8 * it->pad_c4;
                    setup.pad_48 = it->pad_f5;
                    setup.pad_49 = it->pad_f4;
                    setup.pad_4a = 1;
                    setup.m_pos = it->m_position;
                    setup.m_rot = it->m_rotation;
                    setup.pad_4b = it->pad_f9;
                    setup.pad_4c = it->pad_fa;
                    setup.pad_4d = it->pad_fb;
                    if (it->pad_fb) {
                        setup.m_scale = it->pad_c4;
                    }
                    it->pad_10c = effectStart(setup, it->pad_78.m_str);
                    break;
                }
                case 1:
                    effectEnd(it->pad_10c);
                    break;
                }
            }
        }
    }
}

GfComEffectCaster::GfComEffectCaster()
    : m_waterDepthLimit(FLT_MIN), m_chestHeight(FLT_MIN), pad_30(0), pad_38(0), m_resData(nullptr), pad_48(nullptr),
      m_caster(nullptr), m_pPoint(nullptr), pad_117ac(0), pad_117c4(0) {
    pad_116e0 = mm::Mat44(mm::Mat44::identity);
    pad_11720 = mm::Mat44(mm::Mat44::identity);
    pad_18 = 0.0f;
    pad_1c = -1.0f;
    pad_20 = -1.0f;
    pad_11760 = "cmn_001_020";
    pad_11774 = "cmn_001_000";
    m_motionFrame = 0.0f;
    pad_117b4 = 1;
    m_viewnum = 0;
    m_tailId = -1;
    pad_14 = false;
}

GfComEffectCaster::~GfComEffectCaster() {
    s_leaderCasterSet = false;
    cleanup();
}

void GfComEffectCaster::cleanup() {
    for (EventEfHandleTbl* it = m_eventEfHandles.begin(); it != m_eventEfHandles.end(); ++it) {
        if (it->pad_28) {
            it->pad_28->release();
            it->pad_28 = nullptr;
        }
    }
    m_eventEfHandles.clear();
    for (Param* it = m_params.begin(); it != m_params.end(); ++it) {
        if (it->m_id) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(it->m_id);
        }
        if (it->pad_6e && m_pPoint) {
            m_pPoint->m_releaseFrame(it->pad_34.m_str);
        }
    }
    m_params.clear();
    if (pad_48) {
        pad_48->release();
        pad_48 = nullptr;
    }
    for (unsigned int i = 0; i < m_packs.size(); ++i) {
        if (m_packs[i].m_pack) {
            m_packs[i].m_pack->release();
            m_packs[i].m_pack = nullptr;
        }
    }
    m_packs.clear();
    if (EffectCaster* caster = m_caster) {
        if (caster->m_pPoint) {
            caster->m_pPoint->release();
            caster->m_pPoint = nullptr;
        }
        caster->m_isDead = true;
        m_caster = nullptr;
    }
    if (m_pPoint) {
        m_pPoint->release();
        m_pPoint = nullptr;
    }
}

void GfComEffectCaster::setup(const SetupInfo& info) {
    pad_48 = nullptr;
    m_viewnum = info.m_viewnum;
    m_layer = info.pad_10;
    pad_117ac = info.m_kind;
    GfAssetResource* efb = GfObjUtil::getResourceEfb(static_cast<GfObj*>(m_owner)->m_handle);
    pad_48 = efb ? fw::EffectPack::createFromMemory(efb->getAssetData(), efb->getAssetSize(), efb->getAssetName(), false)
                 : nullptr;
    pad_117b8 = info.pad_18;
    mm::mtl::FixedVector<const char*, 128> names;
    GfAssetManager::getFileNameByExt(names, info.m_asset, ".wiefb");
    for (const char*& name : names) {
        if (GfAssetResource* resource = GfAssetManager::getResource(info.m_asset, name)) {
            unsigned int id = 0;
            if (const char* number = strchr(resource->getAssetName(), '_')) {
                char digits[4] = {};
                digits[0] = number[1];
                digits[1] = number[2];
                digits[2] = '\0';
                id = atoi(digits);
            }
            PackEntry entry;
            entry.m_pack = fw::EffectPack::createFromMemory(resource->getAssetData(), resource->getAssetSize(),
                                                            resource->getAssetName(), false);
            entry.m_id = id;
            m_packs.push_back(entry);
        }
    }
    setupEfp(info);
    if (m_caster == nullptr) {
        setupCaster(m_pPoint);
    }
    setupEfTail(1);
    if (GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2)) {
        asmCom->m_callbacks[3].name = ASM_CB_NAME_EFFECT;
        asmCom->m_callbacks[3].delegate.set(this, &GfComEffectCaster::asmCallback);
    } else if (GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2)) {
        evtAnim->m_asm.m_callbacks[3].name = ASM_CB_NAME_EFFECT;
        evtAnim->m_asm.m_callbacks[3].delegate.set(this, &GfComEffectCaster::evtAnimCallback);
    }
    GfExtendResource* extend = GfAssetManager::getExtentResource(info.m_asset, 0);
    if (extend && extend->getRTTI()->isKindOf(&GfExtendPacking::m_rtti)) {
        GfExtendPacking* packing = static_cast<GfExtendPacking*>(extend);
        if (packing->m_pEffectResData) {
            m_resData = packing->m_pEffectResData;
            GfObjAcc acc(static_cast<GfObj*>(m_owner));
            for (fw::EffectAnnotationData* it = packing->m_pEffectResData->m_annotations.begin();
                 it != packing->m_pEffectResData->m_annotations.end(); ++it) {
                if (it->m_type == 0) {
                    EffectSetUp setup;
                    setup.m_name = it->pad_54.m_str;
                    if (it->pad_108 == 1) {
                        setup.m_caster = m_caster;
                    } else {
                        setup.m_caster = nullptr;
                    }
                    setup.m_scale = pad_117b8 * it->pad_c4;
                    setup.pad_48 = it->pad_f5;
                    setup.pad_49 = it->pad_f4;
                    setup.m_pos = it->m_position;
                    setup.m_rot = it->m_rotation;
                    setup.pad_4b = it->pad_f9;
                    setup.pad_4c = it->pad_fa;
                    setup.pad_4d = it->pad_fb;
                    if (it->pad_fb) {
                        setup.m_scale = it->pad_c4;
                    }
                    effectStart(setup, it->pad_78.m_str);
                }
            }
        }
    }
}

void GfComEffectCaster::setupEfp(const SetupInfo& info) {
    GfObjAcc acc(static_cast<GfObj*>(m_owner));
    fw::UpdatableObject* owner = m_owner;
    GfAssetResource* resource;
    switch (pad_117ac) {
    case 0:
    case 1:
        resource = GfAssetManager::getResource(info.m_asset, static_cast<GfFileIdx>(61), static_cast<GfAssetType>(0));
        break;
    case 3:
    case 5:
        resource = GfAssetManager::getResource(info.m_asset, static_cast<GfFileIdx>(3), static_cast<GfAssetType>(0));
        break;
    case 4:
    case 8:
        resource = GfAssetManager::getResource(info.m_asset, static_cast<GfFileIdx>(2), static_cast<GfAssetType>(0));
        break;
    case 2:
    case 6:
    case 7:
        resource = GfAssetManager::getResource(info.m_asset, static_cast<GfFileIdx>(9), static_cast<GfAssetType>(0));
        break;
    default:
        return;
    }
    if (resource) {
        fw::EfpInitData init;
        init.pad_0 = info.pad_10;
        init.scale = 1.0f;
        if (GfComModel* model = owner->getComponent<GfComModel>(1)) {
            init.createFrame.set(model, &GfComModel::createBoneReferenceFrame);
            init.releaseFrame.set(model, &GfComModel::destroyBoneReferenceFrame);
            init.model = model->m_model;
        }
        init.allocator = fw::Framework::getAllocator();
        init.data = resource->getAssetData();
        init.size = resource->getAssetSize();
        m_pPoint = new (init.allocator, 16, __FILE__, 606) fw::EffectPoint(init);
        if (m_pPoint) {
            m_pPoint->addRef();
        }
    }
}

void GfComEffectCaster::setupEfTail(unsigned int id) {
    if (pad_117ac != 0) {
        if (m_tailId != id) {
            mm::mtl::FixedVector<const char*, 128> names;
            GF_ASSET_HANDLE* asset = GfObjUtil::getAssetHandle(static_cast<GfObj*>(m_owner)->m_handle);
            if (GfAssetManager::getFileNameByExt(names, asset, ".wiswt")) {
                if (GfAssetResource* resource = GfAssetManager::getResource(asset, names[0])) {
                    EffectCaster* caster = m_caster;
                    void* data = resource->getAssetData();
                    unsigned int size = resource->getAssetSize();
                    caster->pad_20 = data;
                    caster->pad_28 = size;
                    m_tailId = id;
                }
            }
        }
    } else if (m_caster && m_tailId != id) {
        mm::mtl::FixedVector<const char*, 128> names;
        GF_ASSET_HANDLE* asset = GfObjUtil::getAssetHandle(static_cast<GfObj*>(m_owner)->m_handle);
        GfAssetManager::getFileNameByExt(names, asset, ".wiswt");
        for (const char* name : names) {
            if (GfAssetResource* resource = GfAssetManager::getResource(asset, name)) {
                if (const char* number = strchr(resource->getAssetName(), '_')) {
                    char digits[4] = {};
                    digits[0] = number[1];
                    digits[1] = number[2];
                    digits[2] = '\0';
                    if (atoi(digits) == id) {
                        EffectCaster* caster = m_caster;
                        void* data = resource->getAssetData();
                        unsigned int size = resource->getAssetSize();
                        caster->pad_20 = data;
                        caster->pad_28 = size;
                        m_tailId = id;
                        return;
                    }
                }
            }
        }
    }
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
                caster->m_pModel = model->m_model->getInterface();
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

// 1.0.0's GfComEffectCaster::effectEnd(unsigned int) (0x71005076BC, the same loop without the zero check); 3.0.1
// inlines every call
inline void GfComEffectCaster::effectEnd(unsigned int handle) {
    if (handle == 0) {
        return;
    }
    for (Param& param : m_params) {
        if (param.m_id == handle && param.m_id != 0) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(handle);
            param.pad_ba = true;
            return;
        }
    }
}

void GfComEffectCaster::updateParam(GfComEffectCaster* caster, Param* param, float rate, bool) {
    effect::SendParam sendParam;
    calcMtxAndScale(caster, param, rate, false, sendParam);
    switch (calcFollowAnnotetionTag(param, sendParam)) {
    case 0:
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(param->m_id, &sendParam);
        break;
    case 1:
        sendParam.m_flagB = false;
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(param->m_id, &sendParam);
        break;
    case 2:
        // kills the running effect, once
        if (!param->pad_ba) {
            effectEnd(param->m_id);
        }
        break;
    }
}

bool GfComEffectCaster::getEfpMatrix(const char* name, mm::Mat44& mtx) {
    if (m_caster) {
        if (m_caster->m_pPoint == nullptr) {
            return false;
        }
        int index = m_caster->m_pPoint->getPointIndex(name);
        if (index != -1) {
            mtx.mulSafe(m_caster->m_pPoint->getPointTransform(index), m_caster->m_mtx);
            return true;
        }
    }
    return false;
}

int GfComEffectCaster::calcFollowAnnotetionTag(Param* param, effect::SendParam& sendParam) {
    int result;
    switch (param->m_followKind) {
    case 0:
        return 0;
    default:
        return GfEffectGround::isOnWaterSurface(this) ? 2 : 0;
    case 4:
        GfEffectGround::calcSwimEffectParam(this, false, false, sendParam);
        return 0;
    case 7:
    case 8:
    case 9:
    case 13:
        result = GfEffectGround::calcSwimEffectParam(this, false, false, sendParam);
        break;
    case 10:
    case 11:
        result = GfEffectGround::calcSwimEffectParam(this, false, true, sendParam);
        break;
    case 12:
        result = GfEffectGround::calcSwimEffectParam(this, true, false, sendParam);
        break;
    case 14: {
        GfEnvProperty* env = m_owner->findComponent<GfComProperty>(5)->m_env.get();
        // the flags are read before the null check (the original loads them first)
        if (!(env->m_flags & 2) || env == nullptr) {
            return 0;
        }
        GfObjAcc acc(static_cast<GfObj*>(m_owner));
        return acc.getWorldTransform().position.y - env->m_grounds[0].m_position.y > 3.0f ? 0 : 2;
    }
    }
    return static_cast<unsigned int>(result) < 3 ? result : 0;
}

GfComEffectCaster::Param* GfComEffectCaster::findEffectCasterParam(unsigned int id) {
    for (Param* it = m_params.begin(); it != m_params.end(); ++it) {
        if (it->m_id == id) {
            return it;
        }
    }
    return nullptr;
}

fw::EffectPack* GfComEffectCaster::getWeaponEffectPack(const char* name) {
    if (strncmp(name, "cmn", 3) != 0) {
        unsigned int type;
        {
            DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
            type = GfDataWeapon::getEffWeaponType(acc.getWeaponType(-1, false));
        }
        fw::EffectPack* found = nullptr;
        for (unsigned int i = 0; i < m_packs.size(); ++i) {
            if (m_packs.at(i)->m_id == type || GfGameManager::isGameTypeIra()) {
                if (m_packs[i].m_pack && m_packs[i].m_pack->searchEfb(name)) {
                    found = m_packs[i].m_pack;
                    break;
                }
            }
        }
        if (found) {
            return found;
        }
        fw::EffectPack* pack = pad_48;
        if (pad_117ac == 3 || pad_117ac == 4) {
            GF_OBJ_HANDLE* parent = GfObjUtil::getParentHandle(static_cast<GfObj*>(m_owner)->m_handle);
            if (parent != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                GfObjUtil::getAssetHandle(parent);
                GfAssetResource* resource = GfObjUtil::getResourceEfb(static_cast<GfObj*>(m_owner)->m_handle);
                if (resource) {
                    pack = fw::EffectPack::createFromMemory(resource->getAssetData(), resource->getAssetSize(),
                                                            resource->getAssetName(), false);
                } else {
                    pack = nullptr;
                }
            }
        }
        return pack;
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

void GfComEffectCaster::createFromFileName(const mm::Mat44& mtx, const char* fileName) const {
    effect::SendParam param;
    param.m_mtx = mtx;
    unsigned int handle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(fileName, nullptr, &param, true);
    if (m_viewnum) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setViewnum(handle, m_viewnum);
    }
}

void GfComEffectCaster::addMountEffectEv(const EffectMountSetupEv& setup) {
    if (setup.m_id == 0) {
        return;
    }
    EventEfHandleTbl handle;
    handle.m_boneName = setup.m_boneName;
    handle.m_id = setup.m_id;
    handle.pad_28 = nullptr;
    handle.pad_30 = setup.m_pos;
    handle.pad_41 = setup.pad_41;
    handle.pad_40 = setup.pad_40;
    handle.pad_42 = setup.pad_42;
    if (handle.pad_41) {
        if (m_pPoint) {
            handle.pad_28 = m_pPoint->m_createFrame(handle.m_boneName.m_str);
        } else if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
            handle.pad_28 = model->createBoneReferenceFrame(handle.m_boneName.m_str);
        }
    }
    m_eventEfHandles.push_back(handle);
}

bool GfComEffectCaster::removeMountEffectEv(unsigned int id) {
    for (EventEfHandleTbl& handle : m_eventEfHandles) {
        if (handle.m_id == id) {
            if (handle.pad_41) {
                if (m_pPoint) {
                    m_pPoint->m_releaseFrame(handle.m_boneName.m_str);
                } else if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
                    model->destroyBoneReferenceFrame(handle.m_boneName.m_str);
                }
            }
            m_eventEfHandles.erase(&handle);
            return true;
        }
    }
    return false;
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

bool GfComEffectCaster::getEffectPack(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs) {
    packs.clear();
    if (pad_48) {
        packs.push_back(pad_48);
    }
    if (GfGameManager::isGameTypeIra()) {
        for (PackEntry& entry : m_packs) {
            packs.push_back(entry.m_pack);
        }
    }
    return !packs.empty();
}

bool GfComEffectCaster::getWeaponEffectPack(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs, int id, int) {
    packs.clear();
    for (PackEntry& entry : m_packs) {
        if (entry.m_id == id) {
            packs.push_back(entry.m_pack);
        }
    }
    return !packs.empty();
}

void GfComEffectCaster::applyEffpointByMatrix(const mm::Mat44& mtx) {
    if (m_caster) {
        m_caster->flushDirectMatrix(mtx);
    }
}

void EffectCaster::flushDirectMatrix(const mm::Mat44& mtx) {
    m_mtx = mtx;
    mm::Mat44 pointMtx(mtx);
    setEfpMat(pointMtx, "root", 0);
    if (m_pPoint != nullptr) {
        int index = 1;
        for (int i = 0; i < m_pPoint->getPointCount(); i++) {
            const char* name = m_pPoint->getPointName(i);
            pointMtx.mulSafe(m_pPoint->getPointTransform(i), mtx);
            setEfpMat(pointMtx, name, index);
            m_pPoint->setDirty(i, true);
            index++;
        }
    }
}

void EffectCaster::update(const fw::UpdateInfo&) {
    if (pad_8.get() != nullptr) {
        pad_8.get()->syncWorldMatrix();
        m_mtx = pad_8->m_worldMatrix;
        mm::Mat44 pointMtx(m_mtx);
        setScl(1.0f);
        setEfpMat(m_mtx, "root", 0);
        if (m_pPoint != nullptr) {
            int index = 1;
            for (int i = 0; i < m_pPoint->getPointCount(); i++) {
                const char* name = m_pPoint->getPointName(i);
                if (m_pPoint->isDirty(i)) {
                    pointMtx.mulSafe(m_pPoint->getPointTransform(i), m_mtx);
                    setEfpMat(pointMtx, name, index);
                    m_pPoint->setDirty(i, false);
                    index++;
                }
            }
        }
    }
}
}  // namespace gf

template void mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>::memberFuncInvoker<gf::GfComEffectCaster>(const mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>*, gf::GfComAsm*, const gf::CallBackCache&);

template void mm::mtl::Delegate<void(gf::GfComEvtAnim*, const gf::CallBackCache&)>::memberFuncInvoker<gf::GfComEffectCaster>(const mm::mtl::Delegate<void(gf::GfComEvtAnim*, const gf::CallBackCache&)>*, gf::GfComEvtAnim*, const gf::CallBackCache&);

namespace gf {

mm::mtl::RTTI GfComEffectCaster::m_rtti("GfComEffectCaster", &GfComEffect::m_rtti, nullptr);

}  // namespace gf
