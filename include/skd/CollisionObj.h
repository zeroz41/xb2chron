#ifndef SKD_COLLISIONOBJ_H
#define SKD_COLLISIONOBJ_H

#include "anm/Array.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"
#include "mm/mtl/Vector.h"

namespace anm { class Pose; }
namespace mm { namespace mtl { class IAllocator; }}

namespace skd {
// what every collision resource starts with (the names are not the original's): the bone it follows, by name
// (CollionArray's constructor finds it in the pose's skeleton), and its place and turn in that bone's space
struct ResCollision {
    unsigned char pad_0[0x10];
    const char* m_boneName;
    unsigned int m_group;  // only the group addDetectSphereJob tests is known
    unsigned char pad_1c[0x4];
    mm::Vec3 m_offset;
    mm::Quat m_rotation;
};

// a sphere collision resource (the spelling is the original's; the field names are not)
struct ResCollisionShpere : public ResCollision {
    float m_radius;
};

// a capsule collision resource: a segment of m_length along its turned Y axis, centred on its offset (the names
// are not the original's)
struct ResCollisionCapsule : public ResCollision {
    float m_radius;
    float m_length;
};

// a plane collision resource: the plane through its offset with its turned Y axis as the normal
struct ResCollisionPlane : public ResCollision {};

// a collision object's resources, in its binary (the names are not the original's)
class ResCollisionArray {
public:
    anm::Array<ResCollisionShpere> m_spheres;
    anm::Array<ResCollisionCapsule> m_capsules;
    anm::Array<ResCollisionPlane> m_planes;
};

// a sphere of a collision object (the spelling is the original's)
class ShpereCollObj {
public:
    // whether a sphere of the radius at pos overlaps it, and the push out of it when it does
    bool detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const;
    // its centre from its bone's place in the pose (inline: CollionArray::update inlines it)
    void calc(anm::Pose& pose);

    // the names below are not the original's
    const ResCollisionShpere* m_pRes;
    mm::Vec3 m_pos;        // the centre, in model space
    unsigned short m_bone;  // the bone of the pose it follows, 0xFFFF when the skeleton has none of its name
};

// a capsule of a collision object
class CapsuleCollObj {
public:
    bool detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const;
    void calc(anm::Pose& pose);

    // the names below are not the original's
    const ResCollisionCapsule* m_pRes;
    mm::Vec3 m_pos;  // the segment's start, in model space
    mm::Vec3 m_dir;  // the segment's direction (length 1)
    unsigned short m_bone;
};

// a plane of a collision object
class PlaneCollObj {
public:
    bool detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const;
    void calc(anm::Pose& pose);

    // the names below are not the original's
    const ResCollisionPlane* m_pRes;
    mm::Vec4 m_plane;  // the normal and the distance term: dot(normal, p) + w is p's height above it
    mm::Vec3 m_pos;    // its point, in model space
    mm::Quat m_rotation;
    unsigned short m_bone;
};

// a collision object's spheres, capsules and planes (the spelling is the original's)
class CollionArray {
public:
    CollionArray(mm::mtl::IAllocator* allocator, const ResCollisionArray& res, const anm::Pose& pose);
    // every shape to its bone's place in the pose
    void update(anm::Pose& pose);

    // the names below are not the original's
    const ResCollisionArray* m_pRes;
    mm::mtl::Vector<ShpereCollObj> m_spheres;
    mm::mtl::Vector<CapsuleCollObj> m_capsules;
    mm::mtl::Vector<PlaneCollObj> m_planes;
    bool m_valid;  // every shape's bone was found: update does nothing otherwise
};

}  // namespace skd

#endif
