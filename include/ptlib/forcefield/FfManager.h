#ifndef PTLIB_FORCEFIELD_FFMANAGER_H
#define PTLIB_FORCEFIELD_FFMANAGER_H

#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"

namespace ptlib {

namespace emitter { class ParticleObj; }

// a force the force-field manager adds (effect::SystemManager keeps them until tail hands them on). The field names
// are not the original's: FfManager::addForce copies the force out of it and moveForce reads that copy.
class AddForceParam {
public:
    int m_type;      // FfManager::moveForce's kind of force (1 to 8)
    short m_start;   // the force acts from this many frames on
    short m_life;    // frames until FfManager::update removes it; -1 keeps it
    mm::Vec3 m_pos;  // the force's centre
    mm::Vec3 m_force;
    float m_radius;  // the reach of the kinds that act around m_pos
};

namespace forcefield {

// a force the manager keeps: addForce's copy of the request and its age (the type and field names are not the
// original's; no symbol names them)
class Force {
public:
    int m_frame;  // update adds the frames that passed
    AddForceParam m_param;
};

class FfManager {
public:
    typedef mm::mtl::FixedVector<Force*, 128> ForceList;

    static void init();
    static FfManager*& getPtr();
    static void term();
    void update(float frame);
    void moveForce(emitter::ParticleObj* pParticle);
    void addForce(const AddForceParam& param);

    ForceList m_forces;  // the forces addForce made (the name is not the original's)
};
}  // namespace forcefield

}  // namespace ptlib

#endif
