#ifndef ML_DRPIXLPOSTOBJUNBRANCHTODEPTH_H
#define ML_DRPIXLPOSTOBJUNBRANCHTODEPTH_H

#include "ml/DrPixlPostObj.h"

namespace ml {
// a post-process object: the constructor only builds the base. Fields beyond the base are not declared yet.
class DrPixlPostObjUnbranchToDepth : public DrPixlPostObj {
public:
    DrPixlPostObjUnbranchToDepth(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjUnbranchToDepth();

    void render();
    void renderFull();
    void renderQuater();
};
}  // namespace ml

#endif
