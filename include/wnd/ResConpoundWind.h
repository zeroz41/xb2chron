#ifndef WND_RESCONPOUNDWIND_H
#define WND_RESCONPOUNDWIND_H

#include "math.h"

namespace wnd {
// a compound wind's resource: five waves, each blowing along its own direction (ConpoundWind::calcWind's).
// The names are not the original's.
class ResConpoundWind {
public:
    class Wave {
    public:
        // the strength at a time: between min and max on a sine of the period, shifted by the phase
        float getPower(float time) const {
            return (max - min) * (::sinf((time + phase) * 6.2831855f / period) + 1.0f) * 0.5f + min;
        }

        float max;
        float min;
        float period;
        float phase;
    };

    Wave waves[5];
};
}  // namespace wnd

#endif
