#ifndef ANM_UTIL_H
#define ANM_UTIL_H

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { struct ExtraTruckSlot; }

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

class Util {
public:
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
    static void clampLimitExtraTruck(const ExtraTruckSlot& slot, unsigned int count, float* pValues);
};
}  // namespace anm

#endif
