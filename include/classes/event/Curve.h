#ifndef CLASSES_EVENT_CURVE_H
#define CLASSES_EVENT_CURVE_H

#include "event/CvType.h"

namespace event {
// the eased value of a curve type at a time in [0, 1] (AnmBase::update passes its type and time / end); no table,
// only this static member is known
class Curve {
public:
    static float getValue(CV_TYPE type, float time);
};
}  // namespace event

#endif
