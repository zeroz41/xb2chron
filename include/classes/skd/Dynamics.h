#ifndef CLASSES_SKD_DYNAMICS_H
#define CLASSES_SKD_DYNAMICS_H

#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"

namespace anm { class Pose; }
namespace mm { class Quat; }
namespace mm { class Vec3; }
namespace skd { class DynamicsSolver; }

namespace skd {
// table 0x7100B81668; counted (skd::Factory::createDynamics makes one; DynamicsUpdater::bind references it)
class Dynamics : public anm::ReferenceObject {
public:
    virtual ~Dynamics();  // slot 0
    void setSolverBlendWeight(unsigned int index, float weight);
    void update(float deltaTime);
    void resetDynamics();
    // the reference frame's new place and turn, and the movement since the last call (DynamicsUpdater::update)
    void notifyMovement(const mm::Vec3& position, const mm::Quat& rotation, const mm::Vec3& moveDelta,
                        const mm::Quat& rotateDelta);

    unsigned char pad_18[0x8];
    mm::mtl::Vector<DynamicsSolver*> m_solvers;  // update steps each one (the name is not the original's)
    anm::Pose* m_pPose;  // DynamicsUpdater::update syncs it after update (the name is not the original's)
    unsigned char pad_50[0x138];
    // GfComDynamics' setup and applyAttribute set these three (the names are not the original's): the setup
    // info's level (6, or 30), and two values applyAttribute picks by the object's animation attribute
    int m_level;
    unsigned char pad_18c[0xC];
    float m_paramA;
    float m_paramB;
};
}  // namespace skd

#endif
