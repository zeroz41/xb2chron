#ifndef CLASSES_FW_TWOCHARAGROUNDSOLVER_H
#define CLASSES_FW_TWOCHARAGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/IKGroundInterface.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41D20; an IkSolver (its m_rtti's base): PlacementGroundSolver for two characters as one (a mount
// and its rider: the main's feet and root, the sub's feet and root), each root lowered to its own feet's ground
class TwoCharaGroundSolver : public ::fw::IkSolver {
public:
    // what create sets the solver up with (0x18 bytes: createImpl copies it whole; the names are not the original's)
    struct Description {
        Description() : maxDown(0.3f), footCount(4), mainRootBone(nullptr), subRootBone(nullptr) {}

        float maxDown;             // how far the main's root is lowered at most (mm::clamp's lower bound)
        unsigned int footCount;    // createImpl sizes both solver vectors to it
        const char* mainRootBone;  // createImpl finds the main's root bone by this name
        const char* subRootBone;   // and the sub's
    };

    // inline: 3.0.1 has no out-of-line copy (create holds its stores)
    TwoCharaGroundSolver()
        : m_syncDown(0), m_mainOffset(0.0f), m_subOffset(0.0f), m_mainRoot(0xFFFF), m_subRoot(0xFFFF),
          m_enablePlacement(false), m_enableDown(false), m_enableMain(true), m_enableSub(true), m_ground(nullptr) {}
    virtual ~TwoCharaGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    // null when either root bone is missing
    static TwoCharaGroundSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                        anm::Pose& pose, IKGroundInterface* ground);
    bool createImpl(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose,
                    IKGroundInterface* ground);
    // a foot placement solver for the main's (Sub: the sub's) foot `index`, kept in m_mainSolvers (m_subSolvers);
    // null past the foot count
    FootPlacementIKSolver* createFootPlacementIKMain(IKFootIndex index, ParamAdapter param, const char* bone0,
                                                     const char* bone1, const char* bone2, bool flag);
    FootPlacementIKSolver* createFootPlacementIKSub(IKFootIndex index, ParamAdapter param, const char* bone0,
                                                    const char* bone1, const char* bone2, bool flag);
    void setEnablePlacement(bool enable);
    // the roots lowered towards their feet's ground (solve's first step)
    void doPlacementRoot();
    // every foot solver solved (solve's second step)
    void doPlacementFoot(const UpdateInfo& info);
    static mm::mtl::RTTI m_rtti;

    // the names are not the original's
    mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> m_mainSolvers;  // one per main foot
    mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> m_subSolvers;   // one per sub foot
    Description m_desc;  // createImpl's
    int m_syncDown;  // 1 while FootIkControllerPlugin syncs down (attribute 0x2 or the "syncDownOn" ik event): the
                     // main's feet's placement is off and the main's root follows the sub's feet
    float m_mainOffset;  // the main's root's height offset doPlacementRoot last applied
    float m_subOffset;   // the sub's
    unsigned short m_mainRoot;  // createImpl's: the main's root bone
    unsigned short m_subRoot;   // the sub's
    bool m_enablePlacement;  // setEnablePlacement's
    bool m_enableDown;  // as PlacementGroundSolver's
    bool m_enableMain;  // the main's feet are placed and its root lowered (true unless set)
    bool m_enableSub;   // the sub's
    IKGroundInterface* m_ground;  // createImpl's
};
}  // namespace fw

#endif
