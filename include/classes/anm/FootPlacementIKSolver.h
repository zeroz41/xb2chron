#ifndef CLASSES_ANM_FOOTPLACEMENTIKSOLVER_H
#define CLASSES_ANM_FOOTPLACEMENTIKSOLVER_H

#include "anm/AnimationObject.h"
#include "anm/QsTransform.h"
#include "mm/Vec3.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
class Pose;
class RaycastInterface;
class Skeleton;

// table 0x7100B81098 (its slot 0 is AnimationObject's destructor); places a foot of three bones on the ground a
// RaycastInterface finds. fw::FootPlacementIKSolver makes it with create and releases it (AnimationObject's release)
class FootPlacementIKSolver : public AnimationObject {
public:
    // what create takes (0x80 bytes; fw::FootPlacementIKSolver::createImpl fills it; the field names are not the
    // original's, the default values are its constructor's)
    struct Description {
        Description()
            : boneIndex0(0xFFFF), boneIndex1(0xFFFF), boneIndex2(0xFFFF), up(mm::Vec3::unitY), up2(mm::Vec3::unitY),
              forward(mm::Vec3::zero), cosAngle0(-1.0f), cosAngle1(0.8f), height0(0.0f), height1(0.0f),
              pad_50(0.7f), groundHeight(-0.1f), pad_58(0.3f), toeOffset(mm::Vec3::zero), pad_70(false) {}

        const Skeleton* skeleton;
        unsigned short boneIndex0;  // the three bones fw::FootPlacementIKSolver::createImpl finds by name
        unsigned short boneIndex1;
        unsigned short boneIndex2;
        mm::Vec3 up;
        mm::Vec3 up2;
        mm::Vec3 forward;  // the unit x of the second bone's space in model space (negated by the description's flag)
        float cosAngle0;   // cosines of the description's first two angles (degrees)
        float cosAngle1;
        float height0;     // groundHeight plus the parameter block's third value
        float height1;     // groundHeight plus the parameter block's second value
        float pad_50;      // the parameter block's first value
        float groundHeight;  // the foot bone's model-space height less 0.05
        float pad_58;
        mm::Vec3 toeOffset;  // the description's third value along model z, in the foot bone's space
        bool pad_70;
    };

    // what doFootPlacement takes (the field names are not the original's; the defaults are its constructor's)
    struct Input {
        Input()
            : pad_60(0), up(mm::Vec3::unitY), enable(true), raycaster(nullptr), raycastUp(0.0f),
              raycastDown(0.0f), pad_98(0.2f), pad_9c(1.0f), pad_a0(1.0f), pad_a4(1.0f), pad_a8(1.0f), pad_ac(1.0f) {}

        QsTransform foot;   // the foot bone's model-space transform
        QsTransform frame;  // the reference frame's world transform
        unsigned int pad_60;
        mm::Vec3 up;
        bool enable;
        RaycastInterface* raycaster;
        float raycastUp;
        float raycastDown;
        float pad_98;
        float pad_9c;
        float pad_a0;
        float pad_a4;
        float pad_a8;
        float pad_ac;
    };

    // what doFootPlacement gives (the field names are not the original's)
    struct Output {
        Output() : position(mm::Vec3::zero), normal(mm::Vec3::unitY), pad_20(0), hit(false) {}

        mm::Vec3 position;
        mm::Vec3 normal;
        int pad_20;
        bool hit;
    };

    FootPlacementIKSolver(const Description& desc, mm::mtl::IAllocator& allocator);  // 0x7100869F44
    virtual ~FootPlacementIKSolver();  // slot 0
    static FootPlacementIKSolver* create(const Description& desc, mm::mtl::IAllocator& allocator);
    void doFootPlacement(const Input& input, Output* output, Pose* pose);

    unsigned char pad_18[0x14];
    unsigned short m_footBone;  // fw::FootPlacementIKSolver::solveImpl reads the foot bone's transform by it
    unsigned char pad_2e[0x42];
    float m_raycastUp;    // solveImpl's default raycastUp is it less the foot's height
    float m_raycastDown;  // solveImpl's default raycastDown is the foot's height less it, plus 0.1
    unsigned char pad_78[0x28];
    float m_weight;  // solveImpl sets fw's flag 4 while it is at least 1
    unsigned char pad_a4[0x5C];  // 0x100 bytes: create allocates that many (the constructor stores up to 0xF8)
};
}  // namespace anm

#endif
