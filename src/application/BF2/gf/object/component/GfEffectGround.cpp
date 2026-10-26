#include "gf/GfEffectGround.h"
#include "gf/GfEnvProperty.h"
#include "gf/MsgFxFootPrint.h"
#include "gf/GfTargetProperty.h"
#include "effect/SendParam.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/fw/ReferenceFrame.h"
#include "gf/GfObjUtil.h"
#include "plugin/Bdat.h"
#include "mm/Plane.h"
#include "mm/Quat.h"
#include <string.h>

namespace gf {

namespace {
// the ground and water around the caster's object (inline: the name is not the original's)
inline GfEnvProperty* getEnvProperty(const GfComEffectCaster* caster) {
    return caster->m_owner->findComponent<GfComProperty>(5)->m_env.get();
}

// the object is in water at least as deep as the caster's limit (inline: the name is not the original's)
inline bool isInDeepWater(const GfComEffectCaster* caster) {
    GfEnvProperty* env = getEnvProperty(caster);
    if (env == nullptr || !(env->m_flags & 1)) {
        return false;
    }
    return !(env->m_water.m_depth < caster->m_waterDepthLimit);
}
}  // namespace

bool GfEffectGround::getGroundEffectFileNameImpl(unsigned int kind, unsigned int footStepEffect,
                                                 unsigned int material, const char*& fileName) {
    fileName = nullptr;
    if (footStepEffect == 0) {
        return false;
    }
    unsigned char* materialFp = GfDataBdat::getFP(0x1dd);
    if (materialFp == nullptr) {
        return false;
    }
    unsigned char effectId = Bdat::getVal(materialFp, material, kind);
    unsigned char* footStepFp = GfDataBdat::getFP(0x1df);
    if (effectId == 0 || footStepFp == nullptr) {
        return false;
    }
    unsigned char fileId = Bdat::getVal(footStepFp, footStepEffect - 1, effectId);
    if (fileId == 0) {
        return false;
    }
    fileName = reinterpret_cast<const char*>(Bdat::getVal(GfDataBdat::getFP(0x1de), "file_name", fileId));
    return fileName != nullptr;
}

bool GfEffectGround::isOnWaterSurface(const GfComEffectCaster* caster) {
    GfEnvProperty* env = getEnvProperty(caster);
    if (env == nullptr) {
        return false;
    }
    return env->m_flags & 1;
}

unsigned int GfEffectGround::getGroundMaterial(GfEnvProperty* env, const GfComEffectCaster* caster) {
    if (env->m_flags & 1) {
        unsigned int material;
        if (env->m_water.m_materialOverride != 0 &&
            (env->m_water.m_materialOverride != 1 || GfGameManager::isNight())) {
            material = env->m_water.m_materialOverride + 12;
        } else {
            material = env->m_water.m_material;
        }
        if (isInDeepWater(caster)) {
            switch (material) {
            case 1:
                material = 16;
                break;
            case 11:
                material = 17;
                break;
            case 13:
                material = 18;
                break;
            }
        }
        return material;
    }
    if (env->m_flags & 2) {
        const GfEnvProperty::Ground& ground = env->m_grounds[0];
        if (ground.m_materialOverride != 0 && (ground.m_materialOverride != 1 || GfGameManager::isNight())) {
            return ground.m_materialOverride + 12;
        }
        return ground.m_material;
    }
    return 0;
}

bool GfEffectGround::getGroundEffectFileName(const GfComEffectCaster* caster, unsigned int kind,
                                             const char*& fileName) {
    GfObjSetup* setup = GfObjUtil::getObjSetup(static_cast<GfObj*>(caster->m_owner)->m_handle);
    if (setup == nullptr) {
        return false;
    }
    GfEnvProperty* env = getEnvProperty(caster);
    if (env == nullptr) {
        return false;
    }
    return getGroundEffectFileNameImpl(kind, setup->getFootStepEffect(), getGroundMaterial(env, caster), fileName);
}

}  // namespace gf
