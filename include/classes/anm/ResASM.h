#ifndef CLASSES_ANM_RESASM_H
#define CLASSES_ANM_RESASM_H

#include "anm/Array.h"
#include "anm/AsmListener.h"
#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"

namespace anm { class AsmAnnotetion; }
namespace anm { class Binding; }
namespace anm { class ResResolver; }
namespace anm { class ResStateArray; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// a clip's settings (the names are not the original's)
struct ResClipInfo {
    unsigned char pad_0[0xC];
    unsigned int m_flags;  // bit 2: AsmBlender skips sampling while every clip has it
    float m_speed;         // AsmClip::setSpeed scales the speed by it
    float m_weight;        // AsmClip::setWeight scales the weight by it
};

// a state's loop count: at least m_min, up to m_range more at random (AsmState::initLoopCount; the names are not the
// original's)
struct ResLoopCount {
    unsigned char pad_0[0x8];
    int m_min;
    unsigned int m_range;
};

// a state's settings (the names are not the original's)
struct ResStateInfo {
    unsigned char pad_0[0x30];
    const ResLoopCount* m_pLoopCount;  // none: one loop for a clip that plays once, else none
};

// one clip of a state: 0xE8 bytes (the fields' names are not the original's)
struct ResClipData {
    const ResClipInfo* m_pInfo;
    const Binding* m_pBinding;  // Factory::createASMResource checks its bone count against the skeleton's
    float m_start;  // the part of the animation it plays (AsmBlender::getDeltaExtractMotion)
    float m_end;
    mm::mtl::Vector<AsmKeyframeAnnotation> m_frameAnnotations[5];  // per kind (AsmClip::update)
    unsigned char pad_e0[0x8];
};

// one point of a lerp blend tree: from its position on the variable's value blends its clip towards the next one's
// (0x28 bytes; the names are not the original's)
struct ResLerpNode {
    float m_position;
    unsigned char pad_4[0x24];
};

// a lerp blend tree's resource: the variable it follows and its points, one per clip (the names are not the original's)
struct ResLerpTree {
    unsigned char pad_0[0x4];
    unsigned int m_variableIndex;  // in the state machine's variables
    Array<ResLerpNode> m_nodes;
};

// an added clip of an add blend tree: the variable that weights it (0x28 bytes; the names are not the original's)
struct ResAddNode {
    unsigned int m_variableIndex;  // in the state machine's variables
    unsigned char pad_4[0x24];
};

// an add blend tree's resource: its base clips first, then one added clip per node (the names are not the
// original's)
struct ResAddTree {
    unsigned char pad_0[0x10];
    unsigned int m_baseCount;
    unsigned char pad_14[0x4];
    Array<ResAddNode> m_nodes;
};

// one point of a speed lerp blend tree, as ResLerpNode (the names are not the original's)
struct ResSpeedLerpNode {
    float m_position;
    unsigned char pad_4[0x24];
};

// a speed lerp blend tree's resource, as ResLerpTree (the names are not the original's)
struct ResSpeedLerpTree {
    unsigned char pad_0[0x4];
    unsigned int m_variableIndex;
    Array<ResSpeedLerpNode> m_nodes;
};

// orders a variable's value against a (speed) lerp blend tree's points by their positions (std::upper_bound's
// comparator in LerpBlendTree::adjustWeight and SpeedLerpBlendTree::adjustSpeesAndWeight)
struct CompLerpNode {
    template <typename T>
    bool operator()(float value, const T& node) const {
        return value < node.m_position;
    }
};

// one state of an animation state machine: 0x1E0 bytes
struct ResStateData {
    const ResStateInfo* m_pInfo;
    mm::mtl::Vector<ResClipData> m_clips;
    unsigned char pad_30[0x20];
    mm::mtl::Vector<AsmAnnotetion> m_enterAnnotations[5];  // per kind (AsmState::notifyEnter)
    mm::mtl::Vector<AsmAnnotetion> m_leaveAnnotations[5];  // per kind (AsmState::notifyLeave)
};

// table 0x7100B81198; an animation state machine's resource: its states and the skeleton their clips are bound to
class ResASM : public ::anm::ReferenceObject {
public:
    ResASM(const ResStateArray& states, const ResResolver& resolver, mm::mtl::IAllocator& allocator);
    virtual ~ResASM();  // slot 0

    void setEnterAnnotation(unsigned int kind, const char* stateName, const AsmAnnotetion& annotation);
    void setLeaveAnnotation(unsigned int kind, const char* stateName, const AsmAnnotetion& annotation);
    void setFrameAnnotation(unsigned int kind, const char* stateName, float frame, const AsmAnnotetion& annotation);
    void sortAnnotation(unsigned int kind);

    const Skeleton* m_pSkeleton;  // the names of the fields are not the original's
    unsigned char pad_20[0x8];
    Array<ResStateData> m_states;
    unsigned char pad_38[0x8];  // Factory::createASMResource allocates 0x40 bytes
};
}  // namespace anm

#endif
