#ifndef FW_COLICHECK_H
#define FW_COLICHECK_H

#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"

namespace fw {

// what a collision test looks for (fw::ColiCheck::testCapsule reads it; StateFieldIdle::checkSpace and
// fw::ColiCheck::getSnapPos fill it on the stack). The field names are not the original's.
struct ColiCheckConfig {
    // the defaults getSnapPos keeps (checkSpace changes m_mode and m_option); both set m_flags and m_mask after it
    // the two flags are set in the body, m_callbackParam first: GmkMob::PopXformFinder::findPosRot stores the
    // false before the true (an init list stores them in field order)
    ColiCheckConfig() : m_radius(0.0f), pad_c(), m_mode(1) {
        m_callbackParam = false;
        m_option = true;
    }

    unsigned int m_flags;  // bits 0, 1, 3: test the collision (IDColiDef); bit 2: test the phantoms
    unsigned int m_mask;   // the collision groups to hit (testCapsule hands on its complement)
    float m_radius;        // testCapsule hands on its square
    unsigned char pad_c[0x4];
    unsigned int m_mode;   // 0, 1 or 2 (2: with result buffers)
    bool m_option;         // getSnapPos sets it, checkSpace clears it; testLine and testCapsule do not read it
    bool m_callbackParam;  // testLine and testCapsule copy it into their ColiCheckCallback
};

// one hit of a collision test (the name is the original's: std::sort sorts fw::ContactInfo in
// EnviromentSensor::searchVertical; the field names are not). Its first 0x30 bytes copy as one unit after a
// self test, the rest as plain bytes (the sort's swaps).
struct ContactPoint {
    ContactPoint() {}
    ContactPoint(const ContactPoint& other) { *this = other; }
    ContactPoint& operator=(const ContactPoint& other) {
        if (this != &other) {
            m_position = other.m_position;
            m_normal = other.m_normal;
            pad_20 = other.pad_20;
        }
        return *this;
    }
    mm::Vec3 m_position;  // where the test hit (the field names are not the original's)
    mm::Vec3 m_normal;    // the surface's normal there
    mm::Vec3 pad_20;
};
struct ContactInfo : ContactPoint {
    // the surface a hit found (GfComEnvSensor::flushGroundSingle copies it into its GfEnvProperty::Ground; the
    // field names are not the original's)
    struct Material {
        unsigned short m_id;  // the ground's material
        unsigned char pad_2[0x2];
        unsigned int m_attribute;
        unsigned char pad_8[0x10];
        unsigned char m_params[4];  // the ground takes them as floats
    };
    const Material* m_material;  // none: getMaterial gives a zeroed one
    unsigned char pad_38[0x14];
};

// a collision test's hits: room for N in place, their count, how many were found and whether any was
// (testCapsule clears all three first). The field names are not the original's.
template <unsigned int N>
class TColiCheckResult {
public:
    typedef ContactInfo::Material Material;
    typedef ContactInfo Hit;

    TColiCheckResult() : m_count(0), m_hit(false) {}

    // empties the result before a test (gf::PlayerCamera::getHitPosition; the name is not the original's)
    void clear() {
        m_hit = false;
        m_hits.clear();
        m_count = 0;
    }

    // the accessors' names are not the original's (1.0.0 names getMaterial; GfComEnvSensor::flushGroundSingle
    // inlines them all)
    unsigned int getHitNum() const { return m_hits.size(); }
    const mm::Vec3& getPosition(unsigned int index) const {
        if (index < getHitNum()) {
            return m_hits[index].m_position;
        }
        return mm::Vec3::zero;
    }
    const mm::Vec3& getNormal(unsigned int index) const {
        if (index < getHitNum()) {
            return m_hits[index].m_normal;
        }
        return mm::Vec3::zero;
    }
    // its statics' names are the original's
    const Material& getMaterial(unsigned int index) const {
        if (index < m_count) {
            if (m_hits[index].m_material != nullptr) {
                return *m_hits[index].m_material;
            }
        }
        static bool bInitialized = false;
        static Material nullData;
        if (!bInitialized) {
            memset(&nullData, 0, sizeof(nullData));
            bInitialized = true;
        }
        return nullData;
    }

    mm::mtl::FixedVector<Hit, N> m_hits;
    unsigned int m_count;
    bool m_hit;
};

class ColiCheck {
public:
    static bool testLine(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end,
                         const ColiCheckConfig& config);
    // testLine against the characters' collision (ColiCharactorProxy's unit)
    static bool testLineChara(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end,
                              const ColiCheckConfig& config);
    static bool testCapsule(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end, float radius,
                            const ColiCheckConfig& config);
    // the ground below from (pos gets the hit when it returns true; FormManager::replace passes 6.0 and ~0)
    static bool getSnapPos(mm::Vec3& pos, const mm::Vec3& from, float, unsigned int);
};

}  // namespace fw

#endif
