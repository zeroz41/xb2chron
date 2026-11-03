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
#include "gf/GfObjUtil.h"
#include "gf/GfDataWeapon.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/fw/EffectPack.h"
#include "effect/SendParam.h"
#include "gf/GfEffectGround.h"
#include "gf/GfEnvProperty.h"
#include "classes/gf/GfComProperty.h"
#include <stdlib.h>
#include <string.h>
#include "classes/fw/EffectResData.h"
#include "classes/gf/EffectCaster.h"
#include "classes/gf/GfComEffectCaster.h"
#include "mm/mtl/Delegate.h"

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

GfComEffectCaster::~GfComEffectCaster() {
    s_leaderCasterSet = false;
    cleanup();
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
            if (GfAssetManager::fn_71001AE8A8(names, asset, ".wiswt")) {
                if (GfAssetResource* resource = GfAssetManager::fn_71001AE9D0(asset, names[0])) {
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
        GfAssetManager::fn_71001AE8A8(names, asset, ".wiswt");
        for (const char* name : names) {
            if (GfAssetResource* resource = GfAssetManager::fn_71001AE9D0(asset, name)) {
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
            if (m_packs.at(i)->m_id == type || GfGameManager::fn_71002A9E68()) {
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

bool GfComEffectCaster::fn_71004B39DC(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs) {
    packs.clear();
    if (pad_48) {
        packs.push_back(pad_48);
    }
    if (GfGameManager::fn_71002A9E68()) {
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

void GfComEffectCaster::fn_71004B3B68(const mm::Mat44& mtx) {
    if (m_caster) {
        m_caster->fn_71004B3B78(mtx);
    }
}
}  // namespace gf

template void mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>::memberFuncInvoker<gf::GfComEffectCaster>(const mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>*, gf::GfComAsm*, const gf::CallBackCache&);

template void mm::mtl::Delegate<void(gf::GfComEvtAnim*, const gf::CallBackCache&)>::memberFuncInvoker<gf::GfComEffectCaster>(const mm::mtl::Delegate<void(gf::GfComEvtAnim*, const gf::CallBackCache&)>*, gf::GfComEvtAnim*, const gf::CallBackCache&);

namespace gf {

mm::mtl::RTTI GfComEffectCaster::m_rtti("GfComEffectCaster", &GfComEffect::m_rtti, nullptr);

}  // namespace gf
