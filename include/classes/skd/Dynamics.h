#ifndef CLASSES_SKD_DYNAMICS_H
#define CLASSES_SKD_DYNAMICS_H

#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"
#include "skd/Packet.h"

namespace anm { class Pose; }
namespace anm { template <typename> class Array; }
namespace mm { class Quat; }
namespace mm { class Vec3; }
namespace skd { class CollisionObject; }
namespace skd { class DynamicsSolver; }
namespace skd { class ForceInterface; }
namespace skd { class ResSolver; }

namespace skd {
// table 0x7100B81668; counted (skd::Factory::createDynamics makes one; DynamicsUpdater::bind references it)
class Dynamics : public anm::ReferenceObject {
public:
    Dynamics(CollisionObject& colObj, const anm::Array<ResSolver>& solvers, anm::Pose& pose, ForceInterface* force,
             mm::mtl::IAllocator* allocator);
    virtual ~Dynamics();  // slot 0
    // a solver per resource solver, each initialized from the packet (skd_dynamics.cpp asserts there were none)
    void createSolver();
    void setSolverBlendWeight(unsigned int index, float weight);
    void update(float deltaTime);
    void resetDynamics();
    // the reference frame's new place and turn, and the movement since the last call (DynamicsUpdater::update)
    void notifyMovement(const mm::Vec3& position, const mm::Quat& rotation, const mm::Vec3& moveDelta,
                        const mm::Quat& rotateDelta);

    const anm::Array<ResSolver>* m_pResSolver;  // skd_dynamics.cpp asserts `m_pResSolver`
    mm::mtl::Vector<DynamicsSolver*> m_solvers;  // skd_dynamics.cpp asserts `m_solvers[i]`
    // the bind pose (DynamicsUpdater::update syncs it after update), the force and the level: GfComDynamics' setup
    // and applyAttribute set the level (the setup info's, 6, or 30). The name is not the original's.
    Packet m_packet;
    CollisionObject* m_pColObj;  // referenced; its shapes are what the solvers detect (the name is not the original's)
    // GfComDynamics::applyAttribute picks both by the object's animation attribute; notifyMovement limits the
    // movement it passes on to m_paramA's length and m_paramB's turn (the names are not the original's)
    float m_paramA;
    float m_paramB;
};
}  // namespace skd

#endif
