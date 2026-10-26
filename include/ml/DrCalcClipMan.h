#ifndef ML_DRCALCCLIPMAN_H
#define ML_DRCALCCLIPMAN_H

namespace ml {
class DrCalcClipObj;
// The clip test manager. Only what DrCalcMan::begin calls is declared so far.
class DrCalcClipMan {
public:
    void update();
    DrCalcClipObj* createClipObj(const void* resource);
};
}  // namespace ml

#endif
