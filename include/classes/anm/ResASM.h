#ifndef CLASSES_ANM_RESASM_H
#define CLASSES_ANM_RESASM_H

#include "anm/Array.h"
#include "anm/AsmListener.h"
#include "anm/Util.h"
#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/Vector.h"
#include "string.h"

namespace anm { class AsmAnnotetion; }
namespace anm { enum InterpolateType : int; enum InterpolateCurve : int; }
namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class ResResolver; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// a clip's settings (the names are not the original's)
struct ResClipInfo {
    const char* m_animationName;  // with m_animationIndex, ResResolver::importBinding's
    unsigned int m_animationIndex;
    unsigned int m_flags;  // bit 0: mirrored, bit 2: AsmBlender skips sampling while every clip has it, bit 3:
                           // retargeted (ResClipData::setup)
    float m_speed;         // AsmClip::setSpeed scales the speed by it
    float m_weight;        // AsmClip::setWeight scales the weight by it
    float m_start;  // less than 0: the animation's end (ResClipData::setup)
    float m_end;    // less than 0: the animation's end (ResClipData::setup)
};

// a state's loop count: at least m_min, up to m_range more at random (AsmState::initLoopCount; the names are not the
// original's)
// how a transition picks the new state's start frame (StateMachine::doTrans; the names of the fields are not the
// original's)
struct TransInfo {
    int m_type;  // 0: m_frame on from the caller's frame, 1: the old state's time, 2: random in m_frame + m_range, 3:
                 // the old state's time less the caller's time
    float m_frame;
    float m_range;
};

// how a transition blends the old state out (StateMachine::doTrans keeps it while it blends; the names of the
// fields are not the original's, the order follows AdditiveInfo's)
struct InterpolateInfo {
    float m_time;  // none (epsilon or less): the old state goes at once
    InterpolateCurve m_curve;
    InterpolateType m_type;  // 1: StateMachine::updateFrame keeps updating the old state
};

struct ResLoopCount {
    const char* m_pNextState;  // StateMachine::updateFrame moves to it when the loops are done (the name is not the
                               // original's)
    int m_min;
    unsigned int m_range;
    TransInfo m_trans;
    InterpolateInfo m_interpolate;
};

// a state's settings (the names are not the original's)
// a blend tree resource: its type picks the tree (StateMachine::createState: 0 LerpBlendTree, 2 SpeedLerpBlendTree,
// 3 AddBlendTree, 4 LerpAddBlendTree; the names are not the original's)
struct ResBlendTree {
    int m_type;
};

struct ResState {
    int m_type;  // StateMachine::createState: 0 SimplexState, 1 FrozenState, 2 m_pTree's blend tree
    unsigned char pad_4[0x4];
    const char* m_name;  // StateMachine::getStateName's
    unsigned long m_attribute;  // StateMachine::getAttribute's category 0 (the name is not the original's)
    unsigned int m_layer;  // the StateMachine (ASMControl layer) that plays it (the name is not the original's)
    unsigned char pad_1c[0x14];
    const ResLoopCount* m_pLoopCount;  // none: one loop for a clip that plays once, else none
    unsigned char pad_38[0x30];
    const ResBlendTree* m_pTree;  // type 2's (the name is not the original's)
};

// one clip of a state: 0xE8 bytes (the fields' names are not the original's)
struct ResClipData {
    ResClipData();
    // the clip's binding (retargeted and mirrored as the info asks, else the skeleton's reference pose), its part
    // of the animation and the animation's events as kind 0's frame annotations
    void setup(const ResClipInfo& info, const ResResolver& resolver, mm::mtl::IAllocator& allocator);
    // (anm_res_clip_data.cpp, out of line)
    void cleanup();
    // the kind's frame annotations sorted by frame
    void sortAnnotation(unsigned int kind);
    // the locomotion's reference at time within the clip's part (Util::getAsmLocomotionReference's; anm_res_clip_data.cpp)
    bool getReference(float time, QsTransform* pOut) const;
    // the locomotion's motion from time over dt within the clip's part (Util::getAsmLocomotionDeltaReference's)
    bool getDeltaReference(float time, float dt, QsTransform* pOut) const;
    // a frame annotation of the kind at the frame (none without a binding); sortAnnotation sorts them later
    void setFrameAnnotation(unsigned int kind, float frame, const AsmAnnotetion& annotation);

    const ResClipInfo* m_pInfo;
    const Binding* m_pBinding;  // Factory::createASMResource checks its bone count against the skeleton's
    float m_start;  // the part of the animation it plays (AsmBlender::getDeltaExtractMotion)
    float m_end;    // the part's length past m_start (setup)
    mm::mtl::FixedArray<mm::mtl::Vector<AsmKeyframeAnnotation>, 5> m_frameAnnotations;  // per kind (AsmClip::update)
    // set by ResStateData::setFrameAnnotation: ResStateData::sortAnnotation sorts only a clip that has it (the name
    // is not the original's)
    bool m_unsorted;  // (0xE1..0xE7: tail padding, which Vector<ResClipData>::extend does not copy)
};

// orders frame annotations by frame (ResClipData::sortAnnotation's std::sort comparator)
bool lessAsmKeyframeAnnotation(const AsmKeyframeAnnotation& lhs, const AsmKeyframeAnnotation& rhs);

// one point of a lerp blend tree: from its position on the variable's value blends its clip towards the next one's
// (0x28 bytes; the names are not the original's)
struct ResLerpNode {
    float m_position;
    unsigned char pad_4[0x24];
};

// a lerp blend tree's resource: the variable it follows and its points, one per clip (the names are not the original's)
struct ResLerpTree : ResBlendTree {
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
struct ResAddTree : ResBlendTree {
    unsigned char pad_4[0xC];
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
struct ResSpeedLerpTree : ResBlendTree {
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

// one point of a lerp add blend tree: the added clip it weights (0x28 bytes; the names are not the original's)
struct ResLerpAddNode {
    float m_position;
    unsigned char pad_4[0x24];
};

// a lerp add blend tree's resource: the variable it follows, its base clips first, then one added clip per point
// (the names are not the original's)
struct ResLerpAddTree : ResBlendTree {
    unsigned int m_variableIndex;  // in the state machine's variables
    unsigned char pad_8[0x8];
    unsigned int m_baseCount;
    unsigned char pad_14[0x4];
    Array<ResLerpAddNode> m_nodes;
};

// orders a lerp add blend tree's points against a variable's value by their positions (std::lower_bound's
// comparator in LerpAddBlendTree::adjustWeight)
struct CompLerpAddNode {
    bool operator()(const ResLerpAddNode& node, float value) const {
        return node.m_position < value;
    }
};

struct ResVariable;

// an animation state machine's states and variables as loaded (ResASM's constructor counts the states; the names
// are not the original's)
class ResStateArray {
public:
    unsigned char pad_0[0x8];
    // per pack, its name: fw::AnimResAsmResolver::resolvePackFiles finds each archive's (CArcData::getStr) here
    // (the name is not the original's)
    Array<const char*> m_packNames;
    Array<ResState*> m_states;  // sorted by name (Util::getVariableMinMax finds a state with CompResState)
    Array<ResVariable> m_variables;  // ASMControl makes a Variable of each
    unsigned char pad_38[0x18];
    Array<ResAppendix> m_appendices;  // sorted by name (Util::findAppendix finds one with lessAppendix)
};

// one state of an animation state machine: 0x1E0 bytes
struct ResStateData {
    ResStateData();
    // (anm_res_state_data.cpp)
    void setup(const ResState& info, const ResResolver& resolver, mm::mtl::IAllocator& allocator);
    // a frame annotation of the kind at the frame for the clip
    void setFrameAnnotation(unsigned int kind, unsigned int clip, float frame, const AsmAnnotetion& annotation);
    // every clip's frame annotations of the kind sorted by frame, for the clips given new ones
    void sortAnnotation(unsigned int kind);
    // the clips and the annotations given up
    void cleanup();

    const ResState* m_pInfo;
    mm::mtl::Vector<ResClipData> m_clips;
    unsigned long m_attributes[4];  // StateMachine::getAttribute's categories 1 to 4 (the name is not the original's)
    mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> m_enterAnnotations;  // per kind (AsmState::notifyEnter)
    mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> m_leaveAnnotations;  // per kind (AsmState::notifyLeave)
};

// orders an animation state machine resource's states against a name (std::lower_bound's comparator in ResASM's
// state lookups; the name is the original's)
struct Comp {
    bool operator()(const ResStateData& data, const char* name) const { return strcmp(data.m_pInfo->m_name, name) < 0; }
};

// table 0x7100B81198; an animation state machine's resource: its states and the skeleton their clips are bound to
class ResASM : public ::anm::ReferenceObject {
public:
    ResASM(const ResStateArray& states, const ResResolver& resolver, mm::mtl::IAllocator& allocator);
    virtual ~ResASM();  // slot 0

    // false without a state of the name
    bool setEnterAnnotation(unsigned int kind, const char* stateName, const AsmAnnotetion& annotation);
    bool setLeaveAnnotation(unsigned int kind, const char* stateName, const AsmAnnotetion& annotation);
    bool setFrameAnnotation(unsigned int kind, const char* stateName, float frame, const AsmAnnotetion& annotation);
    void sortAnnotation(unsigned int kind);
    // the state of the name, none without one
    const ResStateData* findResStateData(const char* name) const;

    const Skeleton* m_pSkeleton;  // the names of the fields are not the original's
    const ResStateArray* m_pStates;  // the constructor's
    Array<ResStateData> m_states;
    ResStateData* m_pStateBuffer;  // the allocator's memory m_states lies in (the name is not the original's)
    // Factory::createASMResource allocates 0x40 bytes
};
}  // namespace anm

#endif
