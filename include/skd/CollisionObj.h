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
}  // namespace skd

#endif
