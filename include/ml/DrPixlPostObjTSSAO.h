#ifndef ML_DRPIXLPOSTOBJTSSAO_H
#define ML_DRPIXLPOSTOBJTSSAO_H

#include "ml/DrPixlPostObj.h"

namespace ml {
// a post-process object. Only update is declared so far.
class DrPixlPostObjTSSAO : public DrPixlPostObj {
public:
    void update();
};
}  // namespace ml

#endif
