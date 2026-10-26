#ifndef SKD_CALCUTIL_H
#define SKD_CALCUTIL_H

namespace anm { class JobQueue; }
namespace anm { class Pose; }
namespace anm { class QsTransform; }
namespace anm { template <typename> class Array; }
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename> class Vector; }}
namespace skd { class CollionArray; }
namespace skd { class DetectInfoBuffer; }
namespace skd { class NodeArray; }
namespace skd { struct ResConeLimit; }
namespace skd { struct ResConstraint; }
namespace skd { struct ResHingeConstraint; }
namespace skd { struct ResNodeCollision; }
namespace skd { struct ResSpringConstraint; }
namespace skd { struct ResStickConstraint; }

namespace skd {
// skd_calc_util.cpp's steps of a solve, on a solver's nodes (DynamicsSolver::solve and solveMT run them)
class CalcUtil {
public:
    // whether the nodes could be set up from the pose
    static bool initNodes(anm::Pose& pose, NodeArray* nodes);
    static void cacheNode(anm::Pose& pose, NodeArray* nodes);
    static void addForceTransform(const NodeArray& nodes, mm::mtl::Vector<mm::Vec3>* forces);
    static void addForceSpring(const NodeArray& nodes, const anm::Array<ResSpringConstraint>& constraints,
                               mm::mtl::Vector<mm::Vec3>* forces);
    static void applyAccel(mm::mtl::Vector<mm::Vec3>& forces, NodeArray* nodes);
    static void integrate(float prevDeltaTime, float deltaTime, NodeArray* nodes);
    static void applyStickConstraints(const anm::Array<ResStickConstraint>& constraints, NodeArray* nodes);
    static void applySpringConstraints(const anm::Array<ResSpringConstraint>& constraints, NodeArray* nodes);
    static void applyHingeConstraints(const anm::Array<ResHingeConstraint>& constraints, NodeArray* nodes);
    static void detectCollision(const CollionArray& collisions, NodeArray* nodes);
    static void buildDetectCollisionJobs(const CollionArray& collisions, const NodeArray& nodes,
                                         DetectInfoBuffer* buffer, anm::JobQueue* queue);
    static void blendNode(float weight, NodeArray* nodes);
    static void applyPose(NodeArray& nodes, anm::Pose* pose);
    static void writeBackNode(anm::Pose& pose, NodeArray* nodes);
    static void convertCoordinateSystem(const anm::QsTransform& transform, NodeArray* nodes);
};

// skd_calc_util.cpp's single steps: a stick constraint's cone and a constraint's distance (applyStickConstraints),
// a hinge (applyHingeConstraints), and one collision pair against each shape of the collision array
// (detectCollision passes 0 as the third argument)
void limitCone(const ResConstraint& constraint, const ResConeLimit& cone, NodeArray* nodes);
void limitDistance(const ResConstraint& constraint, NodeArray* nodes);
void limitHinge(const ResHingeConstraint& constraint, NodeArray* nodes);
void detectCollisionSpheres(const ResNodeCollision& collision, const CollionArray& collisions, unsigned int index,
                            NodeArray* nodes);
void detectCollisionCapsules(const ResNodeCollision& collision, const CollionArray& collisions, unsigned int index,
                             NodeArray* nodes);
void detectCollisionPlanes(const ResNodeCollision& collision, const CollionArray& collisions, unsigned int index,
                           NodeArray* nodes);

// skd_calc_util.cpp's: the functions the queue runs each shape's detection jobs with, registered (skd::Packet's
// constructor). registerDetectSphereJobExecuter's address is split into skt/CommandManager.
void registerDetectCapsuleJobExecuter(anm::JobQueue* queue);
void registerDetectPlaneJobExecuter(anm::JobQueue* queue);
void registerDetectSphereJobExecuter(anm::JobQueue* queue);
}  // namespace skd

#endif
