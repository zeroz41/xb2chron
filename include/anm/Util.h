#ifndef ANM_UTIL_H
#define ANM_UTIL_H

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { struct ExtraTruckSlot; }

namespace anm {
class Util {
public:
    // how long the binding's animation plays
    static float getPlayBackTime(const Binding& binding);
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
