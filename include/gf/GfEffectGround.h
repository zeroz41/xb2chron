#ifndef GF_GFEFFECTGROUND_H
#define GF_GFEFFECTGROUND_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace effect { class SendParam; }

namespace gf {
class GfComEffectCaster;
class GfEnvProperty;
class MsgFxFootPrint;

// no table: the effects an object leaves on the ground and water under it (foot steps, splashdowns, swimming),
// for its effect caster. The file names come from three BDAT tables (0x1DD by material and kind, 0x1DF by the
// object's foot step effect, 0x1DE the file_name column).
class GfEffectGround {
public:
    // where a ground effect goes and which row of the tables picks its file (the field names are not the
    // original's)
    struct GroundEffectParam {
        mm::Mat44 m_mtx;  // on the ground, facing the object's front
        unsigned int m_footStepEffect;  // the object's setup's getFootStepEffect
        unsigned int m_material;  // getGroundMaterial's
    };

    // the ground's foot step effects (kind 1, then 2, or 3 for the message's m_alternate), unless the object
    // is deep enough in water
    static void emitFootStepEffect(const GfComEffectCaster* caster, const MsgFxFootPrint& msg);
    // the ground (or water surface) at the object's ground index: false when there is neither
    static bool getGroundEffectParam(const GfComEffectCaster* caster, int index, const char*& fileName,
                                     GroundEffectParam& param);
    static bool getGroundEffectFileNameImpl(unsigned int kind, unsigned int footStepEffect, unsigned int material,
                                            const char*& fileName);
    // the splashdown effect (kind 5, or 6) at the ground under the object
    static void emitSplashdownEffect(const GfComEffectCaster* caster, bool alternate);
    // 0: the swim effect goes at the water's height (set in param); 1: the object is too far below it; 2: no water
    static int calcSwimEffectParam(const GfComEffectCaster* caster, bool checkDepth, bool ignoreHeight,
                                   effect::SendParam& param);
    static bool isOnWaterSurface(const GfComEffectCaster* caster);
    // mtx at pos with its y axis along normal and its x axis front turned onto the surface (front is turned too)
    static void calcGroundMtx(const mm::Vec3& pos, const mm::Vec3& normal, mm::Vec3& front, mm::Mat44& mtx);
    static unsigned int getGroundMaterial(GfEnvProperty* env, const GfComEffectCaster* caster);
    static bool getGroundEffectFileName(const GfComEffectCaster* caster, unsigned int kind, const char*& fileName);
};

}  // namespace gf

#endif
