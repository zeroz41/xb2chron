#ifndef ANM_ANIMATIONOBJECT_H
#define ANM_ANIMATIONOBJECT_H

namespace anm {
// the base of anmlib's objects. Its destructor is trivial and inline: the slot-0 destructor of CubicAnimation's,
// EmptyAnimation's, UncompressAnimation's, FootPlacementIKSolver's and Skeleton's tables is this one (clang
// points a trivial inline destructor's slot at its base's), the copy the linker kept lying in
// anm_foot_placement_ik_solver.cpp's range
class AnimationObject {
public:
    virtual ~AnimationObject() {}
};
}  // namespace anm

#endif
