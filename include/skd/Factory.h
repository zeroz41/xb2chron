#ifndef SKD_FACTORY_H
#define SKD_FACTORY_H

namespace anm { class Pose; }
namespace anm { template <typename> class Array; }
namespace mm { namespace mtl { class IAllocator; }}
namespace skd { class CollisionObject; }
namespace skd { class Dynamics; }
namespace skd { class ForceInterface; }
namespace skd { class ResCollisionArray; }
namespace skd { class ResSolver; }

namespace skd {
// skdlib's maker of collision objects and dynamics, each counted and from the allocator given
class Factory {
public:
    static CollisionObject* createColObject(const ResCollisionArray* collisions, anm::Pose& pose,
                                            mm::mtl::IAllocator* allocator);
    static Dynamics* createDynamics(CollisionObject* colObj, const anm::Array<ResSolver>& solvers, anm::Pose& pose,
                                    ForceInterface* force, mm::mtl::IAllocator* allocator);
};
}  // namespace skd

#endif
