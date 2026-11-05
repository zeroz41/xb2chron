#ifndef GF_GFENVPROPERTY_H
#define GF_GFENVPROPERTY_H

#include "mm/Plane.h"
#include "mm/Vec3.h"

namespace gf {

// no table: the ground and water around an object, as its environment sensor found them (1.0.0's
// EnviromentSensor::writeBackProperty and GfComEnvSensor::flushGroundSingle write one; GfComProperty holds it).
// GfEffectGround reads the fields below; the names are not the original's, and the size past m_flags is not known.
class GfEnvProperty {
public:
    // which of m_grounds (1.0.0's name; its values' names are not known: GfComEnvSensor's feet use 1-6, its root 7)
    // (signed: GfComEnvSensor::flushGroundSingle sign-extends it to index m_grounds)
    enum GROUND_INDEX : int {};
    // one ground under the object (1.0.0's FootStepPlugin takes a GROUND_INDEX; m_grounds holds them by it)
    struct Ground {
        Ground() : m_plane(mm::Vec3::unitY, 0.0f) {}
        mm::Vec3 m_position;  // where the ground was found (GfEffectGround places its effect there)
        mm::Plane m_plane;  // its surface (the effect faces its normal)
        unsigned int m_attribute;  // its collision material's (GfComEnvSensor::flushGroundSingle)
        unsigned int m_material;  // the ground's material (GfEffectGround's effect table row)
        float m_params[4];  // its collision material's bytes (GfComEnvSensor::flushGroundSingle)
        // not 0: the material is it plus 12 instead, 1 only at night (GfEffectGround::getGroundMaterial)
        unsigned int m_materialOverride;
        unsigned char pad_4c[0x4];
    };
    // the water the object is in
    struct Water {
        float m_height;  // the surface's height (GfEffectGround::calcSwimEffectParam places the swim effect at it)
        unsigned char pad_4[0xC];
        mm::Plane m_plane;  // its surface (GfEffectGround projects the object's position onto it)
        // GfComSound::flushVariables sets water_depth to 1 while it is not below the water_th sound variable
        // (in hundredths; the name is not the original's)
        float m_level;
        // how deep the object is (GfEffectGround compares it with the caster's limit)
        float m_depth;
        unsigned int m_material;  // the water's material
        // not 0: the material is it plus 12 instead, 1 only at night (GfEffectGround::getGroundMaterial)
        unsigned int m_materialOverride;
        unsigned char pad_40[0x10];
    };

    Ground m_grounds[8];
    Water m_water;
    // bit 0: m_water holds the water the object is in; bit 1 + i: m_grounds[i] holds a ground
    unsigned int m_flags;
    // GfComIK's grounds read none of it while clear (the name is not the original's)
    bool m_valid;

    // whether m_grounds[index] holds a ground (inline: the name is not the original's)
    bool isGround(int index) const { return ((1 << (index + 1)) & m_flags) != 0; }
    // m_grounds[index] while it holds a ground, else none (inline: the name is not the original's)
    const Ground* getGround(int index) const { return isGround(index) ? &m_grounds[index] : nullptr; }
};

}  // namespace gf

#endif
