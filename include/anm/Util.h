#ifndef ANM_UTIL_H
#define ANM_UTIL_H

#include "mm/mtl/FixStr.h"

namespace anm { class Binding; }
namespace anm { class Control; }
namespace anm { class Pose; }
namespace anm { class QsTransform; }
namespace anm { struct ExtraTruckSlot; }
namespace anm { class ResASM; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { template <typename T> class Vector; } }

namespace anm {
// how a binding's animation plays (Util::getPlayMode; 1 plays once: AsmState::initLoopCount counts it as one loop and
// AsmClip::update ends it at its end. The names are not the original's)
enum PlayMode {
    PLAY_MODE_LOOP = 0,
    PLAY_MODE_ONCE = 1,
};

// x within lo..hi, the bounds taken by reference like mm::clamp but without its assertion: an animation's frame
// clamped to its length compiles to the original's selects only through this shape (UncompressExtraTruck::sampleTrucks).
// The name is not the original's
template <typename T>
inline T clamp(const T& x, const T& lo, const T& hi) {
    return x < lo ? lo : (x > hi ? hi : x);
}

// a random number in [0, 1) (anm_state_machine.cpp; AsmState::initLoopCount draws a loop count with it)
float rand();

// a named appendix of an animation state machine resource: its data follows its name (gf::GfComAsm::getAppendix
// hands out the data; the names are not the original's)
struct ResAppendix {
    const char* m_name;
    const void* m_data;
};

class Util {
public:
    // a part of a bone name whose bones are not mirrored (fw::AnimResAsmResolver::bindSkeleton makes them; the
    // names of the fields are not the original's)
    struct IgnoreName {
        mm::mtl::FixStr<8> m_name;  // a bone name's start is compared with its characters
        unsigned char pad_c[0x4];
    };

    // two name parts that tell a bone from its mirror counterpart (fw::AnimResAsmResolver::bindSkeleton makes them;
    // the names of the fields are not the original's)
    struct PairName {
        mm::mtl::FixStr<8> m_nameA;
        mm::mtl::FixStr<8> m_nameB;
    };

    // per bone, the bone whose name has each pair's parts swapped (itself when there is none), -1 for an ignored
    // bone or one that pairs with none
    static void computeBonePairFromName(const mm::mtl::Vector<PairName>& pairs, const Skeleton* pSkeleton,
                                        const mm::mtl::Vector<signed char>& ignores, mm::mtl::Vector<short>* pOut);
    // per bone, -1 where its name starts with one of names, else 0 (none without a skeleton)
    static void computeIgnoreMirrorFromName(const mm::mtl::Vector<IgnoreName>& names, const Skeleton* pSkeleton,
                                            mm::mtl::Vector<signed char>* pOut);
    // how long the binding's animation plays
    static float getPlayBackTime(const Binding& binding);
    static PlayMode getPlayMode(const Binding& binding);
    // time wrapped or clamped to start..end as the mode plays
    static float calcLocalTime(float time, float start, float end, PlayMode mode);
    // how the binding's animation blends (AsmBlender::getDeltaExtractMotion skips 1); the type is not the original's
    static char getBlendHint(const Binding& binding);
    // the extracted motion from time over dt, within start to end, in *pOut: false when there is none
    static bool calcDeltaExtractMotion(const Binding& binding, float time, float dt, float start, float end,
                                       QsTransform* pOut);
    // count values of the slot, each clamped to its limits
    // the control's animation sampled into the pose (fw::AnimSinglePoseSamper::samplePose passes its flag)
    static void samplePoseSmartFromControl(Control* control, Pose* pose, bool flag);
    static void clampLimitExtraTruck(const ExtraTruckSlot& slot, unsigned int count, float* pValues);
    // a state's clip's playback time, locomotion, binding and appendix (gf::GfComAsm's getters)
    static bool getAsmPlaybackTime(const ResASM& res, const char* state, unsigned int index, float* pTime);
    static bool getAsmLocomotionReference(const ResASM& res, const char* state, float time, unsigned int index,
                                          QsTransform* pOut);
    static bool getAsmLocomotionDeltaReference(const ResASM& res, const char* state, float time, float dt,
                                               unsigned int index, QsTransform* pOut);
    static const Binding* getAsmBinding(const ResASM& res, const char* state, unsigned int index);
    static float getInvFps(const Binding& binding);
    static const ResAppendix* findAppendix(const ResASM& res, const char* name);
    // a variable's minimum and maximum over a state's blend tree into *pMin/*pMax (true when found; the
    // parameter names are not the original's)
    static bool getVariableMinMax(const ResASM& res, const char* state, const char* variable, float* pMin,
                                  float* pMax);
};
}  // namespace anm

#endif
