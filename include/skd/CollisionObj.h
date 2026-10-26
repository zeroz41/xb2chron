#ifndef SKD_COLLISIONOBJ_H
#define SKD_COLLISIONOBJ_H

namespace mm { class Vec3; }

namespace skd {
// a sphere collision resource; only the group addDetectSphereJob tests is known (the name is not the original's)
struct ResCollisionShpere {
    unsigned char pad_0[0x18];
    unsigned int m_group;
};

// a sphere of a collision object (the spelling is the original's)
class ShpereCollObj {
public:
    // whether a sphere of the radius at pos overlaps it, and the push out of it when it does
    bool detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const;

    const ResCollisionShpere* m_pRes;
};

// a capsule collision resource; only the group addDetectCapsuleJob tests is known (the name is not the original's)
struct ResCollisionCapsule {
    unsigned char pad_0[0x18];
    unsigned int m_group;
};

// a capsule of a collision object
class CapsuleCollObj {
public:
    // whether a sphere of the radius at pos overlaps it, and the push out of it when it does
    bool detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const;

    const ResCollisionCapsule* m_pRes;
};

// a plane collision resource; only the group addDetectPlaneJob tests is known (the name is not the original's)
struct ResCollisionPlane {
    unsigned char pad_0[0x18];
    unsigned int m_group;
};

// a plane of a collision object
class PlaneCollObj {
public:
    // whether a sphere of the radius at pos overlaps it, and the push out of it when it does
    bool detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const;

    const ResCollisionPlane* m_pRes;
};
}  // namespace skd

#endif
